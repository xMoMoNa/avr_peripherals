/*
 * KeyPad.c
 *
 * Created: 2024-03-15 2:55:09 AM
 *  Author: Mohammed
 */
#include "..\utils.h"
#include "..\MCAL/DIO_Interface.h"
#include "..\HAL/KeyPad_Interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>

extern const KeyPad_4x4_Pins_t KeyPad_4x4_Pins_Array[KEYPAD_4X4_TOTAL];
extern const u8 KeyPad_4x4_Char[KEYPAD_4X4_TOTAL][4][4];

 void KeyPad_4x4_Init(void){
	 DIO_Pin_t p=0;
	 KeyPad_4x4_t keypad = 0;
	 for (keypad=KEYPAD_4X4_1; keypad< KEYPAD_4X4_TOTAL; keypad++){
		 for (p=0; p<4; p++){
			 DIO_InitPin(KeyPad_4x4_Pins_Array[keypad].pins[p],OUTPUT);
		 }
		 for (p=4; p<8; p++){
			 DIO_InitPin(KeyPad_4x4_Pins_Array[keypad].pins[p],INPULL);
		 }
	 }
	 
 }
 
 u8 KeyPad_4x4_ReadKey(KeyPad_4x4_t keypad){
	 u8 i=0, r=0, c=0;
	 u8 out = ~(1<<i);
	 for (r=0; r<4; r++){
		 out = (~(1<<r));
		 for (i=0; i<4; i++){
			DIO_WritePin(KeyPad_4x4_Pins_Array[keypad].pins[i],ReadBit(out,i)); 
		 }
		 for (c=4; c<8; c++){
			 if (DIO_ReadPin(KeyPad_4x4_Pins_Array[keypad].pins[c])==LOW){
				DIO_WritePin(KeyPad_4x4_Pins_Array[keypad].pins[r], HIGH); 
				 return KeyPad_4x4_Char[KEYPAD_4X4_1][r][c-4];
			 }
		 }
	 }
	 return 0;
 }
 
