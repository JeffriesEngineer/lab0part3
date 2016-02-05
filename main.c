/* 
 * File:   main.c
 * Author: J Jeffries
 * Description: lab 0.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1

//TODO: check code and run

typedef enum stateTypeENUM{
    led1on, led2on, led3on, hold1, hold2, hold3, debounce1, debounce2, debounce3
} stateType;

volatile stateType state=led1on;
volatile stateType next;

//unsigned int timeflag = 0;

int main() {
    SYSTEMConfigPerformance(10000000);    //Configures low-level system parameters for 10 MHz clock
    enableInterrupts();                   //This function is necessary to use interrupts.

    //initialization functions
    initLEDs();
    initTimer1();
    initSW1();
    
    while(1){

        switch(state)
        {
       case led1on:
            LATDbits.LATD0=1;
            LATDbits.LATD1=0;
            LATDbits.LATD2=0;
            break;

            case debounce1:
                TMR1=0;
                IFS0bits.T1IF=0;
                state=hold1;
                break;
                
            case hold1:
                delayMs(1);
                break;
            
        case led2on:
            LATDbits.LATD0=0;
            LATDbits.LATD1=1;
            LATDbits.LATD2=0;
            break;
             
            case debounce2:
                TMR1=0;
                IFS0bits.T1IF=0;
                state=hold2;
                break;
                
            case hold2:
                delayMs(1);
                break;
                
        case led3on:
            LATDbits.LATD0=0;
            LATDbits.LATD1=0;
            LATDbits.LATD2=1;
            break;
            
             case debounce3:
                TMR1=0;
                IFS0bits.T1IF=0;
                state=hold3;
                break;
                
            case hold3:
                delayMs(1);
                break;
            
            defaut:
            LATDbits.LATD0=0;
            LATDbits.LATD1=0;
            LATDbits.LATD2=1;
            
            break;
        
        }
    }
    
    return 0;
}


void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt( void ){
    
    IFS1bits.CNDIF=0;
    PORTD;
    
    if(state==led1on && PORTDbits.RD6==1)
        state=debounce1;
    
     if(state==led2on && PORTDbits.RD6==1)
        state=debounce2;
    
     if(state==led3on && PORTDbits.RD6==1)
        state=debounce3;
    
    
    if(state == hold1 && IFS0bits.T1IF==1 && PORTDbits.RD6==0) { // use dummy variable (flag) that is triggered when the timer reaches 1 sec.
        IFS0bits.T1IF=0;
        state = led3on;
    }
    
    else if(state == hold1 && PORTDbits.RD6==0)
        state = led2on;
    
    
    
       if(state == hold2 && IFS0bits.T1IF==1 && PORTDbits.RD6==0) { // use dummy variable (flag) that is triggered when the timer reaches 1 sec.
        IFS0bits.T1IF=0;
        state = led1on;
    }
    
    
    else if(state == hold2 && PORTDbits.RD6==0)
        state = led3on;
      
       
    
        if(state == hold3 && IFS0bits.T1IF==1 && PORTDbits.RD6==0) { // use dummy variable (flag) that is triggered when the timer reaches 1 sec.
        IFS0bits.T1IF=0;
        state = led2on;
    }
    
    else if(state == hold3 && PORTDbits.RD6==0)
        state = led1on;
    
}