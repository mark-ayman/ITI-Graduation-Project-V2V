/*
 * EEPROM_Program.c
 *
 *  Created on: Aug 27, 2023
 *      Author: marka
 */


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "util/delay.h"

#include "EEPROM_Config.h"
#include "EEPROM_Private.h"
#include "EEPROM_Interface.h"

#include "../../MCAL/UART/UART_interface.h"

//#include "../../MCAL/I2C/I2C_Interface.h"

#include "../../MCAL/TWI/TWI_interface.h"

//
//void EEPROM_ErrorStateSendDataByte ( u16 Copy_u16ByteAddress , u8 Copy_u8Data)
//{
//
////	u8 LocalErrorState =STD_TYPES_OK;
//
//	u8 Local_u8EEPROMAddress = 0x50 ;
//
//	//#if EEPROM_Config_A2 == 0
//	Local_u8EEPROMAddress = 0x50 | (0 << 2) |  ( ( Copy_u16ByteAddress >> 8 ) ) ;
//	//#elif EEPROM_Config_A2 == 1
//	//Local_u8EEPROMAddress |= (1 << 2) |  ( ( Copy_u16ByteAddress >> 8 ) ) ;
//	//#endif
//
//
//	//TWI_Master_voidInit(TWI_Prescaler_1,2,0);
//
//	//TWI_Slave_voidInit(Local_u8EEPROMAddress);
//	UART_voidSendDataSync('A');
//
//	TWI_Start_Condition();
//
//	UART_voidSendDataSync('b');
//
//
//	TWI_Slave_Call_Determine(Local_u8EEPROMAddress , Write);
//
//	UART_voidSendDataSync('c');
//
//
//	TWI_MasterWrite_Data((u8)Copy_u16ByteAddress);
//
//	UART_voidSendDataSync('d');
//
//
//	TWI_MasterWrite_Data(Copy_u8Data);
//
//	UART_voidSendDataSync('e');
//
//
//	TWI_Stop_Conditon();
//
//	UART_voidSendDataSync('f');
//	//_delay_ms(10);
//
//}
//
// u8  EEPROM_ErrorStateRecieveDataByte (u16 Copy_u16ByteAddress ){
//
//	// u8 Local_Error=STD_TYPES_OK;
//
//	 u8 Local_u8EEPROMAddress = 0x50 ;
//
//	 u8 Data;
///*
//	#if EEPROM_Config_A2 == 0
//	Local_u8EEPROMAddress |= (0 << 2) |  ( (  Copy_u8ByteAddress >> 8  )) ;
//	#elif EEPROM_Config_A2 == 1
//	Local_u8EEPROMAddress |= (1 << 2) |  ( (  Copy_u8ByteAddress >> 8  )) ;
//	#endif
//*/
//	Local_u8EEPROMAddress = 0x50 | (0 << 2) |  ( ( Copy_u16ByteAddress >> 8 ) ) ;
//
//	//TWI_Master_voidInit(TWI_Prescaler_1,2,0);
//	//TWI_Slave_voidInit(Local_u8EEPROMAddress);
//
//	UART_voidSendDataSync('z');
//
//	TWI_Start_Condition();
//
//	UART_voidSendDataSync('u');
//	TWI_Slave_Call_Determine(Local_u8EEPROMAddress , Write);
//	UART_voidSendDataSync('v');
//	TWI_MasterWrite_Data((u8)Copy_u16ByteAddress);
//	UART_voidSendDataSync('v');
//	TWI_SendRepeatedStartCondition();
//		UART_voidSendDataSync('x');
//	TWI_Slave_Call_Determine( 0x50 | (0 << 2) |  ( ( Copy_u16ByteAddress >> 8 ) ) , Read);
//
//		UART_voidSendDataSync('M');
//	TWI_MasterRead_Data((&Data));
//	UART_voidSendDataSync('p');
//
//	TWI_Stop_Conditon();
//	//_delay_ms(10);
//
//	return (Data);
//}

/*
void EEPROM_ErrorStateSendDataByte ( u16 Copy_u16ByteAddress , u8 Copy_u8Data){
	TWI_ErrorStatusSendStartConditionWithACK();
	TWI_ErrorStatusSendSlaveAddressWithWriteACK(0x50 | (0 << 2) |  ( ( Copy_u16ByteAddress >> 8 ) ));
	TWI_ErrorStatusMasterWriteDataByteWithACK((u8*)Copy_u16ByteAddress);
	TWI_ErrorStatusMasterWriteDataByteWithACK(Copy_u8Data);
	TWI_voidSendStopCondition();
}
u8  EEPROM_ErrorStateRecieveDataByte (u16 Copy_u16ByteAddress ){
	u8 Data;
	TWI_ErrorStatusSendStartConditionWithACK();
	TWI_ErrorStatusSendSlaveAddressWithWriteACK(0x50 | (0 << 2) |  ( ( Copy_u16ByteAddress >> 8 ) ));
	TWI_ErrorStatusMasterWriteDataByteWithACK((u8*)Copy_u16ByteAddress);
	TWI_ErrorStatusSendRepeatedStartConditionWithACK();
	TWI_ErrorStatusSendSlaveAddressWithReadACK(0x50 | (0 << 2) |  ( ( Copy_u16ByteAddress >> 8 ) ));
	TWI_ErrorStatusMasterReadDataByteWithACK(&Data);
	TWI_voidSendStopCondition();
	return Data;
}
*/

