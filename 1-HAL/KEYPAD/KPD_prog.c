
#include "../../libraries/STD_TYPES_H.h"
#include "../../libraries/ErrType.h"
#include "../../0-MCAL/1-DIO/DIO_interface.h"

#include "KPD_interface.h"
#include "KPD_prv.h"
#include "KPD_cfg.h"

uint8 KPD_u8GetPressedKey(uint8* reference_u8Row,uint8* reference_u8Col){
    
    uint8 Local_u8ItrRow,Local_u8ItrCol,Local_u8KeyState, Local_u8PressedKey= KPD_u8NO_PRESSED_KEY_VAL;
    static uint8 Local_u8RowArr[ROW_SIZE]={KPD_u8R0_PIN,KPD_u8R1_PIN,KPD_u8R2_PIN,KPD_u8R3_PIN};
    static uint8 Local_u8ColArr[ROW_SIZE]={KPD_u8C0_PIN,KPD_u8C1_PIN,KPD_u8C2_PIN,KPD_u8C3_PIN};
    static uint8 Local_u8KPDArr[ROW_SIZE][COL_SIZE]= KPD_u8BUTTONARR_VAL;
    //activate the column pins
    for(Local_u8ItrCol=0;Local_u8ItrCol<COL_SIZE;Local_u8ItrCol++){
    
        //activate the current column
        DIO_u8_SetPinVal(KPD_u8COL_PORT,Local_u8ColArr[Local_u8ItrCol],DIO_PIN_LOW);

        //read the row pins
        for(Local_u8ItrRow=0;Local_u8ItrRow<ROW_SIZE;Local_u8ItrRow++){
            //read the current row 
            DIO_u8_GetPinVal(KPD_u8ROW_PORT,Local_u8RowArr[Local_u8ItrRow],&Local_u8KeyState);
            if(Local_u8KeyState == DIO_PIN_LOW){
                Local_u8PressedKey = Local_u8KPDArr[Local_u8ItrRow][Local_u8ItrCol];
                //wait until key is released (polling with blocking on pin reading)
                while(Local_u8KeyState == DIO_PIN_LOW){
                    DIO_u8_GetPinVal(KPD_u8ROW_PORT,Local_u8RowArr[Local_u8ItrRow],&Local_u8KeyState);
                }
                *reference_u8Row=Local_u8ItrRow;
                *reference_u8Col=Local_u8ItrCol;
                return Local_u8PressedKey;
            }

        }
        //deactivate the current column
        DIO_u8_SetPinVal(KPD_u8COL_PORT,Local_u8ColArr[Local_u8ItrCol],DIO_PIN_HIGH);
    }

    return Local_u8PressedKey;

}
