/* 
 * File:   timer.h
 * Author: J Jeffries
 *
 * 
 */

#ifndef TIMER_H
#define	TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

void initTimer1();
void initTimer2();
void delayMs(int delay);
void resetTimer1();

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */
