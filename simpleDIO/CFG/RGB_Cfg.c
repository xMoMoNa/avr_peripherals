/*
 * RGB_Cfg.c
 *
 * Created: 4/16/2024 8:31:46 AM
 *  Author: Mohammed
 */ 


#include "..\MCAL\DIO_Interface.h"
#include "..\HAL\RGB_Interface.h"

const RGB_Pin_t RGB_PinArray[TOTAL_RGB_LED]={
	//{PA1, PA2, PA3},
		{PC0, PC1, PC2},
};