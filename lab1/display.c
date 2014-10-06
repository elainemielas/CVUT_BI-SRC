#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "oled.h"
#include "display.h"

#define    FCY    16000000UL
#include <libpic30.h>
#define DELAY 300/portTICK_RATE_MS

xQueueHandle xDisplayQueue;

void vDisplayInit ( void )
{
    vOLEDInit();
    xDisplayQueue = xQueueCreate( 5, 10 );
}


void vDisplayPrintTask ( void * pvParameters )
{
    /*
    portBASE_TYPE xI;
    for ( xI = 0; xI < 10; xI++ )
        vOLEDPutChar ( (char) pvParameters );
    vTaskDelete ( NULL );
    */
    while(1){
        vDisplayPutString((char*) pvParameters);
        __delay_ms(500);
    }
    
}

void vDisplayPrintTask2 ( void * pvParameters )
{

    while(1){
        vDisplayPutString((char*) pvParameters);
        vTaskDelay(DELAY);
    }

}

void vDisplayGatekeeperTask ( void * pvParameters )
{
    while(1){
        char buf[10];
        xQueueReceive( xDisplayQueue, (void*) &buf, portMAX_DELAY );
        vOLEDPutString(buf);
    }
}

void vDisplayPutString ( const char * pcString )
{
    xQueueSendToBack( xDisplayQueue, (void*) pcString, portMAX_DELAY);
}
