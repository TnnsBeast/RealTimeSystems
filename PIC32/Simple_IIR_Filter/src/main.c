/*******************************************************************************
  Main Source File

  Copyright 2024 Pomona College, All Rights Reserved
      Special Thanks to Neil
 

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

#include <stddef.h>                       // Defines NULL
#include <stdbool.h>                      // Defines true
#include <stdlib.h>                       // Defines EXIT_FAILURE
#include "definitions.h"                  // SYS function prototypes
#include "definitionsCSCI181RT.h"         // SYS definitions for CSCI 181RT
#include "debounce/debounce.h"            // definitions for debounce
#include "pwm/pwm.h"                      // definitions for pwm
#include "digitalFilter/digitalFilter.h" // definitions for digital filter
#include "dummyTask/dummyTask.h"          // definitions for the dummyTask

#include "FreeRTOS.h"                     // SYS definitions for FreeRTOS
#include "task.h"                         // SYS definitions for Tasks
#include "semphr.h"                       // SYS definitions for Semaphores


//
// Type Declarations
//
    

//
// Global Data Declarations
//

// Global data used by fiveMSProcessing()
int gIntInputSignalState;
int gIntLevelControl;
float gDigitalGPIOSignal;
float gFilterDigitalGPIOSignal;
float gRectifiedDigitalGPIOSignal;


// Global data used by PWM code
pwmStruct gPWMLED2;
pwmStruct gPWMLED3;
pwmStruct gPWMLEDRGB;

// Global data used by the digital filter code
digitalFilterStruct gDigitalFilterGPIO;
        
// Global data used by button de-bounce code
debounceStruct gDebounceButton1;
debounceStruct gDebounceButton2;
debounceStruct gDebounceButton3;
debounceStruct gDebounceButton4;


//
// Global Defines
//

// The following define determines if the external input
// is monitored via software or via the input compare hardware
// and its corresponding interrupt.
//
//#define USE_INPUT_COMPARE
//

#define levelMaxCount 10
#define levelMinCount 0
#define levelInitialCount 4


//
// Method Definitions
//

void vP1Task(void *pvParameters);     // Highest Priority Task (P1)
void vP2Task(void *pvParameters);     // Task Priority 2 (P2)
  void monitorGPIO1PinState( void );
void vP3Task(void *pvParameters);     // Task Priority 3 (P3)
  void levelLED3Adjust( void );
void vP4Task(void *pvParameters);     // Task Priority 4 (P3)


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************


/*
//  Highest Priority Task (P1)
*/
void vP1Task(void *pvParameters)
{
    
    //
    // Task global data and hardware initialization
    //
    
    
    while( true )
    {
    
        // Delay one millisecond until next activation of task
        vTaskDelay(pdMS_TO_TICKS(1));

        // Toggle Task Pin to demonstrate activity
        GPIO_PinToggle(P1TaskPin);
        
        // PWM of LED2 based on gIntLevelControl
        if (pwmProcessing( (int)((gRectifiedDigitalGPIOSignal * levelMaxCount) + 0.049), &gPWMLED2 ) == ledOn)
        {
            GPIO_PinClear( LED_2 );    // Turn on Led 2  NOTE: LED is low true logic
        }
        else
        {
            GPIO_PinSet( LED_2 );    // Turn off Led 2  NOTE: LED is low true logic
        }

        // PWM of LED3 based on gIntLevelControl
        if (pwmProcessing( gIntLevelControl, &gPWMLED3 ) == ledOn)
        {
            GPIO_PinClear( LED_3 );    // Turn on Led 3  NOTE: LED is low true logic
        }
        else
        {
            GPIO_PinSet( LED_3 );    // Turn off Led 3  NOTE: LED is low true logic
        }

        // The following test code turns off the multicolor LED at the same 
        // intensity as LED3 (although light output may vary). A color shift has
        // been added (see green) to make things interesting.)
        if (pwmProcessing( gIntLevelControl, &gPWMLEDRGB ) == ledOn)
        {
            GPIO_PinClear( LED_Red );    // Led Red  NOTE: LED is low true logic
            GPIO_PinSet( LED_Green );  // Led Green  NOTE: LED is low true logic
            GPIO_PinClear( LED_Blue );   // Led Blue  NOTE: LED is low true logic
        }
        else
        {
            GPIO_PinSet( LED_Red );    // Led Red  NOTE: LED is low true logic
            GPIO_PinClear( LED_Green );  // Led Green  NOTE: LED is low true logic
            GPIO_PinSet( LED_Blue );   // Led Blue  NOTE: LED is low true logic
        }

        // Other Processing

    }
}

