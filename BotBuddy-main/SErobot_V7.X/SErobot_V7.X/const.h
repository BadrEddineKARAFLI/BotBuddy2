/* 
 * File:   const.h
 * Author: meimouni
 *
 * Created on 4 septembre 2013, 15:23
 */

#ifndef CONST_H
#define	CONST_H

#ifdef	__cplusplus
extern "C" {
#endif

#define _XTAL_FREQ      40000000L //Fcpu = 40MHz

#define LED_INFO_INIT   {ANSELCbits.ANSC5 = 0;TRISCbits.TRISC5 = 0; LATCbits.LATC5 = 1;} //led eteinte par défaut.
#define LED_INFO        LATCbits.LATC5
#define LED_INFO_ON     LATCbits.LATC5 = 0
#define LED_INFO_OFF    LATCbits.LATC5 = 1

void tempo(unsigned int temps);

#ifdef	__cplusplus
}
#endif

#endif	/* CONST_H */

