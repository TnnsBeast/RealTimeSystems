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

// BOARD USAGE 
// SW1: Decrease brightness
// SW2: Increase brightness
// SW3: System on
// SW4: System off
// LED1: Heartbeat (1s)
// LED2: System on/off
// LED4: Green channel brightness used for 'volume' control


// val should be between 50 and 100
void setRGBLED_Green(uint32_t val) {
    if (val < 50) {
        val = 50;
    }
    if (val > 100) {
        val = 100;
    }
    
    float TimerVal = TMR2_PeriodGet();
    float Psteps = TimerVal/100;
    OCMP8_CompareSecondaryValueSet(val * Psteps);
}

void TIMER4_EventHandler(uint32_t status, uintptr_t context)
{
    /* Toggle LED1 - RJ7 - using a timer once a second */
    GPIO_PinToggle(GPIO_PIN_RJ7);
    TMR4_Start();
}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    OCMP8_Enable();
    
    TMR2_Start();   
    
    TMR4_CallbackRegister(TIMER4_EventHandler, (uintptr_t)NULL);
    TMR4_Start();
    
    GPIO_PinOutputEnable(GPIO_PIN_RJ7);
    GPIO_PinOutputEnable(GPIO_PIN_RK7);
    GPIO_PinInputEnable(GPIO_PIN_RJ4);
    GPIO_PinInputEnable(GPIO_PIN_RJ5);
    GPIO_PinInputEnable(GPIO_PIN_RJ6);
    GPIO_PinInputEnable(GPIO_PIN_RC15);
    
    // higher brightness is dimmer led, 100 is off, 30 is fully on
    uint32_t brightness = 100;
    uint32_t system_on = 1; 

    while ( true )
    {
        if (!GPIO_PinRead(GPIO_PIN_RC15)) {
            system_on = 0; 
        }
        if (!GPIO_PinRead(GPIO_PIN_RJ6)) {
            system_on = 1; 
        }
        
        // excluding the && system on would change brightness (but not display the brightness) even when the system is off
        if (!GPIO_PinRead(GPIO_PIN_RJ4) && system_on) {
            if (brightness < 100) {
                brightness++;
            }
            for (volatile int i = 0; i < 1000000; i++);
        }
        if (!GPIO_PinRead(GPIO_PIN_RJ5) && system_on) {
            if (brightness > 50) {
                brightness--;
            }
            for (volatile int i = 0; i < 1000000; i++);
        }
        
        if (system_on == 0) {
            // Turn RGB Green LED off
            setRGBLED_Green(100);
            GPIO_PinSet(GPIO_PIN_RK7);
        }
        else {
            setRGBLED_Green(brightness);
            GPIO_PinClear(GPIO_PIN_RK7);
        }
        
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

