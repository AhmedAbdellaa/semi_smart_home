#ifndef EXTI_INTERFACE
#define EXTI_INTERFACE

#define LOW_LEVEL 1
#define ON_CHANGE 2
#define FALLING_EDGE 3
#define RISING_EDGE 4
typedef enum {
    INT0,
    INT1,
    INT2,
    
}EXTI_IntNum_t;


/// @brief initialize interrupts as given in configuration file
void EXTI_voidInit(void);

/// @brief change trigger action for given Interrupt
/// @param copy_IntNum Interrupt number choose from EXTI enum
/// @param copy_SenseCtrl trigger source number [LOW_LEVEL:RISING_EDGE]
/// @return error state if everything is ok will return OK
uint8 EXTI_u8SetSenceCtrl(EXTI_IntNum_t copy_IntNum,uint8 copy_SenseCtrl);

/// @brief enable specific interrupt by set GISR-bit for it with high
/// @param copy_IntNum Interrupt number choose from EXTI enum
/// @return error state if everything is ok will return OK
uint8 EXTI_u8IntEnable(EXTI_IntNum_t copy_IntNum);

/// @brief Disable specific interrupt by set GISR-bit for it with low
/// @param copy_IntNum Interrupt number choose from EXTI enum
/// @return error state if everything is ok will return OK
uint8 EXTI_u8IntDisable(EXTI_IntNum_t copy_IntNum);

/// @brief provide ISR function for given interrupt
/// @param copy_IntNum Interrupt number choose from EXTI enum  
/// @param copy_pvFuncPtr address of the function want to execute when interrupt happen
/// @return error state if everything is ok will return OK
uint8 EXTI_u8SetCallBack(EXTI_IntNum_t copy_IntNum,void(*copy_pvFuncPtr)(void));

#endif
