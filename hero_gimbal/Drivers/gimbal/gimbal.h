#ifndef _GIMBAL_H_
#define _GIMBAL_H_

#include "main.h"
#include "gyro.h"
#include "PID.h"
#include "rc.h"
#include "motor.h"
#include "vofa.h"
#include "vision.h"

#define RC_Office_value          50
#define GYRO_Office_value        50
#define OPEN    1
#define CLOSE   0

extern rc_crl_t RC_Ctl;
extern PID pid[14];
extern motor_t Motor[4];
extern Gyro gyro;
extern float pitch;
extern float yaw;
extern vision Vision;
extern can CAN;

void gimbal_whole(void);
void pid_cs(void);
void GIMBAL_INITIALIZA(void);
void gimbal_whole(void);

typedef struct 
{
	float    pitch_target;
	float    yaw_target;
	int16_t  zm_target;
	int16_t  ym_target;
	int16_t  clear_cha_time;
	uint16_t rc_time;
	uint16_t gyro_time;
	struct
	{
	 uint8_t fri;
	 uint8_t gim;
	 uint8_t off;
   uint8_t han;
	 uint8_t sel;
	 uint16_t b;
	 uint16_t v;
	 uint16_t c;
	}Flag;
	int8_t Microswitches;
}gimbal;	











#endif //_GIMBAL_H_

