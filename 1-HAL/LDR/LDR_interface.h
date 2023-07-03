#ifndef LDR_INTERFACE_H
#define LDR_INTERFACE_H

#define DIGITAL_SIGNAL_RES  1023ul
typedef struct LDR_Config_t
{
	uint16 AnalogChannel_DigitalSignal;
	uint16 max_volt;
    uint16 LightLevel;
}LDR_Config_t;

/// @brief get light level for given channel by using adc conversion sync and store result in LightLevel of ldr object
/// @param reference_LDR address of LDR object
/// @return error state if everything is ok will return OK
uint8 LDR_u8GetLighlevel(LDR_Config_t* reference_LDR);

/// @brief get light level for given channel by using digital signal passed in ldr object instead of channel and store result in LightLevel of ldr object
/// @param reference_LDR address of LDR object
/// @return error state if everything is ok will return OK
uint8 LDR_u8GetLLFromDigSignal(LDR_Config_t* reference_LDR);
#endif
