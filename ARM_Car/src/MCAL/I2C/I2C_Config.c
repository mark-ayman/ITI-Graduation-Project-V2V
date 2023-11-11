/******************************************/
/******** 		I2C_Config.h       *******/
/******** 	     I2C Driver         *******/
/******** Created on: Oct 11, 2023  *******/
/******** Author: Mark Ayman Salib  *******/
/******************************************/


#include "I2C_Interface.h"
#include "../GPIO/GPIO_int.h"


I2C_Config_t I2C_cfg =
{
	.I2C_Bus_Mode					=I2C_Bus_Mode_I2C					,
	.I2C_Device_Mode    			=I2C_Device_Mode_Master				,
	.I2C_Clk_Master_Mode			=I2C_Clk_Master_Mode_SM				,
	.I2C_Clk_Frequency			 	=I2C_Clk_Frequency_8MHz				,
	.I2C_Polling_Enable			 	=I2C_Polling_Enable					,
	.I2C_SlaveAdd_Mode			 	=I2C_SlaveAdd_Mode_Normal			,
	.I2C_Peripheral_Reset_Enable 	=I2C_Per_Rst_Notunder_Rst 			,
	.I2C_Technique					=I2C_Technique_Polling				,
	.I2C_Slave_Normal_Addmode		=I2C_Slave_Normal_Addmode_10
};


