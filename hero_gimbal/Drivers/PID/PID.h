#ifndef _PID_H_
#define _PID_H_

#include "main.h"

typedef struct
{
    float target;   //目标值
    float err;          //偏差值
    float err_last;     //上一个偏差值
    float integral;     //积分值
    float output;   //输出值
		float err_dead;
		float kp;
		float ki;
		float kd;
		float integral_max;
		float output_max;
}PID;

float PID_realize(uint8_t num,float target,float measure);


#endif //_PID_H_

