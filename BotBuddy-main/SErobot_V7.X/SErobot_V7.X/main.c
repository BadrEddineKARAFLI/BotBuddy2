/* 
 * File:   main.c
 * Author: meimouni
 *
 * Created on 29 août 2013, 08:55
 */

#include <xc.h>

#include "pragma.h"
#include "const.h"
#include "US.h"
#include "boussole.h"
#include "irDetect.h"
#include "servo.h"
#include "moteur.h"
#include "comI2C.h"
#include "bat.h"


 /******************************
  * Tempo = temps * 10ms
  * @param temps
  *****************************/
 void tempo(unsigned int temps)
 {
  unsigned int i;

   for (i=0; i< temps; i++)  __delay_ms(10);
 }

 void test_led(void)
  {
   while(1)
    {
      LATCbits.LATC5 = 1;  //LED OFF
     tempo(50);
     LATCbits.LATC5 = 0;  //LED ON
     tempo(50);
    }
  }

#define VIT 100
 void testRobotUS(void)
 {
     int v = 0x03EA;

     while(1)
     {
       LATCbits.LATC5 = 0;  //LED ON
      us_send_trig(US_G_ID); //lance la mesure sur l'US centre
       tempo(3);
      us_send_trig(US_C_ID); //lance la mesure sur l'US centre
       tempo(3);
      us_send_trig(US_D_ID); //lance la mesure sur l'US centre
      LATCbits.LATC5 = 1;  //LED OFF    

    /*if (us_distC <= 10) ROBOT_DROITE(VIT)
    else if ((us_distG <= 10) && (us_distC <= 10) && (us_distD <=  10)) ROBOT_RECULER(VIT)
    else ROBOT_AVANCER(VIT)
*/

      
      if ((us_distG > 10) && (us_distC > 10) && (us_distD > 10))  ROBOT_AVANCER(VIT)
      else if ((us_distG <= 10) && (us_distC <= 10) && (us_distD > 10)) ROBOT_DROITE(VIT)
      else if ((us_distG <= 10) && (us_distC > 10) && (us_distD <= 10)) ROBOT_DROITE(VIT)
      else if ((us_distG <= 10) && (us_distC > 10) && (us_distD > 10)) ROBOT_DROITE(VIT)
      else if ((us_distG > 10) && (us_distC <= 10) && (us_distD <= 10)) ROBOT_GAUCHE(VIT)
      else if ((us_distG > 10) && (us_distC <= 10) && (us_distD > 10)) ROBOT_DROITE(VIT)
      else if ((us_distG > 10) && (us_distC > 10) && (us_distD <= 10)) ROBOT_GAUCHE(VIT)
      else if ((us_distG <= 10) && (us_distC <= 10) && (us_distD <=  10)) ROBOT_RECULER(VIT)
      else ROBOT_DROITE(VIT)

      tempo(100);//1ms

    //  v=0;
     }

 }

 void testRobot(void)
 {
     while (1)
     {
      if (IR_AVD_ACTIVE  && !IR_AVG_ACTIVE) ROBOT_GAUCHE(VIT)
      else if(!IR_AVD_ACTIVE  && IR_AVG_ACTIVE) ROBOT_DROITE(VIT)
      else if(IR_AVD_ACTIVE && IR_AVG_ACTIVE) ROBOT_RECULER(VIT)
      else if(IR_ARD_ACTIVE && !IR_ARG_ACTIVE) ROBOT_GAUCHE(VIT)
      else if(!IR_ARD_ACTIVE && IR_ARG_ACTIVE) ROBOT_DROITE(VIT)
      else if(IR_ARD_ACTIVE && IR_ARG_ACTIVE) ROBOT_AVANCER(VIT)
      else ROBOT_AVANCER(VIT)
     }

 }
 //extern volatile unsigned char cmd;
 /*****************************
  *
  ****************************/
