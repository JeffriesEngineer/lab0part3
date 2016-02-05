/* 
 * File:   led.c
 * Author: J Jeffries
 *
 * 
 */

#include <xc.h>
#include "led.h"

#define OUTPUT 0
#define INPUT 1

void initLEDs(){
    
    TRISDbits.TRISD0 = OUTPUT;
    TRISDbits.TRISD1 = OUTPUT;
    TRISDbits.TRISD2 = OUTPUT;
}

void turnOnLED(int led){
    
    
}