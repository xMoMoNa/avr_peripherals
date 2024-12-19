/*
 * bluetooth_Interface.h
 *
 * Created: 4/27/2024 8:42:55 AM
 *  Author: Mohammed
 */ 


#ifndef BLUETOOTH_INTERFACE_H_
#define BLUETOOTH_INTERFACE_H_

void bluetooth_Init();
void bluetooth_Send();
void bluetooth_Recieve();
void bluetooth_AT(u8*str);



#endif /* BLUETOOTH_INTERFACE_H_ */