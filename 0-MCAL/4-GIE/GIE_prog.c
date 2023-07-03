
#include "../../libraries/BIT_MATH.h"
#include "../../libraries/ErrType.h"
#include "../../libraries/STD_TYPES_H.h"
#include "../4-GIE/GIE_interface.h"
#include "../4-GIE/GIE_reg.h"
void GIE_voidEnableGlobal(){
    // SET_BIT(SREG,SREG_I);
    __asm volatile ("SEI");
}
void GIE_voidDisabledGlobal(){
    // cls_BIT(SREG,SREG_I);
    __asm volatile ("CLI");
}
