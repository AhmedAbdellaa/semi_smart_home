#include <util/delay.h>
#include "../../libraries/STD_TYPES_H.h"
#include "../../libraries/BIT_MATH.h"
#include "../../libraries/ErrType.h"
#include "../../0-MCAL/1-DIO/DIO_interface.h"
#include "CLCD_cfg.h"
#include "CLCD_interface.h"
#include "CLCD_prv.h"

#if CLCD_u8CONNECTION_MODE == FOUR_BIT
static void voidSetHalfDataPort(uint8 copy_u8FourBitData)
{
    DIO_u8_SetPinVal(CLCD_u8DATA_PORT, CLCD_u8D4_PIN, GET_BIT(copy_u8FourBitData, 0));
    DIO_u8_SetPinVal(CLCD_u8DATA_PORT, CLCD_u8D5_PIN, GET_BIT(copy_u8FourBitData, 1));
    DIO_u8_SetPinVal(CLCD_u8DATA_PORT, CLCD_u8D6_PIN, GET_BIT(copy_u8FourBitData, 2));
    DIO_u8_SetPinVal(CLCD_u8DATA_PORT, CLCD_u8D7_PIN, GET_BIT(copy_u8FourBitData, 3));
}
#endif
static void voidSendEnablePulse()
{
    DIO_u8_SetPinVal(CLCD_u8CTRL_PORT, CLCD_u8E_PIN, DIO_PIN_HIGH);
    _delay_ms(2);
    DIO_u8_SetPinVal(CLCD_u8CTRL_PORT, CLCD_u8E_PIN, DIO_PIN_LOW);
}

static void _helper_VoidReverseBuffer(uint8 *ref_u8Buffer, uint8 copy_u8StartIndex, uint8 copy_u8EndIndex)
{
    uint8 Local_u8LCounter = copy_u8EndIndex;

    uint8 Local_u8Tmp;
    uint8 Local_u8Mid = (copy_u8EndIndex / 2), Local_u8IncPart = copy_u8EndIndex;
    if (copy_u8StartIndex)
        Local_u8IncPart = copy_u8EndIndex + 1;
    while (Local_u8LCounter > Local_u8Mid)
    {
        Local_u8Tmp = ref_u8Buffer[Local_u8LCounter];
        ref_u8Buffer[Local_u8LCounter] = ref_u8Buffer[Local_u8IncPart - Local_u8LCounter];
        ref_u8Buffer[Local_u8IncPart - Local_u8LCounter] = Local_u8Tmp;
        Local_u8LCounter--;
    }
}
static void _helper_VoidNumToStr(sint32 copy_s32number, uint8 *ref_u8Buffer)
{

    if (copy_s32number == 0)
    {
        ref_u8Buffer[0] = '0';
        ref_u8Buffer[1] = '\0';
        return;
    }

    uint8 Local_u8counter = 0;
    uint8 Local_u8MFlag = 0;

    if (copy_s32number < 0)
    {
        ref_u8Buffer[Local_u8counter] = '-';
        Local_u8counter++;
        copy_s32number *= -1;
        Local_u8MFlag = 1;
    }
    while (copy_s32number)
    {
        // printf("%d ",copy_s32number);

        ref_u8Buffer[Local_u8counter] = (copy_s32number % 10) + 48;
        // printf("%d ",ref_u8Buffer[Local_u8counter]);
        copy_s32number /= 10;
        Local_u8counter++;
    }
    if (Local_u8counter > CLCD_u8_LINE_SIZE)
        ref_u8Buffer[CLCD_u8_LINE_SIZE] = '\0';
    else
        ref_u8Buffer[Local_u8counter] = '\0';
    if (Local_u8MFlag == 0)
        _helper_VoidReverseBuffer(ref_u8Buffer, 0, Local_u8counter - 1);
    else
        _helper_VoidReverseBuffer(ref_u8Buffer, 1, Local_u8counter - 1);
    // return ;
}

