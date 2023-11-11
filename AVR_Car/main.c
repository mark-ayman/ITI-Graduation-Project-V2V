/*
 * main.c
 *
 *  Created on: Oct 6, 2023
 *      Author: marka
 */


#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "util/delay.h"
#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/UART/UART_interface.h"
#include "MCAL/TIMER/TIMER_interface.h"
#include "MCAL/EXTI/EXTI_interface.h"
#include "HAL/Motor_H_Bridge/Motor_H_Bridge_Interface.h"
#include "MCAL/GIE/GIE_interface.h"
#include "HAL/CLCD/CLCD_interface.h"

void APP(void);
TIMER_CONFIG_T0 PWM;

int main(void){

	/**************  AVR PIN CONFIGURATION   ***************/
	/**************  UART PIN Configuration  ***************/
	DIO_voidSetPinDirection(DIO_PORTD , DIO_PIN0 , DIO_INPUT);
	DIO_voidSetPinDirection(DIO_PORTD , DIO_PIN1 , DIO_OUTPUT);
	/************   H-Bridge PIN Configuration  *************/
	DIO_voidSetPinDirection(DIO_PORTA , DIO_PIN0 , DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTA , DIO_PIN1 , DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTA , DIO_PIN2 , DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTA , DIO_PIN3 , DIO_OUTPUT);
	/*************    PWM MOTOR DRIVER    *****************/
	DIO_voidSetPinDirection(DIO_PORTB , DIO_PIN3 , DIO_OUTPUT);
	//>> another one for change mode of direction
	//>>
	/*************   AVR INITIALIZATION   *************/
	UART_voidInit();
	GIE_voidEnable();
	CLCD_voidInit();
	/***************************************************/
	TIMER_CONFIG_T0 PWM = { .timer_mode = FAST_PWM ,.control_oc = CLEAR_OC_FASTPWM,.clock_source =  FCPU_DIVBY_8,.Compare_Value = 200};
	Timer_voidT0Init(&PWM);

	//UART_voidRecvStrSync	(Local_u8ReturnString);
	//UART_voidSendStrSync	(Local_u8ReturnString);
	//UART_voidSendDataAsync(call_back_Sent);
	while(1)
	{
		//UART_voidRecvDataAsync	(APP);
		u8 Return_Val;
		UART_voidRecvDataSync(&Return_Val);
		if (Return_Val=='F')
		{
			H_Motor_H_Bridge_voidForward();

			Timer_StartT0(&PWM,200);

		}
		else if(Return_Val=='B')
		{
			H_Motor_H_Bridge_voidSBackward();

			Timer_StartT0(&PWM,200);

		}
		else if(Return_Val=='L')
		{
			H_Motor_H_Bridge_voidLeft();

			Timer_StartT0(&PWM,200);

		}
		else if(Return_Val=='R')
		{
			H_Motor_H_Bridge_voidRight();

			Timer_StartT0(&PWM,200);

		}
		else if(Return_Val=='S')
		{
			H_Motor_H_Bridge_voidStop();

			Timer_StartT0(&PWM,0);

		}
	}
}


/*void APP(void)
{

	u8 Return_Val;
	UART_voidRecvDataSync(&Return_Val);
	if (Return_Val=='F')
	{
		H_Motor_H_Bridge_voidForward();

		Timer_StartT0(&PWM,200);

	}
	else if(Return_Val=='B')
	{
		H_Motor_H_Bridge_voidSBackward();

		Timer_StartT0(&PWM,200);

	}
	else if(Return_Val=='L')
	{
		H_Motor_H_Bridge_voidLeft();

		Timer_StartT0(&PWM,200);

	}
	else if(Return_Val=='R')
	{
		H_Motor_H_Bridge_voidRight();

		Timer_StartT0(&PWM,200);

	}
	else if(Return_Val=='S')
	{
		H_Motor_H_Bridge_voidStop();

		Timer_StartT0(&PWM,0);

	}

}
*/
