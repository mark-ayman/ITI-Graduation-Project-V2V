/*
 * Motor_H_Bridge_Config.h
 *
 *  Created on: Oct 31, 2023
 *      Author: marka
 */

#ifndef HAL_MOTOR_H_BRIDGE_MOTOR_H_BRIDGE_CONFIG_H_
#define HAL_MOTOR_H_BRIDGE_MOTOR_H_BRIDGE_CONFIG_H_

#include "../../MCAL/DIO/DIO_interface.h"

/*options:
 * 1-DIO_PORTA
 * 2-DIO_PORTB
 * 3-DIO_PORTC
 * 4-DIO_PORTD
 * */


#define LeftMoter_IN1_Port	 	DIO_PORTA
#define LeftMoter_IN2_Port 		DIO_PORTA
#define RightMoter_IN1_Port	 	DIO_PORTA
#define RightMoter_IN2_Port 	DIO_PORTA

/*options:
 * 1-DIO_PIN0
 * 2-DIO_PIN1
 * 3-DIO_PIN2
 * 4-DIO_PIN3
 * ...
 * ....
 * */

#define	LeftMoter_IN1_Pin 	DIO_PIN0
#define	LeftMoter_IN2_Pin	DIO_PIN1
#define	RightMoter_IN1_Pin	DIO_PIN2
#define	RightMoter_IN2_Pin	DIO_PIN3



#endif /* HAL_MOTOR_H_BRIDGE_MOTOR_H_BRIDGE_CONFIG_H_ */
