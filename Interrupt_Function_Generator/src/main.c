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


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

void toggle (EXTERNAL_INT_PIN extIntPin , uintptr_t context)
{
    // Mirror the signal on the RGB led green channel
    RGB_LED_G_Toggle();
    
    // Invert external interrupt edge polarity (so that on the next interrupt captures the other polarity edge)
    // This allows us to capture both rising and falling edge, despite only being able to configure the pin to capture one polarity
    INTCONINV = _INTCON_INT3EP_MASK;
}


int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
     __builtin_enable_interrupts();
    EVIC_ExternalInterruptEnable(EXTERNAL_INT_3);
    EVIC_ExternalInterruptCallbackRegister( EXTERNAL_INT_3, &toggle, (uintptr_t)NULL );

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        
        // Add this delay to demonstrate that using interrupts to monitor the input pin allows us to capture it despite processing in the main loop
        // If we were polling in this case with this same delay, we would be blind for the ~.5 seconds during the for loop
        for (int i = 0; i < 10000000; i++);
        LED3_Toggle();
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

