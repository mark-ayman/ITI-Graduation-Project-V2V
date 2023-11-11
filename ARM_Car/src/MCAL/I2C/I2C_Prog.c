/******************************************/
/******** 		I2C_Interface.h       *******/
/******** 	     I2C Driver         *******/
/******** Created on: Oct 11, 2023  *******/
/******** Author: Mark Ayman Salib  *******/
/******************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"




#include "I2C_Interface.h"
#include "I2C_Private.h"
#include "I2C_Config.h"

extern I2C_Config_t I2C_cfg;

static I2C_Error_State I2C_ErrorState_MasterRequestWrite(I2C_MemMap_t *I2C, u16 I2C_Slave_Address);

static I2C_Error_State I2C_ErrorState_MasterRequestRead(I2C_MemMap_t *I2C, u16 I2C_Slave_Address);


I2C_Error_State I2C_Init(I2C_MemMap_t *I2C)
{
	u8 Error_State;
	switch (I2C_cfg.I2C_Bus_Mode)
	{
	case  (I2C_Bus_Mode_I2C) :
			switch (I2C_cfg.I2C_Technique)
			{
				case I2C_Technique_Polling :
					switch (I2C_cfg.I2C_Device_Mode)
					{
						case I2C_Device_Mode_Master:
							switch (I2C_cfg.I2C_Clk_Master_Mode)
							{
								case I2C_Clk_Master_Mode_SM:
									//Set Frequency to be loke APB Bus
									I2C->CR2=I2C_cfg.I2C_Clk_Frequency;
									//Set Rise Time at TRISE
									I2C->TRISE=I2C_SPEED((I2C_cfg.I2C_Clk_Frequency/1000000),(_speed_),(0));
									//Enable General Call Slave Bit CR1->Bit 6
									SET_BIT(I2C->CR1,I2C_CR1_GeneralCallEnable_Bit);
									//Enable Non Stretched Signal mode
									SET_BIT(I2C->CR1,I2C_CR1_ClkStretchingDisable_Bit);
									//Address Mode
									if (I2C_cfg.I2C_SlaveAdd_Mode==I2C_SlaveAdd_Mode_Normal)
									{
										if (I2C_cfg.I2C_Slave_Normal_Addmode==I2C_Slave_Normal_Addmode_7)
										{
											I2C->OAR1=0x4000;
										}
										else if (I2C_cfg.I2C_Slave_Normal_Addmode==I2C_Slave_Normal_Addmode_10)
										{
											I2C->OAR1=0x4000;
											SET_BIT(I2C->OAR1,15);
										}
									}
									else if (I2C_cfg.I2C_SlaveAdd_Mode==I2C_SlaveAdd_Mode_General_Call)
									{

									}
									else if (I2C_cfg.I2C_SlaveAdd_Mode==I2C_SlaveAdd_Mode_Daul)
									{

									}
									SET_BIT(I2C->CR1,I2C_CR1_Peripheral_Enable_Bit);
									Error_State= I2C_OK;
									break;
								case I2C_Clk_Master_Mode_FM:

									break;
							}
							break;
						case I2C_Device_Mode_Slave:

							break;
					}
					break;
				case I2C_Technique_Interrupt :

					break;
				case I2C_Technique_DMA :
					break;
			}
			break;
	case (I2C_Bus_Mode_SMBus) :
			break;
	}
return Error_State;
}

static I2C_Error_State I2C_ErrorState_MasterRequestRead(I2C_MemMap_t *I2C, u16 I2C_Slave_Address)
{
	u8 Error_State;
	/* Declaration of temporary variable to prevent undefined behavior of volatile usage */
	  //uint32_t CurrentXferOptions = hi2c->XferOptions;

	  /* Generate Start condition if first transfer */
		SET_BIT(I2C->CR1,I2C_CR1_ACK_Enable_Bit);
		SET_BIT(I2C->CR1,I2C_CR1_StartGeneration_Bit);
	  //if((CurrentXferOptions == I2C_FIRST_AND_LAST_FRAME) || (CurrentXferOptions == I2C_FIRST_FRAME)  || (CurrentXferOptions == I2C_NO_OPTION_FRAME))
	  //{
	  //  /* Enable Acknowledge */
	  //  hi2c->Instance->CR1 |= I2C_CR1_ACK;

	  //  /* Generate Start */
	  //  hi2c->Instance->CR1 |= I2C_CR1_START;
	  //}
	  //else if(hi2c->PreviousState == I2C_STATE_MASTER_BUSY_TX)
	  //{
	  //  /* Enable Acknowledge */
	  //  hi2c->Instance->CR1 |= I2C_CR1_ACK;

	  //  /* Generate ReStart */
	  //  hi2c->Instance->CR1 |= I2C_CR1_START;
	  //}

	  /* Wait until SB flag is set */
		while(GET_BIT(I2C->SR1,1)!=1);
	  //if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Timeout, Tickstart) != HAL_OK)
	  //{
	  //  return HAL_TIMEOUT;
	  //}

	  if(I2C_cfg.I2C_Slave_Normal_Addmode == I2C_Slave_Normal_Addmode_7)
	  {
	    /* Send slave address */
	    I2C->DR = I2C_Slave_Address|1;
	  }
	  else
	  {
	    /* Send header of slave address */
		I2C->DR =((u8)((u16)((u16)(((u16)((I2C_Slave_Address) & (u16)(0x0300U))) >> 7U) | (u16)(0x00F0U))));

	    /* Wait until ADD10 flag is set */
		while(GET_BIT(I2C->SR1,3)!=1);
		//if(I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADD10, Timeout, Tickstart) != HAL_OK)
	    //{
	    //  if(hi2c->ErrorCode == HAL_I2C_ERROR_AF)
	    //  {
	    //    return HAL_ERROR;
	    //  }
	    //  else
	    //  {
	    //    return HAL_TIMEOUT;
	    //  }
	    //}

	    /* Send slave address */
		I2C->DR=((u8)((u16)((I2C_Slave_Address) & (u16)(0x00FFU))));

	    /* Wait until ADDR flag is set */
		while(GET_BIT(I2C->SR1,1)!=1);
	    //if(I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, Timeout, Tickstart) != HAL_OK)
	    //{
	    //  if(hi2c->ErrorCode == HAL_I2C_ERROR_AF)
	    //  {
	    //    return HAL_ERROR;
	    //  }
	    //  else
	    //  {
	    //    return HAL_TIMEOUT;
	    //  }
	    //}

	    /* Clear ADDR flag */
		CLR_BIT(I2C->SR1,1);
	    //__HAL_I2C_CLEAR_ADDRFLAG(hi2c);

	    /* Generate Restart */
		SET_BIT(I2C->CR1,I2C_CR1_StartGeneration_Bit);

		//hi2c->Instance->CR1 |= I2C_CR1_START;

	    /* Wait until SB flag is set */
		while(GET_BIT(I2C->SR1,1)!=1);
		//if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Timeout, Tickstart) != HAL_OK)
	    //{
	    //  return HAL_TIMEOUT;
	    //}

	    /* Send header of slave address */
	    I2C->DR = ((u8)((u16)((u16)(((u16)((I2C_Slave_Address) & (u16)(0x0300U))) >> 7U) | (u16)(0x00F1U))));
	  }

	  /* Wait until ADDR flag is set */
	  while(GET_BIT(I2C->SR1,1)!=1);
	  //if(I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, Timeout, Tickstart) != HAL_OK)
	  //{
	  //  if(hi2c->ErrorCode == HAL_I2C_ERROR_AF)
	  //  {
	  //    return HAL_ERROR;
	  //  }
	  //  else
	  //  {
	  //    return HAL_TIMEOUT;
	  //  }
	  //}

	  return I2C_OK;

}

