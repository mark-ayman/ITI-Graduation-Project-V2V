/*
 * ADC_program.c
 *
 *  Created on: Aug 14, 2023
 *      Author: First
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_private.h"


//left or right at config



typedef struct {
	u8 ADC_VREF;
	u8 ADC_ChannelType;
	u8 ADC_Mechanisim;
	u8 ADC_Prescalaer;
}ADC_t;


typedef enum {
	Prescaler_2=1,
	Prescaler_4,
	Prescaler_8,
	Prescaler_16,
	Prescaler_32,
	Prescaler_64,
	Prescaler_128,
}Prescaler;

void ADC_voidInit	(void)
{
	/*
		 * reference volatge = 5 v
		 * Right Adjustment
		 * ADC0
		 * Enable ADC
		 * Disnable PIE ((	polling		))
		 * prescaler / 128
		 * */

		//SET_BIT(ADCSRA_REG,ADC_ADCSRA_Enable_Bit);
		//SET_BIT(ADCSRA_REG,ADC_ADCSRA_Interrup_Bit);

		ADMUX_REG =  0b11000000;
		ADCSRA_REG = 0b10010111;
}

u16 ADC_u16ConvertedValue	(u8 Copy_u8Channel )
{
	u8 time_out_counter=0;

	ADMUX_REG = ADMUX_REG & MASKING_REG ;
	ADMUX_REG |= Copy_u8Channel ;
	u16 Local_u16Conv  = 0 ;

	//AutoTrigger
//	SET_BIT(ADCSRA_REG,ADC_ADCSRA_AutoTriggerEnable_Bit);

	//Free Runing
//	SFIOR_REG = SFIOR_REG & 0b00011111 ;
//  SFIOR_REG = SFIOR_REG | 0 ;


	// Start Conversion
	SET_BIT(ADCSRA_REG , ADC_ADCSRA_StartConversion_Bit );
	// PIF == 1 -> ADC finish conversion
	while((GET_BIT(ADCSRA_REG , ADC_ADCSRA_FLAG_BIT ) == 0 )&&time_out_counter<=2000 )
	{
		time_out_counter++;
	}

				//TIME OUT MECHANISM
	if((GET_BIT(ADCSRA_REG , ADC_ADCSRA_FLAG_BIT ) == 0 )&&time_out_counter==2000 )
	{
		//DO NOTHING
	}
	else
	{
		// Clear Flag
		SET_BIT(ADCSRA_REG , ADC_ADCSRA_FLAG_BIT) ;
		//Read Converted Data
		Local_u16Conv = (ADCL_REG) | (ADCH_REG << 8) ;
	}


	return Local_u16Conv ;
}










