/*
 * Motor_H_Bridge_Program.c
 *
 *  Created on: Oct 31, 2023
 *      Author: marka
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"


#include "Motor_H_Bridge_Config.h"
#include "Motor_H_Bridge_Interface.h"

#include "../../MCAL/DIO/DIO_interface.h"

void H_Motor_H_Bridge_voidStop()
{

	DIO_voidSetPinValue(LeftMoter_IN1_Port,LeftMoter_IN1_Pin,DIO_LOW);
	DIO_voidSetPinValue(LeftMoter_IN2_Port,LeftMoter_IN2_Pin,DIO_LOW);
	DIO_voidSetPinValue(RightMoter_IN1_Port,RightMoter_IN1_Pin,DIO_LOW);
	DIO_voidSetPinValue(RightMoter_IN2_Port,RightMoter_IN2_Pin,DIO_LOW);

}
void H_Motor_H_Bridge_voidRight()
{

	DIO_voidSetPinValue(LeftMoter_IN1_Port,LeftMoter_IN1_Pin,DIO_HIGH);
	DIO_voidSetPinValue(LeftMoter_IN2_Port,LeftMoter_IN2_Pin,DIO_LOW);
	DIO_voidSetPinValue(RightMoter_IN1_Port,RightMoter_IN1_Pin,DIO_LOW);
	DIO_voidSetPinValue(RightMoter_IN2_Port,RightMoter_IN2_Pin,DIO_HIGH);

}
void H_Motor_H_Bridge_voidLeft()
{

	DIO_voidSetPinValue(LeftMoter_IN1_Port,LeftMoter_IN1_Pin,DIO_LOW);
	DIO_voidSetPinValue(LeftMoter_IN2_Port,LeftMoter_IN2_Pin,DIO_HIGH);
	DIO_voidSetPinValue(RightMoter_IN1_Port,RightMoter_IN1_Pin,DIO_HIGH);
	DIO_voidSetPinValue(RightMoter_IN2_Port,RightMoter_IN2_Pin,DIO_LOW);

}
void H_Motor_H_Bridge_voidForward()
{


	DIO_voidSetPinValue(LeftMoter_IN1_Port,LeftMoter_IN1_Pin,DIO_LOW);
	DIO_voidSetPinValue(LeftMoter_IN2_Port,LeftMoter_IN2_Pin,DIO_HIGH);
	DIO_voidSetPinValue(RightMoter_IN1_Port,RightMoter_IN1_Pin,DIO_LOW);
	DIO_voidSetPinValue(RightMoter_IN2_Port,RightMoter_IN2_Pin,DIO_HIGH);


}
void H_Motor_H_Bridge_voidSBackward()
{


	DIO_voidSetPinValue(LeftMoter_IN1_Port,LeftMoter_IN1_Pin,DIO_HIGH);
	DIO_voidSetPinValue(LeftMoter_IN2_Port,LeftMoter_IN2_Pin,DIO_LOW);
	DIO_voidSetPinValue(RightMoter_IN1_Port,RightMoter_IN1_Pin,DIO_HIGH);
	DIO_voidSetPinValue(RightMoter_IN2_Port,RightMoter_IN2_Pin,DIO_LOW);

}



