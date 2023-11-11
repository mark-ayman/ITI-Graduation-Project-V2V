/*
 * SPI_interface.h
 *
 *  Created on: Aug 21, 2023
 *      Author: marka
 */

#ifndef MCAL_SPI_SPI_INTERFACE_H_
#define MCAL_SPI_SPI_INTERFACE_H_


#define SPI_INT_ENB_BIT 	7
#define SPI_ENB_BIT 		6
#define SPI_DATA_ORDER_BIT  5
#define SPI_MS_SS_BIT 		4
#define SPI_CLK_POL_BIT 	3
#define SPI_CLK_PH_BIT 		2

#define SPI_SPEED_BIT		0

typedef enum{
			polling,
			interrupt
			}Mechanisim;

typedef enum {
			MSB,
			LSB
			}Data_Order;

typedef enum {
			Salve,
			Master,
			}MASTER_SLAVE;

typedef enum {
			Leading_Rising_Tralling_Falling,
			Leading_Falling_Tralling_Rising,
			}ClK_Polarity;


typedef enum {
			Leading_Sample_Tralling_Setup,
			Leading_Setup_Tralling_Sample
			}ClK_Phase;

typedef enum {
			FCPU_4,
			FCPU_16,
			FCPU_64,
			FCPU_128,
			FCPU_2,
			FCPU_8,
			FCPU_32
			}ClK_Prescalar;


typedef struct{
			Mechanisim tech;
			MASTER_SLAVE M_S;
			Data_Order   D_O;
			ClK_Polarity CLK_POL;
			ClK_Phase CLK_PH;
			ClK_Prescalar CLK;
				}SPI_t;

void SPI_voidInit(SPI_t t1);

u8 SPI_voidTransmitData (u8 copy_u8SendData);



#endif /* MCAL_SPI_SPI_INTERFACE_H_ */
