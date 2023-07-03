#ifndef DIO_INTERFACE
#define DIO_INTERFACE
#include "../../libraries/STD_TYPES_H.h"
typedef enum DIO_port_t{
    DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD
}DIO_port_t;

typedef enum DIO_pin_t{
    DIO_PIN0,DIO_PIN1,DIO_PIN2,DIO_PIN3,
    DIO_PIN4,DIO_PIN5,DIO_PIN6,DIO_PIN7
}DIO_pin_t;

typedef enum DIO_pinDir_t{
    DIO_PIN_INPUT,DIO_PIN_OUTPUT
}DIO_pinDir_t;

typedef enum DIO_pinVal_t{
    DIO_PIN_LOW, DIO_PIN_HIGH
}DIO_pinVal_t;


/// @brief specify one given pin from given port to make it output or input
/// @param copy_port port number choose from port enum
/// @param copy_pinNum pin number choose from pin enum
/// @param copy_pinDir input or output voltage
/// @return error state if everything is ok will return OK 
uint8 DIO_u8_SetPinDir(DIO_port_t copy_port, DIO_pin_t copy_pinNum, DIO_pinDir_t copy_pinDir);
/// @brief set direction for the port
/// @param copy_port port number choose from port enum
/// @param copy_PortDir 8bits integer number for port direction 
/// @return error state if everything is ok will return OK 
uint8 DIO_u8_SetPortDir(DIO_port_t copy_port,  uint8 copy_PortDir);

/// @brief specify one given pin from given port to make it Low or high
/// @param copy_port port number choose from port enum
/// @param copy_pinNum pin number choose from pin enum
/// @param copy_pinVal choose value  from DIO_pinVal_t low for 0volt and high for 5volt
/// @return error state if everything is ok will return OK 
uint8 DIO_u8_SetPinVal(DIO_port_t copy_port, DIO_pin_t copy_pinNum, DIO_pinVal_t copy_pinVal);
/// @brief set value for the port
/// @param copy_port port number choose from port enum
/// @param copy_PortVal pin number choose from pin enum
/// @return error state if everything is ok will return OK 
uint8 DIO_u8_SetPortVal(DIO_port_t copy_port,  uint8 copy_PortVal);

/// @brief get pin value 
/// @param copy_port port number choose from port enum
/// @param copy_pinNum pin number choose from pin enum
/// @param copy_pinVal address of unsigned 8-bits to store the value of choosen bit
/// @return error state if everything is ok will return OK 
uint8 DIO_u8_GetPinVal(DIO_port_t copy_port, DIO_pin_t copy_pinNum, DIO_pinVal_t *copy_pinVal);
/// @brief get pin direction 
/// @param copy_port port number choose from port enum
/// @param copy_pinNum pin number choose from pin enum
/// @param copy_pinVal address of unsigned 8-bits to store the value of choosen bit
/// @return error state if everything is ok will return OK  
uint8 DIO_u8_GetPinDir(DIO_port_t copy_port, DIO_pin_t copy_pinNum, DIO_pinDir_t *copy_pinDir);

/// @brief toggle the value of given pin
/// @param copy_port port number choose from port enum
/// @param copy_pinNum pin number choose from pin enum
/// @return error state if everything is ok will return OK 
uint8 DIO_u8_TogglePinVal(DIO_port_t copy_port, DIO_pin_t copy_pinNum);


#endif
