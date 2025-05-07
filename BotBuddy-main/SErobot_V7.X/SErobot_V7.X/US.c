#include <xc.h>

#include "const.h"
#include "US.h"

/**
 * Init. du CCP3, utilisé pour la mesure US
 * Front montant actif
 * Timer1 utilisé
 * It validée basse priorité
 */
void us_init_ccp3(void)
{
  unsigned char config;


 CCPTMRS0bits.C3TSEL = 0b00; //CCP3 utilise le timer1
 CCP3CONbits.CCP3M = 0b0101;//mode capture sur front montant.
//  config = CAPTURE_INT_ON|ECAP_EVERY_FALL_EDGE;

//OpenECapture3(CAPTURE_INT_ON|CAP_EVERY_RISE_EDGE/*|ECCP_3_SEL_TMR12*/);

  PIR4bits.CCP3IF = 0; //RAZ flag IT
  
  RCONbits.IPEN = 1;//enable interrupt priority
  INTCONbits.GIEH = 1;//enable only High Priority interrupts

  IPR4bits.CCP3IP = 1; //low priority
  PIE4bits.CCP3IE = 1; // It validée
}

/**
 * Init. du Timer 1:
 * horloge interne (FOSC/4)
 * Prescaler : 1/8
 * TIMER1: 16bits R/W
 */
void us_init_timer1(void)
{
    //OpenTimer1(TIMER_INT_OFF|T1_SOURCE_INT|T1_PS_1_8);
    T1CONbits.TMR1CS = 0b00; //horloge interne à FOSC/4 (olbigatoire pour utiliser le mode capture)
    T1CONbits.T1CKPS = 0b11; //prescaler = 8
    T1CONbits.T1SOSCEN = 0; //desactivé
    T1CONbits.T1RD16 = 1; //lecture/ecriture sur 16bits

    TMR1H = 0;
    TMR1L = 0;

    T1CONbits.TMR1ON = 0; //timer 1 OFF

}

/**
 * Init. interface US
 */
void us_init(void)
{

     us_distC=0;
     us_distG=0;
     us_distD=0;

    ANSELBbits.ANSB5 = 0;//Digital input (echo)

    SELECT_US_G;

    US_TRIGG = 0;
    US_TRIGC = 0;
    US_TRIGD = 0;

    TRISDbits.RD2 = 0; // sel 0  en sortie
    TRISDbits.RD3 = 0; // sel 1  en sortie

    TRISBbits.RB4 = 0; //trigG en sortie
    TRISBbits.RB0 = 0; //trigD en sortie
    TRISAbits.RA2 = 0; //trigC en sortie

    TRISBbits.RB5 = 1; //echo en entrée

    tempo(200); // L'init. genere un trig! Alors on attend ...
    
    us_init_timer1();
    us_init_ccp3();
    T1CONbits.TMR1ON = 1; //timer 1 ON
}


void us_test(void)
{
    int test=0;

//  us_init();
    
   while (1)
    {
     us_send_trig(US_G_ID); //lance la mesure sur l'US centre

     us_send_trig(US_C_ID); //lance la mesure sur l'US centre

     us_send_trig(US_D_ID); //lance la mesure sur l'US centre
 
     test = us_distG;
     test = us_distC;
     test = us_distD;

/*__delay_ms(10);
__delay_ms(10);
__delay_ms(10);
__delay_ms(10);
__delay_ms(10);
__delay_ms(10);
*/
    }
   
 }
    

/*
void us_send_trig_sov(unsigned char us_ID)
{
    flag_us = DIST_NOK;

    us_used = us_ID;

    if (us_ID == US_G_ID)
     {
       SELECT_US_G;
       __delay_us(10);
       US_TRIG = 1;
       __delay_us(300);
       US_TRIG = 0;
     }

    if (us_ID == US_C_ID)
     {
      SELECT_US_C;
        __delay_us(10);
       US_TRIG = 1;
       __delay_us(300);
       US_TRIG = 0;

     }

    if (us_ID == US_D_ID)
     {
       SELECT_US_D;
       __delay_us(10);
       US_TRIG = 1;
       __delay_us(10);
       US_TRIG = 0;

     }
}
*/
/**
 * Lance la mesure US et attend jusqu'à la reception de echo ou la perte signal.
 * @param us_ID
 */
