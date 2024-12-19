/*
 * eepromExt_Interface.h
 *
 * Created: 4/26/2024 9:35:16 PM
 *  Author: Mohammed
 */ 


#ifndef EEPROMEXT_INTERFACE_H_
#define EEPROMEXT_INTERFACE_H_

void eepromExt_Init();
void eepromExt_ReadArr(u8 address, u8 *arr, u8 length);
void eepromExt_WriteArr(u8 address, u8 *arr, u8 length);




#endif /* EEPROMEXT_INTERFACE_H_ */