/*******************************************************************************
  Dummy Task Source File

  Company:
    Jennifer W DesCombes
    Pomona College

  File Name:
    dummyTask.c

  Summary:
    This file contains the lowest priority task for a project. It is designed
    to be always runnable.

  Description:
    This task toggles an IO pin so that a measurement of the system utilization
    can be performed based on when the signal is not toggling (and thus the 
    system is doing something useful).
  
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include "definitions.h"                // SYS function prototypes
#include "definitionsCSCI181RT.h"       // SYS definitions for CSCI 181RT
#include "dummyTask.h"                   // definitions for debounce

#include "FreeRTOS.h"                   // SYS definitions for FreeRTOS
#include "task.h"                       // SYS definitions for Tasks
#include "semphr.h"                     // SYS definitions for Semaphores


// *****************************************************************************
// *****************************************************************************
// Section: dummyTask Entry Point
// *****************************************************************************
// *****************************************************************************

//
// Type Declarations
//


//
// Global Data Declarations
//


//
// Global Defines
//


//
// Method Definitions
//
 

//
// Methods
//


/*
//  Lowest Priority Task
*/
void dummyTask(void *pvParameters)
{
    
    //
    // Task global data and hardware initialization
    //

    while( true )
    {
        
        // Test Code to mostly disable this task
        //vTaskDelay(pdMS_TO_TICKS(10000));

        // Toggle Dummy Task Pin On & Off Continuously when executing
        GPIO_PinSet( DummyTaskPin );
        GPIO_PinClear( DummyTaskPin );
    }
}





/*******************************************************************************
 End of File
*/
