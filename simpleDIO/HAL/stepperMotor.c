/*
 * stepperMotor.c
 *
 * Created: 4/4/2024 2:20:11 PM
 *  Author: Mohammed
 */ 
#include "..\std_types.h"
#include "..\memory_map.h"
#include "..\MCAL/DIO_Interface.h"
#include "..\HAL/stepperMotor_Interface.h"

#define F_CPU	8000000UL
#include <util/delay.h>

extern const StepperMotor_Pins_t stepperMotor_Pins_array[TOTAL_STEPPERMOTOR];

void StepperMotor_Init(void){
	for(StepperMotor_t stepper=0; stepper<TOTAL_STEPPERMOTOR; stepper++){
		for (DIO_Pin_t pin=0; pin<4; pin++){
			DIO_InitPin(stepperMotor_Pins_array[stepper].pin[pin], OUTPUT);
		}
	}
}

void StepperMotor_Rotate(StepperMotor_t stepper, u16 angle, MOTOR_Direction_t direction){
	
}
