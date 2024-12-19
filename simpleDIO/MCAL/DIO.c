/*
* DIO.c
*
* Created: 2024-03-06 2:35:44 AM
*  Author: Mohammed
*/
#include "../std_types.h"
#include "../utils.h"
#include "../memory_map.h"
#include "DIO_Interface.h"
#include "DIO_Private.h"

void DIO_InitPin(DIO_Pin_t pin, DIO_PinStatus_t status){
	DIO_Port_t port=pin/8;
	u8 i=pin%8;
	switch(port){
		case PA:
		switch(status){
			case OUTPUT:
			SetBit(DDRA, i);
			ClearBit(PORTA, LOW);
			break;
			case INFREE:
			ClearBit(DDRA, i);
			break;
			case INPULL:
			ClearBit(DDRA, i);
			SetBit(PORTA, i);
			break;
		}
		break;
		case PB:
		switch(status){
			case OUTPUT:
			SetBit(DDRB, i);
			ClearBit(PORTB, LOW);
			break;
			case INFREE:
			ClearBit(DDRB, i);
			break;
			case INPULL:
			ClearBit(DDRB, i);
			SetBit(PORTB, i);
			break;
		}
		break;
		case PC:
		switch(status){
			case OUTPUT:
			SetBit(DDRC, i);
			ClearBit(PORTC, LOW);
			break;
			case INFREE:
			ClearBit(DDRC, i);
			break;
			case INPULL:
			ClearBit(DDRC, i);
			SetBit(PORTC, i);
			break;
		}
		break;
		case PD:
		switch(status){
			case OUTPUT:
			SetBit(DDRD, i);
			ClearBit(PORTD, LOW);
			break;
			case INFREE:
			ClearBit(DDRD, i);
			break;
			case INPULL:
			ClearBit(DDRD, i);
			SetBit(PORTD, i);
			break;
		}
		break;
		
	}
}
void DIO_Init(void){
	DIO_Pin_t pin=PA0;
	while(pin<TOTAL_PINS){
	DIO_InitPin(pin,PinStatusArray[pin]);
	pin++;
	}
}
void DIO_WritePin(DIO_Pin_t pin, DIO_PinVolt_t volt){
	DIO_Port_t port=pin/8;
	u8 i=pin%8;
	switch(port){
		case PA:
		if(volt==HIGH){
			SetBit(PORTA,i);
		}
		else if(volt==LOW){
			ClearBit(PORTA,i);
		}
		break;
		case PB:
		if(volt==HIGH){
			SetBit(PORTB,i);
		}
		else if(volt==LOW){
			ClearBit(PORTB,i);
		}
		break;
		case PC:
		if(volt==HIGH){
			SetBit(PORTC,i);
		}
		else if(volt==LOW){
			ClearBit(PORTC,i);
		}
		break;
		case PD:
		if(volt==HIGH){
			SetBit(PORTD,i);
		}
		else if(volt==LOW){
			ClearBit(PORTD,i);
		}
		break;
	}
}

void DIO_WritePort(DIO_Port_t port, DIO_PinVolt_t volt){
	switch(port){
		case PA:
		if(volt==HIGH){
			SetPort(PORTA);
		}
		else if(volt==LOW){
			ClearPort(PORTA);
		}
		break;
		case PB:
		if(volt==HIGH){
			SetPort(PORTB);
		}
		else if(volt==LOW){
			ClearPort(PORTB);
		}
		break;
		case PC:
		if(volt==HIGH){
			SetPort(PORTC);
		}
		else if(volt==LOW){
			ClearPort(PORTC);
		}
		break;
		case PD:
		if(volt==HIGH){
			SetPort(PORTD);
		}
		else if(volt==LOW){
			ClearPort(PORTD);
		}
		break;
	}
}


void DIO_TogglePin(DIO_Pin_t pin){
	DIO_Port_t port=pin/8;
	u8 i=pin%8;
	switch(port){
		case PA:
		ToggleBit(PORTA, i);
		break;
		case PB:
		ToggleBit(PORTB, i);
		break;
		case PC:
		ToggleBit(PORTC, i);
		break;
		case PD:
		ToggleBit(PORTD, i);
		break;
	}
}
	

DIO_PinVolt_t DIO_ReadPin(DIO_Pin_t pin){
	DIO_PinVolt_t volt;
	DIO_Port_t port=pin/8;
	u8 i=pin%8;
	switch(port){
		case PA:
		volt=ReadBit(PINA, i);
		break;
		case PB:
		volt=ReadBit(PINB, i);
		break;
		case PC:
		volt=ReadBit(PINC, i);
		break;
		case PD:
		volt=ReadBit(PIND, i);
		break;
	}
	return volt;
}