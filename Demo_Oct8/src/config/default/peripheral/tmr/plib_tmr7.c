/*******************************************************************************
  TMR Peripheral Library Interface Source File

  Company
    Microchip Technology Inc.

  File Name
    plib_tmr7.c

  Summary
    TMR7 peripheral library source file.

  Description
    This file implements the interface to the TMR peripheral library.  This
    library provides access to and control of the associated peripheral
    instance.

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "device.h"
#include "plib_tmr7.h"
#include "interrupts.h"




void TMR7_Initialize(void)
{
    /* Disable Timer */
    T7CONCLR = _T7CON_ON_MASK;

    /*
    SIDL = 0
    TCKPS =7
    T32   = 0
    TCS = 0
    */
    T7CONSET = 0x70;

    /* Clear counter */
    TMR7 = 0x0;

    /*Set period */
    PR7 = 3123U;


}


void TMR7_Start(void)
{
    T7CONSET = _T7CON_ON_MASK;
}


void TMR7_Stop (void)
{
    T7CONCLR = _T7CON_ON_MASK;
}

void TMR7_PeriodSet(uint16_t period)
{
    PR7  = period;
}

uint16_t TMR7_PeriodGet(void)
{
    return (uint16_t)PR7;
}

uint16_t TMR7_CounterGet(void)
{
    return (uint16_t)(TMR7);
}


uint32_t TMR7_FrequencyGet(void)
{
    return (390625);
}



bool TMR7_PeriodHasExpired(void)
{
    bool status;
        status = (IFS1bits.T7IF != 0U);
        IFS1CLR = _IFS1_T7IF_MASK;

    return status;
}
