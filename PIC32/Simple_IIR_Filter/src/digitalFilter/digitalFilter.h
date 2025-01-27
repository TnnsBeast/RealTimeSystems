/* 
 * File:   digitalFilter.h
 * Author: pomonacollege
 *
 * Created on November 12, 2024, 8:33 AM
 */

#ifndef DIGITALFILTER_H
#define	DIGITALFILTER_H

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
typedef struct {
    
    //
    // Add your filter structure internal data here
    //
    float previousResult;
    float gain1;
    float gain2;
    
} digitalFilterStruct;


//
// Method Definitions
//

void initDigitalFilter( digitalFilterStruct *signalFilterStructure);
float digitalFilter( float signalInput, digitalFilterStruct *signalFilterStructure );


#ifdef	__cplusplus
}
#endif

#endif	/* DIGITALFILTER_H */

