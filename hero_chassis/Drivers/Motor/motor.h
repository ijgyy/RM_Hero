#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "main.h"
#include "rc.h"
#include "can.h"



void MSP_motor(void);
void motor_angle(uint8_t motor_num);

typedef struct 
{
		int16_t Rospeed;
		int16_t angle;
		int16_t first_angle;
		int16_t angle_last;
		int32_t total_angle;
	  int16_t Torque;
	  int16_t temperature;
		int16_t round;
		int16_t round_last;
		int16_t err;
	  int16_t flag_angle;	
		int16_t Pos_dir_angle;
}motor_t; 


#endif //