int main(void)
 {
     //int val;

  //ANSELCbits.ANSC5 = 0; //digital
  //TRISCbits.TRISC5 = 0; //LED INFO

 // LATCbits.LATC5 = 1;  //LED OFF
  LED_INFO_INIT;

  comI2C_init();
  bouss_init();
  irDetect_init();
 // servo_init();
  moteur_init();
  us_init();
  bat_init();

 // test_led();
//moteur_test();
//us_test();
//  val = 0;
//  servo_test();
irDetect_test();
//bouss_calibration();
//  bouss_test();

 //testRobot();
 //testRobotUS();
  
     /*----------------------------
     //Attente cmde de start
     //----------------------------
     while (cmd != CMD_CPU_START);
     cmd = CMD_UNKNOWN;
     cmd_temp = CMD_UNKNOWN;
     isCMDorPARAM = DATA_IS_CMD;
      */
     
     LATCbits.LATC5 = 0; //LED ON

 //    servo_cmd(1,8000,10);
 //    servo_cmd(1,0,10);
 //    servo_cmd(1,4000,10);
    //Pos init pince
 //    servo_cmd_w(2,0,50);
 //    servo_cmd_w(3,0,50);

     //-----------------------------
     //Gestion des cmdes I2C recues.
     //-----------------------------
     while (1)
     {
 //       val = cpt;

         switch(cmd)
          {
             case CMD_CPU_STOP:
                 ROBOT_STOP;
                 //tempo(100);
                     while (1)
                      {
                         tempo(100);
                         LATCbits.LATC5 = 0;
                         tempo(100);
                         LATCbits.LATC5 = 1;
                      }
                 break;
  
             case CMD_ROBOT_AVANCER  :
                 ROBOT_AVANCER(cmd_param+ (unsigned int)78);
                 cmd = CMD_UNKNOWN;
                 cmd_temp = CMD_UNKNOWN;
                 isCMDorPARAM = DATA_IS_CMD;
                 break;
             case CMD_ROBOT_STOP     :
                 ROBOT_STOP;
                 cmd = CMD_UNKNOWN;
                 cmd_temp = CMD_UNKNOWN;
                 isCMDorPARAM = DATA_IS_CMD;
                 break;
             case CMD_ROBOT_TOURNER_D:
                 ROBOT_DROITE((unsigned int)cmd_param + (unsigned int)78);
                 cmd = CMD_UNKNOWN;
                 cmd_temp = CMD_UNKNOWN;
                 isCMDorPARAM = DATA_IS_CMD;
                 break;
             case CMD_ROBOT_TOURNER_G:
                 ROBOT_GAUCHE((unsigned int)cmd_param + (unsigned int)78);
                 cmd = CMD_UNKNOWN;
                 cmd_temp = CMD_UNKNOWN;
                 isCMDorPARAM = DATA_IS_CMD;
                 break;
             case CMD_ROBOT_RECULER  :
                 ROBOT_RECULER((unsigned int)cmd_param + (unsigned int)78);
                 cmd = CMD_UNKNOWN;
                 cmd_temp = CMD_UNKNOWN;
                 isCMDorPARAM = DATA_IS_CMD;
                 break;
             case CMD_PINCE_OUVRIR :
                 PINCE_OUVRIR;
                 cmd = CMD_UNKNOWN;
                 cmd_temp = CMD_UNKNOWN;
                 isCMDorPARAM = DATA_IS_CMD;
                 break;
             case CMD_PINCE_FERMER :
                 PINCE_FERMER;
                 cmd = CMD_UNKNOWN;
                 cmd_temp = CMD_UNKNOWN;
                 isCMDorPARAM = DATA_IS_CMD;
                 break;
             case CMD_PINCE_LEVER :
                 PINCE_LEVER;
                 cmd = CMD_UNKNOWN;
                 cmd_temp = CMD_UNKNOWN;
                 isCMDorPARAM = DATA_IS_CMD;
                 break;
             case CMD_PINCE_BAISSER:
                 PINCE_BAISSER;
                 cmd = CMD_UNKNOWN;
                 cmd_temp = CMD_UNKNOWN;
                 isCMDorPARAM = DATA_IS_CMD;
                 break;
             case CMD_CAM_TOURNER_G:
                 CAM_TOURNER_G;
                 cmd = CMD_UNKNOWN;
                 cmd_temp = CMD_UNKNOWN;
                 isCMDorPARAM = DATA_IS_CMD;
                 break;
             case CMD_CAM_TOURNER_D:
                 CAM_TOURNER_D;
                 cmd = CMD_UNKNOWN;
                 cmd_temp = CMD_UNKNOWN;
                 isCMDorPARAM = DATA_IS_CMD;
                 break;
             case CMD_CAM_CENTRER:
                 CAM_CENTRER;
                 cmd = CMD_UNKNOWN;
                 cmd_temp = CMD_UNKNOWN;
                 isCMDorPARAM = DATA_IS_CMD;
                 break;
             case CMD_CAPT_US_DIST :
                 us_send_trig(US_G_ID); //lance la mesure sur l'US centre
                 tempo(5);//50ms
                 us_send_trig(US_C_ID); //lance la mesure sur l'US centre
                 tempo(5);
                 us_send_trig(US_D_ID); //lance la mesure sur l'US centre
                 //tempo(4);

                 cmd = CMD_GET_US; //On se met en attente de la requete I2C de lecture
                 break;
             case CMD_IR_DETECT:
                  cmd = CMD_GET_IR; //On se met en attente de la requete I2C de lecture
                  break;
             case CMD_BOUSSOLE:
                  bouss_read_heading();
                  cmd = CMD_GET_BOUSS; //On se met en attente de la requete I2C de lecture
                 break;
             case CMD_BATT:
                  bat_get_v(); 
                  cmd = CMD_GET_BATT; //On se met en attente de la requete I2C de lecture
                 break;

             case CMD_GET_US: break;
             case CMD_GET_IR: break;
             case CMD_GET_BOUSS: break;
             case CMD_GET_BATT:break;
             case CMD_UNKNOWN: break;
             default:
                 cmd = CMD_UNKNOWN;
                 cmd_temp = CMD_UNKNOWN;
                 isCMDorPARAM = DATA_IS_CMD;
                 break;
          }//fin switch

         if (bat_get_v() <= SEUIL_BAT_MIN) LED_BATT_ON;
         else                              LED_BATT_OFF;
     }//fin while 1
 }


/**
 * Programme d'interruption
 */
   void interrupt prog_it(void)
     {

      //IT provenant des capteurs US
      if (PIR4bits.CCP3IF)
      {
       us_isr();
      }

      //IT provenant de l'I2C
      if(PIR1bits.SSP1IF)
      {
          comI2C_isr();
      }
     }

