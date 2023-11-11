/*
 * Motor_H_Bridge_Config.h
 *
 *  Created on: Oct 29, 2023
 *      Author: marka
 */

#ifndef HAL_MOTOR_H_BRIDGE_MOTOR_H_BRIDGE_CONFIG_H_
#define HAL_MOTOR_H_BRIDGE_MOTOR_H_BRIDGE_CONFIG_H_

#include "../../MCAL/GPIO/GPIO_int.h"

/**
 * Options:
 *
 * 1-GPIO_PortA
 * 2-GPIO_PortB
 * 3-GPIO_PortC
 * */

#define LeftMoter_IN1_Port  	GPIO_PORTB
#define LeftMoter_IN2_Port  	GPIO_PORTB
#define RightMoter_IN1_Port  	GPIO_PORTB
#define RightMoter_IN2_Port  	GPIO_PORTB

/*
 * Option:
 *
 * 1-GPIO_PIN1
 * ..
 * ..
 * ..
 * ..
 * ..
 * 16-GPIO_PIN16
 *
 * */

#define LeftMoter_IN1_Pin  		GPIO_PIN12
#define LeftMoter_IN2_Pin  		GPIO_PIN13
#define RightMoter_IN1_Pin  	GPIO_PIN14
#define RightMoter_IN2_Pin  	GPIO_PIN15



#endif /* HAL_MOTOR_H_BRIDGE_MOTOR_H_BRIDGE_CONFIG_H_ */
