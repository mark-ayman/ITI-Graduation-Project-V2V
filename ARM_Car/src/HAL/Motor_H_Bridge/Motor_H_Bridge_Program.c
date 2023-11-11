/*
 * Motor_H_Bridge_Program.c
 *
 *  Created on: Oct 29, 2023
 *      Author: marka
 */


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/GPIO/GPIO_int.h"



#include "Motor_H_Bridge_Config.h"
#include "Motor_H_Bridge_Interface.h"
#include "../../MCAL/TIMER/Timer_init.h"
#include "../../MCAL/SYSTICK/Systick_interface.h"


void H_Motor_H_Bridge_voidInit()
{
	GPIO_cfg_t IN1 = {.port = LeftMoter_IN1_Port ,.pin = LeftMoter_IN1_Pin , .mode=GPIO_MODE_OUTPUT , .out_type=GPIO_OUTPUTTYPE_PUSHPULL  ,.speed=GPIO_OUTSPEED_LOW};
	MGPIO_vInit(&IN1);
	GPIO_cfg_t IN2 = {.port = LeftMoter_IN2_Port ,.pin = LeftMoter_IN2_Pin , .mode=GPIO_MODE_OUTPUT , .out_type=GPIO_OUTPUTTYPE_PUSHPULL  ,.speed=GPIO_OUTSPEED_LOW};
	MGPIO_vInit(&IN2);
	GPIO_cfg_t IN3 = {.port = RightMoter_IN1_Port ,.pin = RightMoter_IN1_Pin , .mode=GPIO_MODE_OUTPUT , .out_type=GPIO_OUTPUTTYPE_PUSHPULL  ,.speed=GPIO_OUTSPEED_LOW};
	MGPIO_vInit(&IN3);
	GPIO_cfg_t IN4 = {.port = RightMoter_IN2_Port ,.pin = RightMoter_IN2_Pin , .mode=GPIO_MODE_OUTPUT , .out_type=GPIO_OUTPUTTYPE_PUSHPULL  ,.speed=GPIO_OUTSPEED_LOW};
	MGPIO_vInit(&IN4);

	GPIO_cfg_t ena = {.port = GPIO_PORTA ,.pin = GPIO_PIN11 , .mode=GPIO_MODE_OUTPUT , .out_type=GPIO_OUTPUTTYPE_PUSHPULL  ,.speed=GPIO_OUTSPEED_LOW};
	MGPIO_vInit(&ena);
	GPIO_cfg_t enb = {.port = GPIO_PORTA ,.pin = GPIO_PIN12 , .mode=GPIO_MODE_OUTPUT , .out_type=GPIO_OUTPUTTYPE_PUSHPULL  ,.speed=GPIO_OUTSPEED_LOW};
	MGPIO_vInit(&enb);


}
void H_Motor_H_Bridge_voidStop()
{


	//MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN11,GPIO_LOW);
	//MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN12,GPIO_LOW);


	MGPIO_vSetPinValFast(LeftMoter_IN1_Port,LeftMoter_IN1_Pin,GPIO_LOW);
	MGPIO_vSetPinValFast(LeftMoter_IN2_Port,LeftMoter_IN2_Pin,GPIO_LOW);
	MGPIO_vSetPinValFast(RightMoter_IN1_Port,RightMoter_IN1_Pin,GPIO_LOW);
	MGPIO_vSetPinValFast(RightMoter_IN2_Port,RightMoter_IN2_Pin,GPIO_LOW);

	MTimer_voidPWM(TIM2_TYPE , TIM_CHANNEL_1 ,49);
	MTimer_voidPWM(TIM2_TYPE , TIM_CHANNEL_3 ,49);
}
void H_Motor_H_Bridge_voidRight()
{



	MGPIO_vSetPinValFast(LeftMoter_IN1_Port,LeftMoter_IN1_Pin,GPIO_LOW);
	MGPIO_vSetPinValFast(LeftMoter_IN2_Port,LeftMoter_IN2_Pin,GPIO_HIGH);
	MGPIO_vSetPinValFast(RightMoter_IN1_Port,RightMoter_IN1_Pin,GPIO_HIGH);
	MGPIO_vSetPinValFast(RightMoter_IN2_Port,RightMoter_IN2_Pin,GPIO_LOW);

	MTimer_voidPWM(TIM2_TYPE , TIM_CHANNEL_1 ,8);
	MTimer_voidPWM(TIM2_TYPE , TIM_CHANNEL_3 ,8);
}
void H_Motor_H_Bridge_voidLeft()
{


	MGPIO_vSetPinValFast(LeftMoter_IN1_Port,LeftMoter_IN1_Pin,GPIO_HIGH);
	MGPIO_vSetPinValFast(LeftMoter_IN2_Port,LeftMoter_IN2_Pin,GPIO_LOW );
	MGPIO_vSetPinValFast(RightMoter_IN1_Port,RightMoter_IN1_Pin,GPIO_LOW );
	MGPIO_vSetPinValFast(RightMoter_IN2_Port,RightMoter_IN2_Pin,GPIO_HIGH);

	MTimer_voidPWM(TIM2_TYPE , TIM_CHANNEL_1 ,8);
	MTimer_voidPWM(TIM2_TYPE , TIM_CHANNEL_3 , 8);
}
void H_Motor_H_Bridge_voidForwardHighSpeed()
{

	//MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN11,GPIO_HIGH);
	//MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN12,GPIO_HIGH);


	MGPIO_vSetPinValFast(LeftMoter_IN1_Port,LeftMoter_IN1_Pin,GPIO_HIGH);
	MGPIO_vSetPinValFast(LeftMoter_IN2_Port,LeftMoter_IN2_Pin,GPIO_LOW);
	MGPIO_vSetPinValFast(RightMoter_IN1_Port,RightMoter_IN1_Pin,GPIO_HIGH);
	MGPIO_vSetPinValFast(RightMoter_IN2_Port,RightMoter_IN2_Pin,GPIO_LOW);

	MTimer_voidPWM(TIM2_TYPE , TIM_CHANNEL_3 ,5);
	MTimer_voidPWM(TIM2_TYPE , TIM_CHANNEL_1 ,5);
}

