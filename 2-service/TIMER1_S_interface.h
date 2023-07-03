#ifndef T1S_INTERFACE
#define T1S_INTERFACE
#include "../0-MCAL/6-TIMER/TIMER_interface.h"
#define IDLE    1u
#define BUSY    2U
#define T1S_TICK_TIME 0.5
#define Max_time 262144
/// @brief measure timer of pwm signal (period time and duty cycle) **timer1 must be initalized
/// @param reference_u16DutyCycle address of u16 value to return duty value in it
/// @param reference_u16PeriodTime address of u16 value to return cycle value in it 
/// @return error state return OK if everything is okay
uint8 T1S_voidPWM_Measure(uint16* reference_u16DutyCycle ,uint16* reference_u16PeriodTime);

/// @brief schedule timer for do event every given time **timer1 must be initalized
/// @param copy_u32Time_ms time in milli seconds
/// @param copy_u16Periodic how many time repeat it  put -1 for infinity repeat ,1 no repeat
/// @param copy_pvFuncPtr address to function to execute 
/// @return error state return OK if everything is okay
uint8 T1S_voidScheduleMS(TIMER_TINum_t copy_TINum,uint32 copy_u32Time_ms, sint16 copy_s16Periodic, void (*copy_pvFuncPtr)(void));

/// @brief start pwm wave for given time must adjust com to clear and wgm to 14 before start
/// @param copy_u32CycleTime time of cycle in microseconds
/// @param copy_f64Duty percent of duty time from cycle time
/// @return error state return OK if everything is okay
uint8 T1S_voidStartPwm(TIMER_TINum_t copy_TINum,uint32 copy_u32CycleTime, f64 copy_f64Duty);

/// @brief stop pwm put busy flag to idle
void T1S_voidStopPwm();
#endif
