#ifndef ADC_PRV_H
#define ADC_PRV_H

#define AREF                1U
#define AVCC                2U
#define Voltage_2_65        3U

#define EIGHT_BITS          1U
#define TEN_BITS            2U

#define DIVISION_BY_2       1u
#define DIVISION_BY_4       2u
#define DIVISION_BY_8       3u
#define DIVISION_BY_16      4u
#define DIVISION_BY_32      5u
#define DIVISION_BY_64      6u
#define DIVISION_BY_128     7u

#define IDLE				1u
#define BUSY				2u

#define CHANNEL_SELECTION_MASK      0xE0
#define PRESCALER_MASK				0XF8
#endif
