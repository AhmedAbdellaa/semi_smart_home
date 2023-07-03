#ifndef BIT_MATH
#define BIT_MATH

#define SET_BIT(var,bit_num)  ((var) |= (1<<(bit_num)))
#define CLS_BIT(var,bit_num)  ((var) &= ((1<<(bit_num))^-1))
#define TOG_BIT(var,bit_num)  ((var) ^= (1<<(bit_num)))
#define GET_BIT(var,bit_num)  (((var) & (1<<(bit_num)) )?1 :0)
#define CLR_BIT(VAR,BIT_NUM)  ((VAR)&= (~(1<<(BIT_NUM))))

#endif