void H_Motor_H_Bridge_voidForwardLowSpeed()
{


	MGPIO_vSetPinValFast(LeftMoter_IN1_Port,LeftMoter_IN1_Pin,GPIO_LOW);
	MGPIO_vSetPinValFast(LeftMoter_IN2_Port,LeftMoter_IN2_Pin,GPIO_HIGH);
	MGPIO_vSetPinValFast(RightMoter_IN1_Port,RightMoter_IN1_Pin,GPIO_LOW);
	MGPIO_vSetPinValFast(RightMoter_IN2_Port,RightMoter_IN2_Pin,GPIO_HIGH);

	MTimer_voidPWM(TIM2_TYPE , TIM_CHANNEL_3 ,16);
	MTimer_voidPWM(TIM2_TYPE , TIM_CHANNEL_1 ,16);
}

void H_Motor_H_Bridge_voidForward()
{
	MGPIO_vSetPinValFast(LeftMoter_IN1_Port,LeftMoter_IN1_Pin,GPIO_LOW);
	MGPIO_vSetPinValFast(LeftMoter_IN2_Port,LeftMoter_IN2_Pin,GPIO_HIGH);
	MGPIO_vSetPinValFast(RightMoter_IN1_Port,RightMoter_IN1_Pin,GPIO_LOW);
	MGPIO_vSetPinValFast(RightMoter_IN2_Port,RightMoter_IN2_Pin,GPIO_HIGH);

	MTimer_voidPWM(TIM2_TYPE , TIM_CHANNEL_3 ,11);
	MTimer_voidPWM(TIM2_TYPE , TIM_CHANNEL_1 ,11);
}



void H_Motor_H_Bridge_voidSBackward()
{

	MGPIO_vSetPinValFast(LeftMoter_IN1_Port,LeftMoter_IN1_Pin,GPIO_HIGH);
	MGPIO_vSetPinValFast(LeftMoter_IN2_Port,LeftMoter_IN2_Pin,GPIO_LOW);
	MGPIO_vSetPinValFast(RightMoter_IN1_Port,RightMoter_IN1_Pin,GPIO_HIGH);
	MGPIO_vSetPinValFast(RightMoter_IN2_Port,RightMoter_IN2_Pin,GPIO_LOW);




	MTimer_voidPWM(TIM2_TYPE , TIM_CHANNEL_3 ,9);
	MTimer_voidPWM(TIM2_TYPE , TIM_CHANNEL_1 ,9);
}

