
#include "../../libraries/STD_TYPES_H.h"
#include "../../libraries/ErrType.h"
#include "../../libraries/MAP.h"
#include "../../0-MCAL/1-DIO/DIO_interface.h"
#include "../../0-MCAL/5-ADC/ADC_interface.h"
#include "LM_interface.h"



uint8 LM_u8GetTemp(LM_Config_t* reference_LM){
    uint8 Local_u8ErrorState = OK;

    if(reference_LM != NULL ){
    	uint16 Local_u16Reading ;
    	ADC_u8StartConverstionSync(reference_LM->AnalogChannel_DigitalSignal,&Local_u16Reading);
		uint16 Local_u16VoltageReading = (uint16)MAP(0u,DIGITAL_SIGNAL_RES,0u,reference_LM->max_volt,(sint32)Local_u16Reading);
        //return temperature in Celsius
        reference_LM->Temprature =  Local_u16VoltageReading/10 ;
    }else{
        Local_u8ErrorState = NULL_PTR;
    }
    return Local_u8ErrorState;
}

uint8 LM_u8GetTempFromDigSignal(LM_Config_t* reference_LM){
    uint8 Local_u8ErrorState = OK;

    if(reference_LM != NULL ){
		uint16 Local_u16VoltageReading = (uint16)MAP(0u,DIGITAL_SIGNAL_RES,0u,reference_LM->max_volt,(sint32)reference_LM->AnalogChannel_DigitalSignal);

        //return temperature in Celsius
        reference_LM->Temprature =  Local_u16VoltageReading/10 ;
    }else{
        Local_u8ErrorState = NULL_PTR;
    }
    return Local_u8ErrorState;
}


//convert Celsius to Fahrenheit
uint16 LM_u16convertToFahrenheit(uint8 copy_u8CelsiusDeggree){

    return ((((uint16)copy_u8CelsiusDeggree*9)/5)+32);

}
