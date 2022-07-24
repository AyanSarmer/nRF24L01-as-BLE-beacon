#include "DS18B20.h"

unsigned char DS18B20_State = FREE_STATE;
unsigned char temperatureSign;
float temperature;

void DS18B20_Init()
{
  owiInit();
}

void DS18B20_StartConversion()
{
  owiReset();
  owiSendByte(SKIP_ROM);
  owiSendByte(CONVERT_T);
}  

void DS18B20_ReadTemperature()
{
  owiReset();
  owiSendByte(SKIP_ROM);
  owiSendByte(READ_SCRATCH_PAD);
  for(int i = 0; i < 2; i++)
  {
    data[i] = owiReceiveByte();
  }
  owiReset();

  temperature = (data[1] << 8 | data[0])/16.0;
  if(temperature >= 0)
  {
    temperatureSign = PLUS;
  }
  else if(temperature < 0)
  {
    temperatureSign = MINUS; 
  }
}