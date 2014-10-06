/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"

/* Application includes. */
#include "display.h"
#include "stack.h"

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
    xTaskHandle xTask1, xTask2;
    
    /* Create the task. */
    xTaskCreate( vStackTask1, ( signed char * ) "ST 1", 61, NULL, tskIDLE_PRIORITY + 1, &xTask1 );
    xTaskCreate( vStackTask2, ( signed char * ) "ST 2", 69, NULL, tskIDLE_PRIORITY + 1, &xTask2 );
    xTaskCreate( vStackTask3, ( signed char * ) "ST 3", 250, (void*)xTask1, tskIDLE_PRIORITY + 1, NULL );
    //( vStackTask3, ( signed char * ) "ST 4", 250, (void*)xTask2, tskIDLE_PRIORITY + 1, NULL );


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
}

/*-----------------------------------------------------------*/
