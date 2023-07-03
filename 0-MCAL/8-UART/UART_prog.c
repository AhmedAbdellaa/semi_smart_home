
#include "../../libraries/BIT_MATH.h"
#include "../../libraries/ErrType.h"
#include "../../libraries/STD_TYPES_H.h"
#include "UART_interface.h"
#include "UART_reg.h"
#include "UART_prv.h"
#include "UART_cfg.h"
static uint8 *Global_pu8ReceiveBuffer = NULL;
static uint8 *Global_pu8SendBuffer = NULL;

static uint8 Global_u8_ReceiveBufferSize;

static void (*UDRE_pvNotificationFunc)(void) = NULL;

static uint8 Global_u8TXBusyFlag = IDLE;
static uint8 Global_u8RXBusyFlag = IDLE;
// 14 $01A USART, RXC USART, Rx Complete
void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
	static uint16 Local_u16IndexTrace = 0; // init buffer array counter
	if (Global_pu8ReceiveBuffer != NULL)   // check if buffer exist
	{									   // if there is still space to write in it
		if ((Local_u16IndexTrace < Global_u8_ReceiveBufferSize))
		{
			Global_pu8ReceiveBuffer[Local_u16IndexTrace] = UDR; // read udr register
			Local_u16IndexTrace++;
			// Global_pu8ReceiveBuffer[Local_u16IndexTrace]='\0' ;//0
			// display entered character
			UART_voidTransmit(Global_pu8ReceiveBuffer[Local_u16IndexTrace - 1]);
			// if user pass enter then skip rest
			if (Global_pu8ReceiveBuffer[Local_u16IndexTrace - 1] == '\r')
			{
				// end the string
				Global_pu8ReceiveBuffer[Local_u16IndexTrace] = '\0';
				CLS_BIT(UCSRB, UCSRB_RXCIE); // disable RX interrupt
				Local_u16IndexTrace = 0;	 // reset counter
				Global_u8RXBusyFlag = IDLE;	 // reset  rx flag
			}
			else
			{
				/**/
			}
		}
		else
		{ // reach the characters limit
			Global_pu8ReceiveBuffer[Local_u16IndexTrace] = '\0';
			CLS_BIT(UCSRB, UCSRB_RXCIE);
			UART_voidTransmit('\r');
			Local_u16IndexTrace = 0;
			Global_u8RXBusyFlag = IDLE;
		}
	}
	else
	{
		/*do nothing*/
	}
}
// 15 $01C USART, UDRE USART Data Register Empty
void __vector_14(void) __attribute__((signal));
void __vector_14(void)
{
	if (UDRE_pvNotificationFunc != NULL)
	{
		UDRE_pvNotificationFunc();
	}
	else
	{
		/*do nothing*/
	}
}
// 16 $01E USART, TXC USART, Tx Complete
void __vector_15(void) __attribute__((signal));
void __vector_15(void)
{
	static uint16 Local_u16IndexTrace = 0;
	if (Global_pu8SendBuffer != NULL)
	{ // loop until string end
		if (Global_pu8SendBuffer[Local_u16IndexTrace] != '\0')
		{
			UDR = Global_pu8SendBuffer[Local_u16IndexTrace]; // store the value from current index in UDR
			Local_u16IndexTrace++;
		}
		else
		{
			CLS_BIT(UCSRB, UCSRB_TXCIE); // disable transmit interrupt
			Local_u16IndexTrace = 0;	 // reset counter
			Global_u8TXBusyFlag = IDLE;	 // rest transmit flag to idle to proceed with next buffer
		}
	}
	else
	{
		/*do nothing*/
	}
}

