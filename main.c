/*
 * main.c
 *
 *  Created on: Jun 27, 2023
 *      Author: ahmed
 * 		Sami smart home
 */

#include <util/delay.h>

#include "libraries/STD_TYPES_H.h"
#include "libraries/MAP.h"

#include "0-MCAL/1-DIO/DIO_interface.h"
#include "0-MCAL/2-Port/PORT_interface.h"
#include "0-MCAL/3-EXTI/EXTI_interface.h"
#include "0-MCAL/4-GIE/GIE_interface.h"
#include "0-MCAL/5-ADC/ADC_interface.h"
#include "0-MCAL/6-TIMER/TIMER_interface.h"
#include "0-MCAL/8-UART/UART_interface.h"
// #include "0-MCAL/10-TWI/TWI_interface.h"
// output hardware
#include "1-HAL/CLCD/CLCD_interface.h"
#include "1-HAL/LED/LED_interface.h"
#include "1-HAL/SERVO_motor/SVM_interface.h"
#include "1-HAL/DC_motor/DCM_interface.h"
// input hardware
#include "1-HAL/KEYPAD/KPD_interface.h"
#include "1-HAL/LDR/LDR_interface.h"
#include "1-HAL/LM35/LM_interface.h"
#include "1-HAL/SR04/SR04_interface.h"
#include "1-HAL/BUZZER/BUZZER_interface.h"
// pir sensor
/******************************************************/
// #include "1-HAL/EEPROM/EEPROM_interface.h"

#include "2-service/TIMER1_S_interface.h"

#include "3-APP/login/LOGIN_interface.h"
#include "3-APP/TempSys/Temp_interface.h"

// #include "EEPROM_locations.h"


// global variable
static LED_Config_t Global_LedBlue = {LED_ACTIVE_HIGH, DIO_PORTB, DIO_PIN3};
static SR04_TriggerPin Global_SR_trigger = {.trigPort = DIO_PORTC, .trigPin = DIO_PIN3};

// global flags
static uint8 Global_u8DoorStateFlag = 0; // door flag open :0 , close :180
static uint8 Global_u8LedControl = 0;	 // turn off 0,turn on :1, LDR = 2, pir=3
static uint8 Global_u8FanControl = 0;	 // turn off 0,turn on :1, sr04 = 2, temperature_sens =3
static uint8 Global_u8BuzzerState = 0;	 // turn off 0,turn on :1

static uint8 GLobal_u8intensity_led_to_on = 0; // value of led pwm depend on LDR
static uint8 GLobal_u8intensity_led_old = 0;   // value of led pwm depend on LDR

static uint8 Global_u8INT0Flag = 0;
static uint16 melody[49] = {392, 262, 311, 349, 392, 262, 311, 349, 392, 262, 311, 349, 392, 262, 311, 349, 392, 262, 330, 349, 392, 262, 330, 349, 392, 262, 330, 349, 392, 262, 330, 349, 392, 262, 311, 349, 392, 262, 311, 349, 294, 349, 233, 311, 294, 349, 233, 311, 294};
static uint16 delay_duration[49] = {352, 352, 176, 176, 352, 352, 176, 176, 352, 352, 176, 176, 352, 352, 176, 176, 352, 352, 176, 176, 352, 352, 176, 176, 352, 352, 176, 176, 352, 352, 176, 176, 1058, 1058, 176, 176, 705, 705, 176, 176, 2235, 1058, 1058, 176, 176, 705, 1058, 176, 176};//4235

void INT0ISR(void);
void INT2ISR(void);

