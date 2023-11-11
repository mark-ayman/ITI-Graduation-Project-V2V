/*
 * UART_private.h
 *
 *  Created on: Aug 21, 2023
 *      Author: First
 */

#ifndef MCAL_UART_UART_PRIVATE_H_
#define MCAL_UART_UART_PRIVATE_H_

#define UDR_REG			*((volatile u8*)0x2C)
#define UCSRA_REG		*((volatile u8*)0x2B)
#define UCSRB_REG		*((volatile u8*)0x2A)
#define UCSRC_REG		*((volatile u8*)0x40)
#define UBRRL_REG		*((volatile u8*)0x29)
#define UBRRH_REG		*((volatile u8*)0x40)


#endif /* MCAL_UART_UART_PRIVATE_H_ */
