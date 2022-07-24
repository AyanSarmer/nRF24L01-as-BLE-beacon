#include "device.h"

int main()
{
    deviceInit();

    while(1)
    {
        deviceControl();
    }
}  
