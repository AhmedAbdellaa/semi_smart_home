
#include "../../libraries/BIT_MATH.h"
#include "../../libraries/ErrType.h"
#include "../../libraries/STD_TYPES_H.h"
#include "./EXTI_interface.h"
#include "EXTI_reg.h"
#include "EXTI_prv.h"
#include "EXTI_cfg.h"



static void (*EXTI_PFunctionPtr[3])(void) = {NULL,NULL,NULL};

uint8 EXTI_u8SetCallBack(EXTI_IntNum_t copy_IntNum,void(*copy_pvFuncPtr)(void)){
	uint8 Local_u8ErrorState = OK;
	if(copy_pvFuncPtr != NULL){
		if((copy_IntNum>=INT0) &&(copy_IntNum<=INT2)){
			EXTI_PFunctionPtr[copy_IntNum]= copy_pvFuncPtr;

			}else{
			Local_u8ErrorState = NOK;
		}
	}
	else{
		Local_u8ErrorState = NULL_PTR;
	}
	return Local_u8ErrorState;
}
/*INT0 ISR*/
void __vector_1(void) __attribute__((signal));
void __vector_1(void){
	if(EXTI_PFunctionPtr[INT0] != NULL){
		EXTI_PFunctionPtr[INT0]();
		}else{
		/*do nothing*/
	}
}

/*INT1 ISR*/
void __vector_2(void) __attribute__((signal));
void __vector_2(void){
	if(EXTI_PFunctionPtr[INT1] != NULL){
		EXTI_PFunctionPtr[INT1]();
		}else{
		/*do nothing*/
	}
}

/*INT2 ISR*/
void __vector_3(void) __attribute__((signal));
void __vector_3(void){
	if(EXTI_PFunctionPtr[INT2] != NULL){
		EXTI_PFunctionPtr[INT2]();
		}else{
		/*do nothing*/
	}
}


