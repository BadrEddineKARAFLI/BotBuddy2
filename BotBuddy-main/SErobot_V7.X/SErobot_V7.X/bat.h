/* 
 * File:   bat.h
 * Author: meimouni
 *
 * Created on 13 décembre 2013, 15:35
 */

#ifndef BAT_H
#define	BAT_H

#ifdef	__cplusplus
extern "C" {
#endif

#define V_REF               3.3f
#define PONT_DIV_BAT        1.0f/3.36f
#define V_BAT_MIN           10.0f   // Tension de batt. min. = 10V.
#define V_BAT_MAX           12.6f   // Tension de batt. min. = 10V.    
#define SEUIL_BAT_MIN       (1023.0 * V_BAT_MIN)/V_BAT_MAX   ///1024.0f*(V_BAT_MIN*PONT_DIV_BAT)/V_REF

#define LED_BATT_INIT   {ANSELAbits.ANSA3 = 0; TRISAbits.TRISA3 = 0; LATAbits.LATA3 = 1;} //led eteinte par défaut.
#define LED_BATT        LATAbits.LATA3
#define LED_BATT_ON     LATAbits.LATA3 = 0
#define LED_BATT_OFF    LATAbits.LATA3 = 1
    
void bat_init(void);
unsigned int bat_get_v(void);

volatile unsigned int vBat=0;

#ifdef	__cplusplus
}
#endif

#endif	/* BAT_H */