#ifndef USE_INPUT_COMPARE

/*
//  Task Priority 2 (P2)
//
//    Monitor the external input via task polling
*/
void vP2Task(void *pvParameters)
{
    
    //
    // Task global data and hardware initialization
    //

    // Delay a small amount of time to offset simultaneously task startup
    vTaskDelay(pdMS_TO_TICKS(3));

    while( true )
    {

        // Delay five milliseconds until next activation of task
        vTaskDelay(pdMS_TO_TICKS(5));

        // Monitor and display the state of GPIO1
        monitorGPIO1PinState();
        
        // Filter the GPIO input signal
       gFilterDigitalGPIOSignal = digitalFilter( gDigitalGPIOSignal, &gDigitalFilterGPIO );
        
        // Rectify the filtered signal so it can be displayed on the LED
        if (gFilterDigitalGPIOSignal > 0.0)
        {
            gRectifiedDigitalGPIOSignal = gFilterDigitalGPIOSignal;
        }
        else
        {
            gRectifiedDigitalGPIOSignal = -gFilterDigitalGPIOSignal;
        }
                   
    }
}


/*
//  Monitor and display the pin state of GPIO1 on J105-5
*/
void monitorGPIO1PinState( void )
{
    
    // Monitor the state of GPIO1 on J105
    if (GPIO_PinRead( DigitalGPIO_1 ) == 0) 
    {
        if (gIntInputSignalState != 0)
        {
            gIntInputSignalState = 0;
            
            // GPIO_PinSet( LED_2 );    // Led 2  NOTE: LED is low true logic
        }
        gDigitalGPIOSignal = -1.0;
    }
    else
    {
        if (gIntInputSignalState != 1)
        {
            gIntInputSignalState = 1;
            
            // GPIO_PinClear( LED_2 );    // Led 2  NOTE: LED is low true logic
        }
        gDigitalGPIOSignal = +1.0;
    }
}

#else

/*
//  Task Priority 2 (P2)
//
//    Monitor the external input via input compare hardware
*/
void vP2Task(void *pvParameters)
{
    
    //
    //  Task global data and hardware initialization
    //

    // Add your software here to control via input compare and 
    // interrupt.
    
    while( true )
    {

        // Delay five milliseconds until next activation of task
        vTaskDelay(pdMS_TO_TICKS(5));
       
    }
}

#endif

/*
//  Task Priority 3 (P3)
//
//    Toggle the heartbeat LED - 1 second rate
*/
void vP3Task(void *pvParameters)
{
    
    //
    //  Task global data and hardware initialization
    //

    // Delay a small amount of time to offset simultaneously task startup
    vTaskDelay(pdMS_TO_TICKS(5));

    while( true )
    {

        // Delay ten millisecond until next activation of task
        vTaskDelay(pdMS_TO_TICKS(10));

        // Toggle Task Pin to demonstrate activity
        GPIO_PinToggle(P2TaskPin);
        
        
        // De-bounce pushbutton inputs
        debounceInput( GPIO_PinRead( PushButton_1 ), &gDebounceButton1 );
        debounceInput( GPIO_PinRead( PushButton_2 ), &gDebounceButton2 );
        debounceInput( GPIO_PinRead( PushButton_3 ), &gDebounceButton3 );
        debounceInput( GPIO_PinRead( PushButton_4 ), &gDebounceButton4 );

        // Adjust the level of LED3
        levelLED3Adjust();

        // Demonstrate operation of button 1
        if (getDebounceValue( &gDebounceButton1 ) == 0)  // NOTE: button pushed reads zero, low true logic
        {
            GPIO_PinClear( LED_1 );    // Led 1  NOTE: LED is low true logic
        }

    }
}


