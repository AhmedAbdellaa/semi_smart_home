#include <util/delay.h>
#include "../../libraries/STD_TYPES_H.h"
#include "../../libraries/BIT_MATH.h"
#include "../../libraries/ErrType.h"
#include "../../0-MCAL/1-DIO/DIO_interface.h"
#include "../../0-MCAL/6-TIMER/TIMER_interface.h"
#include "SR04_interface.h"

static uint16 Global_u16RisingEdge, Global_u16FallingEdge, Global_u16OVCounts = 0;
static uint8 Local_u8Counter = 0;
static void ICU_ICR(void)
{
	//	static uint8 Local_u8Counter = 0;

	if (Local_u8Counter == 0)
	{
		Global_u16OVCounts = 0;
		ICU_voidSetTriggerSrc(ICU_FALLING_EDGE);
		Local_u8Counter = 1;
		Global_u16RisingEdge = ICU_u16GetICRVal();
	}
	else if (Local_u8Counter == 1)
	{
		Local_u8Counter = 2;
		ICU_voidIntDisable();
		TIMER_voidDisable_OV_Interrupt(TIMER1);
		Global_u16FallingEdge = ICU_u16GetICRVal();
	}
	else
	{
	}
}
static void timer1_ovISR()
{
	Global_u16OVCounts++;
}
uint32 SR04_u32ReadTime(SR04_TriggerPin* ref_trigger)
{
	sint32 Local_s32TotalTime;
	static TIMER_CALLBACK_CONFIG_t Local_Timer1 = {0x0000, 1u};
	ICU_voidSetTriggerSrc(ICU_RISING_EDGE);
	TIMER_u8Start_OV_Interrupt(TIMER1, &Local_Timer1, &timer1_ovISR);
	ICU_u8IntEnable(&ICU_ICR);
	// send signal for 10 ms on trigger pin
	DIO_u8_SetPinVal(ref_trigger->trigPort, ref_trigger->trigPin, DIO_PIN_HIGH);
	_delay_us(10);
	DIO_u8_SetPinVal(ref_trigger->trigPort, ref_trigger->trigPin, DIO_PIN_LOW);
	// print time result
	while (Local_u8Counter != 2)
	{
	}

	Local_s32TotalTime = ((Global_u16FallingEdge - Global_u16RisingEdge) + Global_u16OVCounts * 32768ul) * TICK_TIME;
	Local_u8Counter = 0;
	return Local_s32TotalTime;
}
uint16 SR04_u16GetDistance(sint32 copy_s32Time)
{
	return (uint16)((0.034*(f64)copy_s32Time)/2.0);
}
