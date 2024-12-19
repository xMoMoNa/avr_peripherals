/*
 * UART_Interface.h
 *
 * Created: 4/13/2024 9:59:31 AM
 *  Author: Mohammed
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


void uart_Init(void);



void uart_sendNow(u8 data);
void uart_recieveNow(u8 *data);




void uart_setCallback_RX(void (*pfunc_RX)(void));
void uart_setCallback_TX(void (*pfunc_TX)(void));
void uart_EnableInterrupt_RX(void);
void uart_DisableInterrupt_RX(void);
void uart_EnableInterrupt_TX(void);
void uart_DisableInterrupt_TX(void);

#endif /* UART_INTERFACE_H_ */