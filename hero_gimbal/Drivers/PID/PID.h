#ifndef _PID_H_
#define _PID_H_

#include "main.h"

typedef struct
{
    float target;   //Ŀ��ֵ
    float err;          //ƫ��ֵ
    float err_last;     //��һ��ƫ��ֵ
    float integral;     //����ֵ
    float output;   //���ֵ
		float err_dead;
		float kp;
		float ki;
		float kd;
		float integral_max;
		float output_max;
}PID;

float PID_realize(uint8_t num,float target,float measure);


#endif //_PID_H_

