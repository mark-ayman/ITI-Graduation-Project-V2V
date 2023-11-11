/*
 * IMU_Program.c
 *
 *  Created on: Oct 12, 2023
 *      Author: marka
 */

#include "math.h"

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "IMU_Interface.h"
#include "IMU_Private.h"
#include "IMU_Config.h"

//#include "../../MCAL/RTC/RTC.h"

#include "../../MCAL/I2C/I2C_Interface.h"
#include "../../MCAL/GPIO/GPIO_int.h"



/*
 *
 *  1- SampleRate Rg25
 * 	2- ConfigREg -> Rg26 	-> [0-2] = Digital Low Pass Filter =  choose Bandwidth - Gyroscope
 * 							   [3-5] = External Frame Synchronozation
 * 	3- Gyroscope     Config -> Full Scape Range
 *  4- Accelorometer Config -> Full Scape Range
 *  5- 	motion Thereshod 	->
 *  6- FIFO -> Reg35 = [reg59-reg96] to enable output __VI__
 *  7- master enable and control
 *  8-
 *
 * */

//u16 static GyroAngle_X;
//u16 static GyroAngle_Y;
//u16	static IMU_Yaw_Angle;
u16 PreviuosTime ;
u16 CurrentTime  ;

u16 Elapsed_Time()
{

	PreviuosTime=CurrentTime;
	//CurrentTime=millis();//GetTime();
	return ((PreviuosTime-CurrentTime)/1000);
}



void IMU_voidInit()
{
	/*Reset Register 6B*/
	I2C_Init(I2C2);
	IMU->PWR_MGMT_1	=0x00;
	I2C_ErrorState_MasterTransmitData(I2C2,IMU_Address,0x6B,1);
	I2C_ErrorState_MasterTransmitData(I2C2,IMU_Address,IMU->PWR_MGMT_1,1);


}

void  IMU_voidRecieveData(u8 Local_u8RegAddress , u8 * P_u8RecieveData )
{

	I2C_ErrorState_Master_Receive(I2C2, IMU_Address ,& (*P_u8RecieveData),1);

}

u16  IMU_u16GetAcc_X()
{
	u16 RecieveData;
	u8 RecieveData_L;
	u8 RecieveData_H;
	IMU_voidRecieveData(0x3B,&RecieveData_H);
	IMU_voidRecieveData(0x3C,&RecieveData_L);
	RecieveData=((RecieveData_H<<8)|(RecieveData_L));
	return (RecieveData/16384);
}
u16  IMU_u16GetAcc_Y()
{
	u16 RecieveData;
	u8 RecieveData_L;
	u8 RecieveData_H;
	IMU_voidRecieveData(0x3D,&RecieveData_H);
	IMU_voidRecieveData(0x3E,&RecieveData_L);
	RecieveData=((RecieveData_H<<8)|(RecieveData_L));
	return (RecieveData/16384);
}
u16  IMU_u16GetAcc_Z()
{
	u16 RecieveData;
	u8 RecieveData_L;
	u8 RecieveData_H;
	IMU_voidRecieveData(0x3F,&RecieveData_H);
	IMU_voidRecieveData(0x40,&RecieveData_L);
	RecieveData=((RecieveData_H<<8)|(RecieveData_L));
	return (RecieveData/16384);
}

u16  IMU_u16GetACCAngle_X()
{
	u16 ACC_Angle_X;
	u16 ACC_X;
	u16 ACC_Y;
	u16 ACC_Z;
	ACC_X=IMU_u16GetAcc_X();
	ACC_Y=IMU_u16GetAcc_Y();
	ACC_Z=IMU_u16GetAcc_Z();

	ACC_Angle_X=(atan(ACC_Y/sqrt(pow(ACC_X,2)+pow(ACC_Z,2)))*(180/PI))-0.58;

	return ACC_Angle_X;

}
u16  IMU_u16GetACCAngle_Y()
{
	u16 ACC_Angle_Y;
	u16 ACC_X;
	u16 ACC_Y;
	u16 ACC_Z;
	ACC_X=IMU_u16GetAcc_X();
	ACC_Y=IMU_u16GetAcc_Y();
	ACC_Z=IMU_u16GetAcc_Z();

	ACC_Angle_Y=(atan((-1*ACC_X)/sqrt(pow(ACC_Y,2)+pow(ACC_Z,2)))*(180/PI))+1.58;

	return ACC_Angle_Y;

}

u16  IMU_u16GetGyro_X()
{
	u16 RecieveData;
	u8 RecieveData_L;
	u8 RecieveData_H;
	IMU_voidRecieveData(0x41,&RecieveData_H);
	IMU_voidRecieveData(0x42,&RecieveData_L);
	RecieveData=((RecieveData_H<<8)|(RecieveData_L));
	return (RecieveData/131)+0.56;
}
u16  IMU_u16GetGyro_Y()
{
	u16 RecieveData;
	u8 RecieveData_L;
	u8 RecieveData_H;
	IMU_voidRecieveData(0x43,&RecieveData_H);
	IMU_voidRecieveData(0x44,&RecieveData_L);
	RecieveData=((RecieveData_H<<8)|(RecieveData_L));
	return (RecieveData/131)-2;
}
u16  IMU_u16GetGyro_Z()
{
	u16 RecieveData;
	u8 RecieveData_L;
	u8 RecieveData_H;
	IMU_voidRecieveData(0x45,&RecieveData_H);
	IMU_voidRecieveData(0x46,&RecieveData_L);
	RecieveData=((RecieveData_H<<8)|(RecieveData_L));
	return (RecieveData/131)+0.79;
}
/*
u16  IMU_u16GetRollAngle_X()
{
	u8 IMU_Roll_Angle;
	GyroAngle_X+=IMU_u16GetGyro_X()*Elapsed_Time();
	IMU_Roll_Angle=0.96*GyroAngle_X+(0.04*IMU_u16GetACCAngle_X());
	return IMU_Roll_Angle;

}
u16  IMU_u16GetPitchAngle_Y()
{
	u8 IMU_Pitch_Angle;
	GyroAngle_Y+=IMU_u16GetGyro_Y()*Elapsed_Time();
	IMU_Pitch_Angle=0.96*GyroAngle_Y+(0.04*IMU_u16GetACCAngle_Y());
	return IMU_Pitch_Angle;
}
u16  IMU_u16GetYawAngle_Z()
{
	IMU_Yaw_Angle+=Elapsed_Time()*IMU_u16GetGyro_Z();
	return IMU_Yaw_Angle;
}
*/
