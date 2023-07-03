#ifndef UART_CFG_H
#define UART_CFG_H
/*
* configure UART selects between Asynchronous and Synchronous mode of operation
*                                    options :1-UART_UMSEL_ASYNCHRONOUS
*                                           2-UART_UMSEL_SYNCHRONOUS   
*                                           3-UART_UMSEL_ASYNCHRONOUS_DOUBLE   
*/
#define UART_u8UMSEL_MODE              UART_UMSEL_ASYNCHRONOUS
/*
* configure UART Parity Mode options : 1-UART_UPM_DISABLED
*                                                    2-UART_UPM_EVEN  
*                                                    3-UART_UPM_ODD
*/
#define UART_u8UPM_MODE              UART_UPM_DISABLED
/*
* configure UART Stop Bit Select, options :1-UART_USBS_1BIT
*                                           2-UART_USBS_2BIT                                      
*/
#define UART_u8USBS_MODE              UART_USBS_1BIT
/*
* configure UART   Character Size, options : 1-UART_CH_SIZE_5
*                                                    2-UART_CH_SIZE_6
*                                                    3-UART_CH_SIZE_7
*                                                    4-UART_CH_SIZE_8
*                                                    5-UART_CH_SIZE_9
*/
#define UART_u8_CH_SIZE_COM             UART_CH_SIZE_8
/*
* configure UART Clock Polarity for tx pin options :1-UART_Rising_XCK_Edge
*                                                 2-UART_Falling_XCK_Edge                                      
*/
#define UART_u8UCPOL_MODE              UART_Rising_XCK_Edge
/*configure UART baudRate*/
#define UART_u32_CH_SIZE_COM             9600ul

#define UART_u32_timeout                  50000ul
#endif
