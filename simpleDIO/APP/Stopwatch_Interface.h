/*
 * Stopwatch_Interface.h
 *
 * Created: 2024-03-10 1:53:50 AM
 *  Author: Mohammed
 */ 


#ifndef STOPWATCH_INTERFACE_H_
#define STOPWATCH_INTERFACE_H_
#include "..\std_types.h"
#define PIN_PAUSE_RESUME	PD2
#define PIN_RESET	PD3
#define PIN_MODE	PD4
/*
preset 1 for increment and decrement
preset 2 for increment only and  truncate to 0 
*/
#define STOPWATCH_PRESET 1

#define STOPWATCH_PERIOD_MS	1000

typedef enum{
	STOPWATCH_MODE_PAUSE,
	STOPWATCH_MODE_RESUME,
	STOPWATCH_MODE_RESET,
	STOPWATCH_MODE_EDIT,
	STOPWATCH_MODE_NORMAL
	}Stopwatch_Mode_t;

void Presed_Button(u8 *Pressed_P, u8* Pressed_R, u8* Pressed_E);


#endif /* STOPWATCH_INTERFACE_H_ */