#ifndef LM_INTERFACE_H
#define LM_INTERFACE_H

#define DIGITAL_SIGNAL_RES  1023ul
typedef struct LM_Config_t
{
    uint16 AnalogChannel_DigitalSignal;
    uint16 max_volt;
    uint8 Temprature;
}LM_Config_t;

/// @brief get light level for given channel by using adc conversion sync and store result in LightLevel of LM object
/// @param reference_LM address of LM object
/// @return error state if everything is ok will return OK
uint8 LM_u8GetTemp(LM_Config_t* reference_LM);

/// @brief get light level for given channel by using digital signal passed in LM object instead of channel and store result in LightLevel of LM object
/// @param reference_LM address of LM object
/// @return error state if everything is ok will return OK
uint8 LM_u8GetTempFromDigSignal(LM_Config_t* reference_LM);

/// @brief convert given temperature degree from celsius to Fahrenheit 
/// @param copy_u8CelsiusDegree degree in celsius
/// @return Fahrenheit degree
uint16 LM_u16convertToFahrenheit(uint8 copy_u8CelsiusDegree);

#endif
