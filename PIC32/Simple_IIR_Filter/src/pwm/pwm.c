/*******************************************************************************
  PWM (Pulse Width Modulation) Source File

  Company:
    Jennifer W DesCombes
    Pomona College

  File Name:
    debounce.c

  Summary:
    This file contains the pushbutton PWM function for a project.

  Description:
    This file contains the logic to perform a PWM control (variable brightness
  of an output, such as an LED.
  
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
#include "pwm.h"                        // definitions for pwm


// *****************************************************************************
// *****************************************************************************
// Section: Debounce Entry Point
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
//  Initialize all of the data for this instantiation of the PWM Processor
//
*/
void initPWM( pwmStruct *pwmDataPtr,       // location of the data structure
              int levelMaxCount,           // Maximum value of the PWM output
              int levelMinCount )          // Minimum value of the PWM output
{
    
    pwmDataPtr->pwmLevelMaxCount = levelMaxCount;
    pwmDataPtr->pwmLevelMinCount = levelMinCount;
    pwmDataPtr->pwmCount = 0;
    pwmDataPtr->pwmCountMaximum = levelMaxCount;
 
}


/*
//  Determine if the LED under PWM control should be on or off
//
*/
ledStates pwmProcessing( int currentLevel, pwmStruct *pwmStructure )
{
    
    ledStates returnState;
    
    returnState = ledOff;
    
    // Validate passed in data
    if (currentLevel < pwmStructure->pwmLevelMinCount)
    {
        currentLevel = pwmStructure->pwmLevelMinCount;
    }
    else
    {
        if (currentLevel > pwmStructure->pwmLevelMaxCount)
        {
            currentLevel = pwmStructure->pwmLevelMaxCount;
        }
    }

    // Control PWM
    if ( pwmStructure->pwmCount < currentLevel)
    {
        returnState = ledOn;
    }
    else
    {
        returnState = ledOff;
    }
    pwmStructure->pwmCount += 1;
    if (pwmStructure->pwmCount >= pwmStructure->pwmCountMaximum)
    {
        pwmStructure->pwmCount = 0;  
    }

    return( returnState );
}



/*******************************************************************************
 End of File
*/
