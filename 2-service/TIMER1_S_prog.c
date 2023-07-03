
#include "../libraries/BIT_MATH.h"
#include "../libraries/ErrType.h"
#include "../libraries/STD_TYPES_H.h"
#include "../0-MCAL/6-TIMER/TIMER_interface.h"
#include "../0-MCAL/1-DIO/DIO_interface.h"
#include "TIMER1_S_interface.h"

static uint16 Global_u16Raising1 = 0, Global_u16Raising2 = 0, Global_u16Falling = 0;
static uint8 Global_u8FlagCount = 0;

static uint16 Global_s16Periodic = 1;
static void (*TIMER_PFunctionPtr_schedule)(void) = NULL;
static uint8 TIMER1_u8BusyFlag = IDLE;
TIMER_TINum_t Global_timerAorB ;

void icuIsr()
{

    // raising 1
    if (Global_u8FlagCount == 0)
    {
        // get first reading
        Global_u16Raising1 = ICU_u16GetICRVal();
        Global_u8FlagCount++;

    } // raising 2
    else if (Global_u8FlagCount == 1)
    {
        // get second reading "end of period"
        Global_u16Raising2 = ICU_u16GetICRVal();
        ICU_voidSetTriggerSrc(ICU_FALLING_EDGE);

        Global_u8FlagCount++;
    }
    // down2
    else if (Global_u8FlagCount == 2)
    {
        // get third reading "next falling"
        ICU_voidIntDisable();
        Global_u16Falling = ICU_u16GetICRVal();
        Global_u8FlagCount++;
    }
    else
    {
        /**/
    }
}
void __T1S_scheduleHelper(void)
{DIO_u8_TogglePinVal(DIO_PORTC,DIO_PIN0);
    static uint16 Local_u16PeriodCounter = 1;
    if (TIMER_PFunctionPtr_schedule != NULL)
    {
        if (Global_s16Periodic == -1)
        {
            TIMER_PFunctionPtr_schedule();
        }
        else if (Global_s16Periodic == Local_u16PeriodCounter)
        {
            Local_u16PeriodCounter = 1;
            // disable Interrupt
            TIMER_voidDisable_COM_Interrupt(TIMER1A);
            TIMER1_u8BusyFlag = IDLE;
        }
        else
        {
        	TIMER_voidSetTCNT(Global_timerAorB,0u);
            TIMER_PFunctionPtr_schedule();
            Local_u16PeriodCounter++;
        }
    }
    else
    {
        /**/
    }
}
uint8 T1S_voidPWM_Measure(uint16 *reference_u16DutyCycle, uint16 *reference_u16PeriodTime)
{
    uint8 Local_u8ErrorState = OK;

    if ((reference_u16DutyCycle != NULL) && (reference_u16PeriodTime != NULL))
    {
        if (TIMER1_u8BusyFlag == IDLE)
        {
            TIMER1_u8BusyFlag = BUSY;
            TIMER_voidChangCOM_Mode(TIMER1, TIMER_COM_NORMAL);
            TIMER_voidChangWGM_Mode(TIMER1, TIMER_WGM_Normal);
            ICU_voidSetTriggerSrc(ICU_RISING_EDGE);
            ICU_u8IntEnable(&icuIsr);

            // pooling until isr finish to return ther result
            while (Global_u8FlagCount != 3)
                ;
            // return result
            *reference_u16PeriodTime = Global_u16Raising2 - Global_u16Raising1;
            *reference_u16DutyCycle = Global_u16Falling - Global_u16Raising2;
            // reset flags
            Global_u8FlagCount = 0;
            Global_u16Raising1 = 0;
            Global_u16Raising2 = 0;
            Global_u16Falling = 0;
            TIMER1_u8BusyFlag = IDLE;
        }
        else
        {
            Local_u8ErrorState = BUSY_ERR;
        }
    }
    else
    {
        Local_u8ErrorState = NULL_PTR;
    }
    return Local_u8ErrorState;
}
// prescaler :1024 , min time :(1024/16):64us  max time: 64us * 2^16 ->4194304 us
uint8 T1S_voidScheduleMS(TIMER_TINum_t copy_TINum,uint32 copy_u32Time_ms, sint16 copy_s16Periodic, void (*copy_pvFuncPtr)(void))
{
    uint8 Local_u8ErrorState = OK;
    if (TIMER1_u8BusyFlag == IDLE)
    {
        TIMER1_u8BusyFlag = BUSY;
        Global_timerAorB = copy_TINum;
        // initialize with static because we will need there address
        static uint16 Local_u16CompareVal = 0;
        static TIMER_CALLBACK_CONFIG_t Local_TIMER_Config;

        Global_s16Periodic = copy_s16Periodic;
        if (copy_pvFuncPtr != NULL)
        {
            // check if input time is allowed
            if ((copy_u32Time_ms > T1S_TICK_TIME) && (copy_u32Time_ms < Max_time))
            {
                // get compare match value
                Local_u16CompareVal = copy_u32Time_ms / T1S_TICK_TIME;
                // reset timer to ctc wgm , and normal com
//                TIMER_voidChangCOM_Mode(TIMER1, TIMER_COM_NORMAL);
//                TIMER_voidChangWGM_Mode(TIMER1, TIMER_WGM_PWM_FAST_ICR1);
//                TIMER_voidStart_PWM(TIMER1A, Local_u16CompareVal, Local_u16CompareVal);
                //
                Local_TIMER_Config.TIMER_u16OCR_TCNT_initVal = Local_u16CompareVal;
                Local_TIMER_Config.TIMER_U32ISRDoNum_ICR1 = 1;
                TIMER_PFunctionPtr_schedule = copy_pvFuncPtr;
                TIMER_u8Start_COM_Interrupt(copy_TINum, &Local_TIMER_Config,&__T1S_scheduleHelper);
            }
            else
            {
                Local_u8ErrorState = NOK;
            }
        }
        else
        {
            Local_u8ErrorState = NULL_PTR;
        }
    }
    else
    {
        Local_u8ErrorState = BUSY_ERR;
    }
    return Local_u8ErrorState;
}
// prescaler :1024 , min duty :(1024/16):64us  max duty  freq: 64us * 2^16 ->4194304 us
uint8 T1S_voidStartPwm(TIMER_TINum_t copy_TINum, uint32 copy_u32CycleTime, f64 copy_u8Duty)
{
    uint8 Local_u8ErrorState = OK;
    if (TIMER1_u8BusyFlag == IDLE)
    {
        TIMER1_u8BusyFlag = BUSY;
        uint16 Local_u16ICR1Val = 0;
        uint16 Local_u16DutyValue = 0;

        // get ICR1 match value
        Local_u16ICR1Val = (f64)copy_u32CycleTime / T1S_TICK_TIME;
        Local_u16DutyValue = (f64)Local_u16ICR1Val * (copy_u8Duty / 100.0);

        // check if input time is allowed
        if (((f64)copy_u32CycleTime > T1S_TICK_TIME) && (copy_u32CycleTime < Max_time) && ((copy_u8Duty >= 0) && (copy_u8Duty <= 100)))
        {
            TIMER_voidStart_PWM(copy_TINum, Local_u16DutyValue, Local_u16ICR1Val);
        }
        else
        {
            Local_u8ErrorState = NOK;
        }
    }
    else
    {
        Local_u8ErrorState = BUSY_ERR;
    }
    return Local_u8ErrorState;
}
void T1S_voidStopPwm()
{

    TIMER1_u8BusyFlag = IDLE;
}
