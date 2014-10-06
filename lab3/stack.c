#include <stdlib.h>
#include "stack.h"
#include "oled.h"
#include "FreeRTOS.h"
#include "task.h"

short prvFoo ( long lA )
{
    unsigned char ucArr [20];
    return 42;
}

unsigned char prvBar ( short sB )
{
    short * psP;
    short sA;
    sA = sB;
    psP = &sA;
    return *psP;
}

void vStackTask1 ( void * pvParameters )
{
    unsigned short usI;
    srand('a');
    while ( 1 )
    {
        for ( usI = 0; usI < 10; usI++ )
        {
            if ( rand() % 2 )
                prvFoo ( 1 );
            else
                prvBar ( 2 );
        }
    }
}

unsigned short prvBinomial ( unsigned short usN, unsigned short usK )
{
    if ( usK == 0 || usK == usN )
        return 1;
    return prvBinomial ( usN - 1, usK - 1 ) + prvBinomial ( usN - 1, usK );
}

void vStackTask2 ( void * pvParameters )
{
    while ( 1 )
    {
        prvBinomial ( 4, 2 );
    }
}

void vStackTask3 ( void * pvParameters )
{
    xTaskHandle xTask;
    xTask = (xTaskHandle) pvParameters;
    unsigned portBASE_TYPE uxHighWaterMark;
    uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
    char buf[15];
    while ( 1 )
    {
        uxHighWaterMark = uxTaskGetStackHighWaterMark( xTask );
        snprintf(buf,15,"Task1: %d \n",uxHighWaterMark);
        vOLEDPutString(buf);
    }
}
