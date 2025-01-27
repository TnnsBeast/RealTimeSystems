/*******************************************************************************
  Debounce Source File

  Company:
    Jennifer W DesCombes
    Pomona College

  File Name:
    debounce.c

  Summary:
    This file contains the pushbutton "de-bounce" function for a project.

  Description:
    This file contains the pushbutton "de-bounce" function for a project.  The
    de-bounce processes pushbutton states and determined when the pushbutton
    input has become stable - removing any mechanical bounce of the pushbutton.
 * 
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include "definitions.h"                // SYS function prototypes
#include "debounce.h"                   // definitions for debounce


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
//  Initialize data within the de-bounce structure
*/
void initDebounceInput( debounceStruct *inputStructure, int debounceMaxCount )
{

    inputStructure->buttonEndCount = debounceMaxCount;
    inputStructure->buttonValue = 0;
    inputStructure->buttonSameCount = 0;
    inputStructure->buttonStatusChange = false;
    inputStructure->buttonTime = 0;

}
    

/*
//  Return the current de-bounced button state
*/
int getDebounceValue( debounceStruct *inputStructure )
{
    
    return( inputStructure->buttonValue );
    
}


/*
//  Return the current de-bounced button change state
*/
bool getDebounceStatusChange( debounceStruct *inputStructure )
{
    
    return( inputStructure->buttonStatusChange );
    
}


/*
//  Track the input pushbutton status and returned de-bounced status
*/
void debounceInput( int currentInput, debounceStruct *inputStructure )
{
    
    //
    // Code in this routine is not complete
    //
    
    if (inputStructure->buttonValue != currentInput)
    {
        inputStructure->buttonSameCount += 1;
        if (inputStructure->buttonSameCount > inputStructure->buttonEndCount)
        {
            inputStructure->buttonValue = currentInput;
            inputStructure->buttonSameCount = 0;
            inputStructure->buttonStatusChange = true;
         }
    }
    else
    {
        inputStructure->buttonSameCount = 0;
        inputStructure->buttonStatusChange = false;
    }
   
}


/*******************************************************************************
 End of File
*/
