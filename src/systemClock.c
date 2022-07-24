#include "systemClock.h"

volatile bool transmitFlag; 
volatile unsigned char ds18B20DelayFlag = NO_DELAY;
volatile unsigned char delayCounter = 0; 


ISR(TIM0_COMPA_vect)
{
    transmitFlag = 1;
    
    if(ds18B20DelayFlag == DELAY_START)
    {
        delayCounter++;
        if(delayCounter == 68)
        {
            delayCounter = 0;
            ds18B20DelayFlag = DELAY_STOP;
        }
    }
}

void systemClockInit()
{
    TCCR0A |= (1 << WGM01); 
    OCR0A = 10;    
    TIMSK |= (1 << OCIE0A);
    sei();
    TCCR0B = (1 << CS02) | (1 << CS00);
}
