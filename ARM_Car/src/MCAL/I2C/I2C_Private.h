/******************************************/
/******** 		I2C_Private.h       *******/
/******** 	     I2C Driver         *******/
/******** Created on: Oct 11, 2023  *******/
/******** Author: Mark Ayman Salib  *******/
/******************************************/


#ifndef MCAL_I2C_I2C_PRIVATE_H_
#define MCAL_I2C_I2C_PRIVATE_H_


/**********************************************/
/* 			I2C Register Structure 		      */
/**********************************************/

typedef struct
{
	volatile u32 CR1 	;
	volatile u32 CR2 	;
	volatile u32 OAR1 	;
	volatile u32 OAR2 	;
	volatile u32 DR 	;
	volatile u32 SR1 	;
	volatile u32 SR2 	;
	volatile u32 CCR 	;
	volatile u32 TRISE 	;
	volatile u32 FLTR	;
}I2C_MemMap_t;


/**********************************************/
/* 		The I2C Structure Pointer 		      */
/**********************************************/

#define I2C1_BASE_ADDRESS    (0x40005C00)
#define I2C2_BASE_ADDRESS    (0x40005800)
#define I2C3_BASE_ADDRESS    (0x40005400)

#define   I2C1  (( I2C_MemMap_t *)(I2C1_BASE_ADDRESS))
#define   I2C2  (( I2C_MemMap_t *)(I2C2_BASE_ADDRESS))
#define   I2C3  (( I2C_MemMap_t *)(I2C3_BASE_ADDRESS))

/***************************************/

#define I2C_CR1_SoftwareReset_Bit 			15
#define I2C_CR1_SMBusAlert_Bit 				13
#define I2C_CR1_PacketErrorChecking_Bit 	12
#define I2C_CR1_ACK_PECposition_Bit 		11
#define I2C_CR1_ACK_Enable_Bit 				10
#define I2C_CR1_StopGeneration_Bit 			9
#define I2C_CR1_StartGeneration_Bit 		8
#define I2C_CR1_ClkStretchingDisable_Bit	7
#define I2C_CR1_GeneralCallEnable_Bit 		6
#define I2C_CR1_PEC_Enable_Bit 				5
#define I2C_CR1_ARP_Enable_Bit 				4	/*	SMBus	*/
#define I2C_CR1_SMBusType_Bit 				3	/*	SMBus	*/
#define I2C_CR1_SMBusMode_Bit 				1	/*	choose I2C Mode or SMBus Mode	*/
#define I2C_CR1_Peripheral_Enable_Bit 		0	/* Bit=Zero,I2c Comm Disable at End of Current */

/****************************************/

#define I2C_CR2_DMALastTransfer_Bit        12
#define I2C_CR2_DMA_RequestEnable_Bit      11
#define I2C_CR2_DMA_BufferIntEnable_Bit    10
#define I2C_CR2_EventIntEnable_Bit         9
#define I2C_CR2_ErrorIntEnable_Bit         8


/***************************************/

#define I2C_CCR_MasterModeSelection_Bit     15
#define I2C_CCR_FMDutyCycleMode_Bit         14

/**************************************/


#endif /* MCAL_I2C_I2C_PRIVATE_H_ */
