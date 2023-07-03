#ifndef TIMER_CFG_H
#define TIMER_CFG_H
/*
* configure TIMER0 Waveform Generation Mode, options : 1-TIMER0_2WGM_NORMAL
*                                                    2-TIMER0_2WGM_PWM  
*                                                    3-TIMER0_2WGM_CTC
*                                                    4-TIMER0_2WGM_FAST_PWM
*/
#define TIMER_u8TI0_WGM              TIMER0_2WGM_FAST_PWM
#define TIMER_u8TI2_WGM              TIMER0_2WGM_NORMAL

/*configure TIMER1 Waveform Generation Mode chose mode number [0:14] page 107*/
#define TIMER_u8TI1_WGM              TIMER_WGM_Normal
/*
* configure TIMER0 Compare Match Output Mode, options : 1-TIMER_COM_NORMAL
*                                                    2-TIMER_COM_TOGGLE  
*                                                    3-TIMER_COM_CLEAR
*                                                    4-TIMER_COM_SET
*                                                    5-TIMER_COM_RESERVED
*/
#define TIMER_u8TI0_COM             TIMER_COM_NORMAL
#define TIMER_u8TI1A_COM            TIMER_COM_NORMAL
#define TIMER_u8TI1B_COM            TIMER_COM_NORMAL
#define TIMER_u8TI2_COM             TIMER_COM_NORMAL
/* 
* configure TIMER0 the clock source to be used: 1-TIMER_NO_CLK
*                                           2-TIMER_NO_PS
*                                           3-TIMER_PS_8
*                                           4-TIMER_PS_64
*                                           5-TIMER_PS_256
*                                           6-TIMER_PS_1024
*                                           7-TIMER_EXT_CLK_FALLING_EDGE
*                                           8-TIMER_EXT_CLK_RISING_EDGE
*/
#define TIMER_u8TI0_CLK              TIMER_PS_1024
#define TIMER_u8TI1_CLK              TIMER_PS_8
#define TIMER_u8TI2_CLK              TIMER_PS_1024
/* 
* configure ICU Trigger source: 1-ICU_FALLING_EDGE
*                                           2-ICU_RISING_EDGE
*/
#define ICU_u8TriggerSrc        ICU_RISING_EDGE



#endif
