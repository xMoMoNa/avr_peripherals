/*
 * stepperMotor_Cfg.c
 *
 * Created: 4/4/2024 2:21:20 PM
 *  Author: Mohammed
 */ 
#include "..\MCAL\DIO_Interface.h"
#include "..\HAL\stepperMotor_Interface.h"

const StepperMotor_Pins_t stepperMotor_Pins_array[TOTAL_STEPPERMOTOR]={
	{PC0, PC1, PC2, PC3},
};