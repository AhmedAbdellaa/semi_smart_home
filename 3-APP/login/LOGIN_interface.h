#ifndef LOGIN_INTERFACE_H
#define LOGIN_INTERFACE_H



#define LOGIN_SUCCESS 1u
#define LOGIN_ID_FAILD 2u
#define LOGIN_PASS_FAILD 3u

void LOGIN_voidSystemStart();
sint16 LOGIN_s16GetID_Pass(uint8 copy_ispassword);
uint8 LOGIN_u8login(uint8 *copy_u8INTFlag);
void LOGIN_voidDisable_INTBTN();
void LOGIN_voidEnable_INTBTN();
#endif

