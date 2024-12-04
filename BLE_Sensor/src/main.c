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
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

volatile bool dataReceived1 = false;
char rxBuffer1[256];
volatile size_t rxIndex1 = 0;
volatile bool dataReceived2 = false;
char rxBuffer2[256];
volatile size_t rxIndex2 = 0;

void RN4020_1_SendCommand(const char* command)
{
    // Send command to RN4020 over UART
    UART1_Write((void*)command, strlen(command));
    for (volatile int i = 0; i < 2000; i++);;  // Brief delay for the command to process
}

void RN4020_2_SendCommand(const char* command)
{
    // Send command to RN4020 over UART
    UART4_Write((void*)command, strlen(command));
    for (volatile int i = 0; i < 2000; i++);;  // Brief delay for the command to process
}

void UART1_RX_Callback(uintptr_t context)
{
    // Callback when data is received over UART
    dataReceived1 = true;
    rxIndex1 = UART1_ReadCountGet();  // Get the size of received data
}

void UART4_RX_Callback(uintptr_t context)
{
    // Callback when data is received over UART
    dataReceived2 = true;
    rxIndex2 = UART4_ReadCountGet();  // Get the size of received data
}

void RN4020_1_Init(void)
{
    // Set CMD/MLDP pin high to enter command mode
    GPIO_RD15_Set();
    for (volatile int i = 0; i < 1000; i++); // Ensure stable command mode

    // Reset the RN4020 module to ensure it starts fresh
    GPIO_RJ12_Clear();
    GPIO_RJ12_Set();
    
    RN4020_1_SendCommand("SF,1\n");       // Factory reset
    RN4020_1_SendCommand("SS,C0000000\n"); // enable basic services
    RN4020_1_SendCommand("S-,test1\n");
    RN4020_1_SendCommand("R,1\n"); // reboot
}

void RN4020_2_Init(void)
{
    // Set CMD/MLDP pin high to enter command mode
    GPIO_RD15_Set();
    for (volatile int i = 0; i < 1000; i++); // Ensure stable command mode

    // Reset the RN4020 module to ensure it starts fresh
    GPIO_RJ10_Clear();
    GPIO_RJ10_Set();
    
    RN4020_2_SendCommand("SF,1\n");       // Factory reset
    RN4020_2_SendCommand("SS,C0000000\n"); // enable basic services
    RN4020_2_SendCommand("S-,test2\n");
    RN4020_2_SendCommand("R,1\n"); // reboot
}

int battery = 0;
void changeBatteryLevelTask(void *pvParameters)
{
    for (;;)
    {
        if (battery == 0) {
            RN4020_1_SendCommand("SUW,2A19,19\n");
            RN4020_2_SendCommand("SUW,2A19,19\n");
            battery = 1;
        } else if (battery == 1) {
            RN4020_1_SendCommand("SUW,2A19,32\n");
            RN4020_2_SendCommand("SUW,2A19,32\n");
            battery = 2;
        } else {
            RN4020_1_SendCommand("SUW,2A19,4B\n");
            RN4020_2_SendCommand("SUW,2A19,4B\n");
            battery = 0;
        }
        
        RN4020_1_SendCommand("SDS,TestSerial\n");
        
        RN4020_1_SendCommand("PZ\n");        // Clear private services
        RN4020_1_SendCommand("PS,00112233445566778899AABBCCDDEEFF\n");  // Create custom service
        RN4020_1_SendCommand("PC,00112233445566778899AABBCCDDEEFF,12,10\n"); // Create characteristic as readable
        
        RN4020_1_SendCommand("R,1\n");
        RN4020_2_SendCommand("R,1\n");
        
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    UART1_ReadCallbackRegister(UART1_RX_Callback, (uintptr_t)NULL);
    UART4_ReadCallbackRegister(UART4_RX_Callback, (uintptr_t)NULL);
    
    RN4020_1_Init();
    
    // Set the RN4020 to advertise (make discoverable)
    
    RN4020_1_SendCommand("A\n");           // Start advertising
    
    
    RN4020_2_Init();
    
    RN4020_2_SendCommand("A\n");
    

    xTaskCreate(changeBatteryLevelTask,         // Task function
                "changeBatteryLevelTask",        // Name of the task
                1024,                  // Stack size (in words, not bytes)
                NULL,                  // Task parameter
                1,                     // Task priority (1 is low)
                NULL);                 // Task handle (optional)
    
    vTaskStartScheduler();
    
    while ( true )
    {
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

