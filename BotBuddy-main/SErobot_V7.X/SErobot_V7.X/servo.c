#include <xc.h>

#include "const.h"
#include "servo.h"

/************************************************
 * Initialisation de la liaison série 1 du PIC.
 * 9600bauds, 8bits, 1start,1stop
 ***********************************************/
void servo_init(void)
 {
    unsigned char config;
    unsigned int spbrg;


    ANSELCbits.ANSC6 = 0; //digital
    ANSELCbits.ANSC7 = 0; //digital

    config = USART_TX_INT_OFF & USART_RX_INT_OFF & USART_EIGHT_BIT & \
              USART_ASYNCH_MODE & USART_BRGH_LOW & USART_ADDEN_OFF;

  //Asynchronous mode, high speed: BRG16 à 1 /BRGH à 0
  //Fosc / (16 * (spbrg + 1))
  //spbrg = -1 + Fosc/(16*speed)

  spbrg  = (unsigned int)(-1+(_XTAL_FREQ/(16L*(long)COM_SPEED)));
  BAUDCON1bits.BRG16 = 1; //mode 16bits
  
   Open1USART(config, spbrg);

 
 //  servo_set_startPos(1, 4000); //cam devant
 //  servo_set_startPos(2, 4000);
 //  servo_set_startPos(3, 4000);

   servo_onoff(0, 1); //tous les servos sont activés

   servo_cmd(2, PINCE_BAISSEE,80); //Pince baissée
   servo_cmd(3, PINCE_FERMEE,80); //Pince fermée

   servo_cmd_w(1,CAM_A_DROITE,30);//cam à droite
  // servo_cmd_w(1,CAM_A_GAUCHE,30); //cam à gauche
   servo_cmd_w(1,CAM_CENTREE,30);//cam devant
 }

/****************************************************
 * Active/désactive un servo moteur.
 * @param numServo: Numero du servomoteur : de 1 à 8
 * @param trig : 0 désactivation / 1 activation
 ***************************************************/
void servo_onoff(char numServo, char trig)
 {
    char cmd;
    
    cmd = 0b11000000 + numServo;

   while(!TXSTA1bits.TRMT);
   Write1USART(cmd);

    while(!TXSTA1bits.TRMT);
   Write1USART(trig);
 }

/******************************************
 * Retourne la position courante du moteur
 *****************************************/
unsigned int servo_get_pos(char num)
 {
    unsigned int pos;


    num = 0b10100000 + num;
    while(!TXSTA1bits.TRMT);
    Write1USART(num);

	while(PIR1bits.RCIF==0);//Carac. recu?
	pos= Read1USART();
 
	while(PIR1bits.RCIF==0); //Carac. recu?
	pos = (pos << 6) + (Read1USART() & 0x3F);

        return pos;
}

/***********************************************
 * Commande du servomoteur spécifié par numMot.
 * Retourne que lorsque le mouvmeent est terminé
 * Duty cyvle = (0.5us * pos) + 0.5ms
 * 0.5ms --> pos = 0
 * 1ms --> pos = 1000
 * 1.5ms --> pos = 2000
 * 2ms --> pos = 3000
 * 2.5ms --> pos = 4000
 * @param numServo numero du servo
 * @param pos position moteur [0,8000]
 * @param speed [0,100]
 **********************************************/
void servo_cmd_w(char numServo, unsigned int pos,char speed)
 {
    char mode;
    char posH;
    char posL;
   
    
    mode = 0b11100000 + numServo;
    while(!TXSTA1bits.TRMT);
    Write1USART(mode);

    posH = (char)((pos >> 6) & 0b0000000001111111);
    posL = (char)(pos & 0b0000000000111111);
    while(!TXSTA1bits.TRMT);
    Write1USART(posH);

    while(!TXSTA1bits.TRMT);
    Write1USART(posL);

    while(!TXSTA1bits.TRMT);
    Write1USART(speed&0b01111111);

    while(servo_get_pos(numServo) != pos);
 }

/*********************************************************
 * Commande du servomoteur spécifié par numMot.
 * N'attend pas que le mouvement soit terminé.
 *
 * Duty cyvle = (0.5us * pos) + 0.5ms
 * 0.5ms --> pos = 0
 * 1ms --> pos = 1000
 * 1.5ms --> pos = 2000
 * 2ms --> pos = 3000
 * 2.5ms --> pos = 4000
 * @param numServo numero du servo
 * @param pos position moteur [0,8000]
 * @param speed [0,100]
 *********************************************************/
void servo_cmd(char numServo, unsigned int pos,char speed)
 {
    char mode;
    char posH;
    char posL;


    mode = 0b11100000 + numServo;
    while(!TXSTA1bits.TRMT);
    Write1USART(mode);

    posH = (char)((pos >> 6) & 0b0000000001111111);
    posL = (char)(pos & 0b0000000000111111);
    while(!TXSTA1bits.TRMT);
    Write1USART(posH);

    while(!TXSTA1bits.TRMT);
    Write1USART(posL);

    while(!TXSTA1bits.TRMT);
    Write1USART(speed&0b01111111);

 }

/********************************************
 * Mise en pos. init du servo passé en param.
 * @param numServo : Numéro moteur
 * @param pos : consigne de position.
 * @return
 *******************************************/
void servo_set_startPos(char numServo, unsigned int pos)
  {
    char posH;
    char posL;

    posH = (char)((pos >> 6) & 0b0000000001111111);
    posL = (char)(pos & 0b0000000000111111);

   while(!TXSTA1bits.TRMT);
   Write1USART(0b10000000 + numServo);

   while(!TXSTA1bits.TRMT);
   Write1USART(posH);

   while(!TXSTA1bits.TRMT);
   Write1USART(posL);

   while(PIR1bits.RCIF==0);//Carac. recu? 
   Read1USART(); //0x04 attendu en reponse!
}

/*****************************************
 * Fonction de test ...
 ****************************************/
void servo_test(void)
{
 // servo_init();

//servo_onoff(0, 1);

// servo_cmd_w(1, 8000,20);
// servo_cmd_w(1, 4000,20);

//servo_cmd(2,0,80);
//servo_cmd_w(3,7000,80);

tempo(100);

    while(1)
     {
      servo_cmd_w(1, 0,50);
      servo_cmd_w(1, 8000,50);

     // servo_cmd_w(2,0,80);
     // servo_cmd_w(2,4000,80);
 
   //   servo_cmd_w(3, 1000,80);
   //   servo_cmd_w(3, 6000,80);
    }
}