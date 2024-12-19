/*
 * eepromInternal.h
 *
 * Created: 5/5/2024 1:16:47 PM
 *  Author: Mohammed
 */ 


#ifndef EEPROMINTERNAL_INTERFACE_H_
#define EEPROMINTERNAL_INTERFACE_H_

void eepromInt_Int(void);
void eepromInt_Write(u16 address, u8 data);
void eepromInt_Read(u16 address, u8* data);

#endif /* EEPROMINTERNAL_INTERFACE_H_ */