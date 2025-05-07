/* 
 * File:   US.h
 * Author: meimouni
 *
 * Created on 4 septembre 2013, 10:54
 */

#ifndef US_H
#define	US_H


#ifdef	__cplusplus
extern "C" {
#endif

#define US_ECHO_STATE       PORTBbits.RB5
#define US_ECHO             LATBbits.LATB5
#define US_TRIGG            LATBbits.LATB4
#define US_TRIGC            LATAbits.LATA2
#define US_TRIGD            LATBbits.LATB0

#define US_SEL0             LATDbits.LATD2
#define US_SEL1             LATDbits.LATD3

#define SELECT_US_G         {US_SEL0 = 0;US_SEL1 = 0;}
#define SELECT_US_C         {US_SEL0 = 1;US_SEL1 = 0;}
#define SELECT_US_D         {US_SEL0 = 0;US_SEL1 = 1;}

#define US_G_ID             'G'
#define US_C_ID             'C'
#define US_D_ID             'D'

#define DIST_NOK            0
#define DIST_OK             1

#define FREQ_COMPTAGE       (float)(_XTAL_FREQ/32.0) //1250000.0  //(FOSC/4)/8

#define US_LIMIT            (unsigned int)0xFF00 // --> Val timer 1: 0xFF00 = 65280 (base 10)
                                  // 65280 --> ~ 52ms

void us_init_timer1(void);
void us_init_ccp3(void);
void us_init(void);
void us_test(void);
void us_send_trig(unsigned char us_ID);

void us_isr(void);

volatile unsigned char us_used = US_G_ID;  //Module US en cours d'utilisation

volatile unsigned char us_distG=0; //distances en cm ...
volatile unsigned char us_distC=0;
volatile unsigned char us_distD=0;

volatile unsigned char us_lost=0;

volatile char flag_us = DIST_NOK; //indique si une mesure est faite

#ifdef	__cplusplus
}
#endif

#endif	/* US_H */

