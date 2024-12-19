/*
 * Stopwatch.c
 *
 * Created: 2024-03-10 1:53:15 AM
 *  Author: Mohammed
 */ 
#include "..\std_types.h"
#include "..\MCAL\DIO_Interface.h"
#include "Stopwatch_Interface.h"
void Presed_Button(u8 *Pressed_P, u8* Pressed_R, u8* Pressed_E){
	if (DIO_ReadPin(PIN_RESET) == LOW ){
		*Pressed_R = 1;
		}else{
		*Pressed_R = 0;
	}
	if (DIO_ReadPin(PIN_MODE) == LOW){
		*Pressed_E = 1;
		}else{
		*Pressed_E = 0;
	}
	if (DIO_ReadPin(PIN_PAUSE_RESUME) == LOW){
		*Pressed_P = 1;
		}else{
		*Pressed_P = 0;
	}
	return;
}