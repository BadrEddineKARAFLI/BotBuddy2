/* 
 * File:   boussole.h
 * Author: meimouni
 *
 * Created on 6 septembre 2013, 10:53
 */

#ifndef BOUSSOLE_H
#define	BOUSSOLE_H

#ifdef	__cplusplus
extern "C" {
#endif

#define BOUSS_I2C_ADD            0x42 //addr. device
#define BOUSS_I2C_ADD_W          0x42 //addr. device en écriture
#define BOUSS_I2C_ADD_R          0x43 //addr. device en lecture

#define BOUSS_I2C_FCLK           100000L   //Fsclk = 100Khz

#define BOUSS_HEADING_READ_CMD  'A'
#define BOUSS_CALIBRATION_CMD   'C'
#define BOUSS_BRIDGE_OFFSET_CMD 'O'
#define BOUSS_EXIT_CAL_CMD      'E'

//void bouss_i2c_init(void);
void bouss_init(void);
int bouss_calibration(void);
unsigned char * bouss_read_heading(void);
void bouss_test(void);

unsigned char  heading[2]={0,0};

#ifdef	__cplusplus
}
#endif

#endif	/* BOUSSOLE_H */

