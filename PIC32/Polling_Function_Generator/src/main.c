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

int main ( void )
{
    /* Initialize all modules */
    
    // ******* Note: I configured the pins using MCC, so everything gets setup in GPIO_Initialize (which is called by SYS_Initialize) *******
    
    // Uses pin RB5 as function generator input, which is connected to pin 17 on the Xplained Pro Extension Standard Header 
    // Page 16 https://ww1.microchip.com/downloads/aemDocuments/documents/MCU32/ProductDocuments/UserGuides/PIC32MZ-EF-2.0-Development-Board-Users-Guide-DS70005400.pdf
    
    // Outputs to green channel on RGB LED (middle pin on the LED for probing)
    // Also outputs to pin RB15 (can use this over the LED for easier probing - also removes RC behavior of LED on the pin)
    
    SYS_Initialize ( NULL );

    while ( true )
    {
        if (GPIO_PinRead(GPIO_PIN_RB5)) {
            RGB_LED_G_Off();
            GPIO_RB15_Set();
        } else {
            RGB_LED_G_On();
            GPIO_RB15_Clear();
        }
        
        // About 6 ms
        //for (int i = 0; i < 400000; i++);
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

