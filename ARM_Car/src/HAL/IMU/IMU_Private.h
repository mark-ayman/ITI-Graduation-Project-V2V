/*
 * IMU_Private.h
 *
 *  Created on: Oct 12, 2023
 *      Author: marka
 */

#ifndef HAL_IMU_IMU_PRIVATE_H_
#define HAL_IMU_IMU_PRIVATE_H_


typedef struct
{
	volatile u8 SELF_TEST_X			;
	volatile u8 SELF_TEST_Y			;
	volatile u8 SELF_TEST_Z			;
	volatile u8 SELF_TEST_A			;
	volatile u8 RESERVED1[8]		;
	volatile u8 SMPLRT_DIV			;
	volatile u8 CONFIG				;
	volatile u8 GYRO_CONFIG			;
	volatile u8 ACCEL_CONFIG		;
	volatile u8 RESERVED2[2]		;
	volatile u8 MOT_THR				;
	volatile u8 RESERVED3[3]		;
	volatile u8 FIFO_EN				;
	volatile u8 I2C_MST_CTRL		;
	volatile u8 I2C_SLV0_ADDR		;
	volatile u8 I2C_SLV0_REG		;
	volatile u8 I2C_SLV0_CTRL		;
	volatile u8 I2C_SLV1_ADDR		;
	volatile u8 I2C_SLV1_REG		;
	volatile u8 I2C_SLV1_CTRL		;
	volatile u8 I2C_SLV2_ADDR		;
	volatile u8 I2C_SLV2_REG		;
	volatile u8 I2C_SLV2_CTRL		;
	volatile u8 I2C_SLV3_ADDR		;
	volatile u8 I2C_SLV3_REG		;
	volatile u8 I2C_SLV3_CTRL		;
	volatile u8 I2C_SLV4_ADDR		;
	volatile u8 I2C_SLV4_REG		;
	volatile u8 I2C_SLV4_CTRL		;
	volatile u8 I2C_MST_STATUS		;
	volatile u8 INT_PIN_CFG			;
	volatile u8 INT_ENABLE			;
	volatile u8 RESERVED4			;
	volatile u8 INT_STATUS			;
	volatile u8 ACCEL_XOUT_H		;
	volatile u8 ACCEL_XOUT_L		;
	volatile u8 ACCEL_YOUT_H		;
	volatile u8 ACCEL_YOUT_L		;
	volatile u8 ACCEL_ZOUT_H		;
	volatile u8 ACCEL_ZOUT_L		;
	volatile u8 TEMP_OUT_H			;
	volatile u8 TEMP_OUT_L			;
	volatile u8 GYRO_XOUT_H			;
	volatile u8 GYRO_XOUT_L			;
	volatile u8 GYRO_YOUT_H			;
	volatile u8 GYRO_YOUT_L			;
	volatile u8 GYRO_ZOUT_H			;
	volatile u8 GYRO_ZOUT_L			;
	volatile u8 EXT_SENS_DATA_00	;
	volatile u8 EXT_SENS_DATA_01	;
	volatile u8 EXT_SENS_DATA_02	;
	volatile u8 EXT_SENS_DATA_03	;
	volatile u8 EXT_SENS_DATA_04	;
	volatile u8 EXT_SENS_DATA_05	;
	volatile u8 EXT_SENS_DATA_06	;
	volatile u8 EXT_SENS_DATA_07	;
	volatile u8 EXT_SENS_DATA_08	;
	volatile u8 EXT_SENS_DATA_09	;
	volatile u8 EXT_SENS_DATA_10	;
	volatile u8 EXT_SENS_DATA_11	;
	volatile u8 EXT_SENS_DATA_12	;
	volatile u8 EXT_SENS_DATA_13	;
	volatile u8 EXT_SENS_DATA_14	;
	volatile u8 EXT_SENS_DATA_15	;
	volatile u8 EXT_SENS_DATA_16	;
	volatile u8 EXT_SENS_DATA_17	;
	volatile u8 EXT_SENS_DATA_18	;
	volatile u8 EXT_SENS_DATA_19	;
	volatile u8 EXT_SENS_DATA_20	;
	volatile u8 EXT_SENS_DATA_21	;
	volatile u8 EXT_SENS_DATA_22	;
	volatile u8 EXT_SENS_DATA_23	;
	volatile u8 RESERVED5[2]		;
	volatile u8 I2C_SLV0_D0			;
	volatile u8 I2C_SLV1_D0			;
	volatile u8 I2C_SLV2_D0			;
	volatile u8 I2C_SLV3_D0			;
	volatile u8 I2C_MST_DELAY_CTRL	;
	volatile u8 SIGNAL_PATH_RESET	;
	volatile u8 MOT_DETECT_CTRL		;
	volatile u8 USER_CTRL			;
	volatile u8 PWR_MGMT_1			;
	volatile u8 PWR_MGMT_2			;
	volatile u8 RESERVED6[5]		;
	volatile u8 FIFO_COUNTH			;
	volatile u8 FIFO_COUNTL			;
	volatile u8 FIFO_R_W			;
	volatile u8 WHO_AM_I			;
}IMU_RegMem_t;


#define IMU_BASE_ADDRESS    13

#define   IMU  (( IMU_RegMem_t *)(IMU_BASE_ADDRESS))


#define IMU_Address 	0x68


#endif /* HAL_IMU_IMU_PRIVATE_H_ */
