#ifndef BLE_H_
#define BLE_H_

#include "nRF24.h"

#define PDU_TYPE        0x42
#define PDU_LENGTH      0x11

#define MAC_0           0x23
#define MAC_1           0xFA
#define MAC_2           0xC4
#define MAC_3           0xE3
#define MAC_4           0x17
#define MAC_5           0x8B

unsigned char swapByte(unsigned char a);
void generateCRC(unsigned char* dst);
void whitening(unsigned char channel);
void transformTemperature(float temperature);
void preparePacket();

extern unsigned char channel[3];
extern unsigned char frequency[3];
extern unsigned char channelNum; 
extern float temperature;

#endif /* BLE_H_ */

