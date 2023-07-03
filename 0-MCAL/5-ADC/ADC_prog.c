
#include "../../libraries/BIT_MATH.h"
#include "../../libraries/ErrType.h"
#include "../../libraries/STD_TYPES_H.h"
#include "ADC_prv.h"
#include "ADC_reg.h"
#include "ADC_cfg.h"
#include "ADC_interface.h"


static uint16 *ADC_pu16DigResult = NULL;
static void (*ADC_pvNotificationFunc)(void) = NULL;

static uint8 ADC_u8BusyFlag = IDLE;

static uint8 ADC_u8ChainCounter = 0u;
static uint8 ADC_u8ChainFlag = IDLE;
static uint8 ADC_u8ChainDeviceCount = 0u;

static ADC_CHAIN_config_t *ADC_u8ChainDevices = NULL;

void ADC_voidInit()
{
	// 1- referance selection
#if ADC_u8ReferanceSelection == AREF
	CLS_BIT(ADMUX, REFS1);
	CLS_BIT(ADMUX, REFS0);
#elif ADC_u8ReferanceSelection == AVCC
	CLS_BIT(ADMUX, REFS1);
	SET_BIT(ADMUX, REFS0);
#elif ADC_u8ReferanceSelection == Voltage_2_65
	SET_BIT(ADMUX, REFS1);
	SET_BIT(ADMUX, REFS0);
#else
#error "Wrong ADC_u8ReferanceSelection configuration option"
#endif

	// 2-bits presentaion
#if ADC_u8_presentationBits == EIGHT_BITS // left adjust
	SET_BIT(ADMUX, ADLAR);
#elif ADC_u8_presentationBits == TEN_BITS
	CLS_BIT(ADMUX, ADLAR); // right adjust
#else
#error "Wrong ADC_u8_presentationBits configuration option"
#endif

	// 3- prescaler setting
	ADCSRA &= PRESCALER_MASK;
	ADCSRA |= ADC_u8_DevisionFactor;

	// 3- enable ADC
	SET_BIT(ADCSRA, ADEN);
}

uint8 ADC_u8StartConverstionSync(ADC_channel_t copy_Channel, uint16 *referance_u16DigResult)
{

	uint8 Local_u8ErrorState = OK;
	if (referance_u16DigResult != NULL)
	{
		if (ADC_u8BusyFlag == IDLE)
		{
			ADC_u8BusyFlag = BUSY;

			uint32 Local_u32Counter = 0u;
			// 1-start required channel
			ADMUX &= CHANNEL_SELECTION_MASK;
			ADMUX |= copy_Channel;
			// 2-start conversion
			SET_BIT(ADCSRA, ADSC);

			// polling for adc conversion complete flag or timed out

			while ((GET_BIT(ADCSRA, ADIF) != 1)&& (Local_u32Counter < ADC_u32TIMEOUT_COUNT)) //
			{
				Local_u32Counter++;
			}
			if (Local_u32Counter == ADC_u32TIMEOUT_COUNT)
			{
				/*loop is broken because timeout has passed*/
				Local_u8ErrorState = TIMEOUT_ERR;
			}
			else
			{
				// clear flag
				SET_BIT(ADCSRA, ADIF);
				// read data
				#if ADC_u8_presentationBits == EIGHT_BITS
								*referance_u16DigResult = (uint16)ADCH;
				#elif ADC_u8_presentationBits == TEN_BITS
								*referance_u16DigResult = ADC;
				#else
				#error "Wrong ADC_u8_presentationBits configuration option"
				#endif
			}
			ADC_u8BusyFlag = IDLE;
			// clear flag
			SET_BIT(ADCSRA, ADIF);
		}
		else
			Local_u8ErrorState = BUSY_ERR;
	}
	else
	{
		Local_u8ErrorState = NULL_PTR;
	}
	return Local_u8ErrorState;
}
uint8 ADC_u8StartConverstionAsync(ADC_channel_t copy_Channel, uint16 *referance_u16DigResult, void (*copy_pvNotificationFunc)(void))
{
	uint8 Local_u8ErrorState = OK;
	if (referance_u16DigResult != NULL && copy_pvNotificationFunc != NULL)
	{
		if (ADC_u8BusyFlag == IDLE)
		{
			ADC_u8BusyFlag = BUSY;
			ADC_pu16DigResult = referance_u16DigResult;
			ADC_pvNotificationFunc = copy_pvNotificationFunc;
			// 1-start required channel
			ADMUX &= CHANNEL_SELECTION_MASK;
			ADMUX |= copy_Channel;

			// 2-start conversion
			SET_BIT(ADCSRA, ADSC);

			/*enable ADC conversion complete interrupt*/
			SET_BIT(ADCSRA, ADIE);

			ADC_u8BusyFlag = IDLE;
		}
		else
			Local_u8ErrorState = BUSY_ERR;
	}
	else
	{
		Local_u8ErrorState = NULL_PTR;
	}
	return Local_u8ErrorState;
}

