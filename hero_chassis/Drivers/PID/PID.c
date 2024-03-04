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


PID pid[14];


//void PID_cs(void)
//{
////=============pitch=========================
//	pid[0].target = 0;
//	pid[0].Kp = 15;
//	pid[0].Ki = 0;
//	pid[0].Kd = 0;
//	pid[0].integral_max = 15000;
//	pid[0].output_max = 20000;
//	pid[0].err_dead  = 0;
//	pid[0].err_last  = 0;
//  pid[1].target = 0;	
//	pid[1].Kp = 250;
//	pid[1].Ki = 0.08;
//	pid[1].Kd = 0;
//	pid[1].integral_max = 15000;
//	pid[1].output_max = 20000;
//	pid[1].err_dead  = 0;
//	pid[1].err_last  = 0;
////=============yaw=========================	
//	pid[2].target = 0;
//	pid[2].Kp = 13;
//	pid[2].Ki = 0;
//	pid[2].Kd = 0;
//	pid[2].integral_max = 3000;
//	pid[2].output_max = 20000;
//	pid[2].err_dead  = 1;
//	pid[2].err_last  = 0;
//  pid[3].target = 0;	
//	pid[3].Kp = 300;
//	pid[3].Ki = 2;
//	pid[3].Kd = 0;
//	pid[3].integral_max = 3000;
//	pid[3].output_max = 20000;
//	pid[3].err_dead  = 0;
//	pid[3].err_last  = 0;
////==================bd==================

////	pid[5].target = 0;
////	pid[5].Kp = 10;
////	pid[5].Ki = 0;
////	pid[5].Kd = 0;
////	pid[5].integral_max = 3000;
////	pid[5].output_max = 5000;
////	pid[5].err_dead  = 0;
////	pid[5].err_last  = 0;
////==================yq==================
//	pid[6].target = 0;
//	pid[6].Kp = 6.3;
//	pid[6].Ki = 0.05;
//	pid[6].Kd = 0;
//	pid[6].integral_max = 3000;
//	pid[6].output_max = 5000;
//	pid[6].err_dead  = 0;
//	pid[6].err_last  = 0;
////==================zq==================
//	pid[7].target = 0;
//	pid[7].Kp = 6.3;
//	pid[7].Ki = 0.05;
//	pid[7].Kd = 0;
//	pid[7].integral_max = 3000;
//	pid[7].output_max = 5000;
//	pid[7].err_dead  = 0;
//	pid[7].err_last  = 0;
////==================yh==================
//	pid[8].target = 0;
//	pid[8].Kp = 6.3;
//	pid[8].Ki = 0.05;
//	pid[8].Kd = 0;
//	pid[8].integral_max = 3000;
//	pid[8].output_max = 5000;
//	pid[8].err_dead  = 0;
//	pid[8].err_last  = 0;
////==================zh==================
//	pid[9].target = 0;
//	pid[9].Kp = 6.3;
//	pid[9].Ki = 0.05;
//	pid[9].Kd = 0;
//	pid[9].integral_max = 3000;
//	pid[9].output_max = 5000;
//	pid[9].err_dead  = 0;
//	pid[9].err_last  = 0;
////==================ym==================
//	pid[10].target = 0;
//	pid[10].Kp = 6;
//	pid[10].Ki = 0;
//	pid[10].Kd = 0;
//	pid[10].integral_max = 3000;
//	pid[10].output_max = 5000;
//	pid[10].err_dead  = 0;
//	pid[10].err_last  = 0;
////==================zm==================
//	pid[11].target = 0;
//	pid[11].Kp = 6;
//	pid[11].Ki = 0;
//	pid[11].Kd = 0;
//	pid[11].integral_max = 3000;
//	pid[11].output_max = 5000;
//	pid[11].err_dead  = 0;
//	pid[11].err_last  = 0;
////=============dpgs===============
//	pid[12].target = 0;
//	pid[12].Kp = 1;
//	pid[12].Ki = 0;
//	pid[12].Kd = 0;
//	pid[12].integral_max = 3000;
//	pid[12].output_max = 500;
//	pid[12].err_dead  = 100;
//	pid[12].err_last  = 0;
//}


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

