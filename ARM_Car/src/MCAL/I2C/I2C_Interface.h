/******************************************/
/******** 		I2C_Interface.h       *******/
/******** 	     I2C Driver         *******/
/******** Created on: Oct 11, 2023  *******/
/******** Author: Mark Ayman Salib  *******/
/******************************************/

#include "../../LIB/STD_TYPES.h"
#include "I2C_Private.h"


#ifndef MCAL_I2C_I2C_INTERFACE_H_
#define MCAL_I2C_I2C_INTERFACE_H_



//#define I2C_SM_T_high ( _CCR_ , _TPClk1_ )
//#define I2C_SM_T_low ( _CCR_ , _TPClk1_ )


typedef enum
{
	I2C_Per_Rst_under_Rst	=0		,
	I2C_Per_Rst_Notunder_Rst=1
}I2C_Peripheral_Reset_Enable_t;

typedef enum
{
	I2C_Bus_Mode_I2C	,
	I2C_Bus_Mode_SMBus
}I2C_Bus_Mode_t;

typedef enum
{
	I2C_Device_Mode_Slave	,
	I2C_Device_Mode_Master
}I2C_Device_Mode_t;

typedef enum
{
	I2C_SlaveAdd_Mode_Normal	,
	I2C_SlaveAdd_Mode_Daul		,
	I2C_SlaveAdd_Mode_General_Call
}I2C_SlaveAdd_Mode_t;

typedef enum
{
	I2C_Clk_Master_Mode_SM	,
	I2C_Clk_Master_Mode_FM
}I2C_Clk_Master_Mode_t;

typedef enum
{
	I2C_Clk_Fm_DutyCycle_2	,
	I2C_Clk_Fm_DutyCycle_16_9
}I2C_Clk_Fm_DutyCycle_t;

typedef enum
{
	I2C_Clk_Frequency_2MHz =	2,
	I2C_Clk_Frequency_3MHz,
	I2C_Clk_Frequency_4MHz,
	I2C_Clk_Frequency_5MHz,
	I2C_Clk_Frequency_6MHz,
	I2C_Clk_Frequency_7MHz,
	I2C_Clk_Frequency_8MHz,
	I2C_Clk_Frequency_9MHz,
	I2C_Clk_Frequency_10MHz,
	I2C_Clk_Frequency_11MHz,
	I2C_Clk_Frequency_12MHz,
	I2C_Clk_Frequency_13MHz,
	I2C_Clk_Frequency_14MHz,
	I2C_Clk_Frequency_15MHz,
	I2C_Clk_Frequency_16MHz,
	I2C_Clk_Frequency_17MHz,
	I2C_Clk_Frequency_18MHz,
	I2C_Clk_Frequency_19MHz,
	I2C_Clk_Frequency_20MHz,
	I2C_Clk_Frequency_21MHz,
	I2C_Clk_Frequency_22MHz,
	I2C_Clk_Frequency_23MHz,
	I2C_Clk_Frequency_24MHz,
	I2C_Clk_Frequency_25MHz,
	I2C_Clk_Frequency_26MHz,
	I2C_Clk_Frequency_27MHz,
	I2C_Clk_Frequency_28MHz,
	I2C_Clk_Frequency_29MHz,
	I2C_Clk_Frequency_30MHz,
	I2C_Clk_Frequency_31MHz,
	I2C_Clk_Frequency_32MHz,
	I2C_Clk_Frequency_33MHz,
	I2C_Clk_Frequency_34MHz,
	I2C_Clk_Frequency_35MHz,
	I2C_Clk_Frequency_36MHz,
	I2C_Clk_Frequency_37MHz,
	I2C_Clk_Frequency_38MHz,
	I2C_Clk_Frequency_39MHz,
	I2C_Clk_Frequency_40MHz,
	I2C_Clk_Frequency_41MHz,
	I2C_Clk_Frequency_42MHz,
	I2C_Clk_Frequency_43MHz,
	I2C_Clk_Frequency_44MHz,
	I2C_Clk_Frequency_45MHz,
	I2C_Clk_Frequency_46MHz,
	I2C_Clk_Frequency_47MHz,
	I2C_Clk_Frequency_48MHz,
	I2C_Clk_Frequency_49MHz,
	I2C_Clk_Frequency_50MHz,
}I2C_Clk_Frequency_t;

typedef enum
{
	I2C_Interrupt_Disable=0 ,
	I2C_Interrupt_Enable=1
}I2C_Interrupt_Enable_t;

typedef enum
{
	I2C_Polling_Enable=1	,
	I2C_Polling_Disable=0
}I2C_Polling_Enable_t;


typedef enum
{
	I2C_DMA_Enable=1	,
	I2C_DMA_Disable=0
}I2C_DMA_Enable_t;

typedef enum
{
	I2C_Technique_Polling	,
	I2C_Technique_Interrupt	,
	I2C_Technique_DMA
}I2C_Technique_t;


typedef enum
{
	I2C_Slave_Normal_Addmode_7	,
	I2C_Slave_Normal_Addmode_10
}I2C_Slave_Normal_Addmode_t;

typedef enum
{
  I2C_OK       = 0x00U,
  I2C_ERROR    = 0x01U,
  I2C_BUSY     = 0x02U,
  I2C_TIMEOUT  = 0x03U
} I2C_Error_State;


