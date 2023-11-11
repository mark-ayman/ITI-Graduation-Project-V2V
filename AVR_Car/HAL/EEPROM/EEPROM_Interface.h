/*
 * EEPROM_Interface.h
 *
 *  Created on: Aug 27, 2023
 *      Author: marka
 */

#ifndef HAL_EEPROM_EEPROM_INTERFACE_H_
#define HAL_EEPROM_EEPROM_INTERFACE_H_


ErrorState EEPROM_ErrorStateSendDataByte ( u16 Copy_u8ByteAddress , u8 Copy_u8Data);

ErrorState EEPROM_ErrorStateRecieveDataByte	( u16 Copy_u16ByteAddress	,u8* Copy_pu8Data);

ErrorState EEPROM_ErrorStateRecieveStreamDataByte(u16 Copy_u16ByteAddress	,u8* Copy_pu8Data, u8 Copy_u8NoBytes);

#endif /* HAL_EEPROM_EEPROM_INTERFACE_H_ */
