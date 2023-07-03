#ifndef SR04_INTERFACE_H
#define SR04_INTERFACE_H

#define TICK_TIME  0.5

typedef struct SR04_TriggerPin
{
    DIO_port_t trigPort;
    DIO_pin_t   trigPin;
}SR04_TriggerPin;

/// @brief get time of trigger bin of ultrasonic timer1 and icu should be initialize before call it and set prescaler to 1024 or change the tick time
/// @return time in micro seconds
uint32 SR04_u32ReadTime(SR04_TriggerPin* ref_trigger);

/// @brief get distance from time
/// @param copy_s32Time time want to convert to distance 
/// @return distance in cm
uint16 SR04_u16GetDistance(sint32 copy_s32Time);

#endif
