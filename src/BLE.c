#include "BLE.h"

unsigned char channel[3] = {37, 38, 39};
unsigned char frequency[3] = {2, 26, 80};
unsigned char channelNum = 0; 

unsigned char swapByte(unsigned char a)
{
  unsigned char swappedByte = 0;
  
  if(a & 0x80) swappedByte |= 0x01;
  if(a & 0x40) swappedByte |= 0x02;
  if(a & 0x20) swappedByte |= 0x04;
  if(a & 0x10) swappedByte |= 0x08;
  if(a & 0x08) swappedByte |= 0x10;
  if(a & 0x04) swappedByte |= 0x20;
  if(a & 0x02) swappedByte |= 0x40;
  if(a & 0x01) swappedByte |= 0x80;

  return swappedByte;
}

void generateCRC(unsigned char* dst)
{
  unsigned char len = 28;
  unsigned char* buf = (unsigned char*)&packet;
  
  dst[0] = 0xAA;
  dst[1] = 0xAA;
  dst[2] = 0xAA;

  while (len--) 
  {
    unsigned char d = *(buf++);

    for (unsigned char i = 1; i; i <<= 1, d >>= 1) 
    {
      unsigned char t = dst[0] & 0x01;   dst[0] >>= 1;
      if (dst[1] & 0x01) dst[0] |= 0x80; dst[1] >>= 1;
      if (dst[2] & 0x01) dst[1] |= 0x80; dst[2] >>= 1;

      if (t != (d & 1)) 
      {
        dst[2] ^= 0xDA; 
        dst[1] ^= 0x60; 
      }
    }
  }  
}

void whitening(unsigned char channel) 
{
  unsigned char len = 31;
  unsigned char* buf = (unsigned char*)&packet;
  unsigned char lfsr = channel | 0x40;
   
  while (len--) 
  {
    unsigned char res = 0;
    for (unsigned char i = 1; i; i <<= 1) 
    {
      if (lfsr & 0x01) 
      {
        lfsr ^= 0x88;
        res |= i;
      }
      lfsr >>= 1;
    }
    *(buf++) ^= res;
  }
}

void transformTemperature(float temperature) 
{
  int32_t ret;
  int32_t exponent = -2;
  ret = ((exponent & 0xff) << 24) | (((int32_t)(temperature * 100)) & 0xffffff);
  packet[24] = (unsigned char)(ret);
  packet[25] = (unsigned char)(ret >> 8);
  packet[26] = (unsigned char)(ret >> 16);
  packet[27] = (unsigned char)(ret >> 24);
}

void preparePacket()
{
  packet[0] = 0x42;
  packet[1] = 26;
  
  packet[2] = MAC_0;
  packet[3] = MAC_1;
  packet[4] = MAC_2;
  packet[5] = MAC_3;
  packet[6] = MAC_4;
  packet[7] = MAC_5;

  packet[8] = 2;
  packet[9] = 0x01;
  packet[10] = 0x05;
  
  packet[11] = 8;
  packet[12] = 0x09;
  packet[13] = 'D';
  packet[14] = 'S';
  packet[15] = '1';
  packet[16] = '8';
  packet[17] = 'B';
  packet[18] = '2';
  packet[19] = '0';

  packet[20] = 7;
  packet[21] = 0x16;
  packet[22] = 0x09;
  packet[23] = 0x18;
  
  packet[31] = 0x00;
  
  unsigned char* outbuf = (unsigned char*)&packet;
  generateCRC(outbuf + 28);         
  whitening(channel[channelNum]);  
     
  for(unsigned char byteNum = 0; byteNum < 31; byteNum++)
  {
    packet[byteNum] = swapByte(packet[byteNum]);    
  }  
}
