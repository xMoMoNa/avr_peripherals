/*
* IIC.c
*
* Created: 4/24/2024 11:51:40 AM
*  Author: Mohammed
*/
#include "..\std_types.h"
#include "..\memory_map.h"
#include "..\utils.h"
#include "IIC_Interface.h"
#define F_CPU	8000000UL
#include <util/delay.h>
/**************************************************************/
#define checkStatus(status)	((TWSR&0xf8)==status)

static void iic_Start(u8 address, iic_ReadWrite_t mode);
static void iic_Stop(void);
static void iic_SlaveSendRecieve(void);
static void iic_SlaveSendISR(void);
static void iic_SlaveRecieveISR(void);

/*************************************************************/
static u8 SlaveSend[20];

static u8 SlaveRecieveTop=0, SlaveRecieveHead=0;
static u8 SlaveRecieve[2][20];
static u8 SlaveRecieveLength[2];

static void (*pfunc_ISR)(void) = NULL;


/**************************************************************/
void iic_Init(u8 address, iic_MasterSlave_t mode){
	// Enable acknowledge bit
	SetBit(TWCR, TWEA);
	
	// Enable iic
	SetBit(TWCR, TWEN);
	
	// Set Address for slave and enable general call
	TWAR=(address<<1)|1;
	
	if (mode == IIC_SLAVE){
		iic_SetCallback(iic_SlaveSendRecieve);
		
		// Enable Interrupt
		iic_InterruptEnable();
	}
}

static void iic_Start(u8 address, iic_ReadWrite_t mode){
	/*Set Start Condition*/
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)|(1<<TWEA);
	/* check start condition done*/
	while(!ReadBit(TWCR, TWINT));
	if (!checkStatus(0x08) && !checkStatus(0x10)){
		return ;
	}
	/*Load Slave address and mode read or write*/
	TWDR=(address<<1)|mode;
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	/*wait untill recieve ack from slave*/
	while(!ReadBit(TWCR, TWINT));
	if(!checkStatus(0x18) && mode==IIC_WRITE){
		return;
	}
	if(!checkStatus(0x40) && mode==IIC_READ){
		return;
	}
}


static void iic_Stop(void){
	SetBit(TWCR,TWSTO);
	SetBit(TWCR,TWINT);
}


void iic_MasterSendArr(u8 address, u8 *arr, u8 length){
	u8 i=0;
	ClearBit(TWCR,TWSTO);
	iic_Start(address, IIC_WRITE);
	while(i<length){
	TWDR = arr[i];
	i++;
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(!ReadBit(TWCR, TWINT));
	if (checkStatus(0x28)){
	PORTC|=0x08;
	}else{
	return;
	
	}
	}
	iic_Stop();
}

void iic_MasterRecieveArr(u8 address, u8 *arr, u8 length){
	u8 i=0;
	ClearBit(TWCR,TWSTO);
	iic_Start(address, IIC_READ);
	PORTC|=0x08;
	while(i<length){
		while(!ReadBit(TWCR, TWINT));
		SetBit(TWCR, TWINT);
		if (!checkStatus(0x50)){
			return;
		}
		arr[i]=TWDR;
		i++;
	}
	iic_Stop();
}

static void iic_SlaveSendRecieve(void){
	if (checkStatus(0x60)){ // master send data slave receive
		iic_SetCallback(iic_SlaveRecieveISR);
		SlaveRecieve[SlaveRecieveHead][0]=TWDR;
	}
	else if(checkStatus(0xA8)){// slave send data master receive
		iic_SetCallback(iic_SlaveSendISR);
		TWDR=SlaveSend[0];
	}
}

static void iic_SlaveRecieveISR(void){
	static u8 i=1, length=1;
	if (checkStatus(0x70)){ // check master select slave or general call to receive data
		SlaveRecieve[SlaveRecieveTop][i]=TWDR;
		i++;
		length++;
	}
	if (checkStatus(0xA0)){ // master finish send data
		iic_SetCallback(iic_SlaveSendRecieve);
		SlaveRecieveLength[SlaveRecieveTop]=length;
		i=1;
		length=1;
		if ((SlaveRecieveTop+1)%2 != SlaveRecieveHead){
			SlaveRecieveTop=(SlaveRecieveTop+1)%2;
		}
	}
}

static void iic_SlaveSendISR(void){
	static u8 i=1;
	if (checkStatus(0xB8)){
		TWDR=SlaveSend[i];
		i++;
	}
	if (checkStatus(0xC8)){
		iic_SetCallback(iic_SlaveSendRecieve);
		i=1;
	}
}

void iic_SlaveSendArr(u8 *arr, u8 length){
	u8 i=0;
	while (i<length){
		SlaveSend[i]=arr[i];
		i++;
	}
}

u8 iic_SlaveRecieveArr(u8 **arr, u8 length){
	if (SlaveRecieveTop!=SlaveRecieveHead){
		*arr=SlaveRecieve[SlaveRecieveHead];
		length=SlaveRecieveLength[SlaveRecieveHead];
		SlaveRecieveHead=(SlaveRecieveHead+1)%2;
		return 1;
	}
	return 0;
}


void iic_InterruptEnable(){
	SetBit(TWCR, TWIE);
}

void iic_InterruptDisable(){
	ClearBit(TWCR, TWIE);
}

void iic_SetCallback(void (*func)(void)){
	pfunc_ISR=func;
}



ISR(VECT_TWI){
	if (pfunc_ISR!= NULL){
		pfunc_ISR();
	}
	
}