void CLCD_VoidSendCommand(uint8 copy_u8command)
{

    // 1-set RS pin to low for command
    DIO_u8_SetPinVal(CLCD_u8CTRL_PORT, CLCD_u8RS_PIN, DIO_PIN_LOW);
// 2-set Rw pin to low for write
#if CLCD_u8READ_OPERATION_ENABLE == ENABLED
    DIO_u8_SetPinVal(CLCD_u8CTRL_PORT, CLCD_u8RW_PIN, DIO_PIN_LOW);
#endif
// 3- send the command
#if CLCD_u8CONNECTION_MODE == EIGHT_BIT
    DIO_u8_SetPortVal(CLCD_u8DATA_PORT, copy_u8command);

    // 4- send enable pulse
    DIO_u8_SetPinVal(CLCD_u8CTRL_PORT, CLCD_u8E_PIN, DIO_PIN_HIGH);
    _delay_ms(2);
    DIO_u8_SetPinVal(CLCD_u8CTRL_PORT, CLCD_u8E_PIN, DIO_PIN_LOW);

#elif CLCD_u8CONNECTION_MODE == FOUR_BIT
    // 3- send the command
    voidSetHalfDataPort(copy_u8command >> 4u);
    // 4- send enable pulse
    voidSendEnablePulse();
    // 3- send the command
    voidSetHalfDataPort(copy_u8command);
    // 4- send enable pulse
    voidSendEnablePulse();
#endif
}
void CLCD_VoidSendData(uint8 copy_u8Data)
{
    // 1-set RS pin to low for command
    DIO_u8_SetPinVal(CLCD_u8CTRL_PORT, CLCD_u8RS_PIN, DIO_PIN_HIGH);
// 2-set Rw pin to low for write
#if CLCD_u8READ_OPERATION_ENABLE == ENABLED
    DIO_u8_SetPinVal(CLCD_u8CTRL_PORT, CLCD_u8RW_PIN, DIO_PIN_LOW);
#endif
#if CLCD_u8CONNECTION_MODE == EIGHT_BIT
    // 3- send the data
    DIO_u8_SetPortVal(CLCD_u8DATA_PORT, copy_u8Data);

    // 4- send enable pulse
    DIO_u8_SetPinVal(CLCD_u8CTRL_PORT, CLCD_u8E_PIN, DIO_PIN_HIGH);
    _delay_ms(2);
    DIO_u8_SetPinVal(CLCD_u8CTRL_PORT, CLCD_u8E_PIN, DIO_PIN_LOW);

#elif CLCD_u8CONNECTION_MODE == FOUR_BIT
    // 3- send the most significant part of data
    voidSetHalfDataPort(copy_u8Data >> 4u);
    // 4- send enable pulse
    voidSendEnablePulse();
    // 3- send the least significant part of data
    voidSetHalfDataPort(copy_u8Data);
    // 4- send enable pulse
    voidSendEnablePulse();
#endif
}
void CLCD_VoidInit(void)
{

    // 1- wait for more than 30ms after power on
    _delay_ms(40);
// 2- function set command :2 lines, font size 5*7
#if CLCD_u8CONNECTION_MODE == EIGHT_BIT
    CLCD_VoidSendCommand(0b00111000);

#elif CLCD_u8CONNECTION_MODE == FOUR_BIT
    CLCD_VoidSendCommand(0X22);
    voidSetHalfDataPort(0b1000);
    voidSendEnablePulse();
#endif
    // 3- Display on/off control: display on ,cursor off, blink cursor off
    CLCD_VoidSendCommand(0b00001100);
    // 4- Display clear
    CLCD_VoidSendCommand(1);
}

void CLCD_voidGoToXY(uint8 copy_u8xPos, uint8 copy_Ypos)
{
    uint8 Local_u8DDRamAdd = (copy_Ypos * 0x40u) + copy_u8xPos;

    CLCD_VoidSendCommand(SET_BIT(Local_u8DDRamAdd, 7u));
}

uint8 CLCD_u8WriteSpecialChar(uint8 copy_u8PatternNumber, uint8 *copy_pu8PatternArr)
{
    uint8 Local_u8ErrorState = OK;
    uint8 Local_u8Counter = 0;
    uint8 Local_u8CGRamAdd = copy_u8PatternNumber * 8u;
    if (copy_pu8PatternArr != NULL)
    {
        CLCD_VoidSendCommand(SET_BIT(Local_u8CGRamAdd, 6u));
        while (Local_u8Counter < 8)
        {
            CLCD_VoidSendData(copy_pu8PatternArr[Local_u8Counter]);
            Local_u8Counter++;
        }
        //		CLCD_voidGoToXY()
    }
    else
    {
        Local_u8ErrorState = NOK;
    }
    return Local_u8ErrorState;
}

uint8 CLCD_VoidPrintChars(const uint8 *copy_u8charArray)
{
    uint8 Local_u8ErrorState = OK;
    if (copy_u8charArray != NULL)
    {
        uint8 Local_u8strCounter = 0u;
        while (copy_u8charArray[Local_u8strCounter] != '\0')
        {
            CLCD_VoidSendData(copy_u8charArray[Local_u8strCounter]);
            Local_u8strCounter++;
        }
    }
    else
    {
        Local_u8ErrorState = NOK;
    }
    return Local_u8ErrorState;
}

void CLCD_VoidPrintInt(sint32 copy_s32number)
{
    uint8 Local_u8Buffer[16];
    _helper_VoidNumToStr(copy_s32number, Local_u8Buffer);
    CLCD_VoidPrintChars(Local_u8Buffer);
}

void CLCD_VoidPrintFloat(sint32 copy_s32IntegerPart, uint32 copy_s32FloatingPart)
{
    uint8 Local_u8Buffer[16];
    _helper_VoidNumToStr(copy_s32IntegerPart, Local_u8Buffer);
    CLCD_VoidPrintChars(Local_u8Buffer);
    CLCD_VoidSendData('.');
    _helper_VoidNumToStr(copy_s32FloatingPart, Local_u8Buffer);
    CLCD_VoidPrintChars(Local_u8Buffer);
}
