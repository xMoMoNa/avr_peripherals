/*
 * UltraSonic_Interface.h
 *
 * Created: 4/1/2024 4:35:09 PM
 *  Author: Mohammed
 */ 

#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_
#include "..\MCAL\DIO_Interface.h"

#define ULTRASONIC_MAX_DISTANCE_cm	400



typedef enum{
	ULTRASONIC1,
	//ULTRASONIC2,
	//ULTRASONIC3,
	//ULTRASONIC4,
	TOTAL_ULTRASONIC
}Ultrasonic_t;

typedef union{
	struct{
		DIO_Pin_t trig;
		DIO_Pin_t echo;
	};
	DIO_Pin_t Pin[2];
}Ultrasonic_Pins_t;

void Ultrasonic_Init(void);
u16 Ultrasonic_GetDistance(Ultrasonic_t ultrasonic);
void Ultrasonic_Runnable(void);
#endif /* ULTRASONIC_INTERFACE_H_ */