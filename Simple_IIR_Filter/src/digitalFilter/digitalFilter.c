/*******************************************************************************
  Digital Filter Source File

  Company:
    Jennifer W DesCombes
    Pomona College

  File Name:
    digitalFilter.c

  Summary:
    This file contains a simple single delay IIR Filter for a project.

  Description:
    This file contains a simple single delay IIR Filter function for a project.
    The filter uses a single delay unit and two gains to provide a low pass 
    function.
 
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include "definitions.h"                // SYS function prototypes
#include "digitalFilter.h"              // definitions for digital filter


// *****************************************************************************
// *****************************************************************************
// Section: Digital Filter Entry Point
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
//  Initialize data within the digital filter structure
*/
void initDigitalFilter( digitalFilterStruct *signalFilterStructure)
{

    //
    // Add your filter structure initialization code here
    //

    signalFilterStructure->previousResult = 0;
    signalFilterStructure->gain1 = 0.01;
    signalFilterStructure->gain2 = 1 - signalFilterStructure->gain1;
    
}


/*
//  Perform the digital filter function
*/
float digitalFilter( float signalInput, 
                        digitalFilterStruct *signalFilterStructure )
{
    
    
    //
    // Add your filter code here
    //
    float signalOutput = (signalFilterStructure->gain1) * signalInput + (signalFilterStructure->gain2) * (signalFilterStructure->previousResult);
    signalFilterStructure->previousResult = signalOutput;
    return signalOutput;
   
}


/*******************************************************************************
 End of File
*/
