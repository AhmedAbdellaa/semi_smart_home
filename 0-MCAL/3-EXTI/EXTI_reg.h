#ifndef EXTI_REG
#define EXTI_REG

//define registers
#define SREG *((volatile uint8 *)0x5F) //global open interrupts
#define SREG_I 7U

#define GICR *((volatile uint8 *)0x5B) //enable interrupt
#define GICR_INT1 7U
#define GICR_INT0 6U
#define GICR_INT2 5U

#define MCUCR *((volatile uint8 *)0x55) //configure trigger
#define MCUCR_IS00 0u
#define MCUCR_IS01 1u
#define MCUCR_IS10 2u
#define MCUCR_IS11 3u

#define MCUCSR *((volatile uint8 *)0x54) 
#define MCUCR_ISC2 6u

#define GIFR *((volatile uint8*)0x5A)
#define INTF1	7u
#define INTF0 	6u
#define INTF2	5u

#endif
