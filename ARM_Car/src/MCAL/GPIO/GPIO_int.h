/*
 * GPIO_int.h
 *
 *  Created on: Aug 9, 2023
 *      Author: admin
 */

#ifndef MCAL_GPIO_GPIO_INT_H_
#define MCAL_GPIO_GPIO_INT_H_

typedef struct{
	u8 mode;
	u8 out_type;
	u8 input_type;
	u8 speed;
	u8 A_u8Altfun ;
	u8 port ;
	u8 pin ;
}GPIO_cfg_t;

//////////////////////////////////
#define GPIO_PIN0    0
#define GPIO_PIN1    1
#define GPIO_PIN2    2 // etc
#define GPIO_PIN3    3
#define GPIO_PIN4    4
#define GPIO_PIN5    5
#define GPIO_PIN6    6
#define GPIO_PIN7    7
#define GPIO_PIN8    8
#define GPIO_PIN9    9
#define GPIO_PIN10   10
#define GPIO_PIN11   11
#define GPIO_PIN12   12
#define GPIO_PIN13   13
#define GPIO_PIN14   14
#define GPIO_PIN15   15

/*PORT NAME*/
#define GPIO_PORTA   1
#define GPIO_PORTB   2
#define GPIO_PORTC   3
/*MODES*/
#define GPIO_MODE_INPUT    0b00
#define GPIO_MODE_OUTPUT   0b01
#define GPIO_MODE_ALTFUN   0b10
#define GPIO_MODE_ANALOG   0b11

/*OUT type*/
#define GPIO_OUTTYPE_OPENDRAIN      1
#define GPIO_OUTPUTTYPE_PUSHPULL    2

/*OUT SPEED*/
#define GPIO_OUTSPEED_LOW    0b00
#define GPIO_OUTSPEED_MEDIUM 0b01

/*INPUT TYPE*/
#define GPIO_INPUTTYPE_NPU   0b00
#define GPIO_INPUTTYPE_PU    0b01
#define GPIO_INPUTTYPE_PD    0b10

#define GPIO_HIGH    1
#define GPIO_LOW     0

#define GPIO_AF0    0
#define GPIO_AF1    1
///////////////////////////////////////
/*Mode*/
void MGPIO_vInit(GPIO_cfg_t *A_ptr);
void MGPIO_vSetPinMode(u8 A_u8PortId,
		u8 A_u8PinNo,
		u8 A_u8Mode );
void MGPIO_vSetPinOutputType(u8 A_u8PortId,
		u8 A_u8PinNo,
		u8 A_u8OutType );

void MGPIO_vSetPinOutputSpeed(u8 A_u8PortId,
		u8 A_u8PinNo,
		u8 A_u8OutSpeed );

void MGPIO_vSetPinInputPull(u8 A_u8PortId,
        u8 A_u8PinNo,
        u8 A_u8PullType );

u8 MGPIO_u8GetPinValue(u8 A_u8PortId,
        u8 A_u8PinNo);

void MGPIO_vSetPinValue(u8 A_u8PortId,
        u8 A_u8PinNo,
        u8 A_u8PinVal );

void MGPIO_vSetPinValFast(u8 A_u8PortId,
        u8 A_u8PinNo,
        u8 A_u8PinVal );

void MGPIO_vSetAlternativeFunction(u8 A_u8PortId,
        u8 A_u8PinNo,
        u8 A_u8Altfun );




#endif /* MCAL_GPIO_GPIO_INT_H_ */
