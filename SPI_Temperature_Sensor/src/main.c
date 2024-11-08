/*******************************************************************************
  Main Source File
 * 
 * Author: Neil Chulani
 * Contact: njcf2022@mymail.pomona.edu
 * Date: November 8, 2024
 * 

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a FreeRTOS project that gets the temperature from a DS1722 Temperature Sensor using SPI
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
#include "FreeRTOS.h"
#include "task.h"

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
#define DS1722_CONFIG_REG_ADDR      0x80    // Write address for config register
#define DS1722_TEMP_LSB_REG_ADDR   0x01    // Read address for temperature LSB
#define DS1722_TEMP_MSB_REG_ADDR   0x02    // Read address for temperature MSB

// Configure DS1722 for 12-bit resolution and continuous conversion
static void DS1722_Configure(void)
{
    uint8_t writeBuffer[2];
    
    // First byte: Configuration register write address (0x80)
    // Second byte: Configuration value
    // Set R2=1, R1=X, R0=X for 12-bit resolution
    // Set SD=0 for continuous conversion
    writeBuffer[0] = DS1722_CONFIG_REG_ADDR;
    writeBuffer[1] = 0x80;  // 1000 0000b - 12-bit resolution, continuous conversion
    
    SPI1_Write(writeBuffer, sizeof(writeBuffer));
}

// Read temperature from DS1722 and convert to float
static float DS1722_ReadTemperature(void)
{
    uint8_t readBuffer[2];
    uint16_t tempRaw;
    float temperature;
    
    // Read LSB (register 0x01)
    uint8_t lsbAddr = DS1722_TEMP_LSB_REG_ADDR;
    SPI1_Write(&lsbAddr, 1);
    SPI1_Read(&readBuffer[0], 1);
    
    // Read MSB (register 0x02)
    uint8_t msbAddr = DS1722_TEMP_MSB_REG_ADDR;
    SPI1_Write(&msbAddr, 1);
    SPI1_Read(&readBuffer[1], 1);
    
    // Combine MSB and LSB into 16-bit value
    tempRaw = (readBuffer[1] << 8) | readBuffer[0];
    
    // Convert to temperature
    // For 12-bit resolution:
    // - Bit 15 is sign
    // - Bits 14-4 are integer part
    // - Bits 3-0 are fraction part
    
    // Check if temperature is negative
    if (tempRaw & 0x8000) {
        // Negative temperature: Perform 2's complement conversion
        tempRaw = ~tempRaw + 1;
        temperature = -(float)tempRaw / 16.0f;
    } else {
        // Positive temperature
        temperature = (float)tempRaw / 16.0f;
    }
    
    return temperature;
}

void vGetTemperature(void *pvParameters)
{
    float temperature;
    
    // Configure DS1722 on startup
    DS1722_Configure();
    
    for (;;)
    {
        LED2_Toggle();
        
        // Read temperature
        temperature = DS1722_ReadTemperature();
        
        // Here you can add code to store or process the temperature value
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );

    xTaskCreate(vGetTemperature,         // Task function
            "GetTemperatureTask",        // Name of the task
            1024,                  // Stack size (in words, not bytes)
            NULL,                  // Task parameter
            2,                     // Task priority (1 is low)
            NULL);                 // Task handle (optional)
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

