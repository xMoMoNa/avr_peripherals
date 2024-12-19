/*
* KeyPad_Interface.h
*
* Created: 2024-03-15 2:55:40 AM
*  Author: Mohammed
*/

#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_
#include "..\std_types.h"
#include "..\MCAL\DIO_Interface.h"

typedef union{
	struct{
		DIO_Pin_t r0;
		DIO_Pin_t r1;
		DIO_Pin_t r2;
		DIO_Pin_t r3;
		DIO_Pin_t c0;
		DIO_Pin_t c1;
		DIO_Pin_t c2;
		DIO_Pin_t c3;
	};
	DIO_Pin_t pins[8];
}KeyPad_4x4_Pins_t;

typedef enum{
	KEYPAD_4X4_1,
	KEYPAD_4X4_TOTAL
}KeyPad_4x4_t;

void KeyPad_4x4_Init(void);
u8 KeyPad_4x4_ReadKey(KeyPad_4x4_t keypad);

#endif /* KEYPAD_INTERFACE_H_ */