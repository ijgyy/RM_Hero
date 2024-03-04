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
	//=============�⻷=========================
    /*����Ŀ��ֵ��ʵ��ֵ�����*/
	  pid[num].target = target;
	
		pid[num].err = pid[num].target - measure;
    
		if(pid[num].err<pid[num].err_dead && pid[num].err>-(pid[num].err_dead))   //�������
		{
			pid[num].err = 0;
		}	
    /*������*/
    pid[num].integral += pid[num].err;
	
		if(pid[num].integral>pid[num].integral_max)    //�����޷�
		{
			pid[num].integral = pid[num].integral_max;
		}
		if(pid[num].integral<-(pid[num].integral_max))    //�����޷�
		{
			pid[num].integral = -(pid[num].integral_max);
		}
																																																 								 
    /*PID�㷨ʵ��*/                                                                            
    pid[num].output = (pid[num].kp) * pid[num].err + (pid[num].ki) * pid[num].integral + (pid[num].kd) * (pid[num].err - pid[num].err_last);
																																															 
		if(pid[num].output>pid[num].output_max)  //����޷�
		{	
			pid[num].output = pid[num].output_max;
		}
		if(pid[num].output<-(pid[num].output_max))  //����޷�
		{	
			pid[num].output = -(pid[num].output_max);
		}  		
    /*����*/
    pid[num].err_last = pid[num].err;
		
		return pid[num].output;
}

