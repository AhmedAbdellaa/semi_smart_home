#ifndef TIMER_INTERFACE
#define TIMER_INTERFACE

typedef enum
{
    TIMER0 = 0u,
    TIMER2=1,
    TIMER1=2,
    TIMER1A=2,
    TIMER1B=3,
    

} TIMER_TINum_t;
 
    
#define TIMER_WGM_Normal                0u
#define TIMER_WGM_PWM_PC_8              1u
#define TIMER_WGM_PWM_PC_9              2u
#define TIMER_WGM_PWM_PC_10             3u
#define TIMER_WGM_CTC_OCR1A             4u
#define TIMER_WGM_PWM_FAST_8            5u
#define TIMER_WGM_PWM_FAST_9            6u
#define TIMER_WGM_PWM_FAST_10           7u
#define TIMER_WGM_PWM_PFC_ICR1          8u
#define TIMER_WGM_PWM_PFC_OCR1          9u
#define TIMER_WGM_PWM_PC_ICR1           10u
#define TIMER_WGM_PWM_PC_OCR1A          11u
#define TIMER_WGM_CTC_ICR               12u
#define TIMER_WGM_PWM_FAST_ICR1         14u
#define TIMER_WGM_PWM_FAST_OCR1A        15u

#define TIMER0_2WGM_NORMAL   0u
#define TIMER0_2WGM_PWM      1u
#define TIMER0_2WGM_CTC      2u
#define TIMER0_2WGM_FAST_PWM 3u

#define TIMER_COM_NORMAL        0u
#define TIMER_COM_TOGGLE        1u
#define TIMER_COM_CLEAR         2u
#define TIMER_COM_SET           3u
#define TIMER_COM_RESERVED      4u  

#define TIMER_NO_CLK                    0U
#define TIMER_NO_PS                     1U
#define TIMER_PS_8                      2U
#define TIMER_PS_64                     3U
#define TIMER_PS_256                    4U
#define TIMER_PS_1024                   5U
#define TIMER_EXT_CLK_FALLING_EDGE      6U
#define TIMER_EXT_CLK_RISING_EDGE       7U

#define ICU_FALLING_EDGE 1u
#define ICU_RISING_EDGE 2u
// typedef enum
// {
//     TIMER0_2WGM_NORMAL = 0u,
//     TIMER0_2WGM_PWM,
//     TIMER0_2WGM_CTC,
//     TIMER0_2WGM_FAST_PWM
// } TIMER0_2WGM_t;

// typedef enum
// {
//     TIMER_COM_NORMAL = 0u,
//     TIMER_COM_TOGGLE,
//     TIMER_COM_CLEAR,
//     TIMER_COM_SET,
//     TIMER_COM_RESERVED
// } TIMER_COM_t;

// typedef enum
// {
//     TIMER_NO_CLK = 0u,
//     TIMER_NO_PS,
//     TIMER_PS_8,
//     TIMER_PS_64,
//     TIMER_PS_256,
//     TIMER_PS_1024,
//     TIMER_EXT_CLK_FALLING_EDGE,
//     TIMER_EXT_CLK_RISING_EDGE
// } TIMER_CLK_PS_t;
// typedef struct TIMER0_2_CONFIG_t{
//     TIMER0_2WGM_t   T_WGM;//wave generation mode
//     TIMER_COM_t     T_COM;//compare on mode 
//     TIMER_CLK_PS_t  T_CLK;//timer clock source
// }TIMER0_2_CONFIG_t;


typedef struct TIMER_CALLBACK_CONFIG_t
{

    /// @brief in [timer0 , timer1 and timer2] overflow mode :value of the preload step \
    in other modes used to define "OCR" register
    uint16 TIMER_u16OCR_TCNT_initVal;
    /// @brief  in [timer0 , timer1 and timer2] overflow mode : number of go into isr include preload overflow step \
    in timer1 pwm mode and TIMER_WGM_CTC_ICR :used to define "TOP" value
    uint32 TIMER_U32ISRDoNum_ICR1;
} TIMER_CALLBACK_CONFIG_t;



/// @brief initialize timer0 base on configuration file 
void TIMER0_voidInit(void);

