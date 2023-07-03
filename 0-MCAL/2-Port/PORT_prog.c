
#include "../../libraries/BIT_MATH.h"
#include "../../libraries/ErrType.h"
#include "../../libraries/STD_TYPES_H.h"
#include "./PORT_interface.h"
#include "PORT_reg.h"
#include "PORT_prv.h"
#include "PORT_cfg.h"


// #include "../DIO_interface.h"


void Port_voidInit(){

    DDRA = PORTA_DIR;
    DDRB = PORTB_DIR;
    DDRC = PORTC_DIR;
    DDRD = PORTD_DIR;

    PORTA = PORTA_INITVAL;
    PORTB = PORTB_INITVAL;
    PORTC = PORTC_INITVAL;
    PORTD = PORTD_INITVAL;
}




