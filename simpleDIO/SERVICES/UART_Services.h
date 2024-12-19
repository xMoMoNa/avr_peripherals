/*
 * UART_Services.h
 *
 * Created: 4/15/2024 10:34:25 AM
 *  Author: Mohammed
 */ 


#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_

#define NUMBEROFTASK 8


typedef struct{
	u8 *name;
	void (*pfunc)(u8 data);
} uart_task_t;

u8 uart_sendAsync(u8 data);
u8 uart_recieveAsync(u8 *data);
u8 uart_sendStringAsync(u8 *str);
u8 uart_recieveStringAsync(u8 **data);


void uart_taskInit(void);

#endif /* UART_SERVICES_H_ */