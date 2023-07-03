#ifndef UART_PRV_H
#define UART_PRV_H

#define IDLE 1
#define BUSY 2

#define UART_UMSEL_ASYNCHRONOUS         1u
#define UART_UMSEL_SYNCHRONOUS          2u
#define UART_UMSEL_ASYNCHRONOUS_DOUBLE  3u
#define UART_UPM_DISABLED   1u
#define UART_UPM_EVEN       2u
#define UART_UPM_ODD        3u

#define UART_USBS_1BIT      1u
#define UART_USBS_2BIT      2u

#define UART_CH_SIZE_5      1u
#define UART_CH_SIZE_6      2u
#define UART_CH_SIZE_7      3u
#define UART_CH_SIZE_8      4u
#define UART_CH_SIZE_9      5u

static void _helper_VoidNumToStr(sint32 copy_s32number);

#endif