void UART_voidInit(void)
{
	uint8 Local_u8USRCVal = 0u;
	uint16 Local_u16UBRR = 0u;
#if UART_u8UMSEL_MODE == UART_UMSEL_ASYNCHRONOUS
	/*Async mode*/
	CLS_BIT(Local_u8USRCVal, UCSRC_UMSEL);
	/*UBBR from BAUD RAte*/
	Local_u16UBRR = (1000000ul / UART_u32_CH_SIZE_COM) - 1;
	UBRRL = (0x00FF & Local_u16UBRR);
	UBRRH = (0x000F & (Local_u16UBRR >> 8));
#elif UART_u8UMSEL_MODE == UART_UMSEL_SYNCHRONOUS
	/*sync mode*/
	SET_BIT(Local_u8USRCVal, UCSRC_UMSEL);
#elif UART_u8UMSEL_MODE == UART_UMSEL_ASYNCHRONOUS_DOUBLE
	/*Async mode*/
	CLS_BIT(Local_u8USRCVal, UCSRC_UMSEL);
	SET_BIT(UCSRA, UCSRA_U2X);
	/*UBBR from BAUD RAte*/
	(8000000ul / UART_u32_CH_SIZE_COM) - 1;
	UBRRL &= (0x00FF & Local_u16UBRR);
	UBRRH &= (0x000F & (Local_u16UBRR >> 8));
#else
#error "Wrong UART_u8UMSEL_MODE configuration option"
#endif

#if UART_u8UPM_MODE == UART_UPM_DISABLED
	/*Disable parity*/
	CLS_BIT(Local_u8USRCVal, UCSRC_UPM0);
	CLS_BIT(Local_u8USRCVal, UCSRC_UPM1);
#elif UART_u8UPM_MODE == UART_UPM_EVEN
	/*Enabled, Even Parity*/
	CLS_BIT(Local_u8USRCVal, UCSRC_UPM0);
	SET_BIT(Local_u8USRCVal, UCSRC_UPM1);
#elif UART_u8UPM_MODE == UART_UPM_ODD
	/*Enabled, Odd Parity*/
	SET_BIT(Local_u8USRCVal, UCSRC_UPM0);
	SET_BIT(Local_u8USRCVal, UCSRC_UPM1);
#else
#error "Wrong UART_u8UPM_MODE configuration option"
#endif

#if UART_u8USBS_MODE == UART_USBS_1BIT
	/*1-STOP BIT*/
	CLS_BIT(Local_u8USRCVal, UCSRC_USBS);
#elif UART_u8USBS_MODE == UART_USBS_2BIT
	/*2-STOP BIT*/
	SET_BIT(Local_u8USRCVal, UCSRC_USBS);
#else
#error "Wrong UART_u8USBS_MODE configuration option"
#endif

#if UART_u8_CH_SIZE_COM == UART_CH_SIZE_5
/*clear all*/
#elif UART_u8_CH_SIZE_COM == UART_CH_SIZE_6
	/*CHARACTER Size :6bits*/
	SET_BIT(Local_u8USRCVal, UCSRC_UCSZ0);
#elif UART_u8_CH_SIZE_COM == UART_CH_SIZE_7
	/*CHARACTER Size :7bits*/
	SET_BIT(Local_u8USRCVal, UCSRC_UCSZ1);
#elif UART_u8_CH_SIZE_COM == UART_CH_SIZE_8
	/*CHARACTER Size :8bits*/
	SET_BIT(Local_u8USRCVal, UCSRC_UCSZ0);
	SET_BIT(Local_u8USRCVal, UCSRC_UCSZ1);
#elif UART_u8_CH_SIZE_COM == UART_CH_SIZE_9
	/*CHARACTER Size :9bits*/
	SET_BIT(UCSRB, UCSRB_UCSZ2);
	SET_BIT(Local_u8USRCVal, UCSRC_UCSZ0);
	SET_BIT(Local_u8USRCVal, UCSRC_UCSZ1);
#else
#error "Wrong UART_u8_CH_SIZE_COM configuration option"
#endif

#if UART_u8UCPOL_MODE == UART_Rising_XCK_Edge
	/*tx on rising edge*/
	CLS_BIT(Local_u8USRCVal, UCSRC_UCPOL);
#elif UART_u8UCPOL_MODE == UART_Falling_XCK_Edge
	/*tx on falling edge*/
	SET_BIT(Local_u8USRCVal, UCSRC_UCPOL);
#else
#error "Wrong UART_u8USBS_MODE configuration option"
#endif

	/*Register select: USRC*/
	SET_BIT(Local_u8USRCVal, UCSRC_URSEL);
	UCSRC = Local_u8USRCVal;

	/*Transmitter enable*/
	SET_BIT(UCSRB, UCSRB_TXEN);
	/*Receiver enable*/
	SET_BIT(UCSRB, UCSRB_RXEN);

	/*Baud rate: 9600bps*/
	// UBRRL = 103U;
}

