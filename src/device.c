#include "device.h"

void deviceInit()
{
  DS18B20_Init();
  transceiverInit();  
  systemClockInit();
}  

void deviceControl()
{
  if(DS18B20_State == FREE_STATE)
  {
    DS18B20_State = CONVERSION_STATE;
    DS18B20_StartConversion();
    ds18B20DelayFlag = DELAY_START;
  }

  if(ds18B20DelayFlag == DELAY_STOP)
  {
    ds18B20DelayFlag = NO_DELAY;
    DS18B20_State = FREE_STATE;
    DS18B20_ReadTemperature();   
  }

  if(transmitFlag)
  {
    transmitFlag = 0; 
    transformTemperature(temperature);   
    preparePacket();  
    transceiverTrasmit();      
    channelNum++;
    if(channelNum > 2) channelNum = 0;
    transceiverSetChannel(frequency[channelNum]);  
  }
}