/*
//  Adjust the relative input level on LED 3
*/
void levelLED3Adjust( void )
{
    
    // Validate level data
    if (gIntLevelControl < levelMinCount)
    {
        gIntLevelControl = levelMinCount;
    }
    else
    {
        if (gIntLevelControl > levelMaxCount)
        {
            gIntLevelControl = levelMaxCount;
        }
    }
    
    // Decrease level by pressing button 3
    if (getDebounceStatusChange( &gDebounceButton3 ) == true)
    {
        if (getDebounceValue( &gDebounceButton3 ) == 0)  // NOTE: button pushed reads zero, low true logic
        {
            gIntLevelControl -= 1;
            if (gIntLevelControl < levelMinCount)
            {
                gIntLevelControl = levelMinCount;
            }
        }
    }
    
    // Increase level by pressing button 4
    if (getDebounceStatusChange( &gDebounceButton4 ) == true)
    {
        if (getDebounceValue( &gDebounceButton4 ) == 0)  // NOTE: button pushed reads zero, low true logic
        {
            gIntLevelControl += 1;
            if (gIntLevelControl > levelMaxCount)
            {
                gIntLevelControl = levelMaxCount;
            }
        }
    }
    
}


/*
//  Task Priority 4 (P4)
//
//    Toggle the heartbeat LED - 1 second rate
*/
void vP4Task(void *pvParameters)
{
    
    //
    // Task global data and hardware initialization
    //

    // Delay a small amount of time to offset simultaneously task startup
    vTaskDelay(pdMS_TO_TICKS(7));

    while( true )
    {

        // Delay one second until next activation of task
        vTaskDelay(pdMS_TO_TICKS(1000));

        // Toggle heart beat LED (LED1)
        GPIO_PinToggle( LED_1 );    // Led 1  NOTE: LED is low true logic
    
    }
}


int main ( void )
{

    // Initialize global data
    gIntInputSignalState = 1;
    gIntLevelControl = levelInitialCount;
    gDigitalGPIOSignal = 0.0;
    gFilterDigitalGPIOSignal = 0.0;
    gRectifiedDigitalGPIOSignal = 0.0;
    
    initPWM( &gPWMLED2,               // location of the data structure
             levelMaxCount,           // Maximum value of the PWM output
             levelMinCount );         // Minimum value of the PWM output
     initPWM( &gPWMLED3,               // location of the data structure
             levelMaxCount,           // Maximum value of the PWM output
             levelMinCount );         // Minimum value of the PWM output
    initPWM( &gPWMLEDRGB,            // location of the data structure
             levelMaxCount,           // Maximum value of the PWM output
             levelMinCount );         // Minimum value of the PWM output
    
    initDigitalFilter( &gDigitalFilterGPIO );

    initDebounceInput( &gDebounceButton1,     // Pointer to de-bounce data structure
                       3 );                   // Number of sequential states for de-bounce
    initDebounceInput( &gDebounceButton2,     // Pointer to de-bounce data structure
                       3 );                   // Number of sequential states for de-bounce
    initDebounceInput( &gDebounceButton3,     // Pointer to de-bounce data structure
                       3 );                   // Number of sequential states for de-bounce
    initDebounceInput( &gDebounceButton4,     // Pointer to de-bounce data structure
                       3 );                   // Number of sequential states for de-bounce

    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    xTaskCreate(vP1Task,         // Task function
                "P1Task",        // Name of the task
                1024,            // Stack size (in words, not bytes)
                NULL,            // Task parameter
                5,               // Task priority (1 is lowest priority)
                NULL);           // Task handle (optional)
    
    xTaskCreate(vP2Task,         // Task function
                "P2Task",        // Name of the task
                1024,            // Stack size (in words, not bytes)
                NULL,            // Task parameter
                4,               // Task priority (1 is lowest priority)
                NULL);           // Task handle (optional)
    
    xTaskCreate(vP3Task,         // Task function
                "P3Task",        // Name of the task
                1024,            // Stack size (in words, not bytes)
                NULL,            // Task parameter
                3,               // Task priority (1 is lowest priority)
                NULL);           // Task handle (optional)
    
    xTaskCreate(vP4Task,         // Task function
                "P4Task",        // Name of the task
                1024,            // Stack size (in words, not bytes)
                NULL,            // Task parameter
                2,               // Task priority (1 is lowest priority)
                NULL);           // Task handle (optional)
    
    xTaskCreate(dummyTask,         // Task function
                "DummyTask",       // Name of the task
                1024,              // Stack size (in words, not bytes)
                NULL,              // Task parameter
                1,                 // Task priority (1 is lowest priority)
                NULL);             // Task handle (optional)
    
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

