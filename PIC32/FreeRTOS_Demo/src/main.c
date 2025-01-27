/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

void vLED3BlinkTask(void *pvParameters)
{
    for(;;)
    {
        // Toggle the LED pin
        LED3_Toggle();  // Using the macros that are included in bsp.h (which is included in definitions.h)
        
        // Sit here for a little bit so that we can see that we aren't in another task (escape from dummy for longer)
        // Note: This is so that we can see that we're in this task on the scope
        //for (volatile int i = 0; i < 500000; i++);
        
        // Delay for 2000 milliseconds
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void vLED2BlinkTask(void *pvParameters)
{
    for (;;)
    {
        LED2_Toggle();
        
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void vLED1BlinkTask(void *pvParameters)
{
    for (;;)
    {
        LED1_Toggle();
        uint64_t testticks = pdMS_TO_TICKS(5);
        vTaskDelay(testticks);
    }
}


// ************ UNDER THIS IS USING SEMAPHORES - USES RGB LED ******************

SemaphoreHandle_t mySemaphore;

void vSemaphoreGiveTask(void *pvParameters)
{
    for(;;)
    {
        // Give the semaphore
        xSemaphoreGive(mySemaphore);

        // Delay for 1 second
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vLEDRGBBlueBlinkTask(void *pvParameters)
{
    for(;;)
    {
        // Wait indefinitely until the semaphore is given
        if (xSemaphoreTake(mySemaphore, portMAX_DELAY) == pdTRUE)
        {
            // Toggle the LED when the semaphore is received
            RGB_LED_B_Toggle(); 
            RGB_LED_G_Toggle(); 
            //RGB_LED_R_Toggle();
        }
    }
}



// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize(NULL);
    
    mySemaphore = xSemaphoreCreateBinary();
    
     if (mySemaphore != NULL)
    {
        // Create the Semaphore Give task
        xTaskCreate(vSemaphoreGiveTask,      // Task function
                    "SemaphoreGiveTask",     // Name of the task
                    1024,                    // Stack size
                    NULL,                    // Task parameters
                    1,                       // Task priority
                    NULL);                   // Task handle

        // Create the LED blink task (Semaphore Taking Task)
        xTaskCreate(vLEDRGBBlueBlinkTask,           // Task function
                    "LEDRGBBlueBlinkTask",          // Name of the task
                    1024,                    // Stack size
                    NULL,                    // Task parameters
                    1,                       // Task priority
                    NULL);                   // Task handle
    }

    // Create the LED blink task
    xTaskCreate(vLED1BlinkTask,         // Task function
                "LED1BlinkTask",        // Name of the task
                1024,                  // Stack size (in words, not bytes)
                NULL,                  // Task parameter
                2,                     // Task priority (1 is low)
                NULL);                 // Task handle (optional)
    
    xTaskCreate(vLED2BlinkTask,         // Task function
                "LED1BlinkTask",        // Name of the task
                1024,                  // Stack size (in words, not bytes)
                NULL,                  // Task parameter
                3,                     // Task priority (1 is low)
                NULL);                 // Task handle (optional)
    
    xTaskCreate(vLED3BlinkTask,         // Task function
                "LED1BlinkTask",        // Name of the task
                1024,                  // Stack size (in words, not bytes)
                NULL,                  // Task parameter
                4,                     // Task priority (1 is low)
                NULL);                 // Task handle (optional)

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();

    // Should never reach here
    for(;;);

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

