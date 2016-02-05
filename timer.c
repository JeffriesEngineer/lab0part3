/* 
 * File:   timer.c
 * Author: J Jeffries
 *
 * 
 */

#include <xc.h>

void initTimer1(){
    TMR1 = 0;
    PR1 = 20000;
    T1CONbits.TCKPS = 3;
    T1CONbits.TCS = 0;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0; //timer flag
    IPC1bits.T1IP = 6;
    T1CONbits.ON = 1;
}

initTimer2(){
    TMR2 = 0;
    T2CONbits.TCKPS = 3;
    T2CONbits.TCS = 0;
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1;
}

delayMs(unsigned int delay){
    IFS0bits.T2IF = 0;
    TMR2 = 0;
    PR2 = delay*624;
    T2CONbits.ON = 1;
    while(IFS0bits.T2IF == 0);
    T2CONbits.ON = 0;
}
/*
void resetTimer1(){
    TMR1 = 0;
    T1CONbits.ON = 0;
}
*/