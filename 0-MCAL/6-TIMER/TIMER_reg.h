#ifndef TIMER_REG
#define TIMER_REG

// Timer/Counter Interrupt Mask Register
#define TIMSK *((volatile uint8*)0x59)
#define TIMSK_OCIE2 7U  //Timer/Counter2 Output Compare Match Interrupt Enable
#define TIMSK_TOIE2 6U  //Timer/Counter2 Overflow Interrupt Enable

#define TIMSK_OCIE0 1U  //Timer/Counter0 Output Compare Match Interrupt Enable
#define TIMSK_TOIE0 0U  //Timer/Counter0 Overflow Interrupt Enable

#define TIMSK_OCIE1A    4U  //Timer/Counter1 Output Compare Match Interrupt Enable
#define TIMSK_OCIE1B    3U  //Timer/Counter1 Output Compare Match Interrupt Enable

#define TIMSK_TICIE1    5U  //Timer/Counter1, Input Capture Interrupt Enable
#define TIMSK_TOIE1    2U  //Timer/Counter1 Overflow Interrupt Enable

//Timer/Counter Interrupt Flag Register
#define TIFR *((volatile uint8*)0x58)
#define TIFR_OCIF2 7U  //Timer/Counter2 Output Compare Match Flag
#define TIFR_TOIF2 6U  //Timer/Counter2 Overflow Flag

#define TIFR_OCIF0 1U  //Timer/Counter0 Output Compare Match Flag
#define TIFR_TOIF0 0U  //Timer/Counter0 Overflow Flag

#define TIFR_OCF1A    4U  //Timer/Counter1, Output Compare A Match Flag
#define TIFR_OCF1B    3U  //Timer/Counter1, Output Compare B Match Flag

#define TIFR_ICF1    5U  //Timer/Counter1, Input Capture Flag
#define TIFR_TOV1    2U  //Timer/Counter1, Overflow Flag
/*************************timer0****************************************/
//define Timer/Counter Control Register
#define TCCR0 *((volatile uint8*)0x53)
#define TCCR0_FOC0 7U //Force Output Compare
// Waveform Generation Mode
#define TCCR0_WGM00 6U
#define TCCR0_WGM01 3U
// Compare Match Output Mode
#define TCCR0_COM01 5U
#define TCCR0_COM00 4U
// Clock Select Bit Description
#define TCCR0_CS_Mask 0B11111000

//Timer/Counter Register 
#define TCNT0 *((volatile uint8*)0x52)
//Output Compare Register
#define OCR0 *((volatile uint8*)0x5C)
/*************************end timer0****************************************/

/*************************timer1****************************************/
//define Timer/Counter Control Register
#define TCCR1A *((volatile uint8*)0x4F)
// Compare Output Mode for Channel A
#define TCCR1A_COM1A1 7U
#define TCCR1A_COM1A0 6U
// Compare Output Mode for Channel B
#define TCCR1A_COM1B1 5U
#define TCCR1A_COM1B0 4U

#define TCCR1A_FOC1A 3U //Force Output Compare for Channel A
#define TCCR1A_FOC1B 2U //Force Output Compare for Channel B
// Waveform Generation Mode
#define TCCR1A_WGM11 1U
#define TCCR1A_WGM10 0U
#define TCCR1A_WGM_MASK 0B11111100

//define Timer/Counter Control Register
#define TCCR1B *((volatile uint8*)0x4E)
// Input Capture Noise Canceler
#define TCCR1B_ICNC1 7U
//Input Capture Edge Select
#define TCCR1B_ICES1 6U
// Waveform Generation Mode
#define TCCR1B_WGM13 4U
#define TCCR1B_WGM12 3U
#define TCCR1B_WGM_MASK 0B11100111

// Clock Select Bit Description
#define TCCR1B_CS_Mask 0B11111000


//Timer/Counter Register 
#define TCNT1 *((volatile uint16*)0x4C)
#define TCNT1H *((volatile uint8*)0x4D)
#define TCNT1L *((volatile uint8*)0x4C)
//Output Compare Register
#define OCR1A *((volatile uint16*)0x4A)
#define OCR1AH *((volatile uint8*)0x4B)
#define OCR1AL *((volatile uint8*)0x4A)

//Output Compare Register
#define OCR1B *((volatile uint16*)0x48)
#define OCR1BH *((volatile uint8*)0x49)
#define OCR1BL *((volatile uint8*)0x48)

// Input Capture Register
#define ICR1 *((volatile uint16*)0x46)
#define ICR1H *((volatile uint8*)0x47)
#define ICR1L *((volatile uint8*)0x46)

/*************************end timer1****************************************/
/*************************timer2****************************************/
//define Timer/Counter Control Register
#define TCCR2 *((volatile uint8*)0x45)
#define TCCR2_FOC2 7U //Force Output Compare
// Waveform Generation Mode
#define TCCR2_WGM20 6U
#define TCCR2_WGM21 3U
// Compare Match Output Mode
#define TCCR2_COM21 5U
#define TCCR2_COM20 4U
// Clock Select Bit Description
#define TCCR2_CS_Mask 0B11111000

//Timer/Counter Register 
#define TCNT2 *((volatile uint8*)0x44)
//Output Compare Register
#define OCR2 *((volatile uint8*)0x43)
/*************************end timer2****************************************/


#endif
