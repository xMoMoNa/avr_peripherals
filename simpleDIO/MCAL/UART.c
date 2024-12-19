/*
* UART.c
*
* Created: 4/13/2024 9:59:10 AM
*  Author: Mohammed
*/

#include "..\std_types.h"
#include "..\utils.h"
#include "..\memory_map.h"
#include "UART_Interface.h"
void (*pfunc_TX_ISR)(void)=NULL;
void (*pfunc_RX_ISR)(void)=NULL;
 
void uart_Init(void){
	ClearBit(UCSRA,U2X);
	/*Set Baud Rate 9600Kbps*/
	UBRRL=51;
	
	/*Set Baud Rate 38400*/
	//UBRRL=12;
	/*Set Baud Rate 250000*/
	//UBRRL=1;
	/*set data bus to 8 bit and 1 stop bit even parity*/
	//UCSRC=0xA6;
	
	/*set data bus to 8 bit and 1 stop bit disable parity*/
	UCSRC=0x86;
	
	/*Enable Receiver and Transmitter*/
	SetBit(UCSRB, RXEN);
	SetBit(UCSRB, TXEN);
}

void uart_sendNow(u8 data){
	UDR=data;
	
}

void uart_recieveNow(u8 *data){
	*data=UDR;
}






void uart_EnableInterrupt_RX(void){
	SetBit(UCSRB,RXCIE);
}

void uart_EnableInterrupt_TX(void){
	SetBit(UCSRB,TXCIE);
}

void uart_DisableInterrupt_RX(void){
	ClearBit(UCSRB,RXCIE);
}

void uart_DisableInterrupt_TX(void){
	ClearBit(UCSRB,TXCIE);
}



void uart_setCallback_RX(void (*pfunc_RX)(void)){
	pfunc_RX_ISR=pfunc_RX;
}
void uart_setCallback_TX(void (*pfunc_TX)(void)){
	pfunc_TX_ISR=pfunc_TX;
}



ISR(VECT_USART_RXC){
	if (pfunc_RX_ISR!=NULL){
		pfunc_RX_ISR();
	}
}

ISR(VECT_USART_TXC){
	if (pfunc_TX_ISR!=NULL){
		pfunc_TX_ISR();
	}
}