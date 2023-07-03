#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

typedef enum LED_Activitype_t{
    LED_ACTIVE_HIGH,LED_ACTIVE_LOW
}LED_Activitype_t;

typedef struct LED_Config_t
{
    LED_Activitype_t Activitype;
    DIO_port_t port;
    DIO_pin_t Pin;
}LED_Config_t;



/// @brief set led on using activity type
/// @param copy_LED_Object address of led object
/// @return error state if everything is ok will return OK
uint8 LED_u8SetON(const LED_Config_t* copy_LED_Object);

/// @brief set led on using activity type
/// @param copy_LED_Object address of led object
/// @return error state if everything is ok will return OK
uint8 LED_u8SetOFF(const LED_Config_t* copy_LED_Object);

/// @brief toggle led state
/// @param copy_LED_Object address of led object
/// @return error state if everything is ok will return OK
uint8 LED_u8Toggle(const LED_Config_t* copy_LED_Object);
#endif
