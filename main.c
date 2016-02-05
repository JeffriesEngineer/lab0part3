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

typedef enum stateTypeENUM {
    led1on, led2on, led3on, LT1, GT1, debounce
} stateType;

volatile stateType state = led1on;
volatile stateType next; //stores the next possible state based on the current state
volatile stateType prev; //stores the previous possible state based on the current state
volatile stateType buffer; //stores the most likely next state based on a button press

//unsigned int timeflag = 0;

int main() {
    SYSTEMConfigPerformance(10000000); //Configures low-level system parameters for 10 MHz clock
    enableInterrupts(); //This function is necessary to use interrupts.
    //initialization functions
    initLEDs();
    initTimer1();
    initTimer2();
    initSW1();
    T1CONbits.ON = 0;
    while (1) {
        switch (state) {
            case led1on:
                LATDbits.LATD0 = 1;
                LATDbits.LATD1 = 0;
                LATDbits.LATD2 = 0;
                next = led2on;
                prev = led3on;
                break;
                
            case led2on:
                LATDbits.LATD0 = 0;
                LATDbits.LATD1 = 1;
                LATDbits.LATD2 = 0;
                next = led3on;
                prev = led1on;
                break;
                
            case led3on:
                LATDbits.LATD0 = 0;
                LATDbits.LATD1 = 0;
                LATDbits.LATD2 = 1;
                next = led1on;
                prev = led2on;
                break;
                
            case debounce:
                delayMs(15);
                state = LT1;
                buffer = next;
                TMR1 = 0;
                T1CONbits.ON = 1;
                break;
                
            case LT1:
                CNCONDbits.ON = 1;
                break;
                
            case GT1:
                break;
                
            default:
                LATDbits.LATD0 = 0;
                LATDbits.LATD1 = 0;
                LATDbits.LATD2 = 1;
                next = led1on;
                prev = led1on;
                break;
        }
    }
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void) {
    IFS1bits.CNDIF = 0;
    if(PORTDbits.RD6 == 0) {
        state = debounce;
        CNCONDbits.ON = 0;
    }
    else if(PORTDbits.RD6 == 1) {
        state = buffer;
    }
}

void __ISR(_TIMER_1_VECTOR, IPL6SRS) _T1Interrupt() {
    IFS0bits.T1IF = 0;
    state = GT1;
    buffer = prev;
    T1CONbits.ON = 0;
}