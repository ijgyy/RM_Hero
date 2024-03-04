#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "main.h"

void MSP_motor(void);


typedef struct 
{
		int16_t Rospeed;
		int16_t angle;
		int16_t angle_last;
//		int16_t first_angle;
		int32_t total_angle;
//		int32_t total_angle_last;
//		int16_t sj_angle;
	  int16_t Torque;
	  int16_t temperature;
		int8_t  round;
//		int8_t  sj_round;
		int16_t err;
	  int16_t flag_angle;
//	  int16_t flag_total_angle;
}motor_t; 


#endif //