static I2C_Error_State I2C_ErrorState_MasterRequestWrite(I2C_MemMap_t *I2C, u16 I2C_Slave_Address)
{
  /* Declaration of temporary variable to prevent undefined behavior of volatile usage */
  //uint32_t CurrentXferOptions = hi2c->XferOptions;

  /* Generate Start condition if first transfer */
  //if((CurrentXferOptions == I2C_FIRST_AND_LAST_FRAME) || (CurrentXferOptions == I2C_FIRST_FRAME) || (CurrentXferOptions == I2C_NO_OPTION_FRAME))
  //{
    /* Generate Start */
    SET_BIT(I2C->CR1,I2C_CR1_StartGeneration_Bit);
  //}
  //else if(hi2c->PreviousState == I2C_STATE_MASTER_BUSY_RX)
  //{
    /* Generate ReStart */
   // hi2c->Instance->CR1 |= I2C_CR1_START;
  //}

  /* Wait until SB flag is set */
  while(GET_BIT(I2C->SR1,1)!=1);
  //if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Timeout, Tickstart) != HAL_OK)
  //{
   // return HAL_TIMEOUT;
  //}

  if(I2C_cfg.I2C_Slave_Normal_Addmode == I2C_Slave_Normal_Addmode_7)
  {
    /* Send slave address write Mode */
    I2C->DR = I2C_Slave_Address & ~(0x00000001);
  }
  else
  {
    /* Send header of slave address */

	  I2C->DR=((u8)((u16)((u16)(((u16)((I2C_Slave_Address) & (u16)(0x0300U))) >> 7U) | (u16)(0x00F0U))));


    /* Wait until ADD10 flag is set */
    //if(I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADD10, Timeout, Tickstart) != HAL_OK)
    //{
    // if(hi2c->ErrorCode == HAL_I2C_ERROR_AF)
    //  {
    //    return HAL_ERROR;
    //  }
    //  else
    //   {
    //    return HAL_TIMEOUT;
    //   }
    //}
	/*  wait until flag  ADD10 is set */
	while(GET_BIT(I2C->SR1,3)!=1);
    /* Send slave address */
	I2C->DR=((u16)((u16)((I2C_Slave_Address) & (u16)(0x00FFU))));
  }
  /*  wait until flag  ADDR is set */
	while(GET_BIT(I2C->SR1,1)!=1);
  /* Wait until ADDR flag is set */
  //if(I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, Timeout, Tickstart) != HAL_OK)
  //{
  // if(hi2c->ErrorCode == HAL_I2C_ERROR_AF)
  // {
  //    return HAL_ERROR;
  //  }
  //  else
  // {
  //    return HAL_TIMEOUT;
  // }
  //}

  return I2C_OK;
}

