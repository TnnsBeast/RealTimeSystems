/* 
 * File:   debounce.h
 * Author: pomonacollege
 *
 * Created on November 12, 2024, 8:33 AM
 */

#ifndef DEBOUNCE_H
#define	DEBOUNCE_H

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
    int buttonEndCount;
    int buttonValue;
    int buttonSameCount;
    bool buttonStatusChange;
    int buttonTime;
} debounceStruct;


//
// Method Definitions
//

void initDebounceInput( debounceStruct *inputStructure, int debounceMaxCount );
int getDebounceValue ( debounceStruct *inputStructure );
bool getDebounceStatusChange ( debounceStruct *inputStructure );
void debounceInput( int currentInput, debounceStruct *inputStructure );



#ifdef	__cplusplus
}
#endif

#endif	/* DEBOUNCE_H */

