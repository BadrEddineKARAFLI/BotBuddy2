/* 
 * File:   servo.h
 * Author: meimouni
 *
 * Created on 10 septembre 2013, 17:49
 */

#ifndef SERVO_H
#define	SERVO_H


#ifdef	__cplusplus
extern "C" {
#endif

#define COM_SPEED           9600

#define PINCE_OUVERTE       6000
#define PINCE_FERMEE        1500//500 
#define PINCE_LEVEE         0 
#define PINCE_BAISSEE       3300
  
#define CAM_A_GAUCHE        8000
#define CAM_A_DROITE        0
#define CAM_CENTREE         4000   
    
#define PINCE_OUVRIR        servo_cmd(3, PINCE_OUVERTE,80)
#define PINCE_FERMER        servo_cmd(3, PINCE_FERMEE,80)
#define PINCE_LEVER         servo_cmd(2, PINCE_LEVEE,80)
#define PINCE_BAISSER       servo_cmd(2, PINCE_BAISSEE,80)
#define CAM_TOURNER_G       servo_cmd(1, CAM_A_GAUCHE,30)
#define CAM_TOURNER_D       servo_cmd(1, CAM_A_DROITE,30)
#define CAM_CENTRER         servo_cmd(1, CAM_CENTREE,30)

void servo_init(void);
void servo_onoff(char numServo, char trig);
void servo_cmd(char numServo, unsigned int pos,char speed);
void servo_cmd_w(char numServo, unsigned int pos,char speed);
void servo_set_startPos(char numServo, unsigned int pos);
unsigned int servo_get_pos(char num);
void servo_test(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SERVO_H */

