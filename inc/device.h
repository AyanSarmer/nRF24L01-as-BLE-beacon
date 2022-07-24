#ifndef DEVICE_H_
#define DEVICE_H_

#include "nRF24.h"
#include "BLE.h"
#include "DS18B20.h"
#include "systemClock.h"

void deviceInit();
void deviceControl();

#endif /* DEVICE_H_ */