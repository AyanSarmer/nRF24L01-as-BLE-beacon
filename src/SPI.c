#include "SPI.h"

void spiInit()
{
  SPI_DDR |= (1 << MOSI) | (1 << SCK);
}

void spiByte(unsigned char _byte)
{
  for(uint8_t counter = 8; counter; counter--)
  {
    if (_byte & MSBit)
      MOSI_HIGH;
    else
      MOSI_LOW;
    _byte <<= 1;
    SCK_HIGH; 
      _delay_us(10);
    SCK_LOW; 
  }
}