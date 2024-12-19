/*
 * DIO_Interface.h
 *
 * Created: 2024-03-06 2:35:06 AM
 *  Author: Mohammed
 */ 


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "..\std_types.h"
#include "..\memory_map.h"
typedef enum{
	PA0=0,
	PA1,
	PA2,
	PA3,
	PA4,
	PA5,
	PA6,
	PA7,
	PB0,
	PB1,
	PB2,
	PB3,
	PB4,
	PB5,
	PB6,
	PB7,
	PC0,
	PC1,
	PC2,
	PC3,
	PC4,
	PC5,
	PC6,
	PC7,
	PD0,
	PD1,
	PD2,
	PD3,
	PD4,
	PD5,
	PD6,
	PD7,
	TOTAL_PINS
	}DIO_Pin_t;
	
typedef enum{
	PA=0,
	PB,
	PC,
	PD
	}DIO_Port_t;
	
typedef enum{
	LOW,
	HIGH
}DIO_PinVolt_t;
	
typedef enum{
	INPULL,
	INFREE,
	OUTPUT
	}DIO_PinStatus_t;

void DIO_InitPin(DIO_Pin_t pin, DIO_PinStatus_t status);
void DIO_Init(void);
void DIO_WritePin(DIO_Pin_t pin, DIO_PinVolt_t volt);
void DIO_WritePort(DIO_Port_t port, DIO_PinVolt_t volt);
void DIO_TogglePin(DIO_Pin_t pin);
DIO_PinVolt_t DIO_ReadPin(DIO_Pin_t pin);

#endif /* DIO_INTERFACE_H_ */