#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "led.h"
#include "display.h"
#include "keypad.h"
#include "assignment.h"
#include "stdio.h"
#include "oled.h"
#include <stdlib.h>

#define    FCY    16000000UL
#include <libpic30.h>

#define SEC 1000/portTICK_RATE_MS
#define LIMIT 1000 /*size of integers array*/
#define PRIME 32 /*size of primes array*/

void vAssigmentIncrement ( void )
{
    //vOLEDPutString(" vAssigmentIncrement ");
    portBASE_TYPE xProm = 0;
    while(1){
        char buf[10];
        itoa (buf,xProm,10);
        vOLEDPutString(buf);
        vOLEDPutChar(' ');
        vTaskDelay(SEC);
        xProm++;
    }
}


//Vytvořte task, který bude pomocí Eratosthenova síta hledat největší prvočíslo
//menší než 1000 a přesně jednou za sekundu jej bude vypisovat na displej
//(výpis nějak odlište od výpisu předchozího tasku). Číslo hledejte pokaždé znovu.
void vAssigmentErat (void)
{
    char buf[10];
    portBASE_TYPE i,j;
    portBASE_TYPE primes[PRIME];
    char sieve[LIMIT];
    while (1){
        vTaskDelay(SEC);
        for (i=0; i<LIMIT;i++){sieve[i]=0;}
        for (i=2; i*i <= LIMIT; i++) {
              if (!sieve[i]) {
                   for(j = i+i; j < LIMIT; j+=i) { sieve[j] = 1; }
              }
        }
        for (i=2; i<LIMIT; i++) {
               if (!sieve[i]) { primes[j++]=i; }
        }
        itoa (buf,primes[j-1],10);
        vOLEDPutString(buf);
        vOLEDPutChar('*');
        vOLEDPutChar(' ');
    }
}

void vAssigmentArrInc (void * pvParameters){
    xTaskHandle xTask;
    xTask = (xTaskHandle) pvParameters;
    while(1){
        if ( xSemaphoreTake( xKeypadUp, portMAX_DELAY ) == pdTRUE ) {
                vTaskPrioritySet( xTask, uxTaskPriorityGet( xTask ) + 1 );
                vOLEDPutString(" T1UP ");
        }
        if ( xSemaphoreTake( xKeypadDown, portMAX_DELAY ) == pdTRUE ) {
                vTaskPrioritySet( xTask, uxTaskPriorityGet( xTask ) - 1 );
                vOLEDPutString(" T1DOWN ");
        }
    }
}

void vAssigmentArrErat (void * pvParameters){
    xTaskHandle xTask;
    xTask = (xTaskHandle) pvParameters;
    while(1){
        if ( xSemaphoreTake( xKeypadRight, portMAX_DELAY ) == pdTRUE ) {
                //char buf[15];
                unsigned portBASE_TYPE uxPrior;
                //unsigned portBASE_TYPE uxNew;
                uxPrior = uxTaskPriorityGet( xTask );
                //snprintf(buf,15,"Priorita old: %d \r\n", uxPrior);
                //vOLEDPutString(buf);
                vTaskPrioritySet( xTask, uxPrior + 1);
                //uxNew = uxTaskPriorityGet( xTask );
                //snprintf(buf,15,"Priorita new: %d \r\n", uxNew);
                //vOLEDPutString(buf);
                vOLEDPutString(" T2UP ");

        }
        if ( xSemaphoreTake( xKeypadLeft, portMAX_DELAY ) == pdTRUE ) {
                vTaskPrioritySet( xTask, uxTaskPriorityGet( xTask ) - 1 );
                vOLEDPutString(" T2DOWN ");
        }
    }
}

//Při zmáčknutí prostředního tlačítka vytvořte task, který rozsvítí LED,
//500 ms počká, zhasne LED a smaže sám sebe. Vyzkoušejte alespoň dvacetkrát.
//Pokud to nefunguje, zjistitě proč a proveďte nezbytné změny.
void vAssigmentArrLed (void){
                vLEDSet(0,1);
                vTaskDelay(SEC/2);
                vLEDSet(0,0);
                vTaskDelete(NULL);
      
}

void vAssigmentArrLedCtrl (void){
    xTaskHandle xTask;
    while(1){
        if ( xSemaphoreTake( xKeypadMiddle, portMAX_DELAY ) == pdTRUE ) {
            //vTaskSuspendAll ();
            xTaskCreate( vAssigmentArrLed, ( signed char * ) "LED", 115, NULL, tskIDLE_PRIORITY + 1, &xTask );
            //configASSERT( xTask );
            //xTaskResumeAll ();
            vTaskDelay(SEC/2);
        }
    }
}

void vAssigmentStack ( void * pvParameters )
{
    xTaskHandle xTask;
    xTask = (xTaskHandle) pvParameters;
    unsigned portBASE_TYPE uxHighWaterMark;
    uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
    char buf[15];
    while ( 1 )
    {
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        snprintf(buf,15,"Task: %d \n",uxHighWaterMark);
        vOLEDPutString(buf);
    }
}
