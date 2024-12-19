/*
 * External_Interrupt.c
 *
 * Created: 2024-03-25 4:34:07 AM
 *  Author: Mohammed
 */ 
#include "..\std_types.h"
#include "..\utils.h"
#include "..\memory_map.h"
#include "External_Interrupt_Interface.h"
static void(*CallBack[3])(void);
void EXT_INT_Init(EXT_t ext, Int_Sense sense, void(*fun)(void)){
	EXT_INT_Set_Function(ext, fun);
	if (ext==EXT2){
		switch(sense){
			case FALL_EDGE:
			ClearBit(MCUCSR, ISC2);
			break;
			case RISE_EDGE:
			SetBit(MCUCSR, ISC2);
			break;
		}
	}
	else{
	MCUCR&= (~(0x03)<<(ext-1));
	MCUCR|= ((sense)<<(ext-1));
	}
	SetBit(GICR, ext+5);
}

void EXT_INT_Disable(EXT_t ext){
	ClearBit(GICR, ext+5);
}

void EXT_INT_Set_Function(EXT_t ext, void(*fun)(void)){
	CallBack[ext]=fun;
}

void EXT_INT_Clear_Function(EXT_t ext){
	CallBack[ext]=NULL;
}

ISR(VECT_INT2){
	CallBack[0]();
}

ISR(VECT_INT0){
	CallBack[1]();
}
ISR(VECT_INT1){
	CallBack[2]();
}