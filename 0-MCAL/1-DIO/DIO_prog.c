
//#include "../../libraries/STD_TYPES_H.h"
#include "../../libraries/BIT_MATH.h"
#include "../../libraries/ErrType.h"
#include "DIO_reg.h"
#include "DIO_interface.h"





uint8 DIO_u8_SetPinDir(DIO_port_t copy_port, DIO_pin_t copy_pinNum, DIO_pinDir_t copy_pinDir){
    uint8 Local_u8ErrorState = OK;
    if((copy_pinNum >= DIO_PIN0)  && (copy_pinNum<=DIO_PIN7)){

        if(copy_pinDir == DIO_PIN_INPUT){
            switch (copy_port)
            {
            case DIO_PORTA : CLS_BIT(DDRA,copy_pinNum); break;
            case DIO_PORTB : CLS_BIT(DDRB,copy_pinNum); break;
            case DIO_PORTC : CLS_BIT(DDRC,copy_pinNum); break;
            case DIO_PORTD : CLS_BIT(DDRD,copy_pinNum); break;
            
            default: Local_u8ErrorState = NOK;  break;
            }
        }   
        else if(copy_pinDir == DIO_PIN_OUTPUT){
             switch (copy_port)
            {
            case DIO_PORTA : SET_BIT(DDRA,copy_pinNum); break;
            case DIO_PORTB : SET_BIT(DDRB,copy_pinNum); break;
            case DIO_PORTC : SET_BIT(DDRC,copy_pinNum); break;
            case DIO_PORTD : SET_BIT(DDRD,copy_pinNum); break;
            
            default: Local_u8ErrorState = NOK;  break;
            }
        }else
        Local_u8ErrorState = NOK;
    }else 
    Local_u8ErrorState = NOK;
    return Local_u8ErrorState;

}
uint8 DIO_u8_SetPortDir(DIO_port_t copy_port,  uint8 copy_pinDir){
    uint8 Local_u8ErrorState = OK;
        //if(copy_pinDir == DIO_PIN_INPUT){
            switch (copy_port)
            {
            case DIO_PORTA :DDRA = copy_pinDir; break;
            case DIO_PORTB :DDRB = copy_pinDir; break;
            case DIO_PORTC :DDRC = copy_pinDir; break;
            case DIO_PORTD :DDRD = copy_pinDir; break;
            
            default: Local_u8ErrorState = NOK;  break;
            }
        
        
    
    return Local_u8ErrorState;

}

uint8 DIO_u8_SetPinVal(DIO_port_t copy_port, DIO_pin_t copy_pinNum, DIO_pinVal_t copy_pinVal){
uint8 Local_u8ErrorState = OK;
    if((copy_pinNum >= DIO_PIN0)  && (copy_pinNum<=DIO_PIN7)){

        if(copy_pinVal == DIO_PIN_LOW){
            switch (copy_port)
            {
            case DIO_PORTA : CLS_BIT(PORTA,copy_pinNum); break;
            case DIO_PORTB : CLS_BIT(PORTB,copy_pinNum); break;
            case DIO_PORTC : CLS_BIT(PORTC,copy_pinNum); break;
            case DIO_PORTD : CLS_BIT(PORTD,copy_pinNum); break;
            
            default: Local_u8ErrorState = NOK;  break;
            }
        }   
        else if(copy_pinVal == DIO_PIN_HIGH){
             switch (copy_port)
            {
            case DIO_PORTA : SET_BIT(PORTA,copy_pinNum); break;
            case DIO_PORTB : SET_BIT(PORTB,copy_pinNum); break;
            case DIO_PORTC : SET_BIT(PORTC,copy_pinNum); break;
            case DIO_PORTD : SET_BIT(PORTD,copy_pinNum); break;
            
            default: Local_u8ErrorState = NOK;  break;
            }
        }else
        Local_u8ErrorState = NOK;
    }else 
    Local_u8ErrorState = NOK;
    return Local_u8ErrorState;

}
uint8 DIO_u8_SetPortVal(DIO_port_t copy_port,  uint8 copy_pinVal){
    uint8 Local_u8ErrorState = OK;
        //if(copy_pinVal == DIO_PIN_LOW){
            switch (copy_port)
            {
            case DIO_PORTA :PORTA = copy_pinVal; break;
            case DIO_PORTB :PORTB = copy_pinVal; break;
            case DIO_PORTC :PORTC = copy_pinVal; break;
            case DIO_PORTD :PORTD = copy_pinVal; break;
            
            default: Local_u8ErrorState = NOK;  break;
            }
       
    
    return Local_u8ErrorState;

}

