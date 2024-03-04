#include "PID.h"

//============================
//pid[0]  pitch
//pid[1]  pitch
//pid[2]  yaw
//pid[3]  yaw
//pid[4]  bodan
//pid[5]
//pid[6]  yq
//pid[7]  zq
//pid[8]  yh
//pid[9]  zh
//pid[10]  zm
//pid[11]  ym
//pid[12]  dpgs

//============================

enum pid
{
	pitch_jd=0,pitch_sd,yaw_jd,yaw_sd,bd,
}Pid;


PID pid[14];





float PID_realize(uint8_t num,float target,float measure)
{	
	//=============外环=========================
    /*计算目标值与实际值的误差*/
	  pid[num].target = target;
	
		pid[num].err = pid[num].target - measure;
    
		if(pid[num].err<pid[num].err_dead && pid[num].err>-(pid[num].err_dead))   //误差死区
		{
			pid[num].err = 0;
		}	
    /*积分项*/
    pid[num].integral += pid[num].err;
	
		if(pid[num].integral>pid[num].integral_max)    //积分限幅
		{
			pid[num].integral = pid[num].integral_max;
		}
		if(pid[num].integral<-(pid[num].integral_max))    //积分限幅
		{
			pid[num].integral = -(pid[num].integral_max);
		}
																																																 								 
    /*PID算法实现*/                                                                            
    pid[num].output = (pid[num].kp) * pid[num].err + (pid[num].ki) * pid[num].integral + (pid[num].kd) * (pid[num].err - pid[num].err_last);
																																															 
		if(pid[num].output>pid[num].output_max)  //输出限幅
		{	
			pid[num].output = pid[num].output_max;
		}
		if(pid[num].output<-(pid[num].output_max))  //输出限幅
		{	
			pid[num].output = -(pid[num].output_max);
		}  		
    /*误差传递*/
    pid[num].err_last = pid[num].err;
		
		return pid[num].output;
}