uint8 ADC_u8StartChainConverstionAsync(ADC_CHAIN_config_t *referance_adcChain, uint8 copy_u8NumberOfADC)
{
	uint8 Local_u8ErrorState = OK;
	if (referance_adcChain != NULL)
	{
		/*raise chain method flag*/
		ADC_u8ChainFlag = BUSY;
		/*store channels*/
		ADC_u8ChainDevices = referance_adcChain;
		ADC_u8ChainDeviceCount = copy_u8NumberOfADC;
		/*start first conversation */
		ADC_u8StartConverstionAsync(referance_adcChain[ADC_u8ChainCounter].ConversionChannel,
									referance_adcChain[ADC_u8ChainCounter].result,
									referance_adcChain[ADC_u8ChainCounter].pvnotificationFunction);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR;
	}
	return Local_u8ErrorState;
}
void ADC_voidChainNotification()
{	/*executer (ISR)function for this interrupt*/
	if (ADC_pvNotificationFunc != NULL)
	{
		ADC_pvNotificationFunc();
	}
	else
	{
		/*do nothing*/
	}
	ADC_u8ChainCounter += 1;
	/*if there is no more devices*/
	if (ADC_u8ChainCounter == ADC_u8ChainDeviceCount)
	{
		/*reset flags*/
		ADC_u8ChainCounter = 0u;
		ADC_u8ChainDeviceCount = 0u;
		ADC_u8ChainFlag = IDLE;
	}
	else
	{
		/*start next conversrion*/
		ADC_u8StartConverstionAsync(ADC_u8ChainDevices[ADC_u8ChainCounter].ConversionChannel,
									ADC_u8ChainDevices[ADC_u8ChainCounter].result,
									ADC_u8ChainDevices[ADC_u8ChainCounter].pvnotificationFunction);
	}
}
 /*ADC conversion complete ISR*/
 void __vector_16(void) __attribute__((signal));
 void __vector_16(void)
 {
		// read data
 		#if ADC_u8_presentationBits == EIGHT_BITS
 				*ADC_pu16DigResult = (uint16)ADCH;
 		#elif ADC_u8_presentationBits == TEN_BITS
 				*ADC_pu16DigResult = ADC;
 				ADC = 0x0000;
 		#else
 		#error "Wrong ADC_u8_presentationBits configuration option"
 		#endif

 		/*ADC interrupt disable*/
 		CLS_BIT(ADCSRA, ADIE);
 		/*if called from sync function*/
 		if (ADC_u8ChainFlag == IDLE)
 		{
 			if (ADC_pvNotificationFunc != NULL)
 			{
 				ADC_pvNotificationFunc();
 			}
 			else
 			{
 				/*do nothing*/
 			}
 		}
 		/*if called from chain function*/
 		else if (ADC_u8ChainFlag == BUSY)
 		{
 			ADC_voidChainNotification();
 		}else{
 			/*do nothing*/
 		}
 }
void ADC_voidSetPrescaler(uint8 copy_u8DivisionFactor)
{
	switch (copy_u8DivisionFactor)
	{
	case 2:
		ADCSRA &= DIVISION_BY_2;
		break;
	case 4:
		ADCSRA &= DIVISION_BY_4;
		break;
	case 8:
		ADCSRA &= DIVISION_BY_8;
		break;
	case 16:
		ADCSRA &= DIVISION_BY_16;
		break;
	case 32:
		ADCSRA &= DIVISION_BY_32;
		break;
	case 64:
		ADCSRA &= DIVISION_BY_64;
		break;
	case 128:
		ADCSRA &= DIVISION_BY_128;
		break;
	default:
		break;
	}
}
