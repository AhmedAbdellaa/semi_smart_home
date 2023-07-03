
#include "../../libraries/STD_TYPES_H.h"
#include "../../libraries/ErrType.h"
#include "../../2-service/TIMER1_S_interface.h"
#include "../../0-MCAL/6-TIMER/TIMER_interface.h"
#include "../../0-MCAL/1-DIO/DIO_interface.h"
#include <util/delay.h>
#include "BUZZER_interface.h"
#define BUZZER_MUSIC 0u
#define BUZZER_TONE 1u
#define BUZZER_NO_PLAY 2u

TIMER_TINum_t Global_TINum;
uint8 Global_u8MusicFlag = BUZZER_TONE;
uint16 *Global_u16FrequencyList = NULL;
// uint16 *Global_u16durationList = NULL;
uint16 *Global_u16DelayDurationList = NULL;
uint8 Global_u8ListLength = 1;
TIMER_CALLBACK_CONFIG_t Global_TIMERWait_Config = {0, 0};
static uint8 Global_u8ArrayCounter = 0;
static uint8 Global_u8delayDurationFlag = 0;
static void __BUZZER_ToneHelper(void)
{

	if (Global_u8MusicFlag == BUZZER_MUSIC)
	{

		if (Global_u8ArrayCounter < Global_u8ListLength)
		{
			// wait delay
			if (Global_u8delayDurationFlag == 0)
			{
				// TIMER_voidDisable_OV_Interrupt(TIMER1);
				/*change flag */
				Global_u8delayDurationFlag = 1;
				/*stop buzzer fo delay time*/
				BUZZER_voidNoTone(Global_TINum);
				/*set the delay time after tone*/
				if (Global_u16FrequencyList[Global_u8ArrayCounter] > 0)
				{
					Global_TIMERWait_Config.TIMER_U32ISRDoNum_ICR1 =
						(((uint32)(Global_u16DelayDurationList[Global_u8ArrayCounter] * 0.1) * 1000) / (1000000 / (Global_u16FrequencyList[Global_u8ArrayCounter])));
				}
				else
				{
					Global_TIMERWait_Config.TIMER_U32ISRDoNum_ICR1 =
						(((uint32)(Global_u16DelayDurationList[Global_u8ArrayCounter] * 0.1) * 1000) / 1000);
				}

				/*apply delay time*/
				TIMER_u8Start_OV_Interrupt(TIMER1, &Global_TIMERWait_Config, &__BUZZER_ToneHelper);
			}
			else
			{
				TIMER_voidDisable_OV_Interrupt(TIMER1);
				Global_u8ArrayCounter++;
				// change tone
				Global_u8delayDurationFlag = 0;
				BUZZER_voidTone(Global_TINum, Global_u16FrequencyList[Global_u8ArrayCounter], Global_u16DelayDurationList[Global_u8ArrayCounter] * 0.9);
			}
		}
		else // music finish
		{
			BUZZER_voidKill(Global_TINum);
			TIMER_voidDisable_OV_Interrupt(TIMER1);
		}
	}
	else
	{

		BUZZER_voidNoTone(Global_TINum);
		TIMER_voidDisable_OV_Interrupt(TIMER1);
	}
}

void BUZZER_voidInit(TIMER_TINum_t copy_TINum)
{
	if (copy_TINum == TIMER1A || copy_TINum == TIMER1B)
	{
		TIMER_voidChangCOM_Mode(copy_TINum, TIMER_COM_CLEAR);
		TIMER_voidChangWGM_Mode(TIMER1, TIMER_WGM_PWM_FAST_ICR1);
	}
}
void BUZZER_voidTone(TIMER_TINum_t copy_TINum, uint16 copy_u16Frequency, uint16 copy_u16duration)
{
	static TIMER_CALLBACK_CONFIG_t Local_TIMER_Config;
	if (copy_TINum == TIMER1A || copy_TINum == TIMER1B)
	{

		uint32 Local_u32CycleTime;
		uint16 Local_u16ICRVal;
		if (copy_u16Frequency > 0)
		{
			Local_u32CycleTime = 1000000 / (copy_u16Frequency);
			// icr = cycle time/tick time
			Local_u16ICRVal = Local_u32CycleTime / BUZZER_TICK_TIME;
			Local_TIMER_Config.TIMER_u16OCR_TCNT_initVal = 0;
			Local_TIMER_Config.TIMER_U32ISRDoNum_ICR1 = (((uint32)copy_u16duration * 1000) / Local_u32CycleTime);

			TIMER_u8Start_OV_Interrupt(TIMER1, &Local_TIMER_Config, &__BUZZER_ToneHelper);
			TIMER_voidStart_PWM(copy_TINum, Local_u16ICRVal / 2, Local_u16ICRVal);
			TIMER_voidChangCOM_Mode(copy_TINum, TIMER_COM_CLEAR);

			Global_TINum = copy_TINum;
		}
		else if (copy_u16Frequency == 0)
		{
			Local_u32CycleTime = 1000;
			Local_u16ICRVal = Local_u32CycleTime / BUZZER_TICK_TIME;
			Local_TIMER_Config.TIMER_u16OCR_TCNT_initVal = 0;
			Local_TIMER_Config.TIMER_U32ISRDoNum_ICR1 = (((uint32)copy_u16duration * 1000) / Local_u32CycleTime);

			TIMER_u8Start_OV_Interrupt(TIMER1, &Local_TIMER_Config, &__BUZZER_ToneHelper);
		}
		else
		{
		}
	}
}
void BUZZER_voidNoTone(TIMER_TINum_t copy_TINum)
{
	if (copy_TINum == TIMER1A || copy_TINum == TIMER1B)
	{
		DIO_u8_SetPinVal(DIO_PORTD, DIO_PIN4, DIO_PIN_LOW); // put pin to low to prevent noise
		TIMER_voidChangCOM_Mode(copy_TINum, TIMER_COM_NORMAL);
		// TIMER_voidChangWGM_Mode(TIMER1, TIMER_WGM_Normal);
		// Global_u8MusicFlag = BUZZER_NO_PLAY;
	}
}

uint8 BUZZER_U8PlayMusic(TIMER_TINum_t copy_TINum, uint16 *ref_pu16FrequencyList, uint16 *ref_u16DelayDuration, uint8 Copy_u8ListLength)
{

	uint8 Local_u8ErrorState = OK;
	if ((ref_pu16FrequencyList != NULL) && (ref_u16DelayDuration != NULL))
	{
		Global_u8MusicFlag = BUZZER_MUSIC;

		Global_u16FrequencyList = ref_pu16FrequencyList;
		Global_u16DelayDurationList = ref_u16DelayDuration;
		Global_u8ListLength = Copy_u8ListLength-1;

		BUZZER_voidTone(copy_TINum, ref_pu16FrequencyList[0], ref_u16DelayDuration[0]);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR;
	}
	return Local_u8ErrorState;
}
void BUZZER_voidKill(TIMER_TINum_t copy_TINum)
{
	if (copy_TINum == TIMER1A || copy_TINum == TIMER1B)
	{
		BUZZER_voidNoTone(copy_TINum);
		Global_u8ArrayCounter = 0;
		Global_u8delayDurationFlag = 0;
		TIMER_voidChangWGM_Mode(TIMER1, TIMER_WGM_Normal);
		Global_u8MusicFlag = BUZZER_NO_PLAY;
	}
}