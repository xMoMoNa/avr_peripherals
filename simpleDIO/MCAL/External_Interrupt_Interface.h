/*
 * External_Interrupt_Interface.h
 *
 * Created: 2024-03-25 4:34:25 AM
 *  Author: Mohammed
 */ 


#ifndef EXTERNAL_INTERRUPT_INTERFACE_H_
#define EXTERNAL_INTERRUPT_INTERFACE_H_
typedef enum{
	EXT2,
	EXT0,
	EXT1,
	}EXT_t;

typedef enum{
	LOW_LEVEL,
	LOGIC_CHANGE,
	FALL_EDGE,
	RISE_EDGE,
}Int_Sense;

void EXT_INT_Init(EXT_t ext, Int_Sense sense, void(*fun)(void));
void EXT_INT_Disable(EXT_t ext);
void EXT_INT_Set_Function(EXT_t ext, void(*fun)(void));
void EXT_INT_Clear_Function(EXT_t ext);


#endif /* EXTERNAL_INTERRUPT_INTERFACE_H_ */