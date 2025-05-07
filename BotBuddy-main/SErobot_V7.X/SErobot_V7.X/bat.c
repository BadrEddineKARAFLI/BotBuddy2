#include <xc.h>

#include "const.h"
#include "bat.h"

/**
 * Initialisation de l'entrée analogique, sur laquelle
 * on mesure une fraction de la tension batterie.
 */
void bat_init(void)
 {
    char config,config2,config3;

    LED_BATT_INIT; //Led batt. eteinte par defaut...

    config = ADC_FOSC_64 & ADC_RIGHT_JUST & ADC_0_TAD; //FOSC/64; justif. à droit; mode manuel
    config2 = ADC_CH25 & ADC_INT_OFF;
    config3 = ADC_REF_VDD_VDD & ADC_REF_VDD_VSS;

    ANSELDbits.ANSD5 = 1; //bit5 du port D en analogique ...
    
    OpenADC(config,config2,config3);

 }

/**
 * Lance la conversion et retourne la valeur numerique image de VBAT ...
 * vNBat : variable globale
 * @return
 */
unsigned int bat_get_v(void)
 {

  __delay_us(10);//attent pour acquisiton
  
  ConvertADC(); //Lance la conversion A/N
  while(BusyADC() == 1); //tant que non fin de concersion

 // vBat = (unsigned int)(1024.0f*(float)ReadADC()*PONT_DIV_BAT/V_REF);
  vBat = (unsigned int)ReadADC();

  return vBat;
 }
