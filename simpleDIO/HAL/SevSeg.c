/*
* SevSeg.c
*
* Created: 2024-03-08 4:07:11 AM
*  Author: Mohammed
*/
#include "..\memory_map.h"
#include "..\std_types.h"
#include "..\utils.h"
#include "..\MCAL\DIO_Interface.h"
#include "..\HAL\SevSeg_Interface.h"
#define  F_CPU 8000000
#include <util/delay.h>

extern const SEVSEG_Ones_Pins_t SEVSEG_Ones_Arr_Pins [SEVSEG_ONES_TOTAL];
extern const SEVSEG_Ones_BCD_Pins_t SEVSEG_Ones_BCD_Arr_Pins [SEVSEG_ONES_BCD_TOTAL];
extern const SEVSEG_Tens_Pins_t SEVSEG_Tens_Arr_Pins [SEVSEG_TENS_TOTAL];
extern const SEVSEG_Tens_BCD_Pins_t SEVSEG_Tens_BCD_Arr_Pins [SEVSEG_TENS_BCD_TOTAL];
extern const SEVSEG_2_Pins_t SEVSEG_2_Arr_Pins [SEVSEG_2_TOTAL];

static const u8 segmentArr[]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90,
0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e, 0x7f};

void SEVSEG_Ones_Init(void){
	if(SEVSEG_ONES_TOTAL != 0){
		for (SEVSEG_Ones_t sevSegOnes=0; sevSegOnes<SEVSEG_ONES_TOTAL; sevSegOnes++){
			for (u8 p=0; p<8; p++){
				DIO_InitPin(SEVSEG_Ones_Arr_Pins[sevSegOnes].pin[p], OUTPUT);
			}
		}
	}
}
void SEVSEG_Ones_BCD_Init(void){
	if(SEVSEG_ONES_BCD_TOTAL != 0){
		for (SEVSEG_Ones_BCD_t sevSeg=0; sevSeg<SEVSEG_ONES_BCD_TOTAL; sevSeg++){
			for (u8 p=0; p<4; p++){
				DIO_InitPin(SEVSEG_Ones_BCD_Arr_Pins[sevSeg].pin[p], OUTPUT);
			}
		}
	}
}
void SEVSEG_Tens_Init(void){
	if(SEVSEG_TENS_TOTAL != 0){
		for (SEVSEG_Tens_t sevSegTens=0; sevSegTens<SEVSEG_TENS_TOTAL; sevSegTens++){
			for (u8 p=0; p<16; p++){
				DIO_InitPin(SEVSEG_Tens_Arr_Pins[sevSegTens].pin[p], OUTPUT);
			}
		}
	}
}
void SEVSEG_Tens_BCD_Init(void){
	if(SEVSEG_TENS_BCD_TOTAL != 0){
		for (SEVSEG_Tens_BCD_t sevSeg=0; sevSeg<SEVSEG_TENS_BCD_TOTAL; sevSeg++){
			for (u8 p=0; p<4; p++){
				DIO_InitPin(SEVSEG_Tens_BCD_Arr_Pins[sevSeg].pin[p], OUTPUT);
			}
		}
	}
}
void SEVSEG_2_Init(void){
	if(SEVSEG_2_TOTAL != 0){
		for (SEVSEG_Tens_t sevSeg=0; sevSeg<SEVSEG_2_TOTAL; sevSeg++){
			for (u8 p=0; p<10; p++){
				DIO_InitPin(SEVSEG_2_Arr_Pins[sevSeg].pin[p], OUTPUT);
			}
		}
	}
}


void SEVSEG_Display_Ones(SEVSEG_Ones_t sevSeg, u8 number){
	#if SEVSEG_CONNECTION == COM_CATHOD
	for (u8 bit=0; bit<8; bit++){
		DIO_WritePin(SEVSEG_Ones_Arr_Pins[sevSeg].pin[bit], ReadBit(~segmentArr[number], bit));
	}
	#elif SEVSEG_CONNECTION == COM_ANODE
	for (u8 bit=0; bit<8; bit++){
		DIO_WritePin(SEVSEG_Ones_Arr_Pins[sevSeg].pin[bit], ReadBit(segmentArr[number], bit));
	}
	#endif
}


void SEVSEG_Display_Ones_BCD(SEVSEG_Ones_t sevSeg, u8 number){
	#if SEVSEG_CONNECTION == COM_CATHOD
	for (u8 bit=0; bit<4; bit++){
		DIO_WritePin(SEVSEG_Ones_BCD_Arr_Pins[sevSeg].pin[bit], ReadBit(number, bit));
	}
	#elif SEVSEG_CONNECTION == COM_ANODE
	for (u8 bit=0; bit<4; bit++){
		DIO_WritePin(SEVSEG_Ones_BCD_Arr_Pins[sevSeg].pin[bit], ReadBit(~number, bit));
	}
	#endif
}


