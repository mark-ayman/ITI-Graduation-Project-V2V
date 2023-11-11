#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_interface.h"
#include <util/delay.h>
#include "KPAD_interface.h"
#include "KPAD_config.h"
#include "KPAD_private.h"



u8 KEYPAD [4][4]={{'7','8','9','/'},
				  {'4','5','6','*'},
                  {'1','2','3','-'},
                  {'C','0','=','+'}};

void KEYPAD_voidInit      (void)
{
    /* Set Rows To Input*/
	DIO_voidSetPinDirection(KEYPAD_PORT	 , KEYPAD_C1 , DIO_OUTPUT );
	DIO_voidSetPinDirection( KEYPAD_PORT , KEYPAD_C2 , DIO_OUTPUT);
	DIO_voidSetPinDirection( KEYPAD_PORT , KEYPAD_C3 , DIO_OUTPUT);
	DIO_voidSetPinDirection( KEYPAD_PORT , KEYPAD_C4 , DIO_OUTPUT);

	DIO_voidSetPinDirection( KEYPAD_PORT , KEYPAD_R1 , DIO_INPUT );
	DIO_voidSetPinDirection( KEYPAD_PORT , KEYPAD_R2 , DIO_INPUT);
	DIO_voidSetPinDirection( KEYPAD_PORT , KEYPAD_R3 , DIO_INPUT);
	DIO_voidSetPinDirection( KEYPAD_PORT , KEYPAD_R4, DIO_INPUT);
	//////////////////////////////////////////////////////////////////
	DIO_voidSetPinValue(KEYPAD_PORT	 , KEYPAD_C1 , DIO_HIGH );
	DIO_voidSetPinValue( KEYPAD_PORT , KEYPAD_C2 , DIO_HIGH);
	DIO_voidSetPinValue( KEYPAD_PORT , KEYPAD_C3 , DIO_HIGH);
	DIO_voidSetPinValue( KEYPAD_PORT , KEYPAD_C4 , DIO_HIGH);

	DIO_voidSetPinValue( KEYPAD_PORT , KEYPAD_R1 , DIO_HIGH );
	DIO_voidSetPinValue( KEYPAD_PORT , KEYPAD_R2 , DIO_HIGH);
	DIO_voidSetPinValue( KEYPAD_PORT , KEYPAD_R3 , DIO_HIGH);
	DIO_voidSetPinValue( KEYPAD_PORT , KEYPAD_R4, DIO_HIGH);
}


u8 KEYPAD_u8GetKey(void){
	u8 copy_localPressed=0;
	u8 copy_localvalReturned=255;
	for(u8 counter_column=0;counter_column<NUM_OF_COLUMNS;counter_column++){
		DIO_voidSetPinValue(KEYPAD_PORT,(counter_column),DIO_LOW);
		for(u8 counter_row= 0;counter_row<NUM_OF_ROWS;counter_row++){
			copy_localPressed=DIO_u8GetPinValue(KEYPAD_PORT,counter_row+4);
			if(copy_localPressed==0){
			_delay_ms(50);
			copy_localPressed=DIO_u8GetPinValue(KEYPAD_PORT,counter_row+4);
			if(copy_localPressed==0){
				copy_localvalReturned=KEYPAD[counter_row][counter_column];
			}
			while(copy_localPressed==0){
				copy_localPressed=DIO_u8GetPinValue(KEYPAD_PORT,counter_row+4);
			}
		}
		}
		DIO_voidSetPinValue(KEYPAD_PORT,(counter_column),DIO_HIGH);
	}
	return copy_localvalReturned;
}



