/*
* UltraSonic.c
*
* Created: 4/1/2024 4:34:46 PM
*  Author: Mohammed
*/
#define F_CPU 8000000
#include <util/delay.h>
#include "..\std_types.h"
#include "..\MCAL\DIO_Interface.h"
#include "..\MCAL\Timers.h"
#include "..\SERVICES\Timers_Services.h"
#include "UltraSonic_Interface.h"

#define ULTRASONIC_MAX_TIMEOUT_us	ULTRASONIC_MAX_DISTANCE_cm*58

extern const Ultrasonic_Pins_t Ultrasonic_Pins_Array[TOTAL_ULTRASONIC];
static u16 Ultrasonic_Distance_Array[TOTAL_ULTRASONIC]={};

void Ultrasonic_Init(void){
	for (u8 ultrasonic=0; ultrasonic<TOTAL_ULTRASONIC; ultrasonic++){
		DIO_InitPin(Ultrasonic_Pins_Array[ultrasonic].trig, OUTPUT);
		DIO_InitPin(Ultrasonic_Pins_Array[ultrasonic].echo, INFREE);
	}
}

u16 Ultrasonic_GetDistance(Ultrasonic_t ultrasonic){
	return Ultrasonic_Distance_Array[ultrasonic];
}

void Ultrasonic_Runnable(void){
	u16 time, c;
	sei();
	for (Ultrasonic_t ultrasonic=0; ultrasonic<TOTAL_ULTRASONIC; ultrasonic++){
		time=0;
		c=0;
		DIO_WritePin(Ultrasonic_Pins_Array[ultrasonic].trig, HIGH);
		_delay_us(10);
		DIO_WritePin(Ultrasonic_Pins_Array[ultrasonic].trig, LOW);
		PWM_Measure_High_us(&time, ULTRASONIC_MAX_TIMEOUT_us);
		if (time==ULTRASONIC_MAX_TIMEOUT_us){
			Ultrasonic_Distance_Array[ultrasonic]=400;
		}
		else{
			Ultrasonic_Distance_Array[ultrasonic]=time/58;
		}
	}
}