#ifndef KPD_INTERFACE_H
#define KPD_INTERFACE_H

/// @brief get which key pressed from keypad (button matrix)
/// @param reference_u8Row address of 8-bits to store which row pressed
/// @param reference_u8Col address of 8-bits to store which col pressed
/// @return return which key pressed from KPD_u8BUTTONARR_VAL array
uint8 KPD_u8GetPressedKey(uint8* reference_u8Row,uint8* reference_u8Col);
#endif