uint8 DIO_u8_GetPinVal(DIO_port_t copy_port, DIO_pin_t copy_pinNum, DIO_pinVal_t *copy_pinVal){
    uint8 Local_u8ErrorState = OK;
    if(copy_pinVal !=NULL){
        if((copy_pinNum >= DIO_PIN0)  && (copy_pinNum<=DIO_PIN7)){
            switch (copy_port)
            {
            case DIO_PORTA : *copy_pinVal = GET_BIT(PINA,copy_pinNum); break;
            case DIO_PORTB : *copy_pinVal = GET_BIT(PINB,copy_pinNum); break;
            case DIO_PORTC : *copy_pinVal = GET_BIT(PINC,copy_pinNum); break;
            case DIO_PORTD : *copy_pinVal = GET_BIT(PIND,copy_pinNum); break;
            
            default: Local_u8ErrorState = NOK;  break;
            }
            
        }else 
            Local_u8ErrorState = NOK;
    }
    else
        Local_u8ErrorState = NULL_PTR;
    return Local_u8ErrorState;
}

uint8 DIO_u8_GetPinDir(DIO_port_t copy_port, DIO_pin_t copy_pinNum, DIO_pinDir_t *copy_pinDir){
    uint8 Local_u8ErrorState = OK;
    if(copy_pinDir !=NULL){
        if((copy_pinNum >= DIO_PIN0)  && (copy_pinNum<=DIO_PIN7)){
            switch (copy_port)
            {
            case DIO_PORTA : *copy_pinDir = GET_BIT(DDRA,copy_pinNum); break;
            case DIO_PORTB : *copy_pinDir = GET_BIT(DDRB,copy_pinNum); break;
            case DIO_PORTC : *copy_pinDir = GET_BIT(DDRC,copy_pinNum); break;
            case DIO_PORTD : *copy_pinDir = GET_BIT(DDRD,copy_pinNum); break;

            default: Local_u8ErrorState = NOK;  break;
            }

        }else
            Local_u8ErrorState = NOK;
    }
    else
        Local_u8ErrorState = NULL_PTR;
    return Local_u8ErrorState;
}
uint8 DIO_u8_TogglePinVal(DIO_port_t copy_port, DIO_pin_t copy_pinNum){
    uint8 Local_u8ErrorState = OK;
        if((copy_pinNum >= DIO_PIN0)  && (copy_pinNum<=DIO_PIN7)){
            switch (copy_port)
            {
            case DIO_PORTA :  TOG_BIT(PORTA,copy_pinNum); break;
            case DIO_PORTB :  TOG_BIT(PORTB,copy_pinNum); break;
            case DIO_PORTC :  TOG_BIT(PORTC,copy_pinNum); break;
            case DIO_PORTD :  TOG_BIT(PORTD,copy_pinNum); break;

            default: Local_u8ErrorState = NOK;  break;
            }

        }else
            Local_u8ErrorState = NOK;
    return Local_u8ErrorState;
}

uint8 DIO_u8_PinPullUp(DIO_port_t copy_port, DIO_pin_t copy_pinNum){
    uint8 Local_u8ErrorState = OK;
    Local_u8ErrorState = DIO_u8_SetPinDir(copy_port,copy_pinNum,DIO_PIN_INPUT);
    if(Local_u8ErrorState == OK){
        Local_u8ErrorState = DIO_u8_SetPinVal(copy_port,copy_pinNum,DIO_PIN_HIGH);
    }
    return Local_u8ErrorState;
}
