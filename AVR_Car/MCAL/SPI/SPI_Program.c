/*
 * SPI_Program.c
 *
 *  Created on: Aug 21, 2023
 *      Author: marka
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "SPI_Config.h"
#include "SPI_Private.h"
#include "SPI_interface.h"


void SPI_voidInit(SPI_t t1){
	switch (t1.tech){
	case polling:
		CLR_BIT(SPCR_REG, SPI_INT_ENB_BIT);
		break;
	case interrupt:
		SET_BIT(SPCR_REG,SPI_INT_ENB_BIT);
		break;
	}

	switch (t1.D_O){
	case MSB :
		CLR_BIT(SPCR_REG,SPI_DATA_ORDER_BIT);
		break;
	case LSB :
		SET_BIT(SPCR_REG,SPI_DATA_ORDER_BIT);
		break;
	}

	switch (t1.CLK_POL){
		case Leading_Rising_Tralling_Falling   :
			CLR_BIT(SPCR_REG,SPI_CLK_POL_BIT);
			break;
		case Leading_Falling_Tralling_Rising :
			SET_BIT(SPCR_REG,SPI_CLK_POL_BIT);
			break;
		}
	switch (t1.CLK_PH){
		case Leading_Sample_Tralling_Setup   :
			CLR_BIT(SPCR_REG,SPI_CLK_PH_BIT);
			break;
		case Leading_Setup_Tralling_Sample :
			SET_BIT(SPCR_REG,SPI_CLK_PH_BIT);
			break;
		}
	SPCR_REG  = SPCR_REG  & 248;
	SPCR_REG  = SPCR_REG  | t1.CLK;

}


u8 SPI_voidTransmitData (u8 copy_u8SendData){

	SPDR_REG=copy_u8SendData;

	while(GET_BIT(SPSR_REG,7)==0);

	return SPDR_REG;
}
