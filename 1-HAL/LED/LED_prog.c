
#include "../../libraries/STD_TYPES_H.h"
#include "../../libraries/ErrType.h"
#include "../../0-MCAL/1-DIO/DIO_interface.h"

#include "LED_interface.h"

uint8 LED_u8SetON(const LED_Config_t* copy_LED_Object){
	uint8 Local_u8ErrorState = OK;
	if(copy_LED_Object != NULL){
		if(copy_LED_Object->Activitype== LED_ACTIVE_HIGH){
			DIO_u8_SetPinVal(copy_LED_Object->port,copy_LED_Object->Pin,DIO_PIN_HIGH);
		}else if(copy_LED_Object->Activitype== LED_ACTIVE_LOW){
			DIO_u8_SetPinVal(copy_LED_Object->port,copy_LED_Object->Pin,DIO_PIN_LOW);
		}else{
			Local_u8ErrorState = NOK;
		}
	}else
		Local_u8ErrorState = NULL_PTR;
	return Local_u8ErrorState;
}


uint8 LED_u8SetOFF(const LED_Config_t* copy_LED_Object){
	uint8 Local_u8ErrorState = OK;
	if(copy_LED_Object != NULL){
		if(copy_LED_Object->Activitype== LED_ACTIVE_HIGH){
			DIO_u8_SetPinVal(copy_LED_Object->port,copy_LED_Object->Pin,DIO_PIN_LOW);
		}else if(copy_LED_Object->Activitype== LED_ACTIVE_LOW){
			DIO_u8_SetPinVal(copy_LED_Object->port,copy_LED_Object->Pin,DIO_PIN_HIGH);
		}else{
			Local_u8ErrorState = NOK;
		}
	}else
		Local_u8ErrorState = NULL_PTR;
	return Local_u8ErrorState;
}
uint8 LED_u8Toggle(const LED_Config_t* copy_LED_Object){
	uint8 Local_u8ErrorState = OK;
	if(copy_LED_Object != NULL){
		DIO_u8_TogglePinVal(copy_LED_Object->port,copy_LED_Object->Pin);
	}else
		Local_u8ErrorState = NULL_PTR;
	return Local_u8ErrorState;
}
