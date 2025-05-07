#include <xc.h>

#include "const.h"
#include "boussole.h"

void bouss_i2c_init(void)
{
  ANSELDbits.ANSD0 = 0; //D0 digital
  ANSELDbits.ANSD1 = 0; // D1 digital

  TRISDbits.RD0 = 1; //output SCK
  TRISDbits.RD1 = 1; //output SDA

  OpenI2C2(MASTER,SLEW_OFF);
  
  PIE3bits.SSP2IE = 0;
  /**
   * SSP2ADD est utilisé pour fixer la freq. de la clock i2C
   * Fsclk  = FOSC/((ADD<7:0>+1)*4)
   * Pour SCLK à Fsclk = 100Khz:
   * FOSC = 40MHz
   * ADD<7:0> = (FOSC/(4*Fsclk)) - 1;
   *
   */
    SSP2ADD = (unsigned char)(-1 + (_XTAL_FREQ/(4*BOUSS_I2C_FCLK)));
}

void bouss_init(void)
 {
  bouss_i2c_init(); 
 }

/*******************************************
 * Permet la calibration de la boussole
 *******************************************/
int bouss_calibration(void)
  {
   LED_INFO_ON;
   tempo(300);//300*10ms
   LED_INFO_OFF;
/*
   //----------bridge offset--------------------
   //Envoie de la commande bridge offset
   StartI2C2();
   if (WriteI2C2(BOUSS_I2C_ADD_W) < 0) return -1;
  // IdleI2C2(); //attente bus libre
   if (WriteI2C2(BOUSS_BRIDGE_OFFSET_CMD) < 0) return -1;
 //  IdleI2C2(); //attente bus libre
   StopI2C2();

   tempo(1); //10ms (min 6ms)

   LATCbits.LATC5 = 0;  //LED ON
 */
    //--------------------------------------------
   //Envoie de la commande de calibration
  StartI2C2();
  if (WriteI2C2(BOUSS_I2C_ADD_W) < 0) return -1;
 // IdleI2C2(); //attente bus libre
  if (WriteI2C2(BOUSS_CALIBRATION_CMD) < 0) return -1;
//  IdleI2C2(); //attente bus libre
  StopI2C2();

  tempo(4000);//4000*10ms
 
    //--------------------------------------------
   //Envoie de la commande de calibration
  StartI2C2();
  if (WriteI2C2(BOUSS_I2C_ADD_W) < 0) return -1;
 // IdleI2C2(); //attente bus libre
  if (WriteI2C2(BOUSS_EXIT_CAL_CMD) < 0) return -1;
//  IdleI2C2(); //attente bus libre
  StopI2C2();
 
   LED_INFO_ON;
  while(1);
  return 0;
  }

/***********************************************
 * Retourne le cap en ° dans un float.
 **********************************************/
float bouss_read_heading_f(void)
{
 unsigned char resultH=0;
 unsigned char resultL=0;
 unsigned int  cap    =0;

  //--------------------------------------------
  //Envoie de la commande de lecture du heading.
//  IdleI2C2(); //attente bus libre
  StartI2C2();
  if (WriteI2C2(BOUSS_I2C_ADD_W) < 0) return (float)-1;
 // IdleI2C2(); //attente bus libre
  if (WriteI2C2(BOUSS_HEADING_READ_CMD) < 0) return (float)-1;
//  IdleI2C2(); //attente bus libre
  StopI2C2();
  
 __delay_ms(10);
 
  //--------------------------------------------
  //lecture du heading.
 // IdleI2C2(); //attente bus libre
  StartI2C2();

  if (WriteI2C2(BOUSS_I2C_ADD_R) < 0) return (float)-1;
  resultH = ReadI2C2();
  AckI2C2();
  resultL = ReadI2C2();
  NotAckI2C2();
  StopI2C2();

  cap  = (resultH << 8)+ resultL;

  return (float)cap;
}

/******************************************************************************
 * Retourne dans un tab. de 2octets, les PF et Pf du cap fournis par la boussole.
 * heading[0] = poids fort.
 * heading[1] = poids faible.
 * Le cap est obtenu en concatenant ces 2 octets. Ce qui donne:
 * Une valeur comprise entre 0 et 3599 dixieme de °.
 * @return 
 *****************************************************************************/
unsigned char * bouss_read_heading(void)
{
 //unsigned char resultH=0;
 //unsigned char resultL=0;

  //--------------------------------------------
  //Envoie de la commande de lecture du heading.
//  IdleI2C2(); //attente bus libre
  StartI2C2();
  if (WriteI2C2(BOUSS_I2C_ADD_W) < 0) return NULL;
 // IdleI2C2(); //attente bus libre
  if (WriteI2C2(BOUSS_HEADING_READ_CMD) < 0) return NULL;
//  IdleI2C2(); //attente bus libre
  StopI2C2();

 __delay_ms(10);

  //--------------------------------------------
  //lecture du heading.
 // IdleI2C2(); //attente bus libre
  StartI2C2();

  if (WriteI2C2(BOUSS_I2C_ADD_R) < 0) return NULL;
  heading[0] = ReadI2C2();
  AckI2C2();
  heading[1] = ReadI2C2();
  NotAckI2C2();
  StopI2C2();

  return heading;
}

 float val=0;
void bouss_test(void)
{

 int test=0;
 // bouss_init();
 

  
  while(1)
  {
   val = bouss_read_heading_f()/10.0;



   test =1;
  test=0;
 //  __delay_ms(10);
//    __delay_ms(10);
 //   __delay_ms(10);

  }
}