/// @brief initialize timer1 base on configuration file 
void TIMER1_voidInit(void);

/// @brief initialize timer2 base on configuration file 
void TIMER2_voidInit(void);

/// @brief start overflow interrupt for given timer number *timer will enter your isr function when it reach number of overflow you pass
/// @param copy_TINUM timer number choose from : [TIMER0,TIMER1,TIMER2]
/// @param reference_TimerCallbackConf pass preload value and number of overflows
/// @param copy_pvFuncPtr address to function to execute after finish all overflows you pass
/// @return error state if everything is ok will return OK
uint8 TIMER_u8Start_OV_Interrupt(TIMER_TINum_t copy_TINUM, TIMER_CALLBACK_CONFIG_t *reference_TimerCallbackConf, void (*copy_pvFuncPtr)(void));

/// @brief start compare on match interrupt for given timer number *timer will enter your isr function when it reach number of count you pass
/// @param copy_TINUM timer number choose from : [TIMER0,TIMER1A,TIMER1B,TIMER2]
/// @param reference_TimerCallbackConf pass OCR value and number of repeat
/// @param copy_pvFuncPtr address to function to execute after finish all counts you pass
/// @return error state if everything is ok will return OK
uint8 TIMER_u8Start_COM_Interrupt(TIMER_TINum_t copy_TINUM, TIMER_CALLBACK_CONFIG_t *reference_TimerCallbackConf, void (*copy_pvFuncPtr)(void));

/// @brief disable overflow interrupt for given timer
/// @param copy_TINUM timer number choose from : [TIMER0,TIMER1,TIMER2]
void TIMER_voidDisable_OV_Interrupt(TIMER_TINum_t copy_TINUM);

/// @brief disable compare on match interrupt for given timer
/// @param copy_TINUM timer number choose from : [TIMER0,TIMER1A,TIMER1B,TIMER2]
void TIMER_voidDisable_COM_Interrupt(TIMER_TINum_t copy_TINUM);

/// @brief change Compare Output Mode for given timer
/// @param copy_TINUM timer number choose from : [TIMER0,TIMER1,TIMER2]
/// @param copy_COM choose from TIMER_COM_ macros 
void TIMER_voidChangCOM_Mode(TIMER_TINum_t copy_TINUM, uint8 copy_COM);

/// @brief change Waveform Generation Mode
/// @param copy_TINUM timer number choose from : [TIMER0,TIMER1,TIMER2]
/// @param copy_COM choose from TIMER_WGM_ macros  for [timer0 , timer2] and TIMER0_2WGM_ for timer1
void TIMER_voidChangWGM_Mode(TIMER_TINum_t copy_TINUM, uint8 copy_WGM);

/// @brief start doing pwm for given waveform in timer_init or TIMER_voidChangWGM_Mode(...)
/// @param copy_TINUM timer number choose from : [TIMER0,TIMER1A,TIMER1B,TIMER2]
/// @param copy_u16OCR OCR value for compare 
///@param copy_u16ICR1 if choose TIMER_WGM_PWM_FAST_ICR1 pass ICR value 
void TIMER_voidStart_PWM(TIMER_TINum_t copy_TINUM,uint16 copy_u16OCR,uint16 copy_u16ICR1);
void TIMER_voidSetTCNT(TIMER_TINum_t copy_TINUM,uint16 copy_u16TCNTVal);

/// @brief initialize ICU base on configuration file **timer1 must be initialize before
void ICU_voidInit(void);

/// @brief change trigger source for icu unit
/// @param copy_u8TrSrc choose from [ICU_FALLING_EDGE ,ICU_RISING_EDGE]
void ICU_voidSetTriggerSrc(uint8 copy_u8TrSrc);

/// @brief enable ICU interrupt 
/// @param copy_pvFuncPtr address to function to execute when source triggered
/// @return error state if everything is ok will return OK
uint8 ICU_u8IntEnable(void(*copy_pvFuncPtr)(void));

/// @brief disable ICU interrupt 
void ICU_voidIntDisable();

/// @brief get ICR1 register value
uint16 ICU_u16GetICRVal();

#endif
