/*
 * eepromInternal.c
 *
 * Created: 5/5/2024 1:16:31 PM
 *  Author: Mohammed
 */ 
#include "..\std_types.h"
#include "..\memory_map.h"
#include "..\utils.h"
#include "eepromInternal_Interface.h"

void eepromInt_Int(void){
	
}

void eepromInt_Write(u16 address, u8 data){
	/* wait until complete write*/
	while(ReadBit(EECR, EEWE));
	/*set address and data*/
	EEAR=address;
	EEDR=data;
	/*enable master write bit*/
	SetBit(EECR, EEMWE);
	/*start write data*/
	SetBit(EECR, EEWE);
}

void eepromInt_Read(u16 address, u8* data){
	/* wait until complete write*/
	while(ReadBit(EECR, EEWE));
	/*set address and data*/
	EEAR=address;
	/*start read*/
	SetBit(EECR, EERE);
	*data=EEDR;
}