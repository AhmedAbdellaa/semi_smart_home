#ifndef CLCD_INTERFACE_H
#define CLCD_INTERFACE_H

#define CLCD_CLEAR_CMD 0X01
#define CLCD_RESETCURSOR_CMD 0X10


/// @brief send specific command to lcd screen 
/// @param copy_u8command command want to execute
void CLCD_VoidSendCommand(uint8 copy_u8command);

/// @brief send ASCII data to lcd screen
/// @param copy_u8Data ascii character want to send
void CLCD_VoidSendData(uint8 copy_u8Data);

/// @brief initialize CLCD as given in configuration file
void CLCD_VoidInit(void);

/// @brief go to specific location in screen
/// @param copy_u8xPos x postion location
/// @param copy_Ypos y postion location
void CLCD_voidGoToXY(uint8 copy_u8xPos,uint8 copy_Ypos);

/// @brief build custom character and store it in lcd MC
/// @param copy_u8PatternNumber choose number to store in it [0:8]
/// @param copy_pu8PatternArr array of 8 unsigned 8-bits represent the charcter
/// @return error state if everything is ok will return OK
uint8 CLCD_u8WriteSpecialChar(uint8 copy_u8PatternNumber,uint8* copy_pu8PatternArr);

/// @brief print list of characters
/// @param copy_u8charArray array of characters
/// @return error state if everything is ok will return OK
uint8 CLCD_VoidPrintChars(const uint8* copy_u8charArray);

/// @brief print integer number
/// @param copy_u32number  32-bit number want to print
void CLCD_VoidPrintInt(sint32 copy_u32number);

/// @brief print floating number
/// @param copy_s32IntegerPart 32-bit integral part
/// @param copy_s32FloatingPart 32-bit floating part after convert it to integer
void CLCD_VoidPrintFloat(sint32 copy_s32IntegerPart,uint32 copy_s32FloatingPart);

#endif
