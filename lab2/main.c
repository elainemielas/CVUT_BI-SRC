/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Application includes. */
#include "display.h"
#include "keypad.h"
#include "led.h"
#include "assignment.h"
#include "oled.h"



/*-----------------------------------------------------------*/

/* PIC24F config */
_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF \
     & FWDTEN_OFF & ICS_PGx2)
_CONFIG2( 0xF7FF & IESO_OFF & FCKSM_CSDCMD & OSCIOFNC_OFF \
     & POSCMOD_HS & FNOSC_PRIPLL & PLLDIV_DIV3 & IOL1WAY_ON)

/* Hardware configuration function declaration. */
static void prvSetupHardware ( void );

/*-----------------------------------------------------------*/

/* Create the tasks and start the scheduler. */
int main( void )
{
    /* Configure hardware. */
    prvSetupHardware();
    xTaskHandle xTask1, xTask2, xTask3, xTask4, xTask5, xTask6;
    /* Create the task. */
    xTaskCreate( vAssigmentIncrement, ( signed char * ) "Increment and display", 45, NULL, tskIDLE_PRIORITY, &xTask1 );
    xTaskCreate( vAssigmentErat, ( signed char * ) "Eratosthenovo sito", 1210, NULL, tskIDLE_PRIORITY, &xTask2 );
    xTaskCreate( vKeypadMonitor, ( signed char * ) "Monitor", 52, NULL, tskIDLE_PRIORITY + 3, &xTask3 );
    xTaskCreate( vDisplayGatekeeperTask, ( signed char * ) "Gatekeeper", 115, NULL, tskIDLE_PRIORITY + 3, &xTask6 );
    xTaskCreate( vAssigmentArrInc, ( signed char * ) "Priority increment", 225, (void*)xTask1, tskIDLE_PRIORITY + 1, &xTask4 );
    xTaskCreate( vAssigmentArrErat, ( signed char * ) "Priority erat", 225, (void *)xTask2, tskIDLE_PRIORITY + 1, &xTask5 );
    xTaskCreate( vAssigmentArrLedCtrl, ( signed char * ) "LED", 115, NULL, tskIDLE_PRIORITY + 1, NULL );
    //xTaskCreate( vAssigmentStack, ( signed char * ) "Stack", 125, (void*)xTask6, tskIDLE_PRIORITY + 1, NULL );
    
    /* Start the scheduler. */
    vTaskStartScheduler();

    /* Will only reach here if there is insufficient heap available to start
    the scheduler. */
    return 0;
}
/*-----------------------------------------------------------*/

/* Hardware configuration function definition. */
static void prvSetupHardware ( void )
{
    vDisplayInit();
    vKeypadInit();
    vLEDInit();
}
