/*
 * IMU_Interface.h
 *
 *  Created on: Oct 12, 2023
 *      Author: marka
 */

#ifndef HAL_IMU_IMU_INTERFACE_H_
#define HAL_IMU_IMU_INTERFACE_H_

#define PI 3.14


void IMU_voidInit();
void  IMU_voidRecieveData(u8 Local_u8RegAddress , u8 * P_u8RecieveData );
u16  IMU_u16GetAcc_X();
u16  IMU_u16GetAcc_Y();
u16  IMU_u16GetAcc_Z();
u16  IMU_u16GetGyro_X();
u16  IMU_u16GetGyro_Y();
u16  IMU_u16GetGyro_Z();
u16  IMU_u16GetACCAngle_X();
u16  IMU_u16GetACCAngle_Y();
u16  IMU_u16GetRollAngle_X();
u16  IMU_u16GetPitchAngle_Y();
u16  IMU_u16GetYawAngle_Z();

#endif /* HAL_IMU_IMU_INTERFACE_H_ */
