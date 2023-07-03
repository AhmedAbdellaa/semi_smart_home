#ifndef ADC_REG
#define ADC_REG

//define registers
#define ADMUX *((volatile uint8 *)0x27)
#define REFS1 7U
#define REFS0 6U
#define ADLAR 5U
//#define MUX4 4U
//#define MUX3 3U
//#define MUX2 2U
//#define MUX1 1U
//#define MUX0 0U

#define ADCSRA *((volatile uint8 *)0x26)
#define ADEN 7U
#define ADSC 6U
#define ADATE 5U
#define ADIF 4U
#define ADIE 3U
//#define ADPS2 2U
//#define ADPS1 1U
//#define ADPS0 0U

#define ADCH *((volatile uint8 *)0x25)
#define ADCL *((volatile uint8 *)0x24)
#define ADC  *((volatile uint16 *)0x24)
#endif







