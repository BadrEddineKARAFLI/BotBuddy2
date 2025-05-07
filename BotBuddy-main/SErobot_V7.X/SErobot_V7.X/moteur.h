/* 
 * File:   moteur.h
 * Author: meimouni
 *
 * Created on 11 septembre 2013, 17:00
 */

#ifndef MOTEUR_H
#define	MOTEUR_H

#ifdef	__cplusplus
extern "C" {
#endif

#define TMR2_PRESC              4L
#define FPWM                    30000L

#define MOTG_IN1                LATCbits.LATC1
#define MOTG_IN1_DIR            TRISCbits.RC1
#define MOTG_IN2                LATAbits.LATA4
#define MOTG_IN2_DIR            TRISAbits.RA4
#define MOTG_STBY               LATCbits.LATC0
#define MOTG_STBY_DIR           TRISCbits.RC0

#define MOTD_IN1                LATEbits.LATE0
#define MOTD_IN1_DIR            TRISEbits.RE0
#define MOTD_IN2                LATEbits.LATE1
#define MOTD_IN2_DIR            TRISEbits.RE1
#define MOTD_STBY               LATAbits.LATA5
#define MOTD_STBY_DIR           TRISAbits.RA5

#define ROBOT_RECULER(duty)      {MOTG_IN1 = 1;MOTG_IN2 =0;MOTD_IN1 = 1;MOTD_IN2 =0; \
                                  MOTG_STBY = 1;MOTD_STBY = 1;SetDCEPWM1(duty);SetDCPWM5(duty);}

#define ROBOT_AVANCER(duty)      {MOTG_IN1 = 0;MOTG_IN2 =1;MOTD_IN1 = 0;MOTD_IN2 =1; \
                                  MOTG_STBY = 1;MOTD_STBY = 1; \
                                 SetDCEPWM1(duty);SetDCPWM5(duty);}

#define ROBOT_GAUCHE(duty)       {MOTG_IN1 = 1;MOTG_IN2 =0;MOTD_IN1 = 0;MOTD_IN2 =1; \
                                 MOTG_STBY = 1;MOTD_STBY = 1; \
                                 SetDCEPWM1(duty);SetDCPWM5(duty);}


#define ROBOT_DROITE(duty)       {MOTG_IN1 = 0;MOTG_IN2 =1;MOTD_IN1 = 1;MOTD_IN2 =0; \
                                 MOTG_STBY = 1;MOTD_STBY = 1; \
                                 SetDCEPWM1(duty);SetDCPWM5(duty);}

#define ROBOT_STOP               {MOTD_STBY = 0;MOTG_STBY = 0;SetDCEPWM1(0);SetDCPWM5(0);}
    
void moteur_init(void);
void moteur_test(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MOTEUR_H */

