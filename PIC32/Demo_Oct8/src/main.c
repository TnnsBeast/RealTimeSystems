/*******************************************************************************
  Main Source File

  Author:
    Neil Chulani

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a FreeRTOS demo project.

  Description:
    This file contains the "main" function for a FreeRTOS demo project.  The
    "main" function creates 3 tasks to blink the different on-board LEDs at 
    different intervals with different priorities, and then starts the FreeRTOS
    scheduler.
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



#define P1Task_pin      GPIO_PIN_RB3
#define P2Task_pin      GPIO_PIN_RB5
#define P3Task_pin      GPIO_PIN_RB14

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

void clearAll(void)
{
    GPIO_PinClear(P1Task_pin);
    GPIO_PinClear(P2Task_pin);
    GPIO_PinClear(P3Task_pin);
}

void vP1Task(void *pvParameters)
{
    for (;;)
    {
        clearAll();
        GPIO_PinSet(P1Task_pin);
        // About 6 ms
        for (int i = 0; i < 400000; i++);
        GPIO_PinClear(P1Task_pin);
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void vP2Task(void *pvParameters)
{
    for (;;)
    {
        clearAll();
        GPIO_PinSet(P2Task_pin);
        // About 60 ms
        for (int i = 0; i < 4000000; i++);
        GPIO_PinClear(P2Task_pin);
        vTaskDelay(pdMS_TO_TICKS(250));
    }
}

void vP3Task(void *pvParameters)
{
     for (;;)
    {
        clearAll();
        GPIO_PinSet(P3Task_pin);
        // About 600 ms
        for (int i = 0; i < 40000000; i++);
        GPIO_PinClear(P3Task_pin);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    xTaskCreate(vP1Task,         // Task function
                "P1Task",        // Name of the task
                1024,                  // Stack size (in words, not bytes)
                NULL,                  // Task parameter
                1,                     // Task priority (1 is low)
                NULL);                 // Task handle (optional)
    
    xTaskCreate(vP2Task,
                "P2Task",
                1024,
                NULL,
                2,
                NULL);
    
    xTaskCreate(vP3Task,
                "P3Task",
                1024,
                NULL,
                3,
                NULL);
    
    vTaskStartScheduler();

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