I2C_Error_State I2C_ErrorState_MasterTransmitData (I2C_MemMap_t * I2C , u16 SlaveAddress , u8 * Data , u16 size)
{
	  //uint32_t tickstart = 0x00U;
	  u8 Error_State;
	  /* Init tickstart for timeout management*/
	  //tickstart = HAL_GetTick();

	  if(I2C_cfg.I2C_State == I2C_STATE_READY)
	  {
	    /* Wait until BUSY flag is reset */
	    /*if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
	    {
	      return HAL_BUSY;
	    }*/

	    /* Process Locked */
	    //__HAL_LOCK(hi2c);  ?????!!!!!
		  /*wait until Busy Flag Reset*/
		  while (GET_BIT(I2C->SR2,1)!=0);
	    /* Disable Pos */
		CLR_BIT(I2C->CR1,I2C_CR1_ACK_PECposition_Bit) ;

	    I2C_cfg.I2C_State = I2C_STATE_BUSY_TX;
	    /*
	    hi2c->Mode = HAL_I2C_MODE_MASTER;
	    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
	    hi2c->XferOptions = I2C_NO_OPTION_FRAME;
	     */

	    /* Send Slave Address */
	    while(I2C_ErrorState_MasterRequestWrite(I2C, SlaveAddress ) != I2C_OK)
	    //{
	    //  if(hi2c->ErrorCode == HAL_I2C_ERROR_AF)
	    //  {
	    //    /* Process Unlocked */
	    //    __HAL_UNLOCK(hi2c);
	    //    return HAL_ERROR;
	    //  }
	    //  else
	    //  {
	    //    /* Process Unlocked */
	    //    __HAL_UNLOCK(hi2c);
	    //    return HAL_TIMEOUT;
	    //  }
	    //}

	    /* Clear ADDR flag */
	    CLR_BIT(I2C->SR1,1);
	    //__HAL_I2C_CLEAR_ADDRFLAG(hi2c);

	    while(size > 0U)
	    {
	      /* Wait until TXE flag is set */
//	      if(I2C_WaitOnTXEFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
//	      {
//	        if(hi2c->ErrorCode == HAL_I2C_ERROR_AF)
//	        {
//	          /* Generate Stop */
//	          hi2c->Instance->CR1 |= I2C_CR1_STOP;
//	          return HAL_ERROR;
//	        }
//	        else
//	        {
//	          return HAL_TIMEOUT;
//	        }
//	      }

	      /* Wait until TXE flag is set */
	    	while(GET_BIT(I2C->SR1,7)!=1);


	      /* Write data to DR */
	      I2C->DR = (*Data++);
	      size--;

	      if((GET_BIT(I2C->SR1,2)== 1) && (size != 0U))
	      {
	        /* Write data to DR */
		    I2C->DR = (*Data++);
	        size--;
	      }

	      /* Wait until BTF flag is set */
	      while(GET_BIT(I2C->SR1,2)!= 1);

	      //if(I2C_WaitOnBTFFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
	      //{
	      //  if(hi2c->ErrorCode == HAL_I2C_ERROR_AF)
	      //  {
	      //    /* Generate Stop */
	      //    hi2c->Instance->CR1 |= I2C_CR1_STOP;
	      //    return HAL_ERROR;
	      //   }
	      //  else
	      //  {
	      //    return HAL_TIMEOUT;
	      //  }
	      //}
	    }

	    /* Generate Stop */
	    /* Stop Bit */
	     SET_BIT(I2C->CR1,I2C_CR1_StopGeneration_Bit);
	    //hi2c->Instance->CR1 |= I2C_CR1_STOP;

	    I2C_cfg.I2C_State = I2C_STATE_READY;
	    //hi2c->Mode = HAL_I2C_MODE_NONE;

	    /* Process Unlocked */
	    //__HAL_UNLOCK(hi2c);

	    Error_State= I2C_OK;
	  }
	  else
	  {
		Error_State= I2C_OK;
	  }
	return Error_State;
}

