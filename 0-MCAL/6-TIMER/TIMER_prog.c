
#include "../../libraries/BIT_MATH.h"
#include "../../libraries/ErrType.h"
#include "../../libraries/STD_TYPES_H.h"
#include "./TIMER_interface.h"
#include "TIMER_reg.h"
#include "TIMER_prv.h"
#include "TIMER_cfg.h"
//[TIMER0,TIMER1,TIMER2]
//[TIMER0,TIMER1A,TIMER1B,TIMER2]
static void (*TIMER_PFunctionPtr_overflow[3])(void) = {NULL, NULL, NULL};
static void (*TIMER_PFunctionPtr_COM[4])(void) = {NULL, NULL, NULL, NULL};
static void (*TIMER_PFunctionPtr_ISR)(void) = NULL;

static TIMER_CALLBACK_CONFIG_t *Global_TimerCallbackConf_overflow[3] = {NULL, NULL, NULL};
static TIMER_CALLBACK_CONFIG_t *Global_TimerCallbackConf_COM[4] = {NULL, NULL, NULL, NULL};

uint8 TIMER_u8Start_OV_Interrupt(TIMER_TINum_t copy_TINUM, TIMER_CALLBACK_CONFIG_t *reference_TimerCallbackConf, void (*copy_pvFuncPtr)(void))
{
	uint8 Local_u8ErrorState = OK;
	if ((copy_pvFuncPtr != NULL) && (reference_TimerCallbackConf != NULL))
	{
		switch (copy_TINUM)
		{
		case TIMER0:
			// ISR function address
			TIMER_PFunctionPtr_overflow[TIMER0] = copy_pvFuncPtr;
			// preload and count of overflow to reach time needed
			Global_TimerCallbackConf_overflow[TIMER0] = reference_TimerCallbackConf;
			// initialize preload value
			TCNT0 = reference_TimerCallbackConf->TIMER_u16OCR_TCNT_initVal;
			// enable interrupt
			SET_BIT(TIMSK, TIMSK_TOIE0);
			break;
		case TIMER1:
			// ISR function address
			TIMER_PFunctionPtr_overflow[TIMER1] = copy_pvFuncPtr;
			// preload and count of overflow to reach time needed
			Global_TimerCallbackConf_overflow[TIMER1] = reference_TimerCallbackConf;
			// initialize preload value
			TCNT1 = reference_TimerCallbackConf->TIMER_u16OCR_TCNT_initVal;
			// enable interrupt
			SET_BIT(TIMSK, TIMSK_TOIE1);
			break;
		case TIMER2:
			// ISR function address
			TIMER_PFunctionPtr_overflow[TIMER2] = copy_pvFuncPtr;
			// preload and count of overflow to reach time needed
			Global_TimerCallbackConf_overflow[TIMER2] = reference_TimerCallbackConf;
			// initialize preload value
			TCNT2 = reference_TimerCallbackConf->TIMER_u16OCR_TCNT_initVal;
			// enable interrupt
			SET_BIT(TIMSK, TIMSK_TOIE2);
			break;
		default:
			break;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR;
	}
	return Local_u8ErrorState;
}

uint8 TIMER_u8Start_COM_Interrupt(TIMER_TINum_t copy_TINUM, TIMER_CALLBACK_CONFIG_t *reference_TimerCallbackConf, void (*copy_pvFuncPtr)(void))
{
	uint8 Local_u8ErrorState = OK;
	if ((copy_pvFuncPtr != NULL) && (reference_TimerCallbackConf != NULL))
	{
		switch (copy_TINUM)
		{
		case TIMER0:
			// ISR function address
			TIMER_PFunctionPtr_COM[TIMER0] = copy_pvFuncPtr;
			// preload and count of COM to reach time needed
			Global_TimerCallbackConf_COM[TIMER0] = reference_TimerCallbackConf;
			// initialize preload value
			OCR0 = reference_TimerCallbackConf->TIMER_u16OCR_TCNT_initVal;
			// enable interrupt
			SET_BIT(TIMSK, TIMSK_OCIE0);
			break;
		case TIMER1A:
			// ISR function address
			TIMER_PFunctionPtr_COM[TIMER1A] = copy_pvFuncPtr;
			// preload and count of COM to reach time needed
			Global_TimerCallbackConf_COM[TIMER1A] = reference_TimerCallbackConf;
			// initialize preload value
			OCR1A = reference_TimerCallbackConf->TIMER_u16OCR_TCNT_initVal;
			// enable interrupt
			SET_BIT(TIMSK, TIMSK_OCIE1A);
			break;
		case TIMER1B:
			// ISR function address
			TIMER_PFunctionPtr_COM[TIMER1B] = copy_pvFuncPtr;
			// preload and count of COM to reach time needed
			Global_TimerCallbackConf_COM[TIMER1B] = reference_TimerCallbackConf;
			// initialize preload value
			OCR1B = reference_TimerCallbackConf->TIMER_u16OCR_TCNT_initVal;
			// enable interrupt
			SET_BIT(TIMSK, TIMSK_OCIE1B);
			break;
		case TIMER2:
			// ISR function address
			TIMER_PFunctionPtr_COM[TIMER2] = copy_pvFuncPtr;
			// preload and count of COM to reach time needed
			Global_TimerCallbackConf_COM[TIMER2] = reference_TimerCallbackConf;
			// initialize preload value
			OCR2 = reference_TimerCallbackConf->TIMER_u16OCR_TCNT_initVal;
			// enable interrupt
			SET_BIT(TIMSK, TIMSK_OCIE2);
			break;
		default:
			break;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR;
	}
	return Local_u8ErrorState;
}

void TIMER_voidDisable_OV_Interrupt(TIMER_TINum_t copy_TINUM)
{
	switch (copy_TINUM)
	{
	case TIMER0:
		CLS_BIT(TIMSK, TIMSK_TOIE0);
		break;
	case TIMER1:
		CLS_BIT(TIMSK, TIMSK_TOIE1);
		break;
	case TIMER2:
		CLS_BIT(TIMSK, TIMSK_TOIE2);
		break;
	default:
		break;
	}
}

void TIMER_voidDisable_COM_Interrupt(TIMER_TINum_t copy_TINUM)
{

	switch (copy_TINUM)
	{
	case TIMER0:
		CLS_BIT(TIMSK, TIMSK_OCIE0);
		break;
	case TIMER1A:
		CLS_BIT(TIMSK, TIMSK_OCIE1A);
		break;
	case TIMER1B:
		CLS_BIT(TIMSK, TIMSK_OCIE1B);
		break;
	case TIMER2:
		CLS_BIT(TIMSK, TIMSK_OCIE2);
		break;
	default:
		break;
	}
}

void TIMER_voidChangCOM_Mode(TIMER_TINum_t copy_TINUM, uint8 copy_COM)
{
	switch (copy_TINUM)
	{
	case TIMER0:
		__TIMER_ComStamp(0, 0, 0, 1);
		break;
	case TIMER1A:
		__TIMER_ComStamp(1A, 1A, 0, 1);
		break;
	case TIMER1B:
		__TIMER_ComStamp(1A, 1B, 0, 1);
		break;
	case TIMER2:
		__TIMER_ComStamp(2, 2, 0, 1);
		break;
	default:
		break;
	}
}

void TIMER_voidChangWGM_Mode(TIMER_TINum_t copy_TINUM, uint8 copy_WGM)
{
	switch (copy_TINUM)
	{
	case TIMER0:
		__TIMER_WGMStamp(0, 00, 01);
		break;
	case TIMER2:
		__TIMER_WGMStamp(2, 20, 21);
		break;
	case TIMER1:
		TCCR1B = ((TCCR1B_WGM_MASK & TCCR1B) | (((copy_WGM)&WGM13_12_MASK) << 1));
		TCCR1A = ((TCCR1A_WGM_MASK & TCCR1A) | ((copy_WGM)&WGM11_10_MASK));
		break;
	default:
		break;
	}
}

void TIMER_voidStart_PWM(TIMER_TINum_t copy_TINUM, uint16 copy_u16OCR, uint16 copy_u16ICR1)
{
	switch (copy_TINUM)
	{
	case TIMER0:
		OCR0 = copy_u16OCR;
		break;
	case TIMER1A:
		// compare on
		OCR1A = copy_u16OCR;
		// overflow on (top)
		ICR1 = copy_u16ICR1;
		break;
	case TIMER1B:
		// overflow on (top)
		OCR1B = copy_u16OCR;
		ICR1 = copy_u16ICR1;

		break;
	case TIMER2:
		OCR2 = copy_u16OCR;
		break;
	default:
		break;
	}
}

void TIMER0_voidInit(void)
{

#if TIMER_u8TI0_WGM == TIMER0_2WGM_NORMAL
	// set wave form generation
	CLS_BIT(TCCR0, TCCR0_WGM00);
	CLS_BIT(TCCR0, TCCR0_WGM01);
#elif TIMER_u8TI0_WGM == TIMER0_2WGM_PWM
	SET_BIT(TCCR0, TCCR0_WGM00);
	CLS_BIT(TCCR0, TCCR0_WGM01);
#elif TIMER_u8TI0_WGM == TIMER0_2WGM_CTC
	CLS_BIT(TCCR0, TCCR0_WGM00);
	SET_BIT(TCCR0, TCCR0_WGM01);
#elif TIMER_u8TI0_WGM == TIMER0_2WGM_FAST_PWM
	SET_BIT(TCCR0, TCCR0_WGM00);
	SET_BIT(TCCR0, TCCR0_WGM01);
#else
#error "Wrong TIMER_u8TI0_WGM configuration option"
#endif

#if TIMER_u8TI0_COM == TIMER_COM_NORMAL
	CLS_BIT(TCCR0, TCCR0_COM00);
	CLS_BIT(TCCR0, TCCR0_COM01);
#elif TIMER_u8TI0_COM == TIMER_COM_TOGGLE || TIMER_u8TI0_COM == TIMER_COM_RESERVED
	SET_BIT(TCCR0, TCCR0_COM00);
	CLS_BIT(TCCR0, TCCR0_COM01);
#elif TIMER_u8TI0_COM == TIMER_COM_CLEAR
	CLS_BIT(TCCR0, TCCR0_COM00);
	SET_BIT(TCCR0, TCCR0_COM01);
#elif TIMER_u8TI0_COM == TIMER_COM_SET
	SET_BIT(TCCR0, TCCR0_COM00);
	SET_BIT(TCCR0, TCCR0_COM01);
#else
#error "Wrong TIMER_u8TI0_COM configuration option"
#endif

	TCCR0 &= TCCR0_CS_Mask;
	TCCR0 |= TIMER_u8TI0_CLK;
}

void TIMER2_voidInit(void)
{

#if TIMER_u8TI2_WGM == TIMER0_2WGM_NORMAL
	// set wave form generation
	CLS_BIT(TCCR2, TCCR2_WGM20);
	CLS_BIT(TCCR2, TCCR2_WGM21);
#elif TIMER_u8TI2_WGM == TIMER0_2WGM_PWM
	SET_BIT(TCCR2, TCCR2_WGM20);
	CLS_BIT(TCCR2, TCCR2_WGM21);
#elif TIMER_u8TI2_WGM == TIMER0_2WGM_CTC
	CLS_BIT(TCCR2, TCCR2_WGM20);
	SET_BIT(TCCR2, TCCR2_WGM21);
#elif TIMER_u8TI2_WGM == TIMER0_2WGM_FAST_PWM
	SET_BIT(TCCR2, TCCR2_WGM20);
	SET_BIT(TCCR2, TCCR2_WGM21);
#else
#error "Wrong TIMER_u8TI2_WGM configuration option"
#endif

#if TIMER_u8TI2_COM == TIMER_COM_NORMAL
	CLS_BIT(TCCR2, TCCR2_COM20);
	CLS_BIT(TCCR2, TCCR2_COM21);
#elif TIMER_u8TI2_COM == TIMER_COM_TOGGLE || TIMER_u8TI2_COM == TIMER_COM_RESERVED
	SET_BIT(TCCR2, TCCR2_COM20);
	CLS_BIT(TCCR2, TCCR2_COM21);
#elif TIMER_u8TI2_COM == TIMER_COM_CLEAR
	CLS_BIT(TCCR2, TCCR2_COM20);
	SET_BIT(TCCR2, TCCR2_COM21);
#elif TIMER_u8TI2_COM == TIMER_COM_SET
	SET_BIT(TCCR2, TCCR2_COM20);
	SET_BIT(TCCR2, TCCR2_COM21);
#else
#error "Wrong TIMER_u8TI2_COM configuration option"
#endif

	TCCR2 &= TCCR2_CS_Mask;
	TCCR2 |= TIMER_u8TI2_CLK;
}

void TIMER1_voidInit(void)
{
	// setWaveform Generation Mode
	TCCR1B = ((TCCR1B_WGM_MASK & TCCR1B) | (((TIMER_u8TI1_WGM)&WGM13_12_MASK) << 1));
	TCCR1A = ((TCCR1A_WGM_MASK & TCCR1A) | ((TIMER_u8TI1_WGM)&WGM11_10_MASK));

// Compare Output Mode, Phase Correct and Phase and Frequency Correct PWM timer1A
#if TIMER_u8TI1A_COM == TIMER_COM_NORMAL
	CLS_BIT(TCCR1A, TCCR1A_COM1A0);
	CLS_BIT(TCCR1A, TCCR1A_COM1A1);
#elif TIMER_u8TI1A_COM == TIMER_COM_TOGGLE || TIMER_u8TI1A_COM == TIMER_COM_RESERVED
	SET_BIT(TCCR1A, TCCR1A_COM1A0);
	CLS_BIT(TCCR1A, TCCR1A_COM1A1);
#elif TIMER_u8TI1A_COM == TIMER_COM_CLEAR
	CLS_BIT(TCCR1A, TCCR1A_COM1A0);
	SET_BIT(TCCR1A, TCCR1A_COM1A1);
#elif TIMER_u8TI1A_COM == TIMER_COM_SET
	SET_BIT(TCCR1A, TCCR1A_COM1A0);
	SET_BIT(TCCR1A, TCCR1A_COM1A1);
#else
#error "Wrong TIMER_u8TI1A_COM configuration option"
#endif
// Compare Output Mode, Phase Correct and Phase and Frequency Correct PWM timer1B
#if TIMER_u8TI1B_COM == TIMER_COM_NORMAL
	CLS_BIT(TCCR1A, TCCR1A_COM1B0);
	CLS_BIT(TCCR1A, TCCR1A_COM1B1);
#elif TIMER_u8TI1B_COM == TIMER_COM_TOGGLE || TIMER_u8TI1B_COM == TIMER_COM_RESERVED
	SET_BIT(TCCR1A, TCCR1A_COM1B0);
	CLS_BIT(TCCR1A, TCCR1A_COM1B1);
#elif TIMER_u8TI1B_COM == TIMER_COM_CLEAR
	CLS_BIT(TCCR1A, TCCR1A_COM1B0);
	SET_BIT(TCCR1A, TCCR1A_COM1B1);
#elif TIMER_u8TI1B_COM == TIMER_COM_SET
	SET_BIT(TCCR1A, TCCR1A_COM1B0);
	SET_BIT(TCCR1A, TCCR1A_COM1B1);
#else
#error "Wrong TIMER_u8TI1B_COM configuration option"
#endif
	// Clock Select Bit Description
	TCCR1B &= TCCR1B_CS_Mask;
	TCCR1B |= TIMER_u8TI1_CLK;
}

void TIMER_voidSetTCNT(TIMER_TINum_t copy_TINUM, uint16 copy_u16TCNTVal)
{

	switch (copy_TINUM)
	{
	case TIMER0:
		TCNT0 = (uint8)copy_u16TCNTVal;
		break;
	case TIMER1:
		TCNT1 = copy_u16TCNTVal;
		break;
	case TIMER2:
		TCNT2 = (uint8)copy_u16TCNTVal;
		break;
	default:
		break;
	}
}
/****************************ICU*******************************/
void ICU_voidInit(void)
{
	// // setWaveform Generation Mode
	// TCCR1B = ((TCCR1B_WGM_MASK & TCCR1B) | (((12)&WGM13_12_MASK) << 1));
	// TCCR1A = ((TCCR1A_WGM_MASK & TCCR1A) | ((12)&WGM11_10_MASK));

#if ICU_u8TriggerSrc == ICU_RISING_EDGE
	SET_BIT(TCCR1B, TCCR1B_ICES1);
#elif ICU_u8TriggerSrc == ICU_FALLING_EDGE
	CLS_BIT(TCCR1B, TCCR1B_ICES1);
#else
#error "wrong ICU_u8TriggerSrc"
#endif
	// // Clock Select Bit Description
	// TCCR1B &= TCCR1B_CS_Mask;
	// TCCR1B |= TIMER_u8TI1_CLK;
}
void ICU_voidSetTriggerSrc(uint8 copy_u8TrSrc)
{
	if (copy_u8TrSrc == ICU_RISING_EDGE)
		SET_BIT(TCCR1B, TCCR1B_ICES1);
	else if (copy_u8TrSrc == ICU_FALLING_EDGE)
		CLS_BIT(TCCR1B, TCCR1B_ICES1);
	else
	{
		/**/
	}
}
uint8 ICU_u8IntEnable(void (*copy_pvFuncPtr)(void))
{
	uint8 Local_u8ErrorState = OK;
	if (copy_pvFuncPtr != NULL)
	{
		TIMER_PFunctionPtr_ISR = copy_pvFuncPtr;
		// enable interrupt
		SET_BIT(TIMSK, TIMSK_TICIE1);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR;
	}
	return Local_u8ErrorState;
}
void ICU_voidIntDisable()
{
	// disable interrupt
	CLS_BIT(TIMSK, TIMSK_TICIE1);
}
uint16 ICU_u16GetICRVal()
{
	return ICR1;
}

/****************************end ICU*******************************/


// 5 $008 TIMER2 COMP Timer/Counter2 Compare Match
void __vector_4(void) __attribute__((signal));
void __vector_4(void)
{
	static uint16 Local_u16Counter = 1; // init the overflows tracking counter

	if ((TIMER_PFunctionPtr_COM[TIMER2] != NULL) && (Global_TimerCallbackConf_COM[TIMER2] != NULL))
	{

		// if the counter equal to number of overflows do the function and reset the counter to 0
		if (Local_u16Counter == Global_TimerCallbackConf_COM[TIMER2]->TIMER_U32ISRDoNum_ICR1)
		{
			TIMER_PFunctionPtr_COM[TIMER2]();
			Local_u16Counter = 1;
		}
		else
		{
			Local_u16Counter++;
		}
	}
	else
	{
		/*do nothing*/
	}
}
// 6 $00A TIMER2 OVF Timer/Counter2 Overflow
void __vector_5(void) __attribute__((signal));
void __vector_5(void)
{
	static uint16 Local_u16Counter = 1; // init the overflows tracking counter

	if ((TIMER_PFunctionPtr_overflow[TIMER2] != NULL) && (Global_TimerCallbackConf_overflow[TIMER2] != NULL))
	{

		// if the counter equal to number of overflows do the function and reset the counter to 0
		if (Local_u16Counter == Global_TimerCallbackConf_overflow[TIMER2]->TIMER_U32ISRDoNum_ICR1)
		{
			TIMER_PFunctionPtr_overflow[TIMER2]();
			Local_u16Counter = 1;
			// if there is preload at it in the first over flow for next counter
			TCNT2 = (uint8)Global_TimerCallbackConf_overflow[TIMER2]->TIMER_u16OCR_TCNT_initVal;
		}
		else
		{
			Local_u16Counter++;
		}
	}
	else
	{
		/*do nothing*/
	}
}
// 7 $00C TIMER1 CAPT Timer/Counter1 Capture Event
void __vector_6(void) __attribute__((signal));
void __vector_6(void)
{
	if (TIMER_PFunctionPtr_ISR != NULL)
	{

		TIMER_PFunctionPtr_ISR();
	}
	else
	{
		/*do nothing*/
	}
}
// 8 $00E TIMER1 COMP A Timer/Counter1 Compare Match A
void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{
	static uint16 Local_u16Counter = 1; // init the overflows tracking counter

	if ((TIMER_PFunctionPtr_COM[TIMER1A] != NULL) && (Global_TimerCallbackConf_COM[TIMER1A] != NULL))
	{

		// if the counter equal to number of overflows do the function and reset the counter to 0
		if (Local_u16Counter == Global_TimerCallbackConf_COM[TIMER1A]->TIMER_U32ISRDoNum_ICR1)
		{
			TIMER_PFunctionPtr_COM[TIMER1A]();
			Local_u16Counter = 1;
		}
		else
		{
			/*do nothing*/
			Local_u16Counter++;
		}
	}
	else
	{
		/*do nothing*/
	}
}

// 9 $010 TIMER1 COMP B Timer/Counter1 Compare Match B
void __vector_8(void) __attribute__((signal));
void __vector_8(void)
{
	static uint16 Local_u16Counter = 1; // init the overflows tracking counter

	if ((TIMER_PFunctionPtr_COM[TIMER1B] != NULL) && (Global_TimerCallbackConf_COM[TIMER1B] != NULL))
	{

		// if the counter equal to number of overflows do the function and reset the counter to 0
		if (Local_u16Counter == Global_TimerCallbackConf_COM[TIMER1B]->TIMER_U32ISRDoNum_ICR1)
		{
			TIMER_PFunctionPtr_COM[TIMER1B]();
			Local_u16Counter = 1;
		}
		else
		{
			/*do nothing*/
			Local_u16Counter++;
		}
	}
	else
	{
		/*do nothing*/
	}
}

// 10 $012 TIMER1 OVF Timer/Counter1 Overflow
void __vector_9(void) __attribute__((signal));
void __vector_9(void)
{
	static uint16 Local_u16Counter = 1; // init the overflows tracking counter

	if ((TIMER_PFunctionPtr_overflow[TIMER1] != NULL) && (Global_TimerCallbackConf_overflow[TIMER1] != NULL))
	{
		// if there is preload at it in the first over flow
		// if the counter equal to number of overflows do the function and reset the counter to 0
		if (Local_u16Counter == Global_TimerCallbackConf_overflow[TIMER1]->TIMER_U32ISRDoNum_ICR1)
		{
			TIMER_PFunctionPtr_overflow[TIMER1]();
			Local_u16Counter = 1;
			// if there is preload at it in the first over flow for next counter
			TCNT1 = (uint16)Global_TimerCallbackConf_overflow[TIMER1]->TIMER_u16OCR_TCNT_initVal;
		}
		else
		{
			Local_u16Counter++;
		}
	}
	else
	{
		/*do nothing*/
	}
}
// 11 $014 TIMER0 COMP Timer/Counter0 Compare Match
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	static uint16 Local_u16Counter = 1; // init the overflows tracking counter

	if ((TIMER_PFunctionPtr_COM[TIMER0] != NULL) && (Global_TimerCallbackConf_COM[TIMER0] != NULL))
	{

		// if the counter equal to number of overflows do the function and reset the counter to 0
		if (Local_u16Counter == Global_TimerCallbackConf_COM[TIMER0]->TIMER_U32ISRDoNum_ICR1)
		{
			TIMER_PFunctionPtr_COM[TIMER0]();
			Local_u16Counter = 1;
		}
		else
		{
			Local_u16Counter++;
		}
	}
	else
	{
		/*do nothing*/
	}
}
// 12 $016 TIMER0 OVF Timer/Counter0 Overflow
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	static uint16 Local_u16Counter = 1; // init the overflows tracking counter

	if ((TIMER_PFunctionPtr_overflow[TIMER0] != NULL) && (Global_TimerCallbackConf_overflow[TIMER0] != NULL))
	{

		// if the counter equal to number of overflows do the function and reset the counter to 0
		if (Local_u16Counter == Global_TimerCallbackConf_overflow[TIMER0]->TIMER_U32ISRDoNum_ICR1)
		{
			TIMER_PFunctionPtr_overflow[TIMER0]();
			Local_u16Counter = 1;
			// if there is preload at it in the first over flow for next counter
			TCNT0 = (uint8)Global_TimerCallbackConf_overflow[TIMER0]->TIMER_u16OCR_TCNT_initVal;
		}
		else
		{
			Local_u16Counter++;
		}
	}
	else
	{
		/*do nothing*/
	}
}