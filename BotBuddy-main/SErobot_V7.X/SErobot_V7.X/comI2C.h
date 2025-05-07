/* 
 * File:   comI2C.h
 * Author: meimouni
 *
 * Created on 13 septembre 2013, 09:33
 */

#ifndef COMI2C_H
#define	COMI2C_H

#ifdef	__cplusplus
extern "C" {
#endif

#define CMD_CPU_START                   0x01
#define CMD_CPU_WAIT                    0x02
#define CMD_CPU_STOP                    0x00

#define CMD_ROBOT_AVANCER               0x10
#define CMD_ROBOT_STOP                  0x11
#define CMD_ROBOT_TOURNER_D             0x12
#define CMD_ROBOT_TOURNER_G             0x13
#define CMD_ROBOT_RECULER               0x14

#define CMD_PINCE_OUVRIR                0x20
#define CMD_PINCE_FERMER                0x21
#define CMD_PINCE_LEVER                 0x22
#define CMD_PINCE_BAISSER               0x23

#define CMD_CAM_TOURNER_G               0x30
#define CMD_CAM_TOURNER_D               0x31
#define CMD_CAM_CENTRER                 0x32

#define CMD_CAPT_US_DIST                0x40

#define CMD_IR_DETECT                   0x50

#define CMD_BOUSSOLE                    0x60

#define CMD_BATT                        0x70

#define CMD_GET_US                      0x90
#define CMD_GET_IR                      0x91
#define CMD_GET_BOUSS                   0x92
#define CMD_GET_BATT                    0x93

#define CMD_UNKNOWN                     0xFF

#define DATA_IS_CMD                     0x00
#define DATA_IS_PARAM                   0x01

volatile unsigned char cmd_temp = CMD_UNKNOWN;
volatile unsigned char cmd = CMD_UNKNOWN;
volatile unsigned char cmd_param = 0;
volatile unsigned char numero_param = 0;
volatile unsigned char isCMDorPARAM = DATA_IS_CMD;

void comI2C_init(void);
void comI2C_isr(void);

#ifdef	__cplusplus
}
#endif

#endif	/* COMI2C_H */