I2C_Error_State  I2C_ErrorState_Master_Receive	(I2C_MemMap_t *I2C, u16 SlaveAddress, u8 * Data,u16 size)
{
	  u8 Error_State;

	// tickstart = 0x00U;

	  /* Init tickstart for timeout management*/
	  //tickstart = HAL_GetTick();

	  if(I2C_cfg.I2C_State == I2C_STATE_READY)
	  {
	    /* Wait until BUSY flag is reset */
	    //if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
	    //{
	    //  return HAL_BUSY;
	    // }
		  /* Wait until BUSY flag is reset */
		  while (GET_BIT(I2C->SR2,2)!=0);
	    /* Process Locked */
	    //__HAL_LOCK(hi2c);

	    /* Disable Pos */
	    CLR_BIT(I2C->CR1,I2C_CR1_ACK_PECposition_Bit);

		I2C_cfg.I2C_State = I2C_STATE_BUSY_RX;
	    //hi2c->Mode = HAL_I2C_MODE_MASTER;
	    //hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
	    //hi2c->XferOptions = I2C_NO_OPTION_FRAME;

	    /* Send Slave Address */
	    if(I2C_ErrorState_MasterRequestRead(I2C, SlaveAddress) != I2C_OK)
	    {
	      //if(hi2c->ErrorCode == HAL_I2C_ERROR_AF)
	      //{
	       // /* Process Unlocked */
	       // __HAL_UNLOCK(hi2c);
	       // return HAL_ERROR;
	      //}
	      //else
	      //{
	      //  /* Process Unlocked */
	      //  __HAL_UNLOCK(hi2c);
	      //  return HAL_TIMEOUT;
	      //}
	    }

	    if(size == 0U)
	    {
	      /* Clear ADDR flag */
		   CLR_BIT(I2C->SR1,1);

	      /* Generate Stop */
	       SET_BIT(I2C->CR1,I2C_CR1_StopGeneration_Bit);
	    }
	    else if(size == 1U)
	    {
	      /* Disable Acknowledge */
			CLR_BIT(I2C->CR1,I2C_CR1_ACK_Enable_Bit);
	      //hi2c->Instance->CR1 &= ~I2C_CR1_ACK;

	      /* Clear ADDR flag */
		    CLR_BIT(I2C->SR1,1);
			//__HAL_I2C_CLEAR_ADDRFLAG(hi2c);

	      /* Generate Stop */
		    SET_BIT(I2C->CR1,I2C_CR1_StopGeneration_Bit);
		    //hi2c->Instance->CR1 |= I2C_CR1_STOP;
	    }
	    else if(size == 2U)
	    {
	      /* Disable Acknowledge */
			CLR_BIT(I2C->CR1,I2C_CR1_ACK_Enable_Bit);
	    	//hi2c->Instance->CR1 &= ~I2C_CR1_ACK;

	      /* Enable Pos */
			SET_BIT(I2C->CR1,I2C_CR1_ACK_PECposition_Bit) ;
			//hi2c->Instance->CR1 |= I2C_CR1_POS;


	      /* Clear ADDR flag */
		    CLR_BIT(I2C->SR1,1);
			//__HAL_I2C_CLEAR_ADDRFLAG(hi2c);
	    }
	    else
	    {
	      /* Enable Acknowledge */
			SET_BIT(I2C->CR1,I2C_CR1_ACK_Enable_Bit);
	    	//hi2c->Instance->CR1 |= I2C_CR1_ACK;

	      /* Clear ADDR flag */
		    CLR_BIT(I2C->SR1,1);
			//__HAL_I2C_CLEAR_ADDRFLAG(hi2c);
	    }

	    while(size > 0U)
	    {
	      if(size <= 3U)
	      {
	        /* One byte */
	        if(size == 1U)
	        {
	          /* Wait until RXNE flag is set */
	          while(GET_BIT(I2C->SR1,6)!=1);
	          //if(I2C_WaitOnRXNEFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
	          //{
	          //  if(hi2c->ErrorCode == HAL_I2C_ERROR_TIMEOUT)
	          //  {
	          //    return HAL_TIMEOUT;
	          //  }
	          //  else
	          //  {
	          //    return HAL_ERROR;
	          //  }
	          //}

	          /* Read data from DR */
	          (*Data++) = I2C->DR;
	          size--;
	        }
	        /* Two bytes */
	        else if(size == 2U)
	        {
	          /* Wait until BTF flag is set */
	  	      while(GET_BIT(I2C->SR1,2)!= 1);
	          //if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET, Timeout, tickstart) != HAL_OK)
	          //{
	          //  return HAL_TIMEOUT;
	          //}

	          /* Generate Stop */
			  SET_BIT(I2C->CR1,I2C_CR1_StopGeneration_Bit);
	  	      //hi2c->Instance->CR1 |= I2C_CR1_STOP;

	          /* Read data from DR */
	          (*Data++) = I2C->DR;
	          size--;

	          /* Read data from DR */
	          (*Data++) = I2C->DR;
	          size--;
	        }
	        /* 3 Last bytes */
	        else
	        {
	          /* Wait until BTF flag is set */
		  	  while(GET_BIT(I2C->SR1,2)!= 1);

	          //if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET, Timeout, tickstart) != HAL_OK)
	          //{
	          //  return HAL_TIMEOUT;
	          //}

	          /* Disable Acknowledge */
        	  SET_BIT(I2C->CR1,I2C_CR1_ACK_Enable_Bit);
 		  	  //hi2c->Instance->CR1 &= ~I2C_CR1_ACK;

	          /* Read data from DR */
	          (*Data++) = I2C->DR;
	          size--;

	          /* Wait until BTF flag is set */
		  	  while(GET_BIT(I2C->SR1,2)!= 1);
	          //if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET, Timeout, tickstart) != HAL_OK)
	          //{
	          //  return HAL_TIMEOUT;
	          //}

	          /* Generate Stop */
			  SET_BIT(I2C->CR1,I2C_CR1_StopGeneration_Bit);
		  	  //hi2c->Instance->CR1 |= I2C_CR1_STOP;

	          /* Read data from DR */
	          (*Data++) = I2C->DR;
	          size--;

	          /* Read data from DR */
	          (*Data++) = I2C->DR;
	          size--;
	        }
	      }
	      else
	      {
	        /* Wait until RXNE flag is set */
	       while(GET_BIT(I2C->SR1,6)!=1);
	    	//if(I2C_WaitOnRXNEFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
	        //{
	        //  if(hi2c->ErrorCode == HAL_I2C_ERROR_TIMEOUT)
	        //  {
	        //    return HAL_TIMEOUT;
	        //  }
	        //  else
	        //  {
	        //    return HAL_ERROR;
	        //  }
	       }

	        /* Read data from DR */
	        (*Data++) = I2C->DR;
	        size--;
	        /* BTF Flag */
	        if(GET_BIT(I2C->SR1,2) == 1){
	        {
	          /* Read data from DR */
	          (*Data++) = I2C->DR;
	          size--;
	        }
	      }
	    }

	    I2C_cfg.I2C_State = I2C_STATE_READY;
	    //hi2c->Mode = HAL_I2C_MODE_NONE;

	    /* Process Unlocked */
	   // __HAL_UNLOCK(hi2c);

	    Error_State= I2C_OK;
	  }
	  else
	  {
		Error_State = I2C_BUSY ;
	  }

	return  Error_State;
}