ErrorState EEPROM_ErrorStateRecieveStreamDataByte(u16 Copy_u16ByteAddress	,u8* Copy_pu8Data, u8 Copy_u8NoBytes)
{
	u8 Local_u8ByteNo=0;
	ErrorState Local_ErrorState = STD_TYPES_OK ;
	u8 Local_u8I2cError = NoError ;
	/*Start Condition */
	Local_u8I2cError = TWI_ErrorStatusSendStartConditionWithACK();
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = Local_u8I2cError ;
	}
	/*Send SLA+W ACK*/
	Local_u8I2cError = TWI_ErrorStatusSendSlaveAddressWithWriteACK(0x50 | (EEPROM_A2 << 2) | (Copy_u16ByteAddress >> 8)	);
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = Local_u8I2cError ;
	}
	/*Send Reset of byte address*/
	Local_u8I2cError = TWI_ErrorStatusMasterWriteDataByteWithACK((u8) Copy_u16ByteAddress);
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = Local_u8I2cError ;
	}
	/*send repeated start*/
	Local_u8I2cError = TWI_ErrorStatusSendRepeatedStartConditionWithACK();
	if(Local_u8I2cError != NoError)
		{
			Local_ErrorState = Local_u8I2cError ;
		}
	/*Send SLA+R*/
	Local_u8I2cError = TWI_ErrorStatusSendSlaveAddressWithReadACK(0x50 | (EEPROM_A2 << 2) | (Copy_u16ByteAddress >> 8));
	if(Local_u8I2cError != NoError)
			{
				Local_ErrorState = Local_u8I2cError ;
			}
	/*Read Data */
	while(Local_u8ByteNo<Copy_u8NoBytes)
	//while(Copy_pu8Data[Local_u8ByteNo-1]!='\r')
	{

	TWI_ErrorStatusMasterReadDataByteWithACK(& Copy_pu8Data[Local_u8ByteNo] );
	if(( Copy_pu8Data[Local_u8ByteNo]==255))
	{
		break;
	}
	Local_u8ByteNo++;
	//if(Local_u8I2cError != NoError)
	//		{
	//			Local_ErrorState = Local_u8I2cError ;
	//		}
	}
	/*Stop Conditon*/
	TWI_voidSendStopCondition();
	_delay_ms(10);
	return Local_ErrorState ;
}

ErrorState  EEPROM_ErrorStateSendDataByte	( u16 Copy_u16ByteAddress , u8 Copy_u8Data	)
{
	ErrorState Local_ErrorState = STD_TYPES_OK ;
	u8 Local_u8I2cError = NoError ;
	/*Start Condition*/

	Local_u8I2cError = TWI_ErrorStatusSendStartConditionWithACK();
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Send SLA + W ACK*/
	Local_u8I2cError = TWI_ErrorStatusSendSlaveAddressWithWriteACK(0x50 | (EEPROM_A2 << 2) | (Copy_u16ByteAddress >> 8)	);
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Send Rest of byte address*/
	Local_u8I2cError = TWI_ErrorStatusMasterWriteDataByteWithACK((u8) Copy_u16ByteAddress);
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Send Data */

	Local_u8I2cError = TWI_ErrorStatusMasterWriteDataByteWithACK(Copy_u8Data );
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Stop Condition*/
	TWI_voidSendStopCondition();

	_delay_ms(10);

	return Local_ErrorState ;
}

ErrorState EEPROM_ErrorStateRecieveDataByte	( u16 Copy_u16ByteAddress	,u8* Copy_pu8Data)
{

	ErrorState Local_ErrorState = STD_TYPES_OK ;
	u8 Local_u8I2cError = NoError ;
	/*Start Condition */
//	UART_voidSendDataSync('M');
	Local_u8I2cError = TWI_ErrorStatusSendStartConditionWithACK();
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = Local_u8I2cError ;
	}
	/*Send SLA+W ACK*/
	//UART_voidSendDataSync('L');
	Local_u8I2cError = TWI_ErrorStatusSendSlaveAddressWithWriteACK(0x50 | (EEPROM_A2 << 2) | (Copy_u16ByteAddress >> 8)	);
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = Local_u8I2cError ;
	}
	/*Send Reset of byte address*/
	//UART_voidSendDataSync('w');
	Local_u8I2cError = TWI_ErrorStatusMasterWriteDataByteWithACK((u8) Copy_u16ByteAddress);
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = Local_u8I2cError ;
	}
	/*send repeated start*/
	//UART_voidSendDataSync('V');
	Local_u8I2cError = TWI_ErrorStatusSendRepeatedStartConditionWithACK();
	if(Local_u8I2cError != NoError)
		{
			Local_ErrorState = Local_u8I2cError ;
		}
	/*Send SLA+R*/
	//UART_voidSendDataSync('X');
	Local_u8I2cError = TWI_ErrorStatusSendSlaveAddressWithReadACK(0x50 | (EEPROM_A2 << 2) | (Copy_u16ByteAddress >> 8));
	if(Local_u8I2cError != NoError)
			{
				Local_ErrorState = Local_u8I2cError ;
			}
	/*Read Data */
	//UART_voidSendDataSync('Y');
	TWI_ErrorStatusMasterReadDataByteWithACK(Copy_pu8Data);
	if(Local_u8I2cError != NoError)
			{
				Local_ErrorState = Local_u8I2cError ;
			}
	//UART_voidSendDataSync('T');
	/*Stop Conditon*/
	//TWI_voidSendStopCondition();
	//TWI_ErrorStatusSendStartConditionWithACK();
	//_delay_ms(10);
	//UART_voidSendDataSync('P');

	return Local_ErrorState ;
}

