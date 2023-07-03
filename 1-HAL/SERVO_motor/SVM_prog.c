
#include "../../libraries/STD_TYPES_H.h"
#include "../../libraries/MAP.h"

#include "../../0-MCAL/1-DIO/DIO_interface.h"
#include "../../2-service/TIMER1_S_interface.h"
#include "../../0-MCAL/6-TIMER/TIMER_interface.h"
#include "../../0-MCAL/8-UART/UART_interface.h"
#include "SVM_interface.h"

void SVM_init(TIMER_TINum_t copy_TINum)
{
	if (copy_TINum == TIMER1A || copy_TINum == TIMER1B)
	{
		TIMER_voidChangCOM_Mode(copy_TINum, TIMER_COM_CLEAR);
		TIMER_voidChangWGM_Mode(TIMER1, TIMER_WGM_PWM_FAST_ICR1);
	}
}
void SVM_voidRotateTo(TIMER_TINum_t copy_TINum, uint8 copy_u8Angel)
{
	if ((copy_u8Angel >= 0) && (copy_u8Angel <= 180))
	{
		if (copy_TINum == TIMER1A || copy_TINum == TIMER1B)
		{
			f64 Local_s32DutyPercent = MAP(0.0, 180.0, 2.1, 12.9, (f64)copy_u8Angel);
			T1S_voidStopPwm();
			T1S_voidStartPwm(copy_TINum, 20000, Local_s32DutyPercent);
		}
	}
}
void SVM_voidStop(TIMER_TINum_t copy_TINum)
{
	if (copy_TINum == TIMER1A || copy_TINum == TIMER1B)
	{
		TIMER_voidChangCOM_Mode(copy_TINum, TIMER_COM_NORMAL);
		TIMER_voidChangWGM_Mode(TIMER1, TIMER_WGM_Normal);
		// T1S_voidStopPwm();
	}
}
