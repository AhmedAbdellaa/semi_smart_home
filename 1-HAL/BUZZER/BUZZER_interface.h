#ifndef BUZZER_INTERFACE_H
#define BUZZER_INTERFACE_H

#define BUZZER_TICK_TIME  0.5


/// @brief initialize [TIMER1A or TIMER1B] COM to clear on compare and WGM to TIMER_WGM_PWM_FAST_ICR1 
/// @param copy_TINum choose between TIMER1A and TIMER1B
void BUZZER_voidInit(TIMER_TINum_t copy_TINum);

/// @brief it will start tone for given frequency and time **make sure no thing use timer1 at same time and choose prscaler suitable for tick time above**
/// @param copy_TINum choose between TIMER1A and TIMER1B
/// @param copy_u16Frequency the frequency of the tone in hertz
/// @param copy_u16duration the duration of the tone in milliseconds
void BUZZER_voidTone(TIMER_TINum_t copy_TINum, uint16 copy_u16Frequency,uint16 copy_u16duration);

/// @brief reset timer1 COM to normal on compare and WGM to TIMER_WGM_NORMAL
/// @param copy_TINum choose between TIMER1A and TIMER1B
void BUZZER_voidNoTone(TIMER_TINum_t copy_TINum);

/// @brief play multi tone in background
/// @param copy_TINum choose between TIMER1A and TIMER1B
/// @param ref_pu16FrequencyList list of frequency of the tone in hertz to play one after another
/// @param ref_pu16durationList list of duration of the tone in milliseconds to play one after another
/// @param Copy_u8ListLength list length
/// @return 
uint8 BUZZER_U8PlayMusic(TIMER_TINum_t copy_TINum, uint16 *ref_pu16FrequencyList, uint16 *ref_u16DelayDuration, uint8 Copy_u8ListLength);

void BUZZER_voidKill(TIMER_TINum_t copy_TINum);
#endif
