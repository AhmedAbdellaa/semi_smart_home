#ifndef PORT_REG
#define PORT_REG

#define PORTA *((volatile uint8*) 0x3B)
#define DDRA *((volatile uint8*) 0x3A)

#define PORTB *((volatile uint8*) 0x38)
#define DDRB *((volatile uint8*) 0x37)

#define PORTC *((volatile uint8*) 0x35)
#define DDRC *((volatile uint8*) 0x34)

#define PORTD *((volatile uint8*) 0x32)
#define DDRD *((volatile uint8*) 0x31)

#endif