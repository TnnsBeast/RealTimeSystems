/*******************************************************************************
  System Definitions for CSCI 181RT

  File Name:
    definitionsCSCI181RT.h

  Summary:
    project system definitions for CSCI 181RT.

  Description:
    This file contains the system-wide prototypes and definitions for a project
    used in Pomona College CSCI 181RT.

 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2024 Jennifer DesCombes, all rights reserved.
********************************************************************************/

#include "peripheral/gpio/plib_gpio.h"

#ifndef DEFINITIONSCSCI181RT_H
#define DEFINITIONSCSCI181RT_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

//
// Evaluation Board Information
//

typedef enum {
    ledOn,
    ledOff
} ledStates;


#define LED_1      GPIO_PIN_RJ7   // NOTE: LED is low true logic
#define LED_2      GPIO_PIN_RK7   // NOTE: LED is low true logic
#define LED_3      GPIO_PIN_RJ3   // NOTE: LED is low true logic
#define LED_Red    GPIO_PIN_RB7   // NOTE: LED is low true logic
#define LED_Green  GPIO_PIN_RB8   // NOTE: LED is low true logic
#define LED_Blue   GPIO_PIN_RB9   // NOTE: LED is low true logic
    
#define PushButton_1    GPIO_PIN_RJ4  // NOTE: button pushed reads zero, low true logic
#define PushButton_2    GPIO_PIN_RJ5  // NOTE: button pushed reads zero, low true logic
#define PushButton_3    GPIO_PIN_RJ6  // NOTE: button pushed reads zero, low true logic
#define PushButton_4    GPIO_PIN_RC15  // NOTE: button pushed reads zero, low true logic
    
#define DigitalGPIO_1   GPIO_PIN_RK4

#define P1TaskPin      GPIO_PIN_RB3
#define P2TaskPin      GPIO_PIN_RB5
#define DummyTaskPin   GPIO_PIN_RB14


// *****************************************************************************
// *****************************************************************************
// Section: extern declarations
// *****************************************************************************
// *****************************************************************************




//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* DEFINITIONSCSCI181RT_H */
/*******************************************************************************
 End of File
*/

