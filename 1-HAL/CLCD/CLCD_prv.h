#ifndef CLCD_PRV_H
#define CLCD_PRV_H

#define FOUR_BIT        1U
#define EIGHT_BIT       2U

#define ENABLED     1U
#define DISABLED    2u



static void _helper_VoidReverseBuffer(uint8* ref_u8Buffer, uint8 copy_u8StartIndex,uint8 copy_u8EndIndex);

static void _helper_VoidNumToStr(sint32 copy_u32number,uint8* ref_u8Buffer);

#if CLCD_u8CONNECTION_MODE ==  FOUR_BIT
static void voidSetHalfDataPort(uint8 copy_u8FourBitData);
#endif
static void voidSendEnablePulse();
#endif
