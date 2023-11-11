/**
 * @file Ultrasonic_program.c
 * @authors Hossam Elzhar , Mohammed Akram
 * @brief functions implementations for ultrasonic
 * @version 1.0
 * @date 2023-02-10
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/GPIO/GPIO_int.h"
#include "../../MCAL/SYSTICK/Systick_interface.h"
#include "../../MCAL/TIMER/Timer_init.h"
#include "../../MCAL/UART/UART_int.h"
#include "../../HAL/Motor_H_Bridge/Motor_H_Bridge_Interface.h"

#include "Ultrasonic_interface.h"




extern volatile u32 Distance;
u32 Ultrasonic_Capture1;
u32 Ultrasonic_Capture2;
u32 Ultrasonic_Time;
u8 Ultrasonic_flag;

extern GPIO_cfg_t LED ;
extern GPIO_cfg_t Buzzer;


/**
 * @brief trigger function for ultrasonic
 * @param void
 * @return void
 *
 */
void Ultrasonic_voidTrigger(void)
{
	MTimer_voidClearCounterReg(TIM3_TYPE);
	MGPIO_vSetPinValue(GPIO_PORTA, GPIO_PIN4,GPIO_HIGH);
	for (u32 i = 0; i < 15 * 30; i++) {
		asm("NOP");
	}
	MGPIO_vSetPinValue(GPIO_PORTA, GPIO_PIN4,GPIO_LOW);
}


/**
 * @brief interrupt function for ultrasonic
 * @param void
 * @return void
 */
void TIM3_IRQHandler(void)
{

	if (Ultrasonic_flag == 0)
	{
		Ultrasonic_Capture1 = MTimer_u32ReadCaptureReg(TIM3_TYPE , TIM_CHANNEL_1);
		Ultrasonic_flag = 1;
	}
	else if (Ultrasonic_flag == 1)
	{
		Ultrasonic_Capture2 = MTimer_u32ReadCaptureReg(TIM3_TYPE , TIM_CHANNEL_1);
		MTimer_voidClearCounterReg(TIM3_TYPE);
		Ultrasonic_flag = 0;
		Ultrasonic_Time = Ultrasonic_Capture2 - Ultrasonic_Capture1;		
		Distance = Ultrasonic_Time * (0.068/4);
		//MUSART_vTransmitNumSynch(USART2,Distance);
		//Distance = (time * sound speed) / 2
		//Distance = (Counts * tick time) * 0.034cm/u)/2
		//tick time = prescaler/timer freq.
		//tick time = 64 / 16 = 4
		// Distance = (counts*4 *0.034)/2

	}
}
