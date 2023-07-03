#include <util/delay.h>

#include "../../libraries/STD_TYPES_H.h"
#include "../../libraries/ErrType.h"
#include "../../libraries/BIT_MATH.h"
#include "../../0-MCAL/1-DIO/DIO_interface.h"
#include "../../0-MCAL/3-EXTI/EXTI_interface.h"
#include "../../0-MCAL/8-UART/UART_interface.h"
#include "../../1-HAL/CLCD/CLCD_interface.h"
#include "../../1-HAL/KEYPAD/KPD_interface.h"
#include "../hmaoksha/HAMO_interface.h"
#include "LOGIN_interface.h"
#define ID 1234
#define PASSWORD 4321
void LOGIN_voidEnable_INTBTN()
{
	// enable interrupt
	// reset pins for interrupt
	DIO_u8_SetPinVal(DIO_PORTD, DIO_PIN2, DIO_PIN_LOW);
	DIO_u8_SetPinDir(DIO_PORTD, DIO_PIN2, DIO_PIN_INPUT);

	DIO_u8_SetPinVal(DIO_PORTB, DIO_PIN7, DIO_PIN_LOW);
	DIO_u8_SetPinDir(DIO_PORTB, DIO_PIN7, DIO_PIN_OUTPUT);

	// DIO_u8_SetPinVal(DIO_PORTD, DIO_PIN4, DIO_PIN_LOW);
	// DIO_u8_SetPinDir(DIO_PORTD, DIO_PIN4, DIO_PIN_OUTPUT);

	// DIO_u8_SetPinVal(DIO_PORTD, DIO_PIN5, DIO_PIN_LOW);
	// DIO_u8_SetPinDir(DIO_PORTD, DIO_PIN5, DIO_PIN_OUTPUT);

	
	EXTI_u8IntEnable(INT0);
}
void LOGIN_voidDisable_INTBTN()
{
	EXTI_u8IntDisable(INT0);
	//initialize keypad pins
	DIO_u8_SetPinVal(DIO_PORTD, DIO_PIN2, DIO_PIN_HIGH);
	DIO_u8_SetPinDir(DIO_PORTD, DIO_PIN2, DIO_PIN_OUTPUT);

	DIO_u8_SetPinVal(DIO_PORTB, DIO_PIN7, DIO_PIN_HIGH);
	DIO_u8_SetPinDir(DIO_PORTB, DIO_PIN7, DIO_PIN_INPUT);

	// DIO_u8_SetPinVal(DIO_PORTD, DIO_PIN4, DIO_PIN_HIGH);
	// DIO_u8_SetPinDir(DIO_PORTD, DIO_PIN4, DIO_PIN_OUTPUT);

	// DIO_u8_SetPinVal(DIO_PORTD, DIO_PIN5, DIO_PIN_HIGH);
	// DIO_u8_SetPinDir(DIO_PORTD, DIO_PIN5, DIO_PIN_OUTPUT);

	

}
// hamoksha
void LOGIN_voidSystemStart()
{
	// disable intrrupt

	CLCD_VoidSendCommand(CLCD_CLEAR_CMD);
	LOGIN_voidDisable_INTBTN();
	Hamo_voidWalkRightScene();
}
// get IDget Passowrd
sint16 LOGIN_s16GetID_Pass(uint8 copy_ispassword)
{

	uint8 Local_u8NumbersCounter = 0;
	uint8 Local_u8_keypadStatus, Local_u8Row, Local_u8Col;
	sint16 Local_s16ID = 0;
	CLCD_voidGoToXY(0u, 1u);
	while (Local_u8NumbersCounter < 4)
	{
		Local_u8_keypadStatus = KPD_u8GetPressedKey(&Local_u8Row, &Local_u8Col);
		if ((Local_u8_keypadStatus >= 0) && (Local_u8_keypadStatus <= 9))
		{

			CLCD_VoidSendData(Local_u8_keypadStatus + '0');

			Local_s16ID = (Local_s16ID * 10) + Local_u8_keypadStatus;
			Local_u8NumbersCounter++;
			if (copy_ispassword == 1u)
			{
				_delay_ms(200);
				CLCD_voidGoToXY(Local_u8NumbersCounter - 1, 1u);
				CLCD_VoidSendData('*');
			}
		}
	}

	return Local_s16ID;
}

uint8 LOGIN_u8login(uint8 *copy_u8INTFlag)
{
	uint8 Local_u8LogInState = LOGIN_SUCCESS;
	// *copy_u8INTFlag=0;
	CLCD_VoidPrintChars("Enter ID");

	uint8 Local_u8TrialsNumber = 3;
	sint16 Local_s16ID = LOGIN_s16GetID_Pass(0u);

	sint16 Local_s16Pass = 0;
	uint8 Local_u8Iter0;

	if (Local_s16ID == ID)
	{
		// disable intrrupt
		CLCD_VoidSendCommand(CLCD_CLEAR_CMD);
		CLCD_VoidPrintChars("Enter Password");

		CLCD_voidGoToXY(6, 1);
		CLCD_VoidSendData(Local_u8TrialsNumber + '0');
		CLCD_VoidPrintChars(" trials");

		while ((Local_s16Pass != PASSWORD) && (Local_u8TrialsNumber > 0))
		{
			// clear old password
			for (Local_u8Iter0 = 0; Local_u8Iter0 < 4; Local_u8Iter0++)
			{
				CLCD_voidGoToXY(Local_u8Iter0, 1);
				CLCD_VoidSendData(' ');
			}
			CLCD_voidGoToXY(6, 1);
			CLCD_VoidSendData(Local_u8TrialsNumber + '0');
			Local_s16Pass = LOGIN_s16GetID_Pass(1u);

			Local_u8TrialsNumber--;
		}
		_delay_ms(200);
		// *copy_u8INTFlag = 1;
		UART_VoidPrintInt(*copy_u8INTFlag);
			UART_voidTransmit(' ');
		LOGIN_voidEnable_INTBTN();
		UART_VoidPrintInt(*copy_u8INTFlag);
			UART_voidTransmit(' ');
		if (Local_u8TrialsNumber != 0)
		{
			// login successfully
			
		}
		else
		{
			// login faild
			// red led on
			Local_u8LogInState = LOGIN_PASS_FAILD;
		}
	}
	else
	{ // login faild
		Local_u8LogInState = LOGIN_ID_FAILD;
		// enable interrupt
		// reset pins for interrupt
		LOGIN_voidEnable_INTBTN();
		// *copy_u8INTFlag = 1;
	}

	return Local_u8LogInState;
}