void SEVSEG_Display_Tens(SEVSEG_Tens_t sevSeg, u8 number){
	#if SEVSEG_CONNECTION == COM_CATHOD
	for (u8 bit=0; bit<8; bit++){
		DIO_WritePin(SEVSEG_Tens_Arr_Pins[sevSeg].pin[bit], ReadBit(~segmentArr[number%10], bit));
	}
	for (u8 bit=8; bit<16; bit++){
		DIO_WritePin(SEVSEG_Tens_Arr_Pins[sevSeg].pin[bit], ReadBit(~segmentArr[number/10], bit));
	}
	#elif SEVSEG_CONNECTION == COM_ANODE
	for (u8 bit=0; bit<8; bit++){
		DIO_WritePin(SEVSEG_Tens_Arr_Pins[sevSeg].pin[bit], ReadBit(segmentArr[number%10], bit));
	}
	for (u8 bit=8; bit<16; bit++){
		DIO_WritePin(SEVSEG_Tens_Arr_Pins[sevSeg].pin[bit], ReadBit(segmentArr[number/10], bit));
	}
	#endif
}


void SEVSEG_Display_Tens_BCD(SEVSEG_Tens_t sevSeg, u8 number){
	#if SEVSEG_CONNECTION == COM_CATHOD
	for (u8 bit=0; bit<4; bit++){
		DIO_WritePin(SEVSEG_Tens_BCD_Arr_Pins[sevSeg].pin[bit], ReadBit(number%10, bit));
	}
	for (u8 bit=4; bit<8; bit++){
		DIO_WritePin(SEVSEG_Tens_BCD_Arr_Pins[sevSeg].pin[bit], ReadBit(number/10, bit));
	}
	#elif SEVSEG_CONNECTION == COM_ANODE
	for (u8 bit=0; bit<4; bit++){
		DIO_WritePin(SEVSEG_Tens_BCD_Arr_Pins[sevSeg].pin[bit], ReadBit(~(number%10), bit));
	}
	for (u8 bit=4; bit<8; bit++){
		DIO_WritePin(SEVSEG_Tens_BCD_Arr_Pins[sevSeg].pin[bit], ReadBit(~(number/10), bit));
	}
	#endif
}


void SEVSEG_Display_2_Digit(SEVSEG_2_t sevSeg, u8 number){
	DIO_WritePin(SEVSEG_2_Arr_Pins[sevSeg]._1, HIGH);
	
	#if SEVSEG_CONNECTION == COM_CATHOD
	for (u8 bit=0; bit<8; bit++){
		DIO_WritePin(SEVSEG_2_Arr_Pins[sevSeg].pin[bit], ReadBit(~segmentArr[number%10], bit));
	}
	#elif SEVSEG_CONNECTION == COM_ANODE
	for (u8 bit=0; bit<8; bit++){
		DIO_WritePin(SEVSEG_2_Arr_Pins[sevSeg].pin[bit], ReadBit(segmentArr[number%10], bit));
	}
	#endif
	DIO_WritePin(SEVSEG_2_Arr_Pins[sevSeg]._2, LOW);
	
	_delay_ms(1);
	
	DIO_WritePin(SEVSEG_2_Arr_Pins[sevSeg]._2, HIGH);
	#if SEVSEG_CONNECTION == COM_CATHOD
	for (u8 bit=0; bit<8; bit++){
		DIO_WritePin(SEVSEG_2_Arr_Pins[sevSeg].pin[bit], ReadBit(~segmentArr[number/10], bit));
	}
	#elif SEVSEG_CONNECTION == COM_ANODE
	for (u8 bit=0; bit<8; bit++){
		DIO_WritePin(SEVSEG_2_Arr_Pins[sevSeg].pin[bit], ReadBit(segmentArr[number/10], bit));
	}
	#endif
	DIO_WritePin(SEVSEG_2_Arr_Pins[sevSeg]._1, LOW);
	_delay_ms(1);
}


void FreeRTOS_SEVSEG_Display_2_Digit(SEVSEG_2_t sevSeg, u8 number, u8 state){
	if (state==1){
		DIO_WritePin(SEVSEG_2_Arr_Pins[sevSeg]._2, LOW);
		#if SEVSEG_CONNECTION == COM_CATHOD
		for (u8 bit=0; bit<8; bit++){
			DIO_WritePin(SEVSEG_2_Arr_Pins[sevSeg].pin[bit], ReadBit(~segmentArr[number%10], bit));
		}
		#elif SEVSEG_CONNECTION == COM_ANODE
		for (u8 bit=0; bit<8; bit++){
			DIO_WritePin(SEVSEG_2_Arr_Pins[sevSeg].pin[bit], ReadBit(segmentArr[number%10], bit));
		}
		#endif
		DIO_WritePin(SEVSEG_2_Arr_Pins[sevSeg]._1, HIGH);
	}
	else if (state==2){
		DIO_WritePin(SEVSEG_2_Arr_Pins[sevSeg]._1, LOW);
		#if SEVSEG_CONNECTION == COM_CATHOD
		for (u8 bit=0; bit<8; bit++){
			DIO_WritePin(SEVSEG_2_Arr_Pins[sevSeg].pin[bit], ReadBit(~segmentArr[number/10], bit));
		}
		#elif SEVSEG_CONNECTION == COM_ANODE
		for (u8 bit=0; bit<8; bit++){
			DIO_WritePin(SEVSEG_2_Arr_Pins[sevSeg].pin[bit], ReadBit(segmentArr[number/10], bit));
		}
		#endif
		DIO_WritePin(SEVSEG_2_Arr_Pins[sevSeg]._2, HIGH);
	}
}

