#ifndef UART_REG
#define UART_REG
// USART I/O Data Register 
#define UDR     *((volatile uint8*)0x2C)
// USART Control and Status Register A
#define UCSRA   *((volatile uint8*)0x2B)
#define UCSRA_RXC   7U //USART Receive Complete
#define UCSRA_TXC   6U  //USART Transmit Complete
#define UCSRA_UDRE  5U  //USART Data Register Empty ready to receive new data.
#define UCSRA_FE    4U  //Frame Error
#define UCSRA_DOR   3U  //Data OverRun
#define UCSRA_PE    2U  //Parity Error
#define UCSRA_U2X   1U //Double the USART Transmission Speed
#define UCSRA_MPCM  0U //Multi-processor Communication Mode

// USART Control and Status Register B
#define UCSRB   *((volatile uint8*)0x2A)
#define UCSRB_RXCIE  7U //RX Complete Interrupt Enable
#define UCSRB_TXCIE  6U //TX Complete Interrupt Enable
#define UCSRB_UDRIE  5U //USART Data Register Empty Interrupt Enable
#define UCSRB_RXEN   4U //Receiver Enable
#define UCSRB_TXEN   3U //Transmitter Enable
#define UCSRB_UCSZ2  2U //Character Size
#define UCSRB_RXB8  1U //Receive Data Bit 8
#define UCSRB_TXB8  0U //Transmit Data Bit 8

// USART Control and Status Register C
#define UCSRC   *((volatile uint8*)0x40)
#define UCSRC_URSEL   7U    //Register Select UCSRC or the UBRRH
#define UCSRC_UMSEL   6U    //USART Mode Select between Asynchronous and Synchronous
#define UCSRC_UPM1    5U    //Parity Mode
#define UCSRC_UPM0    4U    //Parity Mode
#define UCSRC_USBS    3U    //Stop Bit Select
#define UCSRC_UCSZ1   2U    //Character Size
#define UCSRC_UCSZ0   1U    //Character Size
#define UCSRC_UCPOL   0U    //Clock Polarity **Synchronous mode only
// USART Baud Rate Registers
#define UBRRH   *((volatile uint8*)0x40)//contains the four most significant bits
#define UBRRL   *((volatile uint8*)0x29)//contains the 8 least significant bits

#endif
