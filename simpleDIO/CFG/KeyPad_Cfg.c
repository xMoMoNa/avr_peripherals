/*
* KeyPad_Cfg.c
*
* Created: 2024-03-15 2:56:11 AM
*  Author: Mohammed
*/

#include "..\std_types.h"
#include "..\MCAL\DIO_Interface.h"
#include "..\HAL\KeyPad_Interface.h"

const KeyPad_4x4_Pins_t KeyPad_4x4_Pins_Array[KEYPAD_4X4_TOTAL]={
//    R0    R1    R2    R3	 C1     C2    C3     C4    
	{PB4, PB5, PB6, PB7,PD2, PD3, PD4, PD5}, // KeyPad1 4x4 Pins
};

const u8 KeyPad_4x4_Char[KEYPAD_4X4_TOTAL][4][4]={
	{{'7','8','9','/'},
	{'4','5','6','*'},
	{'1','2','3','-'},
	{'c','0','=','+'}}
};