typedef enum
{
  I2C_STATE_RESET             = 0x00U,   /*!< Peripheral is not yet Initialized         */
  I2C_STATE_READY             = 0x20U,   /*!< Peripheral Initialized and ready for use  */
  I2C_STATE_BUSY              = 0x24U,   /*!< An internal process is ongoing            */
  I2C_STATE_BUSY_TX           = 0x21U,   /*!< Data Transmission process is ongoing      */
  I2C_STATE_BUSY_RX           = 0x22U,   /*!< Data Reception process is ongoing         */
  I2C_STATE_LISTEN            = 0x28U,   /*!< Address Listen Mode is ongoing            */
  I2C_STATE_BUSY_TX_LISTEN    = 0x29U,   /*!< Address Listen Mode and Data Transmission
                                                 process is ongoing                         */
  I2C_STATE_BUSY_RX_LISTEN    = 0x2AU,   /*!< Address Listen Mode and Data Reception
                                                 process is ongoing                         */
  I2C_STATE_ABORT             = 0x60U,   /*!< Abort user request ongoing                */
  I2C_STATE_TIMEOUT           = 0xA0U,   /*!< Timeout state                             */
  I2C_STATE_ERROR             = 0xE0U    /*!< Error                                     */

}I2C_State_t;


typedef struct
{
	I2C_Peripheral_Reset_Enable_t 	I2C_Peripheral_Reset_Enable ;
	I2C_Bus_Mode_t 					I2C_Bus_Mode				;	/*      CR1->2........SMDus or I2C			*/
	I2C_Device_Mode_t 				I2C_Device_Mode				; 	/*	         Master or Slave  				*/
	I2C_SlaveAdd_Mode_t 			I2C_SlaveAdd_Mode			;	/*	Normal - Dual - General Call Add		*/
	I2C_Clk_Master_Mode_t 			I2C_Clk_Master_Mode			;	/* 		standrard Speed and fast Speed 		*/
	I2C_Clk_Fm_DutyCycle_t 			I2C_Clk_Fm_DutyCycle		;
	I2C_Clk_Frequency_t 			I2C_Clk_Frequency			;
	I2C_Interrupt_Enable_t 			I2C_Interrupt_Enable		;
	I2C_Polling_Enable_t	 		I2C_Polling_Enable			;
	I2C_DMA_Enable_t 				I2C_DMA_Enable				;
	I2C_Technique_t					I2C_Technique				;
	I2C_Slave_Normal_Addmode_t		I2C_Slave_Normal_Addmode	;
	I2C_State_t						I2C_State					;
}I2C_Config_t;



I2C_Error_State I2C_Init(I2C_MemMap_t *I2C);
//void HAL_I2C_MspInit		(I2C_MemMap_t *I2C);

/******* Blocking mode: Polling */
I2C_Error_State I2C_ErrorState_MasterTransmitData (I2C_MemMap_t * I2C , u16 SlaveAddress , u8 * Data , u16 size);
I2C_Error_State I2C_ErrorState_Master_Receive	(I2C_MemMap_t *I2C, u16 SlaveAddress, u8 * Data,u16 size);
//I2C_Error_State I2C_Slave_Transmit	(I2C_MemMap_t *I2C, u8 *pData, 		u16 Size);
//I2C_Error_State I2C_Slave_Receive	(I2C_MemMap_t *I2C, u8 *pData, 		u16 Size);
//I2C_Error_State I2C_Mem_Write		(I2C_MemMap_t *I2C, u16 DevAddress, u16 MemAddress, u16 MemAddSize, u8 *pData, u16 Size );
//I2C_Error_State I2C_Mem_Read		(I2C_MemMap_t *I2C, u16 DevAddress, u16 MemAddress, u16 MemAddSize, u8 *pData, u16 Size );
//I2C_Error_State I2C_IsDeviceReady	(I2C_MemMap_t *I2C, u16 DevAddress, u32 Trials	);


#define I2C_SPEED_STANDARD(__PCLK__, __SPEED__)            (((((__PCLK__)/((__SPEED__) << 1U)) & 0x00000FFFU) < 4U)? 4U:((__PCLK__) / ((__SPEED__) << 1U)))
#define I2C_SPEED_FAST(__PCLK__, __SPEED__, __DUTYCYCLE__) (((__DUTYCYCLE__) == 0)? ((__PCLK__) / ((__SPEED__) * 3U)) : (((__PCLK__) / ((__SPEED__) * 25U)) | 0x00004000U))
#define I2C_FREQRANGE(__PCLK__)                            ((__PCLK__)/1000000U)
#define I2C_RISE_TIME(__FREQRANGE__, __SPEED__)            (((__SPEED__) <= 100000U) ? ((__FREQRANGE__) + 1U) : ((((__FREQRANGE__) * 300U) / 1000U) + 1U))
#define I2C_SPEED(__PCLK__, __SPEED__, __DUTYCYCLE__)      (((__SPEED__) <= 100000U)? (I2C_SPEED_STANDARD((__PCLK__), (__SPEED__))) : \
                                                                  ((I2C_SPEED_FAST((__PCLK__), (__SPEED__), (__DUTYCYCLE__)) & 0x00000FFFU ) == 0U)? 1U : \
                                                                  ((I2C_SPEED_FAST((__PCLK__), (__SPEED__), (__DUTYCYCLE__))) | 0x00008000U ))

#endif /* MCAL_I2C_I2C_INTERFACE_H_ */
