#include <util/delay.h>
#include "../../libraries/STD_TYPES_H.h"
#include "HAMO_interface.h"
#include "../../1-HAL/CLCD/CLCD_interface.h"



//special characters
uint8 MOVEZERO[]={0X0E,0X0E,0X05,0X0E,0X0C,0X04,0X06,0X05};
uint8 MOVEONE[]={0X0E,0X0E,0X04,0X0E,0X16,0X04,0X0C,0X14};

 void _voidIniWalk(){
    CLCD_u8WriteSpecialChar(0X06,MOVEZERO);
    CLCD_u8WriteSpecialChar(0X07,MOVEONE);
}



void Hamo_voidWalkRightScene(){
    _voidIniWalk();
    CLCD_voidGoToXY(0u,0u);
    CLCD_VoidPrintChars("welcome");
    uint8 Local_u8counter=0;
	while(Local_u8counter<16){
		CLCD_voidGoToXY(Local_u8counter-1,1U);
		CLCD_VoidSendData(' ');

        CLCD_voidGoToXY(Local_u8counter,1U);
		CLCD_VoidSendData(6);
		_delay_ms(50);
		
		CLCD_voidGoToXY(Local_u8counter,1U);
		CLCD_VoidSendData(7);
		_delay_ms(50);

        Local_u8counter++;
    }
    CLCD_VoidSendCommand(CLCD_CLEAR_CMD);
}
void Hamo_voidWalkLeftScene(){
    _voidIniWalk();
    CLCD_VoidSendCommand(CLCD_CLEAR_CMD);
    CLCD_voidGoToXY(0u,0u);
    CLCD_VoidPrintChars(" thanks...");
    sint8 Local_u8counter=15;
	while(Local_u8counter>=0){
		CLCD_voidGoToXY(Local_u8counter+1,1U);
		CLCD_VoidSendData(' ');

        CLCD_voidGoToXY(Local_u8counter,1U);
		CLCD_VoidSendData(6);
		_delay_ms(100);

		CLCD_voidGoToXY(Local_u8counter,1U);
		CLCD_VoidSendData(7);
		_delay_ms(100);

        Local_u8counter--;
    }
    CLCD_VoidSendCommand(CLCD_CLEAR_CMD);
}

