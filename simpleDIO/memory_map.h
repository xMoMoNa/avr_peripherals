/*
 * memory_map.h
 *
 * Created: 2024-01-28 10:10:51 PM
 *  Author: Mohammed
 */ 
#include "std_types.h"

#ifndef MEMORY_MAP_H_
#define MEMORY_MAP_H_
#define SREG			(*(volatile u8*)(0x5F))

/********** DIO register ***********/
#define  PORTA		(*(volatile u8*)(0x3B))
#define DDRA		(*(volatile u8*)(0x3A))
#define PINA			(*(volatile u8*)(0x39))

#define  PORTB		(*(volatile u8*)(0x38))
#define DDRB		(*(volatile u8*)(0x37))
#define PINB			(*(volatile u8*)(0x36))

#define  PORTC		(*(volatile u8*)(0x35))
#define DDRC		(*(volatile u8*)(0x34))
#define PINC			(*(volatile u8*)(0x33))

#define  PORTD		(*(volatile u8*)(0x32))
#define DDRD		(*(volatile u8*)(0x31))
#define PIND			(*(volatile u8*)(0x30))

/********** ADC register ***********/
#define ADMUX		(*(volatile u8*)(0x27))
#define REFS1		7
#define REFS0		6
#define ADLAR		5
#define MUX4		4
#define MUX3		3
#define MUX2		2
#define MUX1		1
#define MUX0		0

#define ADCSRA		(*(volatile u8*)(0x26))
#define ADEN		7
#define ADSC		6
#define ADATE		5
#define ADIF		4
#define ADIE		3
#define ADOS2		2
#define ADOS1		1
#define ADOS0		0

#define ADCH		(*(volatile u8*)(0x25))
#define ADCL		(*(volatile u8*)(0x24))

#define SFIOR		(*(volatile u8*)(0x50))
#define ADTS2		7
#define ADTS1		6
#define ADTS0		5

/********** Vector Table ***********/
#define VECT_INT0				__vector_1  // External Interrupt Request 0
#define VECT_INT1				__vector_2  // External Interrupt Request 1
#define VECT_INT2				__vector_3  // External Interrupt Request 2
#define VECT_TIM2_COMP		__vector_4  // Timer/Counter2 Compare Match
#define VECT_TIM2_OVF		__vector_5  // Timer/Counter2 Overflow
#define VECT_TIM1_CAP		__vector_6  // Timer/Counter1 Capture Event	
#define VECT_TIM1_COMPA	__vector_7  // Timer/Counter1 Compare Match A
#define VECT_TIM1_COMPB	__vector_8  // Timer/Counter1 Compare Match B
#define VECT_TIM1_OVF		__vector_9  // Timer/Counter1 Overflow
#define VECT_TIM0_COMP		__vector_10 // Timer/Counter0 Compare Match
#define VECT_TIM0_OVF		__vector_11 // Timer/Counter0 Overflow
#define VECT_SPI_STC			__vector_12 // Serial Transfer Complete
#define VECT_USART_RXC		__vector_13 // USART, Rx Complete
#define VECT_USART_UDRE	__vector_14 // USART Data Register Empty
#define VECT_USART_TXC		__vector_15 // USART, Tx Complete
#define VECT_ADC				__vector_16 // ADC Conversion Complete
#define VECT_EE_RDY			__vector_17 // EEPROM Ready
#define VECT_ANA_COMP		__vector_18 // Analog Comparator
#define VECT_TWI				__vector_19 // Two-wire Serial Interface
#define VECT_SPM_RDY		__vector_20 // Store Program Memory Ready

#define ISR(vector) \
void vector(void) __attribute__((signal));\
void vector(void)

#define sei()	__asm__ __volatile__("sei" ::) // Enable Global Interrupt
#define cli()	__asm__ __volatile__("sei" ::) // Disable Global Interrupt
#define reti()	__asm__ __volatile__("sei" ::) // 
#define ret()	__asm__ __volatile__("sei" ::) // 

#define MCUCR	(*(volatile u8*)(0x55))
#define ISC11		3
#define ISC10	2
#define ISC01	1
#define ISC00	0
#define MCUCSR	(*(volatile u8*)(0x54))
#define ISC2		6
#define GICR		(*(volatile u8*)(0x5B))
#define INT1		7
#define INT0		6
#define INT2		5
#define GIFR		(*(volatile u8*)(0x5A))
#define INTF1	7
#define INTF0	6
#define INTF2	5

/********** Timer ***********/
/* Timer 0 */
#define TCNT0   (*(volatile unsigned char*)0x52)
#define TCCR0   (*(volatile unsigned char*)0x53)
/* TCCR0 */
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

#define TWCR    (*(volatile unsigned char*)0x56)
#define SPMCR   (*(volatile unsigned char*)0x57)
#define TIFR    (*(volatile unsigned char*)0x58)
#define TIMSK   (*(volatile unsigned char*)0x59)
/* TIMSK */
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0

#define OCR0    (*(volatile unsigned char*)0x5C)
/****************************************************************************************************/

/*TIMER 1*/


#define ICR1         (*(volatile unsigned short*)0x46)
#define ICR1L     (*(volatile unsigned char*)0x46)
#define ICR1H     (*(volatile unsigned char*)0x47)
#define OCR1B     (*(volatile unsigned short*)0x48)
#define OCR1BL    (*(volatile unsigned char*)0x48)
#define OCR1BH       (*(volatile unsigned char*)0x49)
#define OCR1A     (*(volatile unsigned short*)0x4A)
#define OCR1AL    (*(volatile unsigned char*)0x4A)
#define OCR1AH      (*(volatile unsigned char*)0x4B)
#define TCNT1       (*(volatile unsigned short*)0x4C)
#define TCNT1L    (*(volatile unsigned char*)0x4C)
#define TCNT1H    (*(volatile unsigned char*)0x4D)
#define TCCR1B       (*(volatile unsigned char*)0x4E)
#define TCCR1A        (*(volatile unsigned char*)0x4F)

