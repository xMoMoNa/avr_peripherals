/*
 * Motors_Cfg.c
 *
 * Created: 2024-03-07 4:53:02 AM
 *  Author: Mohammed
 */ 
#include "..\std_types.h"
#include "..\MCAL\DIO_Interface.h"
#include "..\HAL\Motors_Interface.h"


const MOTOR_Pin_t motors_Pins_Array[TOTAL_MOTORS]={
	{PC0, PC1, PC2},
	//{PA3, PA4, PA5},
	//{PB0, PB1, PB2},
	//{PB3, PB4, PB5},
	};