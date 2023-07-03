#ifndef TIMER_PRV_H
#define TIMER_PRV_H


#define TIMER_DISBLE_INT      1U
#define TIMER_OVERFLOW_INT    2U
#define TIMER_COMPARE_INT     3U   

#define WGM13_12_MASK                       0B00001100
#define WGM11_10_MASK                       0B00000011

#define TCCR_CON(num)          TCCR##num
#define TCCR_COM_CON(num,num2,idx)          TCCR##num##_COM##num2##idx

#define TCCR_WGM_CON(num,idx)          TCCR##num##_WGM##idx

#define __TIMER_ComStamp(num,num2,idx1,idx2)      do{if (copy_COM == TIMER_COM_NORMAL){   \
			CLS_BIT(TCCR_CON(num) , TCCR_COM_CON(num,num2,idx1)); CLS_BIT(TCCR_CON(num) , TCCR_COM_CON(num,num2,idx2));    }\
		else if (copy_COM == TIMER_COM_TOGGLE || copy_COM == TIMER_COM_RESERVED){\
			SET_BIT(TCCR_CON(num) , TCCR_COM_CON(num,num2,idx1)); CLS_BIT(TCCR_CON(num) , TCCR_COM_CON(num,num2,idx2)); }\
		else if (copy_COM == TIMER_COM_CLEAR){\
			CLS_BIT(TCCR_CON(num) , TCCR_COM_CON(num,num2,idx1)); SET_BIT(TCCR_CON(num) , TCCR_COM_CON(num,num2,idx2)); }\
		else if (copy_COM == TIMER_COM_SET){\
			SET_BIT(TCCR_CON(num) , TCCR_COM_CON(num,num2,idx1)); SET_BIT(TCCR_CON(num) , TCCR_COM_CON(num,num2,idx2)); }\
            else{/**/}}while(0)

#define __TIMER_WGMStamp(num,idx1,idx2) do{if (copy_WGM == TIMER0_2WGM_NORMAL){  \
			CLS_BIT(TCCR_CON(num) , TCCR_WGM_CON(num,idx1)); CLS_BIT(TCCR_CON(num) , TCCR_WGM_CON(num,idx2));  }  \
		else if (copy_WGM == TIMER0_2WGM_PWM){\
			SET_BIT(TCCR_CON(num) , TCCR_WGM_CON(num,idx1)); CLS_BIT(TCCR_CON(num) , TCCR_WGM_CON(num,idx2)); }\
		else if (copy_WGM == TIMER0_2WGM_CTC){\
			CLS_BIT(TCCR_CON(num) , TCCR_WGM_CON(num,idx1)); SET_BIT(TCCR_CON(num) , TCCR_WGM_CON(num,idx2));} \
		else if (copy_WGM == TIMER0_2WGM_FAST_PWM){\
            SET_BIT(TCCR_CON(num) , TCCR_WGM_CON(num,idx1)); SET_BIT(TCCR_CON(num) , TCCR_WGM_CON(num,idx2));}\
		else{/**/}}while(0)

#endif
