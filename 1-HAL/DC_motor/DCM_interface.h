#ifndef DCM_INTERFACE_H
#define DCM_INTERFACE_H


typedef struct DCM_Config_t
{
    DIO_port_t port;
    DIO_pin_t Pin0;
    DIO_pin_t Pin1;
}DCM_Config_t;

/// @brief rotate given motor clock wise by set second pin to high
/// @param reference_motor address of motor object
void DCM_voidRotateCW(DCM_Config_t* reference_motor );
/// @brief rotate given motor counter clock wise by set first pin to high
/// @param reference_motor address of motor object
void DCM_voidRotateCCW(DCM_Config_t* reference_motor );
/// @brief stop given motor by set two pins to Low
/// @param reference_motor address of motor object
void DCM_voidStop(DCM_Config_t* reference_motor );

#endif

