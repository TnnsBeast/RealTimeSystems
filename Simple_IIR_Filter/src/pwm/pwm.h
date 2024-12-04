/* 
 * File:   pwm.h
 *
 * Author: Jennifer W DesCombes
 *         Pomona College
 * 
 * Created on November 14, 2024, 8:33 AM
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

//
// Type Declarations
//

// NOTE: do not access the individual elements of the structure
// as the type, name, and location of these elements may change as
// improvements are made to the code. Use the access methods to
// access information about the pwm status/states.
typedef struct {
    int pwmLevelMinCount;
    int pwmLevelMaxCount;
    int pwmCountMaximum;
    int pwmCount;
} pwmStruct;


//
// Method Definitions
//

void initPWM( pwmStruct *pwmDataPtr,       // location of the data structure
              int levelMaxCount,           // Maximum value of the PWM output
              int levelMinCount );         // Minimum value of the PWM output

ledStates pwmProcessing( int currentLevel, pwmStruct *pwmStructure );



#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

