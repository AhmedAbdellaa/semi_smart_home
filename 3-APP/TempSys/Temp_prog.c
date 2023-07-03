#include "util/delay.h"

#include "../../libraries/STD_TYPES_H.h"
#include "../../libraries/ErrType.h"

#include "../../0-MCAL/1-DIO/DIO_interface.h"
#include "../../0-MCAL/2-Port/PORT_interface.h"
#include "../../0-MCAL/5-ADC/ADC_interface.h"
#include "../../0-MCAL/4-GIE/GIE_interface.h"

#include "../../1-HAL/LDR/LDR_interface.h"
#include "../../1-HAL/LM35/LM_interface.h"
#include "../../1-HAL/DC_motor/DCM_interface.h"
#include "../../1-HAL/CLCD/CLCD_interface.h"

#include "Temp_interface.h"

#define CHAIN_LENGTH 3u
static ADC_CHAIN_config_t Global_ADC_Chain_devices[CHAIN_LENGTH];
static TESY_CONFIG_t *Global_TESY;

// ADC Notification Callback
void ADC0CallBack(void)
{
	// measure light level from given digital signal
	LDR_u8GetLLFromDigSignal(&Global_TESY->TE_LDR);
}
void ADC7CallBack(void)
{
	// read last dig signal
	static uint8 Local_u8_counter = 0;

	Local_u8_counter++;
	// measure temperature from given digital signal
	if (Local_u8_counter == 2)
	{

		LM_u8GetTempFromDigSignal(&Global_TESY->TE_LM);
		Local_u8_counter = 0;
	}
	else
	{
		/**/
	}
}

uint8 TESY_u8init(TESY_CONFIG_t *reference_TESY)
{
	uint8 Local_u8ErrorState = OK;
	if (reference_TESY != NULL)
	{
		Global_TESY = reference_TESY;
		// init LDR
		Global_ADC_Chain_devices[0].ConversionChannel = (ADC_channel_t)Global_TESY->TE_LDR.AnalogChannel_DigitalSignal;
		Global_ADC_Chain_devices[0].pvnotificationFunction = &ADC0CallBack;
		Global_ADC_Chain_devices[0].result = &(Global_TESY->TE_LDR.AnalogChannel_DigitalSignal);
		// init LM
		Global_ADC_Chain_devices[1].ConversionChannel = (ADC_channel_t)Global_TESY->TE_LM.AnalogChannel_DigitalSignal;
		Global_ADC_Chain_devices[1].pvnotificationFunction = &ADC7CallBack;
		Global_ADC_Chain_devices[1].result = &(Global_TESY->TE_LM.AnalogChannel_DigitalSignal);
		// Repeat lm read for solving some hardware issue and remove
		Global_ADC_Chain_devices[2].ConversionChannel = (ADC_channel_t)Global_TESY->TE_LM.AnalogChannel_DigitalSignal;
		Global_ADC_Chain_devices[2].pvnotificationFunction = &ADC7CallBack;
		Global_ADC_Chain_devices[2].result = &(Global_TESY->TE_LM.AnalogChannel_DigitalSignal);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR;
	}
	return Local_u8ErrorState;
}

void TESY_voidMainSystem(uint8 copy_u8controlFan, uint8 *ref_u8intensity_led_to_on)
{
	uint8 Local_u8LedsNumber;
	uint16 Local_u16OldTemp = 0u, Local_u16OldLight = 2u;

	// read all LDR light level
	ADC_u8StartChainConverstionAsync(Global_ADC_Chain_devices, CHAIN_LENGTH);

	// if temperature read change
	_delay_ms(150);
	if (Global_TESY->TE_LM.Temprature != Local_u16OldTemp)
	{
		Local_u16OldTemp = Global_TESY->TE_LM.Temprature;
		CLCD_voidGoToXY(0, 0);
		CLCD_VoidPrintChars("            ");
		CLCD_voidGoToXY(0, 0);
		CLCD_VoidPrintChars("Temp: ");
		// temp measure here
		CLCD_VoidPrintInt((sint32)Local_u16OldTemp);
		if (copy_u8controlFan == 1)
		{
			if (Local_u16OldTemp >= TESY_MAX_TEMP_FAN_ON)
			{
				DCM_voidRotateCCW(&Global_TESY->TE_DCMotor);
			}
			else if (Local_u16OldTemp <= TESY_MAX_TEMP_FAN_OFF)
			{
				DCM_voidStop(&Global_TESY->TE_DCMotor);
			}
			else
			{
				/*do nothing*/
			}
		}
		else
		{
			/**/
		}
	}
	else
	{
		/*do nothing*/
	}
	if (Global_TESY->TE_LDR.LightLevel != Local_u16OldLight)
	{
		Local_u16OldLight = Global_TESY->TE_LDR.LightLevel;
		CLCD_voidGoToXY(0, 1);
		CLCD_VoidPrintChars("            ");
		CLCD_voidGoToXY(0, 1);
		CLCD_VoidPrintChars("LEDS: ");
		// LDR : number of leds = 9-(light level /division )
		// leds increase when light level decrease
		Local_u8LedsNumber = 8 - (Global_TESY->TE_LDR.LightLevel / TESY_LIGHT_LEVEL_RANGE);
		CLCD_VoidPrintInt((sint32)Local_u8LedsNumber);
		*ref_u8intensity_led_to_on = Local_u8LedsNumber;
	}
	else
	{
		/*do nothing*/
	}
}
