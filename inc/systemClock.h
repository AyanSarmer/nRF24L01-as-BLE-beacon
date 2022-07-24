#ifndef SYSTEM_CLOCK_H_
#define SYSTEM_CLOCK_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define NO_DELAY            0
#define DELAY_START         1
#define DELAY_STOP          2

void systemClockInit();

extern volatile bool transmitFlag;
extern volatile unsigned char ds18B20DelayFlag;

#endif /* SYSTEM_CLOCK_H_ */