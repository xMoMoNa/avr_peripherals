/*
 * UltraSonic_Cfg.c
 *
 * Created: 4/2/2024 4:41:11 PM
 *  Author: Mohammed
 */ 
#include "..\MCAL\DIO_Interface.h"
#include "..\HAL\UltraSonic_Interface.h"

const Ultrasonic_Pins_t Ultrasonic_Pins_Array[TOTAL_ULTRASONIC]={
// 	trig, echo
	{PC0, PD6},
//	{PC1, PD6},
//	{PC2, PD6},
//	{PC3, PD6},
};