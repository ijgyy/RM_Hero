#ifndef _CHASSIS_H
#define _CHASSIS_H


#include "stm32f4xx_hal.h"
#include "rc.h"
#include "vofa.h"
#include "motor.h"
#include "can.h"
#include "PID.h"
#include "math.h"
#include "pid.h"
#include "Referee_system.h"


extern float err;
extern float Yaw;
extern Referee_info_t REF;
extern rc_crl_t RC_Ctl;


void chassis_whole(void);
void CHASSIS_INITIALIZA(void);

#define OPEN    1
#define CLOSE   0
#define CHASSIS_OFFICE_VALUE  100



typedef struct 
{
	int16_t Motor_zq_target;
	int16_t Motor_yq_target;
	int16_t Motor_yh_target;
	int16_t Motor_zh_target;
	int32_t Motor_bd_target;
	int16_t time;
		struct
	{
		uint8_t cnt;
		int16_t flag;
	}Pluck; 
		struct 
	{
		int16_t cha;
		int16_t off;
		int16_t Han;
		int16_t Sma;
		int16_t tcf;
		int16_t b;
		int16_t v;
		int16_t c;
		int16_t state;
	}Flag;
		struct 
	{
		int16_t  now;
		int16_t  err;
		uint8_t last;
	}Microswitches;
  float Vx,Vy,W;
  float Vx_g,Vy_g;	
	uint8_t Speed_Multiplier;
}chassis;



typedef struct 
{
  int16_t cap_percent;
}cap_measure_t;








#endif //_CHASSIS_H

