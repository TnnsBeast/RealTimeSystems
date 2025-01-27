/* 
 * File:   dummyTask.h
 *
 * Author: Jennifer W DesCombes
 *         Pomona College
 * 
 * Created on November 14, 2024, 8:33 AM
 */

#ifndef DUMMYTASK_H
#define	DUMMYTASK_H

#ifdef	__cplusplus
extern "C" {
#endif

//
// Type Declarations
//

// NOTE: do not access the individual elements of the structure
// as the type, name, and location of these elements may change as
// improvements are made to the code. Use the access methods to
// access information about the de-bounced pushbutton.


//
// Method Definitions
//

void dummyTask(void *pvParameters);   // Lowest Priority Task



#ifdef	__cplusplus
}
#endif

#endif	/* DUMMYTASK_H */

