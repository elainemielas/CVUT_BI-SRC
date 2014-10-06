/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"

/* Application includes. */
#include "oled.h"
#include "display.h"

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
    
    /* Create the task. */
    xTaskCreate( vDisplayPrintTask, ( signed char * ) "Print A", configMINIMAL_STACK_SIZE, (void *) "Ahoj", tskIDLE_PRIORITY + 1, NULL );
    xTaskCreate( vDisplayPrintTask2, ( signed char * ) "Print B", configMINIMAL_STACK_SIZE, (void *) "Blah", tskIDLE_PRIORITY + 2, NULL );
    xTaskCreate( vDisplayGatekeeperTask, ( signed char * ) "Gatekeeper", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 5, NULL );
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
