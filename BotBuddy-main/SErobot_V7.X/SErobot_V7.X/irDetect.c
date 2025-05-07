#include <xc.h>

#include "const.h"
#include "irDetect.h"

void irDetect_init(void)
{
    ANSELBbits.ANSB1 = 0; //digital input
    ANSELBbits.ANSB2 = 0; //digital input
    ANSELAbits.ANSA0 = 0; //digital input
    ANSELAbits.ANSA1 = 0; //digital input

    TRISBbits.RB1 = 1; //input
    TRISBbits.RB2 = 1; //input
    TRISAbits.RA0 = 1; //input
    TRISAbits.RA1 = 1; //input
}

/**
 * Retourne un octet indiquant l'etat des capteurs.
 * Codage sur un octet :
 * 0000<IR_AVG><IR_AVD><IR_ARG><IR_ARD>
 * @return
 */
unsigned char irDetect_getState(void)
 {
  return ((IR_AVG_ACTIVE << 3) + (IR_AVD_ACTIVE << 2) + (IR_ARG_ACTIVE << 1) + IR_ARD_ACTIVE);
 }

void irDetect_test(void)
{
   // irDetect_init();
    
  while (1)
    {
     if ((IR_AVD_ACTIVE) || (IR_AVG_ACTIVE) || (IR_ARD_ACTIVE) || (IR_ARG_ACTIVE))
      {
       LATCbits.LATC5 = 0; //led allumée
        tempo(30);
       LATCbits.LATC5 = 1; //led allumée
        tempo(30);
       LATCbits.LATC5 = 0; //led allumée
        tempo(30);
      }
     else LATCbits.LATC5 = 1;

    }
}