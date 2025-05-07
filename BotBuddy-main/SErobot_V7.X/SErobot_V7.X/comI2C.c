#include <xc.h>

//#include <plib.h>

#include "const.h"
#include "comI2C.h"
#include "US.h"
#include "irDetect.h"
#include "boussole.h"
#include "bat.h"

/**
 * Initialisation de l'interface I2C
 */
void comI2C_init(void)
{
 ANSELCbits.ANSC3 = 0;
 ANSELCbits.ANSC4 = 0;
 TRISCbits.RC3 = 1; //input SCK
 TRISCbits.RC4 = 1; //input SDA

 SSP1STAT = 0b10000000;
 SSP1CON1 = 0b00110110;
 SSP1CON2 = 0b00000001;
 SSP1CON3 = 0b00000000;
 SSP1MSK  = 0b11110000;
//    OpenI2C(SLAVE_7,SLEW_OFF);
   // OpenI2C1(SLAVE_7_STSP_INT,SLEW_OFF);

 SSP1ADD = 0xE0;
 RCONbits.IPEN = 1;//enable interrupt priority
 INTCONbits.GIEH = 1;//enable only High Priority interrupts
 PIE1bits.SSP1IE = 1;//enable MSSP interrrupt
 IPR1bits.SSP1IP = 1;//Set MSSP to High Priority

 SSP1CON2bits.SEN = 1;
//    SSP1CON3bits.SCIE=1;
//    SSP1CON3bits.PCIE=1;
}

void comI2C_cmd(void)
 {
   
    if (isCMDorPARAM == DATA_IS_CMD)
      {
       cmd_temp = SSP1BUF;

       isCMDorPARAM = DATA_IS_PARAM;
      }
    else
     {
       cmd_param = SSP1BUF;

         switch (cmd_temp)
          {
             case CMD_CPU_START:
             case CMD_CPU_STOP:
             case CMD_ROBOT_AVANCER:
             case CMD_ROBOT_STOP:
             case CMD_ROBOT_TOURNER_D:
             case CMD_ROBOT_TOURNER_G:
             case CMD_ROBOT_RECULER:
             case CMD_PINCE_OUVRIR:
             case CMD_PINCE_FERMER:
             case CMD_PINCE_LEVER:
             case CMD_PINCE_BAISSER:
             case CMD_CAPT_US_DIST:
             case CMD_BOUSSOLE:
             case CMD_IR_DETECT:
             case CMD_CAM_TOURNER_G:
             case CMD_CAM_CENTRER:
             case CMD_CAM_TOURNER_D:
             case CMD_BATT:
                  cmd = cmd_temp;
                  break;

             default: cmd = CMD_UNKNOWN;
                      cmd_temp = CMD_UNKNOWN;
                  break;
          }
     }
 }

/**********************************************************
 * Gère les demandes d'acquisition: etat capteurs IR et US.
 *
 *********************************************************/
void comI2c_acqu(void)
{
   unsigned char addr;

   while(SSP1STATbits.BF); //attendre tant que buffer plein?
     SSP1CON1bits.WCOL1=0;

   switch (cmd)
    {
       case CMD_GET_US:
           
            switch (numero_param)
            {
               case 0: //capteur Gauche
                   SSP1BUF = us_distG; //envoie distance
                   numero_param=1;
               break;
               case 1: //capteur Centre
                   SSP1BUF = us_distC; //envoie distance
                   numero_param=2;
               break;  
               case 2: //capteur droit
                   SSP1BUF = us_distD; //envoie distance
                   numero_param=0;
                   cmd = CMD_UNKNOWN;
                   cmd_temp = CMD_UNKNOWN;
                   isCMDorPARAM = DATA_IS_CMD;
               break;
               default:
                   cmd = CMD_UNKNOWN;
                   cmd_temp = CMD_UNKNOWN;
                   isCMDorPARAM = DATA_IS_CMD;
               break;
             }
           break;

       case CMD_GET_BOUSS:
           if (numero_param == 0)
           {
               SSP1BUF = heading[0]; //envoie poids fort du cap boussole
               numero_param = 1;
           }
           else
           {
               SSP1BUF = heading[1]; //envoie poids fort du cap boussole
               numero_param= 0;

               cmd = CMD_UNKNOWN;
               cmd_temp = CMD_UNKNOWN;
               isCMDorPARAM = DATA_IS_CMD;
           }         
           break;

       case CMD_GET_IR:
           SSP1BUF = irDetect_getState();
           cmd = CMD_UNKNOWN;
           cmd_temp = CMD_UNKNOWN;
           isCMDorPARAM = DATA_IS_CMD;
           break;
       case CMD_GET_BATT:
           if (numero_param == 0)
            {            
             SSP1BUF = (unsigned char)(vBat >> 8); //On retourne le PF
             numero_param = 1;
            }
           else
            {
             SSP1BUF = (unsigned char)(vBat); //On retourne le pf
             numero_param = 0;

             cmd = CMD_UNKNOWN;
             cmd_temp = CMD_UNKNOWN;
             isCMDorPARAM = DATA_IS_CMD;
            }
           break;

       default: break;
   }//fin switch cmd
}

//volatile int cpt = 0;

/**
 * Prog. it I2C
 */
void comI2C_isr(void)
{
  unsigned char tmp;
  unsigned char i2c_state;
   
  PIR1bits.SSP1IF = 0; //RAZ flag it I2C

  if (SSP1CON1bits.SSPOV == 1) //Reception Overflow ?
   {
      SSP1CON1bits.SSPOV = 0;  //clear overflow
      tmp = SSPBUF;
   }
  else //Pas d'overflow
   {
     i2c_state = SSP1STAT & 0b00101101; //masquage, on garde que ce dont on a besoin

     //state 1 Master just wrote our address
     if ((i2c_state ^ 0b00001001) == 0)//S=1 && RW==0 && DA==0 && BF==1
        tmp = SSP1BUF; //lecture de l'adresse
       
     //state 2 Master just wrote data
     else if ((i2c_state ^ 0b00101001) == 0)//S=1 && RW==0 && DA==1 && BF==1
     {     
       comI2C_cmd();
     }

     //state 3 Master want to read, juste on recoit une addresse
     else if ((i2c_state ^ 0b00001101) == 0) //S=1 && RW==1 && DA==0 && BF==1
     {
        tmp = SSP1BUF; //On lit l'adresse, On a reçu au préalable une cmde d'acquisition
        comI2c_acqu();
     }

     //state 4 Master want to read, last byte was already data
     else if (((i2c_state ^ 0b00101100) == 0) && (SSP1CON1bits.CKP == 0))//S=1 && RW==1 && DA==1 && BF==0
       comI2c_acqu();

     //state 5 Master sends NACK to end message (avant un stop)
     //i2c_state = (val2 ^ 0b00101000) &&*/ (SSP1CON2bits.ACKSTAT1)
     else if (((i2c_state ^ 0b00101100) == 0) && (SSP1CON1bits.CKP == 1))// RW==0 && DA==1 && BF==0 && S==1 && CKP==1 (Nack)
//     else if (SSPSTATbits.P/*((i2c_state ^ 0b00101000) == 0) && (SSPCON1bits.CKP == 1)*/)// RW==0 && DA==1 && BF==0 && S==1 && CKP==1 (Nack)
     {
      //tmp=0;
     }//do nothing...

   }

   SSPCON1bits.CKP=1; //On relache la clock I2C
}