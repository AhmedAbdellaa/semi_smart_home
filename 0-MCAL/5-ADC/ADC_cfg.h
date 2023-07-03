#ifndef ADC_CFG_H
#define ADC_CFG_H

/* Voltage Reference Selections for ADC, options : 1-AREF, Internal Vref turned off
*                                         1-AREF
*                                         2-AVCC with external capacitor at AREF pin 
*                                         2-AVCC 
*                                         3-Internal 2.56V Voltage Reference with external capacitor at AREF pin
*                                         3-Voltage_2_65
*/
#define ADC_u8ReferanceSelection              AVCC

/* bit affects the presentation of the ADC conversion result in the ADC Data Register
*                                                 1-EIGHT_BITS
*                                                 2-TEN_BITS
*/
#define ADC_u8_presentationBits               TEN_BITS
/* ADC Prescaler Select division factor:    1-DIVISION_BY_2  
*                                           2-DIVISION_BY_4  
*                                           3-DIVISION_BY_8  
*                                           4-DIVISION_BY_16 
*                                           5-DIVISION_BY_32 
*                                           6-DIVISION_BY_64 
*                                           7-DIVISION_BY_128
*/
#define ADC_u8_DevisionFactor                 DIVISION_BY_128

#define ADC_u32TIMEOUT_COUNT                5000000ul

#endif
