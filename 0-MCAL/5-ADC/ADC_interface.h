#ifndef ADC_INTERFACE
#define ADC_INTERFACE

typedef enum{
	ADC0_SINGLE_ENDED =0   ,
	ADC1_SINGLE_ENDED    ,
	ADC2_SINGLE_ENDED    ,
	ADC3_SINGLE_ENDED    ,
	ADC4_SINGLE_ENDED    ,
	ADC5_SINGLE_ENDED    ,
	ADC6_SINGLE_ENDED    ,
	ADC7_SINGLE_ENDED    ,
	ADC0_POS_ADC0_NEG_10x_GAIN        ,
	ADC1_POS_ADC0_NEG_10x_GAIN        ,
	ADC0_POS_ADC0_NEG_200x_GAIN       ,
	ADC1_POS_ADC0_NEG_200x_GAIN       ,
	ADC2_POS_ADC2_NEG_10x_GAIN        ,
	ADC3_POS_ADC2_NEG_10x_GAIN        ,
	ADC2_POS_ADC2_NEG_200x_GAIN       ,
	ADC3_POS_ADC2_NEG_200x_GAIN       ,
	ADC0_POS_ADC1_NEG_1x_GAIN         ,
	ADC1_POS_ADC1_NEG_1x_GAIN         ,
	ADC2_POS_ADC1_NEG_1x_GAIN         ,
	ADC3_POS_ADC1_NEG_1x_GAIN         ,
	ADC4_POS_ADC1_NEG_1x_GAIN         ,
	ADC5_POS_ADC1_NEG_1x_GAIN         ,
	ADC6_POS_ADC1_NEG_1x_GAIN         ,
	ADC7_POS_ADC1_NEG_1x_GAIN         ,
	ADC0_POS_ADC2_NEG_1x_GAIN         ,
	ADC1_POS_ADC2_NEG_1x_GAIN         ,
	ADC2_POS_ADC2_NEG_1x_GAIN         ,
	ADC3_POS_ADC2_NEG_1x_GAIN         ,
	ADC4_POS_ADC2_NEG_1x_GAIN         ,
	ADC5_POS_ADC2_NEG_1x_GAIN
}ADC_channel_t;


typedef struct ADC_CHAIN_config_t{
	ADC_channel_t ConversionChannel;
	uint16* result;
	void(*pvnotificationFunction)(void);
}ADC_CHAIN_config_t;

/// @brief initialize ADC as given in configuration file
void ADC_voidInit();

/// @brief execute adc for given channel by pulling (wait until adc finish)
/// @param copy_Channel channel to execute adc on it choose from ADC_channel_t enum
/// @param referance_u16DigResult address of unsigned 16-bits variable address to store adc result
/// @return error state if everything is ok will return OK
uint8 ADC_u8StartConverstionSync(ADC_channel_t copy_Channel,uint16* referance_u16DigResult);


/// @brief execute adc for given channel and executer ISR when finish
/// @param copy_Channel channel to execute adc on it choose from ADC_channel_t enum
/// @param referance_u16DigResult address unsigned 16-bits variable address to store adc result
/// @param copy_pvNotificationFunc address of the function want to execute when interrupt happen
/// @return error state if everything is ok will return OK
uint8 ADC_u8StartConverstionAsync(ADC_channel_t copy_Channel,uint16* referance_u16DigResult,void (*copy_pvNotificationFunc)(void));

/// @brief execute async conversion fo given list of channels by same sort
/// @param referance_adcChain address of devises list want to execute adc on it 
/// @param copy_u8NumberOfADC number of devises in the given list
/// @return error state if everything is ok will return OK
uint8 ADC_u8StartChainConverstionAsync(ADC_CHAIN_config_t* referance_adcChain,uint8 copy_u8NumberOfADC);
/// @brief chain conversation helper function for internal use only
void ADC_voidChainNotification();
#endif

