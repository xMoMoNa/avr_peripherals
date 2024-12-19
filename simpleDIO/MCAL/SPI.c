/*
* SPI.c
*
* Created: 4/17/2024 6:03:02 PM
*  Author: Mohammed
*/
#include "..\std_types.h"
#include "..\memory_map.h"
#include "..\utils.h"
#include "SPI_Interface.h"

#define F_CPU	8000000UL
#include <util/delay.h>

u8 masterRecieveStr[20];

static u8 headRecieve, topRecieve;
u8 slaveRecieveData[8];

static u8 headRecieveStr, topRecieveStr;
u8 slaveRecieveStr[8][20];

static u8 headSendStr, topSendStr;
static u8 *slaveSendStr[8];

static void (*pfunc_ISR)(void) = NULL;

static void spi_recieveISR(void);

static void spi_recieveStrISR(void);
static void spi_sendStrISR(void);



void spi_Init(SPI_mode mode){
	/*Chose Mode*/
	if (mode==SPI_MASTER){
		SetBit(SPCR, MSTR);
		spi_InterruptDisable();
		/*enable interrupt*/
		spi_InterruptDisable();
	}
	else{
		ClearBit(SPCR, MSTR);
		spi_InterruptEnable();
	}
	//change speed
	//SetBit(SPCR, SPR0);
	//SetBit(SPCR, SPR1);
	/*Enable SPI*/
	SetBit(SPCR, SPE);
}

u8 spi_MasterSendReceive(u8 data){
	SPDR=data;
	while(!ReadBit(SPSR, SPIF));
	return SPDR;
}

u8* spi_MasterSendReceiveStr(u8 *str){
	u8 i=0;
	while(str[i]){
		masterRecieveStr[i]=spi_MasterSendReceive(str[i]);
		i++;
		_delay_us(7);
	}
	masterRecieveStr[i]=spi_MasterSendReceive(str[i]);
	_delay_us(5);
	return masterRecieveStr;
}

void spi_SlaveSend(u8 data){
	SPDR=data;
}

u8 spi_SlaveRecieve(u8 *data){
	spi_SetCallback(spi_recieveISR);
	if (headRecieve!=topRecieve){
		*data=slaveRecieveData[headRecieve];
		headRecieve= (headRecieve+1)%8;
		return 1;
	}
	return 0;
}

static void spi_recieveISR(void){
	slaveRecieveData[topRecieve]=SPDR;
	topRecieve= (topRecieve+1)%8==headRecieve ? headRecieve : (topRecieve+1)%8;
}

u8 spi_SlaveRecieveStr(u8 **str){
	spi_SetCallback(spi_recieveStrISR);
	if (headRecieveStr!=topRecieveStr){
		*str=slaveRecieveStr[headRecieveStr];
		headRecieveStr= (headRecieveStr+1)%8;
		return 1;
	}
	return 0;
}

static void spi_recieveStrISR(void){
	static u8 i=0;
	slaveRecieveStr[topRecieve][i]=SPDR;
	if (slaveRecieveStr[topRecieve][i]==0x0D){
		slaveRecieveStr[topRecieve][i]=0;
		topRecieve= (topRecieve+1)%8==headRecieve ? headRecieve : (topRecieve+1)%8;
		i=0;
		return;
	}
	i++;
}


u8 spi_SlaveSendStr(u8 *str){ //need to complete
	spi_SetCallback(spi_sendStrISR);
	if (topSendStr == headRecieveStr){
		SPDR= str[0];
		slaveSendStr[topSendStr]=str+1;
	}
	else{
		slaveSendStr[topSendStr]=str;
	}
	
	topSendStr= (topSendStr+1)%8==headSendStr ? headSendStr : (topSendStr+1)%8;
}

static void spi_sendStrISR(void){ // need to complete
	static u8 i=0;
	if (slaveSendStr[headSendStr][i]==0){
		headSendStr= (headSendStr+1)%8;
		return;
	}
	SPDR= slaveSendStr[headSendStr][i];
	i++;
}



void spi_InterruptEnable(void){
	SetBit(SPCR, SPIE);
}

void spi_InterruptDisable(void){
	ClearBit(SPCR, SPIE);
}

void spi_SetCallback(void (*fun)(void)){
	pfunc_ISR=fun;
}

ISR(VECT_SPI_STC){
	if (pfunc_ISR!=NULL){
		pfunc_ISR();
	}
}

