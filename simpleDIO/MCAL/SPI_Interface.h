/*
* SPI_Interface.h
*
* Created: 4/17/2024 6:03:22 PM
*  Author: Mohammed
*/


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

typedef enum{
	SPI_SLAVE,
	SPI_MASTER
} SPI_mode;


void spi_Init(SPI_mode mode);
u8 spi_MasterSendReceive(u8 data);
u8* spi_MasterSendReceiveStr(u8 *str);

void spi_SlaveSend(u8 data);
u8 spi_SlaveRecieve(u8 *data);
void spi_InterruptEnable();
void spi_InterruptDisable();
void spi_SetCallback(void (*fun)(void));

u8 spi_SlaveRecieveStr(u8 **str);
u8 spi_SlaveSendStr(u8 *str);

#endif /* SPI_INTERFACE_H_ */