//#define SFIOR       (*(volatile unsigned char*)0x50)

#define OSCCAL       (*(volatile unsigned char*)0x51)
/******************************************************************************/
/* Timer 2 */

#define OCR2     (*(volatile unsigned char*)0x43)
#define TCNT2    (*(volatile unsigned char*)0x44)
#define TCCR2    (*(volatile unsigned char*)0x45)




/* TCCR2 */
#define FOC2    7
#define WGM20   6
#define COM21   5
#define COM20   4
#define WGM21   3
#define CS22    2
#define CS21    1
#define CS20    0

/* ASSR */
/* bits 7-4 reserved */
#define AS2     3
#define TCN2UB  2
#define OCR2UB  1
#define TCR2UB  0

/* TCCR1A */
#define COM1A1  7
#define COM1A0  6
#define COM1B1  5
#define COM1B0  4
#define FOC1A   3
#define FOC1B   2
#define WGM11   1
#define WGM10   0

/* TCCR1B */
#define ICNC1   7
#define ICES1   6
/* bit 5 reserved */
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0

/* WDTCR */
#define WDTCR    (*(volatile unsigned char*)0x41)
/* bits 7-5 reserved */
#define WDTOE   4
#define WDE     3
#define WDP2    2
#define WDP1    1
#define WDP0    0








/*****************************UART Registers*******************************/
/* USART Baud Rate Register Low */
#define UBRRL    (*(volatile unsigned char*)0x29)

/* USART Control and Status Register B */
#define UCSRB   (*(volatile unsigned char*)0x2A)

#define    RXCIE        7
#define    TXCIE        6
#define    UDRIE        5
#define    RXEN         4
#define    TXEN         3
#define    UCSZ         2
#define    UCSZ2        2
#define    RXB8         1
#define    TXB8         0
/* USART Control and Status Register A */
#define UCSRA    (*(volatile unsigned char*)0x2B)

#define    RXC          7
#define    TXC          6
#define    UDRE         5
#define    FE           4
#define    DOR          3
#define    UPE          2
#define    U2X          1
#define    MPCM         0
/* USART I/O Data Register */
#define UDR       (*(volatile unsigned char*)0x2C)

/* USART Baud Rate Register High */
#define UBRRH    (*(volatile unsigned char*)0x40)

/* USART Control and Status Register C */
#define UCSRC     (*(volatile unsigned char*)0x40)

/* USART Register C */
#define    URSEL        7
#define    UMSEL        6
#define    UPM1         5
#define    UPM0         4
#define    USBS         3
#define    UCSZ1        2
#define    UCSZ0        1
#define    UCPOL        0



/******************************************************************************/
/* SPI */
/* SPI Control Register */
#define SPCR       (*(volatile unsigned char*)0x2D)
/* SPI Status Register */
#define SPSR       (*(volatile unsigned char*)0x2E)
/* SPI I/O Data Register */
#define SPDR       (*(volatile unsigned char*)0x2F)

/* SPI Status Register - SPSR */
#define    SPIF         7
#define    WCOL         6
#define    SPI2X        0

/* SPI Control Register - SPCR */
#define    SPIE         7
#define    SPE          6
#define    DORD         5
#define    MSTR         4
#define    CPOL         3
#define    CPHA         2
#define    SPR1         1
#define    SPR0         0

/****************************** EEPROM Control Register ****************************/
/* EEPROM Control Register */
#define EECR	(*(volatile unsigned char*)0x3C)

#define    EERIE        3
#define    EEMWE        2
#define    EEWE         1
#define    EERE         0

/* EEPROM Data Register */
#define EEDR	(*(volatile unsigned char*)0x3D)

/* EEPROM Address Register */
#define EEAR	(*(volatile unsigned short*)0x3E)
#define EEARL	(*(volatile unsigned char*)0x3E)
#define EEARH	(*(volatile unsigned char*)0x3F)

/* TWI stands for "Two Wire Interface" or "TWI Was I2C(tm)" */
#define TWBR    (*(volatile unsigned char*)0x20)
#define TWSR    (*(volatile unsigned char*)0x21)
#define TWAR    (*(volatile unsigned char*)0x22)
#define TWDR    (*(volatile unsigned char*)0x23)

/* TIMSK */
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0

/* TIFR */
#define OCF2    7
#define TOV2    6
#define ICF1    5
#define OCF1A   4
#define OCF1B   3
#define TOV1    2
#define OCF0    1
#define TOV0    0

/* SPMCR */
#define SPMIE   7
#define RWWSB   6
/* bit 5 reserved */
#define RWWSRE  4
#define BLBSET  3
#define PGWRT   2
#define PGERS   1
#define SPMEN   0

/* TWCR */
#define TWINT   7
#define TWEA    6
#define TWSTA   5
#define TWSTO   4
#define TWWC    3
#define TWEN    2
/* bit 1 reserved */
#define TWIE    0

/* TWAR */
#define TWA6    7
#define TWA5    6
#define TWA4    5
#define TWA3    4
#define TWA2    3
#define TWA1    2
#define TWA0    1
#define TWGCE   0

/* TWSR */
#define TWS7    7
#define TWS6    6
#define TWS5    5
#define TWS4    4
#define TWS3    3
/* bit 2 reserved */
#define TWPS1   1
#define TWPS0   0

#endif /* MEMORY_MAP_H_ */