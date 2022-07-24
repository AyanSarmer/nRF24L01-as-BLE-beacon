#include "OneWire.h"

void owiInit()
{
    OWI_RELEASE_BUS;
    _delay_us(DELAY_H);
}

void owiReset()
{
    OWI_PULL_BUS_LOW;
    _delay_us(DELAY_H);  
    OWI_RELEASE_BUS;
    _delay_us(DELAY_I);  
    _delay_us(DELAY_J);
}

void owiWriteBit0()
{
    OWI_PULL_BUS_LOW;
    _delay_us(DELAY_C);
    OWI_RELEASE_BUS;
    _delay_us(DELAY_D);  
}

void owiWriteBit1()
{
    OWI_PULL_BUS_LOW;
    _delay_us(DELAY_A);
    OWI_RELEASE_BUS;
    _delay_us(DELAY_B);    
}

unsigned char owiReadBit()
{
    uint32_t bitsRead = 0;
    OWI_PULL_BUS_LOW;
    _delay_us(DELAY_A);  
    OWI_RELEASE_BUS;
    _delay_us(DELAY_E);  
    if(OWI_PIN & (1 << OWI_BUS)) 
        bitsRead = 1;  
    _delay_us(DELAY_F);  
    return bitsRead;
}

void owiSendByte(unsigned char data)
{
    unsigned char temp, currentBit;

    for (currentBit = 0; currentBit < 8; currentBit++) 
    {
        temp = data & 0x01;
        if (temp) 
        {
            owiWriteBit1();
        } 
        else 
        {
            owiWriteBit0();
        }
        data >>= 1;
    }  
}

unsigned char owiReceiveByte()
{
    unsigned char data = 0, currentBit = 0;  

    for (currentBit = 0; currentBit < 8; currentBit++) 
    {  
        data >>= 1;
        if (owiReadBit()) 
        {
        data |= MSBit;
        }
    }
    return data;    
}