#ifndef SVM_INTERFACE_H
#define SVM_INTERFACE_H
#include "../../0-MCAL/6-TIMER/TIMER_interface.h"
 
/// @brief initialize [TIMER1A,TIMER1B] COM to clear on compare and WGM to TIMER_WGM_PWM_FAST_ICR1
/// @param copy_TINum choose between TIMER1A and TIMER1B
void SVM_init(TIMER_TINum_t copy_TINum);

/// @brief rotate servo motor to given degree **it will automatic stop any service used in T1S
/// @param copy_u8Angel angle to rotate to [0:180]
/// @param copy_TINum choose between TIMER1A and TIMER1B
void SVM_voidRotateTo(TIMER_TINum_t copy_TINum,uint8 copy_u8Angel);

/// @brief reset timer1 COM to normal on compare and WGM to TIMER_WGM_NORMAL
/// @param copy_TINum choose between TIMER1A and TIMER1B
void SVM_voidStop(TIMER_TINum_t copy_TINum);

#endif

