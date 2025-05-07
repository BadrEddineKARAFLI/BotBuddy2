/* 
 * File:   irDetect.h
 * Author: meimouni
 *
 * Created on 9 septembre 2013, 18:16
 */

#ifndef IRDETECT_H
#define	IRDETECT_H


#ifdef	__cplusplus
extern "C" {
#endif

#define IR_AVD              PORTBbits.RB1
#define IR_AVG              PORTBbits.RB2

#define IR_ARD              PORTAbits.RA0
#define IR_ARG              PORTAbits.RA1

#define IR_AVD_ACTIVE       !IR_AVD//(IR_AVD == 0)
#define IR_AVG_ACTIVE       !IR_AVG//(IR_AVG == 0)
#define IR_ARD_ACTIVE       !IR_ARD//(IR_ARD == 0)
#define IR_ARG_ACTIVE       !IR_ARG//(IR_ARG == 0)

void irDetect_init(void);
unsigned char irDetect_getState(void);
void irDetect_test(void);

#ifdef	__cplusplus
}
#endif

#endif	/* IRDETECT_H */

