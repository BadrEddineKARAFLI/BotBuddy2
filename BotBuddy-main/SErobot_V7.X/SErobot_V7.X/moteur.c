#include <xc.h>

#include "const.h"
#include "moteur.h"


/**
 * PWM period = [(period ) + 1] x 4 x Tosc x TMRx prescaler
 * On veut un signal PWM à 30KHz: Tpwm = 1/30Khz
 * Le timer utilisé est le 2.
 * Le prescaler est choisi à 4, sinon les valeurs trop grandes (on déborde des registres).
 * Valeur à charger dans PR2 pour fixer la freq. PWM à 30Khz:
 * PR2 = Fosc/(4*TRM2PResc*Fpwm) -1
 * PR2 = 40000000/(4*4*30000)-1 = 82
 *
 * Calcul du rapport cyclique :
 * Pulse Width = (CCPRxL:CCPxCON<5:4>) * Tosc *TMRx Prescale Value
 *
 * Valeur à mettre dans CCPRxL:CCPxCON<5:4>: Fixe le temps de niveau haut (duty)
 * Avec un PRESCALER à 1, on dépasse (valeur trop grande > 10bits)
 * CCPRxL:CCPxCON<5:4> = PulseWidth * FOSC/TRM2PREscaler
 * TRM2PRescaler = 4
 * Si on considère le duty max : 1/Fpwm
 * CCPRxL:CCPxCON<5:4> = (1/30000)*40000000/4 = 333
 *
 * Le duty est initialisé à 0 pour les 2 moteurs (moteurs à l'arret)
 */
void moteur_init_pwm(void)
{
 unsigned char configTMR2;
 unsigned char period;
 unsigned char timer_source;
unsigned char outputconfig;
unsigned char outputmode;

 ANSELCbits.ANSC2 = 0; //digital
 ANSELEbits.ANSE2 = 0; //digital

 configTMR2 = TIMER_INT_OFF & T2_PS_1_4 & T2_POST_1_1;
 OpenTimer2(configTMR2);

 period = (char)(_XTAL_FREQ/(4L*TMR2_PRESC*FPWM) - 1);// period = 82=0x52;
 timer_source = ECCP_1_SEL_TMR12; //le timer2 est utilisé
 OpenEPWM1(period, timer_source);
 
 timer_source = CCP_5_SEL_TMR12; //le timer2 est utilisé
 OpenPWM5(period, timer_source);

 SetDCEPWM1(0);
 SetDCPWM5(0);

 TRISCbits.RC2 = 0; //output --> active la sortie PWM
 TRISEbits.RE2 = 0; //output --> active la sortie PWM
}

/*************************************************************
 * Init. des I/O de controle des moteurs.
 * Les moteur droit et gauche sont initialisés en standby.
 * Les sorties IN1 et IN2 sont initialisées à 0 (moteur stop).
 ************************************************************/
void moteur_init_io(void)
 {
  MOTG_STBY     = 0; // moteur Gauche standby
  MOTG_STBY_DIR = 0; // output
  MOTD_STBY     = 0; // moteur droit standby
  MOTD_STBY_DIR = 0; // output

  //moteur gauche "stop"
  MOTG_IN1      = 0;
  MOTG_IN1_DIR  = 0; // output
  MOTG_IN2  = 0;
  MOTG_IN2_DIR  = 0; // output

  //moteur droit "stop"
  MOTD_IN1      = 0;
  MOTD_IN1_DIR  = 0; // output
  MOTD_IN2  = 0;
  MOTD_IN2_DIR  = 0; // output
}

void moteur_init(void)
{
  moteur_init_io();
  moteur_init_pwm();
}

void moteur_test(void)
{
   unsigned int i;
   unsigned duty;

  moteur_init();

 // TMR2 = 0;

  MOTG_IN1      = 1;
  MOTG_IN2      = 0; // output
  MOTG_STBY     = 1;

  MOTD_IN1      = 1;
  MOTD_IN2      = 0; // output
  MOTD_STBY     = 1;


 // SetDCEPWM1(100);

 do
 {
  for(i= 0; i <= 10; i++)
  {
      duty = i*33;
 LATCbits.LATC5 = 1;
      SetDCEPWM1(duty);
      SetDCPWM5(duty);
   //   __delay_ms(10);
   //   __delay_ms(10);
   //   __delay_ms(10);
   //   __delay_ms(10);
   //   __delay_ms(10);

      tempo(100);
       LATCbits.LATC5 = 0;
       tempo(100);
  }
  for(i = 10; i > 0; i--)
  {
     LATCbits.LATC5 = 1;
       duty = i*33;
      SetDCEPWM1(duty);
      SetDCPWM5(duty);
      tempo(100);

      LATCbits.LATC5 = 0;
      tempo(100);
  //    __delay_ms(10);
  //    __delay_ms(10);
  //    __delay_ms(10);
   //   __delay_ms(10);
   //   __delay_ms(10);
 // SetDCPWM5(160);
  }
 
}
  while(1);
}