void us_send_trig(unsigned char us_ID)
{
    int test=0;
    flag_us = DIST_NOK;

    us_used = us_ID;

    if (us_ID == US_G_ID)
     {
       SELECT_US_G;
       US_TRIGG = 1;
       __delay_us(10);
       US_TRIGG = 0;

       while (flag_us == DIST_NOK) //attente mesure terminée
        {
          if (TMR1 >= US_LIMIT)
           {
              us_lost=1;//perte signal, pas d'obstacle
              us_distG = 100;
           }
        }

       if (us_lost == 0) us_distG = (unsigned short)(1700.0f*(float)CCPR3/FREQ_COMPTAGE);

     }
    else if (us_ID == US_C_ID)
     {
      test=1;
       SELECT_US_C;
       US_TRIGC = 1;
       __delay_us(10);
       US_TRIGC = 0;
       
       while (flag_us == DIST_NOK) //attente mesure terminée
        {
          if (TMR1 >= US_LIMIT)
           {
              us_lost=1;// perte signal, pas d'obstacle
              us_distC = 100;
           }
        }

       if (us_lost == 0) us_distC = (unsigned short)(1700.0f*(float)CCPR3/FREQ_COMPTAGE);

     }
    else //(us_ID == US_D_ID)
     {
       SELECT_US_D;
       US_TRIGD = 1;
       __delay_us(10);
       US_TRIGD = 0;

       while (flag_us == DIST_NOK) //attente mesure terminée
        {
         if (TMR1 >= US_LIMIT)
         {
             us_lost=1;// perte signal, pas d'obstacle
             us_distD = 100;
         }
        }
       
       if (us_lost == 0) us_distD = (unsigned short)(1700.0f*(float)CCPR3/FREQ_COMPTAGE);             
     }
}

/**
 *------------------------------------------------
 *Programme d'IT. US.
 */
void us_isr(void)
{
   if (CCP3CONbits.CCP3M == 0b0101) //actif sur front montant??
    {
     TMR1 = 0x0000; //RAZ TIMER 1
     CCP3CONbits.CCP3M = 0b0100;//mode capture sur front descendant.
    }
   else
    {
     CCP3CONbits.CCP3M = 0b0101; ////actif sur front descendant
 
     flag_us = DIST_OK;
     us_lost = 0;
     
    }//fin else du if (CCP3CONbits.CCP3M == 0b0101)

 PIR4bits.CCP3IF = 0; //RAZ flag IT
}





/**
 * Lance la mesure US et attend jusqu'à la reception de echo ou la perte signal.
 * @param us_ID
 */
void us_send_trig_old(unsigned char us_ID)
{
    int test=0;
    flag_us = DIST_NOK;

    us_used = us_ID;

    if (us_ID == US_G_ID)
     {
       SELECT_US_G;
       US_TRIGG = 1;
       __delay_us(100);
       US_TRIGG = 0;

       while (flag_us == DIST_NOK) //attente mesure terminée
        if (TMR1 >= US_LIMIT)  us_lost=1;//perte signal, pas d'obstacle

     }
    else if (us_ID == US_C_ID)
     {
      test=1;
       SELECT_US_C;
       US_TRIGC = 1;
       __delay_us(10);
       US_TRIGC = 0;
       while (flag_us == DIST_NOK) //attente mesure terminée
        if (TMR1 >= US_LIMIT)  us_lost=1;// perte signal, pas d'obstacle
     }
    else //(us_ID == US_D_ID)
     {
       SELECT_US_D;
       US_TRIGD = 1;
       __delay_us(10);
       US_TRIGD = 0;

       while (flag_us == DIST_NOK) //attente mesure terminée
         if (TMR1 >= US_LIMIT)  us_lost=1;// perte signal, pas d'obstacle
     }
}

/**
 *------------------------------------------------
 *Programme d'IT. US.
 */
void us_isr_old(void)
{
   if (CCP3CONbits.CCP3M == 0b0101) //actif sur front montant??
    {
     TMR1 = 0x0000; //RAZ TIMER 1
     CCP3CONbits.CCP3M = 0b0100;//mode capture sur front descendant.
    }
   else
    {
     CCP3CONbits.CCP3M = 0b0101; ////actif sur front descendant

     switch(us_used)
     {
        case US_G_ID:
                        if (us_lost == 0) us_distG = (unsigned short)(1700.0f*(float)CCPR3/FREQ_COMPTAGE);
                        else us_distG = 100;

                        flag_us = DIST_OK;
                        break;
        case US_C_ID:
                        if (us_lost == 0) us_distC = (unsigned char)(1700.0f*(float)CCPR3/FREQ_COMPTAGE);
                        else us_distC = 100;

                        flag_us = DIST_OK;
                        break;
        case US_D_ID:
                        if (us_lost == 0) us_distD = (unsigned char)(1700.0f*(float)CCPR3/FREQ_COMPTAGE);
                        else us_distD = 100;

                        flag_us = DIST_OK;
                        break;

        default :       us_used = US_G_ID; //US par defaut ...
                        flag_us = DIST_NOK;
                        break;
      } //fin switch

     us_lost = 0;

    }//fin else du if (CCP3CONbits.CCP3M == 0b0101)

 PIR4bits.CCP3IF = 0; //RAZ flag IT
}