void main()
{

	uint8 Local_u8LoginState = LOGIN_SUCCESS; // login state variable
	sint16 Local_s16UartReceivedVal = -1;	  // input uart value
	uint16 Local_u16Distance = 0;
	uint16 Local_u16OldDistance = 0;
	uint8 Local_u8mappedLedIntensity = 0;
	uint8 Local_u8Iter;
	TESY_CONFIG_t Local_TESY = {.TE_LDR = {.AnalogChannel_DigitalSignal = ADC7_SINGLE_ENDED,
										   .max_volt = 5000ul,
										   .LightLevel = 0u},
								.TE_LM = {.AnalogChannel_DigitalSignal = ADC0_SINGLE_ENDED,
										  .max_volt = 5000ul,
										  .Temprature = 30u},
								.TE_DCMotor = {DIO_PORTD, DIO_PIN7, DIO_PIN6}};
	/*Initialize mcal*/
	Port_voidInit();
	GIE_voidEnableGlobal();
	EXTI_voidInit();
	ADC_voidInit();
	TIMER0_voidInit();
	TIMER1_voidInit();
	TIMER2_voidInit();
	ICU_voidInit();
	UART_voidInit();
	// TWI_voidMasterInit(0);
	
	/*initialize ISR*/
	EXTI_u8SetCallBack(INT0, &INT0ISR);
	EXTI_u8SetCallBack(INT2, &INT2ISR);

	/*initialize hal*/
	CLCD_VoidInit();

	TESY_u8init(&Local_TESY);

	while (1)
	{
		_delay_ms(150);
		if (Global_u8INT0Flag == 1)
		{
			Global_u8INT0Flag = 0;
			// hamoksha walking and disable interrupt
			LOGIN_voidSystemStart();
			UART_voidTransmit(Global_u8INT0Flag);
			UART_voidTransmit(' ');
			// get login state
			Local_u8LoginState = LOGIN_u8login(&Global_u8INT0Flag);

			if (Local_u8LoginState == LOGIN_SUCCESS)
			{
				DIO_u8_SetPinVal(DIO_PORTD,DIO_PIN5,DIO_PIN_LOW);
					DIO_u8_SetPinVal(DIO_PORTD,DIO_PIN4,DIO_PIN_LOW);
				DIO_u8_SetPinVal(DIO_PORTC,DIO_PIN4,DIO_PIN_HIGH);
				CLCD_VoidSendCommand(CLCD_CLEAR_CMD);
				// loop in application
				while (Global_u8INT0Flag == 0)
				{
					_delay_ms(150);
					
					TESY_voidMainSystem((Global_u8FanControl == 3 ? 1 : 0), &GLobal_u8intensity_led_to_on);
					// if intensity change change reading

					if (GLobal_u8intensity_led_old != GLobal_u8intensity_led_to_on)
					{
						GLobal_u8intensity_led_old = GLobal_u8intensity_led_to_on;

						if (Global_u8LedControl == 2)
						{
							Local_u8mappedLedIntensity = (uint8)MAP(0, 8, 0, 255, GLobal_u8intensity_led_to_on);
							TIMER_voidStart_PWM(TIMER0, Local_u8mappedLedIntensity, 0);
						}
						else
						{
							/**/
						}
					}

					if (Global_u8FanControl == 2)
					{
						Local_u16Distance = SR04_u16GetDistance((sint32)SR04_u32ReadTime(&Global_SR_trigger));

						// UART_VoidPrintInt(Local_u16Distance);
						// UART_VoidPrintln(" ");
						_delay_ms(150);
						if ((Local_u16Distance <= 20) && (Local_u16Distance >= 3))
						{
							if (Local_u16OldDistance != Local_u16Distance)
							{
								Local_u16OldDistance = Local_u16Distance;

								TIMER_voidStart_PWM(TIMER2, (uint16)MAP(3, 20, 0, 255, Local_u16Distance), 0);
							}
							else
							{
							}
						}
						else
						{
							/**/
						}
					}
					else
					{
					}
					// uart choose menu
					Local_s16UartReceivedVal = UART_voidReceive();

					if (Local_s16UartReceivedVal != -1)
					{
						// UART_voidTransmit(Local_s16UartReceivedVal);
						// UART_voidTransmit('\r');
						// UART_voidTransmit('\n');
						switch (Local_s16UartReceivedVal)
						{
							/*door state*/
						case 97: // a
								 //  open the door
							if (Global_u8DoorStateFlag == 180)
							{
								Global_u8DoorStateFlag = 0;
								/*solving conflict*/
								BUZZER_voidKill(TIMER1B);
								Global_u8BuzzerState = 0;
								Global_u8FanControl = 0;

								SVM_init(TIMER1A);
								for (Local_u8Iter = 0; Local_u8Iter < 20; Local_u8Iter++)
								{
									SVM_voidRotateTo(TIMER1A, Global_u8DoorStateFlag);
									_delay_ms(20);
								}
								SVM_voidStop(TIMER1A);

								// EEPROM_u8WriteDataByte(LOC_DOOR_ADDRESS, Global_u8DoorStateFlag);
								//// EEPROM_u8WriteDataByte(LOC_BUZZER_ADDRESS, Global_u8BuzzerState);
								// EEPROM_u8WriteDataByte(LOC_FAN_ADDRESS, Global_u8FanControl);
							}
							else
							{
								/*door already open*/
							}
							break;
						case 98: // b
							// close the door
							if (Global_u8DoorStateFlag == 0)
							{
								Global_u8DoorStateFlag = 180;
								/*solving conflict*/
								BUZZER_voidKill(TIMER1B);
								Global_u8BuzzerState = 0;
								Global_u8FanControl = 0;
								SVM_init(TIMER1A);
								for (Local_u8Iter = 0; Local_u8Iter < 20; Local_u8Iter++)
								{
									SVM_voidRotateTo(TIMER1A, Global_u8DoorStateFlag);
									_delay_ms(20);
								}
								SVM_voidStop(TIMER1A);
								// EEPROM_u8WriteDataByte(LOC_DOOR_ADDRESS, Global_u8DoorStateFlag);
								// EEPROM_u8WriteDataByte(LOC_BUZZER_ADDRESS, Global_u8BuzzerState);
								// EEPROM_u8WriteDataByte(LOC_FAN_ADDRESS, Global_u8FanControl);
							}
							else
							{
								/*door already close*/
							}
							break;
						/*end door state*/
						/*led control*/
						case 99: // c
							// turn on led
							if (Global_u8LedControl != 1)
							{
								Global_u8LedControl = 1;
								TIMER_voidChangCOM_Mode(TIMER0, TIMER_COM_NORMAL); // turn off ldr effect
								EXTI_u8IntDisable(INT2);						   // turn of pir effect
								LED_u8SetON(&Global_LedBlue);
								UART_VoidPrintln("led on");
								// EEPROM_u8WriteDataByte(LOC_LED_ADDRESS, Global_u8LedControl);
							}
							else
							{
								/*led already on*/
							}
							break;
						case 100: // d
							// turn off led
							if (Global_u8LedControl != 0)
							{
								Global_u8LedControl = 0;
								TIMER_voidChangCOM_Mode(TIMER0, TIMER_COM_NORMAL); // turn off ldr effect
								EXTI_u8IntDisable(INT2);						   // turn of pir effect
								LED_u8SetOFF(&Global_LedBlue);
								UART_VoidPrintln("led of");
								// EEPROM_u8WriteDataByte(LOC_LED_ADDRESS, Global_u8LedControl);
							}
							else
							{
								/*led already off*/
							}
							break;
						case 101: // e
							// LDR control led
							if (Global_u8LedControl != 2)
							{
								Global_u8LedControl = 2;
								EXTI_u8IntDisable(INT2); // turn of pir effect
								LED_u8SetOFF(&Global_LedBlue);

								GLobal_u8intensity_led_to_on = MAP(0, 8, 0, 255, GLobal_u8intensity_led_to_on);
								TIMER_voidStart_PWM(TIMER0, GLobal_u8intensity_led_to_on, 0);
								TIMER_voidChangCOM_Mode(TIMER0, TIMER_COM_CLEAR);
								// EEPROM_u8WriteDataByte(LOC_LED_ADDRESS, Global_u8LedControl);
							}
							else
							{
								/*led already control by LDR*/
							}
							break;
						case 102: // f
							// PIR control led
							if (Global_u8LedControl != 3)
							{
								Global_u8LedControl = 3;
								LED_u8SetOFF(&Global_LedBlue);
								TIMER_voidChangCOM_Mode(TIMER0, TIMER_COM_NORMAL); // turn off ldr effect
								EXTI_u8IntEnable(INT2);							   // turn of pir effect

								// EEPROM_u8WriteDataByte(LOC_LED_ADDRESS, Global_u8LedControl);
							}
							else
							{
								/*led already control by PIR*/
							}
							break;
						/*end led control*/
						/*Fan control*/
						case 103: // g
								  //  turn off fan
							if (Global_u8FanControl != 0)
							{
								Global_u8FanControl = 0;
								TIMER_voidChangCOM_Mode(TIMER2, TIMER_COM_NORMAL); // turn off sr04 effect
								DCM_voidStop(&Local_TESY.TE_DCMotor);
								// EEPROM_u8WriteDataByte(LOC_FAN_ADDRESS, Global_u8FanControl);
							}
							else
							{
								/*fan already off*/
							}
							break;
						case 104: // h
							// turn on fan
							if (Global_u8FanControl != 1)
							{
								Global_u8FanControl = 1;
								TIMER_voidChangCOM_Mode(TIMER2, TIMER_COM_NORMAL); // turn off sr04 effect
								DCM_voidRotateCCW(&Local_TESY.TE_DCMotor);
								// EEPROM_u8WriteDataByte(LOC_FAN_ADDRESS, Global_u8FanControl);
							}
							else
							{
								/*fan already on*/
							}
							break;
						case 105: // i
							// ultrasonic control fan
							if (Global_u8FanControl != 2)
							{
								BUZZER_voidKill(TIMER1B);
								SVM_voidStop(TIMER1A);
								TIMER_voidChangCOM_Mode(TIMER2, TIMER_COM_CLEAR); // turn on sr04 effect
								TIMER_voidChangWGM_Mode(TIMER2, TIMER0_2WGM_FAST_PWM);
								TIMER_voidChangWGM_Mode(TIMER1, TIMER_WGM_Normal);
								Global_u8FanControl = 2;
								Global_u8BuzzerState = 0;
								// EEPROM_u8WriteDataByte(LOC_FAN_ADDRESS, Global_u8FanControl);
							}
							else
							{
								/*fan already control by ultrasonic*/
							}
							break;
						case 106: // j
							// temperature control fan
							if (Global_u8FanControl != 3)
							{
								Global_u8FanControl = 3;
								TIMER_voidChangCOM_Mode(TIMER2, TIMER_COM_NORMAL); // turn off sr04 effect
								DCM_voidStop(&Local_TESY.TE_DCMotor);
								// EEPROM_u8WriteDataByte(LOC_FAN_ADDRESS, Global_u8FanControl);
							}
							else
							{
								/*fan already control by temperature*/
							}
							break;
							/*end fan control*/
							/*buzzer control*/
						case 107: // k
							// play music

							Global_u8BuzzerState = 1;
							SVM_voidStop(TIMER1A);
							TIMER_voidChangCOM_Mode(TIMER2, TIMER_COM_NORMAL); // turn off sr04 effect
							DCM_voidStop(&Local_TESY.TE_DCMotor);
							Global_u8FanControl = 0;
							BUZZER_voidKill(TIMER1B);
							BUZZER_voidInit(TIMER1B);
							BUZZER_U8PlayMusic(TIMER1B, melody, delay_duration, 49);

							// EEPROM_u8WriteDataByte(LOC_BUZZER_ADDRESS, Global_u8BuzzerState);
							// buzzer
							break;
						case 108: // l
							// stop music
							Global_u8BuzzerState = 0;
							BUZZER_voidKill(TIMER1B);
							// EEPROM_u8WriteDataByte(LOC_BUZZER_ADDRESS, Global_u8BuzzerState);
							break;
							/*end buzzer control*/
						// get temperature
						case 121: // y python code
							UART_VoidPrintInt(Local_TESY.TE_LM.Temprature);
							break;
						case 122: // z
							UART_VoidPrintInt(Local_TESY.TE_LDR.LightLevel);
							_delay_ms(10);
							break;
						default:
							break;
						}
					}
					else
					{
						/**/
					}
				}
			}
			/*login failed */
			else if ((Local_u8LoginState == LOGIN_ID_FAILD) || (Local_u8LoginState == LOGIN_PASS_FAILD))
			{
				CLCD_VoidSendCommand(CLCD_CLEAR_CMD);
				CLCD_voidGoToXY(0u, 0u);
				CLCD_VoidPrintChars("LOG IN Failed");
				_delay_ms(2000);
				CLCD_VoidSendCommand(CLCD_CLEAR_CMD);
			}
			else
			{
				/*do nothing*/
			}
		}
	}
}

void INT0ISR(void)
{
	if (Global_u8INT0Flag == 0){
		Global_u8INT0Flag = 2;
		
	}
	else if (Global_u8INT0Flag == 2){
		DIO_u8_SetPinVal(DIO_PORTC,DIO_PIN4,DIO_PIN_LOW);
		Global_u8INT0Flag = 1;
	}
	else
		Global_u8INT0Flag = 0;
}

void INT2ISR(void)
{
	static uint8 Local_u8flag = 0;
	if (Local_u8flag == 0)
	{
		EXTI_u8SetSenceCtrl(INT2, FALLING_EDGE); // next interrupt will be on falling edge
		LED_u8SetON(&Global_LedBlue);			 // turn on light
		Local_u8flag++;							 // change the flag
	}
	else
	{
		EXTI_u8SetSenceCtrl(INT2, RISING_EDGE); // next interrupt will be on rising edge
		LED_u8SetOFF(&Global_LedBlue);			// turn off light

		Local_u8flag = 0; // reset the flag
	}
}
