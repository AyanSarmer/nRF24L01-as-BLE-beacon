#ifndef DS18B20_H_
#define DS18B20_H_

#include "OneWire.h"

#define SKIP_ROM            0xCC
#define READ_SCRATCH_PAD    0xBE
#define CONVERT_T           0x44

#define MINUS               1
#define PLUS                0

#define SIGN_BITS           0xf8

#define FREE_STATE          0             
#define CONVERSION_STATE    1

void DS18B20_Init();
void DS18B20_StartConversion();
void DS18B20_ReadTemperature();

unsigned char data[2];
extern unsigned char DS18B20_State;
extern float temperature;

#endif /* DS18B20_H_ */
