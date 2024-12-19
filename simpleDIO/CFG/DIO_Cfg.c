/*
 * DIO_Cfg.c
 *
 * Created: 2024-03-06 3:03:29 AM
 *  Author: Mohammed
 */ 
#include "..\std_types.h"
#include "..\memory_map.h"
#include "..\MCAL\DIO_Interface.h"

const DIO_PinStatus_t PinStatusArray [TOTAL_PINS]={
	INFREE,	//Port A pin 0
	OUTPUT,	//Port A pin 1
	OUTPUT,	//Port A pin 2
	OUTPUT,	//Port A pin 3
	OUTPUT,	//Port A pin 4
	OUTPUT,	//Port A pin 5
	OUTPUT,	//Port A pin 6
	INFREE,	//Port A pin 7
	OUTPUT,	//Port B pin 0
	OUTPUT,	//Port B pin 1
	INPULL,	//Port B pin 2
	OUTPUT,	//Port B pin 3
	OUTPUT,	//Port B pin 4 ss
	OUTPUT,	//Port B pin 5 MOSI
	OUTPUT,	//Port B pin 6 MISO
	OUTPUT,	//Port B pin 7 SPI Clc
	OUTPUT,	//Port C pin 0
	OUTPUT,	//Port C pin 1
	OUTPUT,	//Port C pin 2
	OUTPUT,	//Port C pin 3
	OUTPUT,	//Port C pin 4
	OUTPUT,	//Port C pin 5
	OUTPUT,	//Port C pin 6
	OUTPUT,	//Port C pin 7
	INFREE,	//Port D pin 0
	OUTPUT,	//Port D pin 1
	INFREE,	//Port D pin 2
	INFREE,	//Port D pin 3
	OUTPUT,	//Port D pin 4
	OUTPUT,	//Port D pin 5
	INPULL,	//Port D pin 6
	OUTPUT,	//Port D pin 7
	};