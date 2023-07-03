
#include "../../libraries/STD_TYPES_H.h"
#include "../../libraries/ErrType.h"
#include "../../0-MCAL/1-DIO/DIO_interface.h"
#include "DCM_interface.h"

void DCM_voidRotateCW(DCM_Config_t* reference_motor ){
    DIO_u8_SetPinVal(reference_motor->port, reference_motor->Pin0, DIO_PIN_LOW);
    DIO_u8_SetPinVal(reference_motor->port, reference_motor->Pin1, DIO_PIN_HIGH);
}
void DCM_voidRotateCCW(DCM_Config_t* reference_motor ){
    DIO_u8_SetPinVal(reference_motor->port, reference_motor->Pin1, DIO_PIN_LOW);
    DIO_u8_SetPinVal(reference_motor->port, reference_motor->Pin0, DIO_PIN_HIGH);
}
void DCM_voidStop(DCM_Config_t* reference_motor ){
    DIO_u8_SetPinVal(reference_motor->port, reference_motor->Pin0, DIO_PIN_LOW);
    DIO_u8_SetPinVal(reference_motor->port, reference_motor->Pin1, DIO_PIN_LOW);
}

