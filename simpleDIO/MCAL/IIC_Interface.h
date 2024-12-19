/*
 * IIC_Interface.h
 *
 * Created: 4/24/2024 11:51:57 AM
 *  Author: Mohammed
 */ 


#ifndef IIC_INTERFACE_H_
#define IIC_INTERFACE_H_

typedef enum{
	IIC_WRITE=0,
	IIC_READ,
}iic_ReadWrite_t;

typedef enum{
	IIC_SLAVE=0,
	IIC_MASTER,
}iic_MasterSlave_t;

void iic_Init(u8 address, iic_MasterSlave_t mode);

void iic_MasterSendArr(u8 address, u8 *arr, u8 length);
void iic_MasterRecieveArr(u8 address, u8 *arr, u8 length);

void iic_SlaveSendArr(u8 *arr, u8 length);
u8 iic_SlaveRecieveArr(u8 **arr, u8 length);

void iic_InterruptEnable();
void iic_InterruptDisable();

void iic_SetCallback(void (*fun)(void));

#endif /* IIC_INTERFACE_H_ */