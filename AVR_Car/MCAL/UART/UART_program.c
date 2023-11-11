/*
 * UART_program.c
 *
 *  Created on: Aug 21, 2023
 *      Author: First
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"


void UART_voidInit	(void)
{
	UCSRB_REG = 0b00011000 ;

	/*Config USCRC */
	u8 Local_u8Var	= 0b10000000 ;
	/*	Async	*/
	CLR_BIT(Local_u8Var , 6 );
	/*	Disable parity */
	CLR_BIT(Local_u8Var , 5);
	CLR_BIT(Local_u8Var , 4);
	/*	1 Stop Bit */
	CLR_BIT(Local_u8Var , 3);
	/*	8 Bit Mode , UCS2 -- > 0 , UCS1,0 --> 1 */
	SET_BIT(Local_u8Var , 2 );
	SET_BIT(Local_u8Var , 1 );
	/*CPOL --> Leading Edge ( Raising )*/
	CLR_BIT(Local_u8Var , 0 );

	UCSRC_REG = Local_u8Var ;

	/*Baud Rate */
	UBRRL_REG = (u8)	 UART_BAUD_RATE;
	UBRRH_REG = (u8)	(UART_BAUD_RATE >> 8 );

}

void UART_voidSendDataSync	(u8 Copy_u8Data)
{
	/*Check if buffer is empty */
	while ( GET_BIT(UCSRA_REG , 5) == 0 );

	/*Send Data */
	UDR_REG = Copy_u8Data ;
}

void UART_voidRecvDataSync	(u8 *Copy_pu8RecievedData)
{
	u8 count_char=0;
	/*Wait untill Recieve Data */
	while ( GET_BIT(UCSRA_REG , 7 ) == 0 ) ;
	if(Copy_pu8RecievedData != NULL)
	{
		//*Copy_pu8RecievedData = UDR_REG ;
	   *Copy_pu8RecievedData = UDR_REG;
	}
}

void UART_voidSendStrSync	(u8 *Copy_u8Data){
	u8 Local_etraro = 0;
	while(Copy_u8Data[Local_etraro] != '\0'){
		UART_voidSendDataSync	(Copy_u8Data[Local_etraro]);
		Local_etraro++;
	}
}

void UART_voidRecvStrSync	(u8 *Copy_pu8RecievedData){
	u8 Local_etraro = 0;
		while(Local_etraro != 5){
			UART_voidRecvDataSync	(Copy_pu8RecievedData[Local_etraro]);
			Local_etraro++;
		}
		Copy_pu8RecievedData[Local_etraro]='\0';
}

static u8 UART_u8Flag = 0 ;
static void (*Glo_Pf) (void) = NULL ;

void UART_voidRecvDataAsync	(void (*Copy_pfNotification) ( void))
{
	if( (Copy_pfNotification != NULL) && (UART_u8Flag == 0))
	{
		UART_u8Flag=1;
		Glo_Pf = Copy_pfNotification;
		/*enable_pie*/
		SET_BIT(UCSRB_REG,7);
	}
}

u8 UART_Return_Rec_Data(void){
	return UDR_REG;
}

void UART_Sent_Data(u8 Copy_u8SentData){
	UDR_REG = Copy_u8SentData;
}

void UART_voidSendDataAsync	(void (*Copy_pfNotification) (void)){
	if(Copy_pfNotification != NULL	&&	UART_u8Flag	==	0){
		UART_u8Flag=1;
		Glo_Pf = Copy_pfNotification;
		/*TX Complete Interrupt Enable*/
		SET_BIT(UCSRB_REG,5);
	}
}

void __vector_13	(void) __attribute__((signal));
void __vector_13	(void)
{
	if(Glo_Pf != NULL )
	{
		Glo_Pf();
	}
	/* 	Disable PIE		*/
	CLR_BIT(UCSRB_REG,7);
	/* Clear Flag */
	UART_u8Flag = 0 ;
}

void __vector_14	(void) __attribute__((signal));
void __vector_14	(void)
{
	if(Glo_Pf != NULL )
	{
		Glo_Pf();
	}
	/* 	Disable PIE	: UDR Complete Interrupt 	*/
	CLR_BIT(UCSRB_REG,5);
	/* Clear Flag */
	UART_u8Flag = 0 ;
}
