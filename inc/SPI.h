#ifndef SPI_H_
#define SPI_H_

#define F_CPU                   1000000UL

#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>

#define SPI_DDR                 DDRB
#define SPI_PORT                PORTB
#define SPI_PIN                 PINB
#define MOSI                    PB1
#define SCK                     PB2

#define MOSI_HIGH               SPI_PORT |= (1 << MOSI)
#define MOSI_LOW                SPI_PORT &= ~(1 << MOSI)
#define SCK_HIGH                SPI_PORT |= (1 << SCK)
#define SCK_LOW                 SPI_PORT &= ~(1 << SCK)

#define MSBit                   0x80
#define LSBit                   0x01

void spiInit();
void spiByte(unsigned char _byte);

#endif /* SPI_H_ */
