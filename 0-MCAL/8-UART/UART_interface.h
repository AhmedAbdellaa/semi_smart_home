#ifndef UART_INTERFACE
#define UART_INTERFACE
/*work on pins D0 and D1*/

/// @brief init uart from cfg file
void UART_voidInit(void);

/// @brief send data out
/// @param copy_u16Data data want to send max is 9-bits depends on cfg file
void UART_voidTransmit(uint16 copy_u16Data);

/// @brief  receive data from out of mc
/// @return received data with number of bits as configure in cfg file -1 if no data pass
sint16 UART_voidReceive(void);

/// @brief send buffer of data synchronous with timeout
/// @param copy_u8charArray buffer want to send
/// @return error state OK if every thing go right  return -1 if timeout without receive anything
uint8 UART_u8SendBufferSynch(const uint8 *copy_u8charArray);

/// @brief send buffer of data Asynchronous with interrupt
/// @param copy_u8charArray buffer want to send
/// @return error state OK if every thing go right
uint8 UART_u8SendBufferASynch( uint8 *copy_u8charArray);

/// @brief receive buffer of data synchronous with timeout
/// @param copy_pu8charArray address location received buffer
/// @param copy_u8BufferSize size of buffer you want to receive or receive data until press enter before buffer length end
/// @return error state OK if every thing go right
uint8 UART_u8ReceiveBufferSynch(uint8 *copy_pu8charArray, uint8 copy_u8BufferSize);

/// @brief receive buffer of data synchronous with interrupt enable
/// @param copy_pu8charArray address location received buffer
/// @param copy_u8BufferSize size of buffer you want to receive or receive data until press enter before buffer length end
/// @return error state OK if every thing go right
uint8 UART_u8ReceiveBufferASynch(uint8 *copy_pu8charArray, uint8 copy_u8BufferSize);

/// @brief send data and new line at the end of it
/// @param copy_u8charArray buffer want to send
void UART_VoidPrintln(uint8 *copy_u8charArray);

/// @brief send integer number of 32-bits 
/// @param copy_s32number number to send
void UART_VoidPrintInt(sint32 copy_s32number);

/// @brief receive integer number of 32-bits 
/// @return received number
sint32 UART_s32_ReceiveInt();

/// @brief send floating point number 
/// @param copy_f64number  number to send 
void UART_VoidPrintFloat(f64 copy_f64number);
#endif