void UART_voidTransmit(uint16 copy_u16Data)
{
	uint32 local_u32TimeCounter = 0;
	/*wait until transmit buffer is ready or timeout*/
	while (((GET_BIT(UCSRA, UCSRA_UDRE)) == 0) && (local_u32TimeCounter < UART_u32_timeout)) //
	{
		local_u32TimeCounter++;
	} // exit because of timeout
	if (local_u32TimeCounter == UART_u32_timeout)
	{
		return;
	}
	else
	{
#if UART_u8_CH_SIZE_COM == UART_CH_SIZE_9
		CLS_BIT(UCSRB, UCSRB_TXB8);
		UCSRB |= ((copy_u16Data >> 7) | 0xfffD);
#else
/**/
#endif

		UDR = (uint8)copy_u16Data;
	}
}
sint16 UART_voidReceive(void)
{
	uint32 local_u32TimeCounter = 0;

	/*wait until there is data in the receive buffer or timeout*/
	while (((GET_BIT(UCSRA, UCSRA_RXC)) == 0) && (local_u32TimeCounter < UART_u32_timeout))
	{
		local_u32TimeCounter++;
	}
	if (local_u32TimeCounter == UART_u32_timeout) // if timeout return -1
	{
		return -1;
	}
	else // return  udr and 9th bit if exist
	{
#if UART_u8_CH_SIZE_COM == UART_CH_SIZE_9
		uint16 Local_u16Result;
		Local_u16Result = GET_BIT(UCSRB, UCSRB_RXB8) << 8;
		Local_u16Result |= UDR;
		return Local_u16Result;
#else
		return UDR;
#endif
	}
}
uint8 UART_u8SendBufferSynch(const uint8 *copy_u8charArray)
{
	uint8 Local_u8ErrorState = OK;
	if (copy_u8charArray != NULL)
	{
		uint8 Local_u8strCounter = 0u;
		while (copy_u8charArray[Local_u8strCounter] != '\0')
		{ // transmit buffer character by character
			UART_voidTransmit(copy_u8charArray[Local_u8strCounter]);
			Local_u8strCounter++;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR;
	}
	return Local_u8ErrorState;
}
uint8 UART_u8SendBufferASynch(uint8 copy_u8charArray[])
{
	uint8 Local_u8ErrorState = OK;
	// check if there is no buffer use interrupt
	if (Global_u8TXBusyFlag == IDLE)
	{
		if (copy_u8charArray != NULL)
		{
			/*enable transmit interrupt*/
			SET_BIT(UCSRB, UCSRB_TXCIE);
			Global_pu8SendBuffer = copy_u8charArray; // send buffer to global
			Global_u8TXBusyFlag = BUSY;				 // set tx flag to busy
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

uint8 UART_u8ReceiveBufferSynch(uint8 *copy_pu8charArray, uint8 copy_u8BufferSize)
{
	uint8 Local_u8ErrorState = OK;
	sint16 Local_s16_receivedChar;
	if (copy_pu8charArray != NULL)
	{
		uint8 Local_u8strCounter = 0u;
		do
		{
			Local_s16_receivedChar = UART_voidReceive(); // get received character
			if (Local_s16_receivedChar != -1)
			{ // check if character is valid
				copy_pu8charArray[Local_u8strCounter] = (uint8)Local_s16_receivedChar;
				// display character on terminal
				UART_voidTransmit(copy_pu8charArray[Local_u8strCounter]);

				Local_u8strCounter++;
			}
			else
			{
				/**/
			}
			// loop until reach end of buffer length or user press enter
		} while (Local_u8strCounter < copy_u8BufferSize && (copy_pu8charArray[Local_u8strCounter - 1] != '\r')); //&&copy_pu8charArray[Local_u8strCounter-1] == '\n'
		copy_pu8charArray[Local_u8strCounter] = '\0';
	}
	else
	{
		Local_u8ErrorState = NULL_PTR;
	}
	return Local_u8ErrorState;
}

uint8 UART_u8ReceiveBufferASynch(uint8 *copy_pu8charArray, uint8 copy_u8BufferSize)
{
	uint8 Local_u8ErrorState = OK;
	if (Global_u8RXBusyFlag == IDLE)
	{
		if (copy_pu8charArray != NULL)
		{
			/*enable receive interrupt*/
			SET_BIT(UCSRB, UCSRB_RXCIE);
			Global_pu8ReceiveBuffer = copy_pu8charArray; // send store buffer location to global
			Global_u8_ReceiveBufferSize = copy_u8BufferSize;
			Global_u8RXBusyFlag = BUSY;
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
void UART_VoidPrintln(uint8 *copy_u8charArray)
{
	UART_u8SendBufferASynch(copy_u8charArray);
	UART_voidTransmit(0x0D); //\r carriage return cr
	UART_voidTransmit(0x0A); //\n new line
}

static void _helper_VoidNumToStr(sint32 copy_s32number)
{

	uint8 Local_u8Buffer[11];

	if (copy_s32number == 0)
	{
		// Local_u8Buffer[0] = '0';
		// Local_u8Buffer[1] = '\0';
		UART_voidTransmit('0');
		return;
	}

	uint8 Local_s8counter = 0;
	sint8 Local_s8PrintCounter;
	uint8 Local_s8MFlag = 0;

	if (copy_s32number < 0)
	{
		Local_u8Buffer[Local_s8counter] = '-';
		Local_s8counter++;
		copy_s32number *= -1;
		Local_s8MFlag = 1;
	}
	while (copy_s32number)
	{
		// printf("%d ",copy_s32number);

		Local_u8Buffer[Local_s8counter] = (copy_s32number % 10) + 48;
		// printf("%d ",ref_u8Buffer[Local_u8counter]);
		copy_s32number /= 10;
		Local_s8counter++;
	}
	Local_u8Buffer[Local_s8counter] = '\0';
	if (Local_s8MFlag == 1)
	{
		UART_voidTransmit('-');
	}
	else
	{
		/**/
	}
	for (Local_s8PrintCounter = Local_s8counter - 1; Local_s8PrintCounter >= Local_s8MFlag; Local_s8PrintCounter--)
	{
		UART_voidTransmit(Local_u8Buffer[Local_s8PrintCounter]);
	}
}

void UART_VoidPrintInt(sint32 copy_s32number)
{
	_helper_VoidNumToStr(copy_s32number);
}

void UART_VoidPrintFloat(f64 copy_f64number)
{
	sint32 Local_s32IntegerPart = (sint32)copy_f64number;
	_helper_VoidNumToStr(Local_s32IntegerPart);
	UART_voidTransmit('.');
	_helper_VoidNumToStr((sint32)((copy_f64number - Local_s32IntegerPart) * 10000));
}

static uint8 _voidStrToNum(uint8 *ref_pu8StrBuffer, sint32 *ref_ps32ReturnNum)
{
	uint8 Local_u8ErrorState = OK;
	
		uint8 Local_u8LastIndex = 0;
		sint32 Local_s32Num = 0;
		uint32 Local_u32Inc = 1;
	if ((ref_ps32ReturnNum != NULL) && (ref_ps32ReturnNum != NULL))
	{
		// get string end index
		while (ref_pu8StrBuffer[Local_u8LastIndex] != '\0' && ref_pu8StrBuffer[Local_u8LastIndex] != '\r')
		{
			Local_u8LastIndex++;
		}
		Local_u8LastIndex -= 1;//last number index
		while (Local_u8LastIndex > 0)
		{
			if ((ref_pu8StrBuffer[Local_u8LastIndex] >= '0') && (ref_pu8StrBuffer[Local_u8LastIndex] <= '9'))
			{
				Local_s32Num += ((ref_pu8StrBuffer[Local_u8LastIndex] - '0')*Local_u32Inc);
			}
			else
			{
				Local_u8ErrorState = NOK;
			}
			Local_u8LastIndex--;
			Local_u32Inc*=10; //10 100 1000 10000 
		}
		// first character in buffer will be num or (-)sign
		if ((ref_pu8StrBuffer[Local_u8LastIndex] >= '0') && (ref_pu8StrBuffer[Local_u8LastIndex] <= '9'))
		{
			Local_s32Num += ((ref_pu8StrBuffer[Local_u8LastIndex] - '0')*Local_u32Inc);
		}
		else if (ref_pu8StrBuffer[Local_u8LastIndex] >= '-')
		{
			Local_s32Num *= -1;
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
		*ref_ps32ReturnNum = Local_s32Num;
	}
	else
	{
		Local_u8ErrorState = NULL_PTR;
	}
	return Local_u8ErrorState;
}

sint32 UART_s32_ReceiveInt()
{
	uint8 Local_pu8Buffer[11]; // maximum length of integer number
	sint32 Local_s32ReturnNum = 0;
	UART_u8ReceiveBufferSynch(Local_pu8Buffer, 11u);
	_voidStrToNum(Local_pu8Buffer, &Local_s32ReturnNum);
	return Local_s32ReturnNum;
}