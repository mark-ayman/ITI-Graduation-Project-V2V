/*
 * EXTI_int.h
 *
 *  Created on: Aug 14, 2023
 *      Author: admin
 */

#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

enum {
	EXTI_LINE0,
	EXTI_LINE1,
	EXTI_LINE2,
	EXTI_LINE3,
	EXTI_LINE4,
	EXTI_LINE5,
	EXTI_LINE6

};
enum{
	EXTI_ONCHANGE,
	EXTI_FAILING,
	EXTI_RISING
};
void MEXTI_vEnableLine(u8 A_u8Line,u8 A_u8Trigger);

void MEXTI_vDisableLine(u8 A_u8Line);

void MEXTI_vSetTrigger(u8 A_u8Line,u8 A_u8Trigger);

void MEXTI_vSoftwareTrigger(u8 A_u8Line);

void MEXTI_vClearFlage(u8 A_u8Line);

void MEXTI_vSetCallBack (u8 A_u8Line ,void (*A_ptr)(void));

#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
