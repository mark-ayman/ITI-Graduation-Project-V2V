/*
 * UART_interface.h
 *
 *  Created on: Aug 21, 2023
 *      Author: First
 */

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

void UART_voidInit	(void);

void UART_voidSendDataSync	(u8 Copy_u8Data);

void UART_voidSendStrSync	(u8 *Copy_u8Data);

void UART_voidRecvDataSync	(u8 *Copy_pu8RecievedData);

void UART_voidRecvStrSync	(u8 *Copy_pu8RecievedData);

void UART_voidRecvDataAsync	(void (*Copy_pfNotification) ( void));

void UART_voidSendDataAsync	(void (*Copy_pfNotification) ( void));

void UART_Sent_Data(u8 Copy_u8SentData);

u8 UART_Return_Rec_Data(void);

#endif /* MCAL_UART_UART_INTERFACE_H_ */