void EXTI_voidInit(void)
{

	#if EXTI_u8INT0_TRGSRC == LOW_LEVEL
	CLS_BIT(MCUCR, MCUCR_IS00);
	CLS_BIT(MCUCR, MCUCR_IS01);
	#elif EXTI_u8INT0_TRGSRC == ON_CHANGE
	SET_BIT(MCUCR, MCUCR_IS00);
	CLS_BIT(MCUCR, MCUCR_IS01);
	#elif EXTI_u8INT0_TRGSRC == FALLING_EDGE
	CLS_BIT(MCUCR, MCUCR_IS00);
	SET_BIT(MCUCR, MCUCR_IS01);
	#elif EXTI_u8INT0_TRGSRC == RISING_EDGE
	SET_BIT(MCUCR, MCUCR_IS00);
	SET_BIT(MCUCR, MCUCR_IS01);
	#else
	#error "Wrong EXTI_u8INT0_TRIG_SRG configuration option"
	#endif

	#if EXTI_u8INT1_TRGSRC == LOW_LEVEL
	CLS_BIT(MCUCR, MCUCR_IS10);
	CLS_BIT(MCUCR, MCUCR_IS11);
	#elif EXTI_u8INT1_TRGSRC == ON_CHANGE
	SET_BIT(MCUCR, MCUCR_IS10);
	CLS_BIT(MCUCR, MCUCR_IS11);
	#elif EXTI_u8INT1_TRGSRC == FALLING_EDGE
	CLS_BIT(MCUCR, MCUCR_IS10);
	SET_BIT(MCUCR, MCUCR_IS11);
	#elif EXTI_u8INT1_TRGSRC == RISING_EDGE
	SET_BIT(MCUCR, MCUCR_IS10);
	SET_BIT(MCUCR, MCUCR_IS11);
	#else
	#error "Wrong EXTI_u8INT1_TRIG_SRG configuration option"
	#endif

	#if EXTI_u8INT2_TRGSRC == FALLING_EDGE
	CLS_BIT(MCUCSR, MCUCR_ISC2);
	#elif EXTI_u8INT2_TRGSRC == RISING_EDGE
	SET_BIT(MCUCSR, MCUCR_ISC2);
	#else
	#error "Wrong EXTI_u8INT2_TRIG_SRG configuration option"
	#endif

	#if EXTI_u8INT0_INIT_STATE == DISABLED
	CLS_BIT(GICR, GICR_INT0);
	#elif EXTI_u8INT0_INIT_STATE == ENABLED
	SET_BIT(GICR, GICR_INT0);
	#else
	#error "Wrong EXTI_u8INT0_INIT_STATE configuration option"
	#endif

	#if EXTI_u8INT1_INIT_STATE == DISABLED
	CLS_BIT(GICR, GICR_INT1);
	#elif EXTI_u8INT1_INIT_STATE == ENABLED
	SET_BIT(GICR, GICR_INT1);
	#else
	#error "Wrong EXTI_u8INT0_INIT_STATE configuration option"
	#endif

	#if EXTI_u8INT2_INIT_STATE == DISABLED
	CLS_BIT(GICR, GICR_INT2);
	#elif EXTI_u8INT2_INIT_STATE == ENABLED
	SET_BIT(GICR, GICR_INT2);
	#else
	#error "Wrong EXTI_u8INT0_INIT_STATE configuration option"
	#endif
}
uint8 EXTI_u8SetSenceCtrl(EXTI_IntNum_t copy_IntNum, uint8 copy_SenseCtrl)
{
	uint8 Local_u8Error_state = OK;
	if (copy_IntNum == INT0){
		switch (copy_SenseCtrl){
			case LOW_LEVEL:CLS_BIT(MCUCR, MCUCR_IS00);CLS_BIT(MCUCR, MCUCR_IS01);break;
			case ON_CHANGE:SET_BIT(MCUCR, MCUCR_IS00);CLS_BIT(MCUCR, MCUCR_IS01);break;
			case FALLING_EDGE:CLS_BIT(MCUCR, MCUCR_IS00);SET_BIT(MCUCR, MCUCR_IS01);break;
			case RISING_EDGE:SET_BIT(MCUCR, MCUCR_IS00);SET_BIT(MCUCR, MCUCR_IS01);break;
			default:Local_u8Error_state = NOK;break;
		}
	}
	else if (copy_IntNum == INT1){
		switch (copy_SenseCtrl){
			case LOW_LEVEL:CLS_BIT(MCUCR, MCUCR_IS10);CLS_BIT(MCUCR, MCUCR_IS11);break;
			case ON_CHANGE:SET_BIT(MCUCR, MCUCR_IS10);CLS_BIT(MCUCR, MCUCR_IS11);break;
			case FALLING_EDGE:CLS_BIT(MCUCR, MCUCR_IS10);SET_BIT(MCUCR, MCUCR_IS11);break;
			case RISING_EDGE:SET_BIT(MCUCR, MCUCR_IS10);SET_BIT(MCUCR, MCUCR_IS11);break;
			default:Local_u8Error_state = NOK;break;
		}
	}
	else if (copy_IntNum == INT2){
		switch (copy_SenseCtrl){
			case FALLING_EDGE:CLS_BIT(MCUCSR, MCUCR_ISC2);break;
			case RISING_EDGE:SET_BIT(MCUCSR, MCUCR_ISC2);break;
			default:Local_u8Error_state = NOK;break;
		}
	}
	else
	Local_u8Error_state = NOK;

	return Local_u8Error_state;
}

uint8 EXTI_u8IntEnable(EXTI_IntNum_t copy_IntNum){
	uint8 Local_u8Error_state = OK;
	switch (copy_IntNum){
		case INT0:SET_BIT(GIFR,INTF0);SET_BIT(GICR,GICR_INT0);break;
		case INT1:SET_BIT(GIFR,INTF1);SET_BIT(GICR,GICR_INT1);break;
		case INT2:SET_BIT(GIFR,INTF2);SET_BIT(GICR,GICR_INT2);break;
		default:Local_u8Error_state = NOK;break;
	}
	return Local_u8Error_state;
}
uint8 EXTI_u8IntDisable(EXTI_IntNum_t copy_IntNum){
	uint8 Local_u8Error_state = OK;
	switch (copy_IntNum){
		case INT0:CLS_BIT(GICR,GICR_INT0);SET_BIT(GIFR,INTF0);break;
		case INT1:CLS_BIT(GICR,GICR_INT1);SET_BIT(GIFR,INTF1);break;
		case INT2:CLS_BIT(GICR,GICR_INT2);SET_BIT(GIFR,INTF2);break;
		default:Local_u8Error_state = NOK;break;
	}
	return Local_u8Error_state;
}
