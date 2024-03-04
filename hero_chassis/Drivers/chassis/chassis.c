#include "chassis.h"

extern PID pid[14];
extern motor_t Motor[6];
extern can CAN;

chassis Chassis;

void CHASSIS_INITIALIZA(void)
{
	Chassis.Flag.cha      	= CLOSE;
	Chassis.Flag.Han			 	= CLOSE;
	Chassis.Flag.Sma      	= CLOSE;
	Chassis.Flag.tcf			 	= CLOSE;
	Chassis.Flag.state      = 0;
	Chassis.Flag.off        = CLOSE;
	Chassis.Pluck.flag      = CLOSE;
	
	pid[4].kp = 0.2;              //bd_jd
	pid[4].ki = 0;
	pid[4].kd = 0;
	pid[4].err_dead = 0;
	pid[4].integral_max = 3000;
	pid[4].output_max = 10000;
	
	pid[5].kp = 0.6;              //bd_sd
	pid[5].ki = 0;
	pid[5].kd = 0;
	pid[5].err_dead = 0;
	pid[5].integral_max = 3000;
	pid[5].output_max = 16000;
	
	pid[6].kp = 9;              //zq
	pid[6].ki = 0;
	pid[6].kd = 0;
	pid[6].err_dead = 0;
	pid[6].integral_max = 3000;
	pid[6].output_max = 5000;
	
	pid[7].kp = 9;              //yq
	pid[7].ki = 0;
	pid[7].kd = 0;
	pid[7].err_dead = 0;
	pid[7].integral_max = 3000;
	pid[7].output_max = 5000;
	
	pid[8].kp = 9;              //zh
	pid[8].ki = 0;
	pid[8].kd = 0;
	pid[8].err_dead = 0;
	pid[8].integral_max = 3000;
	pid[8].output_max = 5000;
	
	pid[9].kp = 9;              //yh
	pid[9].ki = 0;
	pid[9].kd = 0;
	pid[9].err_dead = 0;
	pid[9].integral_max = 3000;
	pid[9].output_max = 5000;
	
	pid[12].kp = 4;              //µ×ÅÌ¸úËæ
	pid[12].ki = 0;
	pid[12].kd = 0;
	pid[12].err_dead = 10;
	pid[12].integral_max = 3000;
	pid[12].output_max = 5000;
	
	pid[13].kp = 1;              //µ×ÅÌ¸úËæ
	pid[13].ki = 0;
	pid[13].kd = 0;
	pid[13].err_dead = 0;
	pid[13].integral_max = 3000;
	pid[13].output_max = 5000;
}

uint16_t max_power_limit = 40;
float chassis_max_power = 0;
float input_power = 0;		 // input power from battery (referee system)
float initial_give_power[4]; // initial power from PID calculation
float initial_total_power = 0;
float scaled_give_power[4];

float chassis_power = 0.0f;
float chassis_power_buffer = 0.0f;

float toque_coefficient = 1.99688994e-6f; // (20/16384)*(0.3)*(187/3591)/9.55
float a = 1.23e-07;						 // k1
float k2 = 1.453e-07;					 // k2
float constant = 4.081f;
float Out_Max = 12000;

void Chassis_Power_Control(void)
{
	
	chassis_max_power    = REF_Report_CHAS_MaxPower();
	chassis_power 		   = REF_Report_CHAS_Power();	
	chassis_power_buffer = REF_Report_CHAS_Power_Buffer();
	
	PID_realize(13,30,chassis_power_buffer);
	input_power = max_power_limit - pid[13].output;
	
	for (uint8_t i = 0; i < 4; i++) // first get all the initial motor power and total motor power
	{
		initial_give_power[i] = pid[i].output * toque_coefficient * Motor[i].Rospeed + k2 * Motor[i].Rospeed * Motor[i].Rospeed +									
														a * pid[i].output * pid[i].output + constant;

		if (initial_give_power < 0) // negative power not included (transitory)
			continue;
		initial_total_power += initial_give_power[i];
	}
	
	if (initial_total_power > chassis_max_power) // determine if larger than max power
	{
		float power_scale = chassis_max_power / initial_total_power;
		for (uint8_t i = 0; i < 4; i++)
		{
			scaled_give_power[i] = initial_give_power[i] * power_scale; // get scaled power
			if (scaled_give_power[i] < 0)
			{
				continue;
			}
			
			float b = toque_coefficient * Motor[i].Rospeed;
			float c = k2 * Motor[i].Rospeed * Motor[i].Rospeed - scaled_give_power[i] + constant;

			if (pid[i].output > 0) // Selection of the calculation formula according to the direction of the original moment
			{
				float temp = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
				if (temp > Out_Max)
				{
					pid[i].output = Out_Max;
				}
				else
					pid[i].output = temp;
			}
			else
			{
				float temp = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
				if (temp < -Out_Max)
				{
					pid[i].output = -Out_Max;
				}
				else
					pid[i].output = temp;
			}
		}
	}
}	


		
void SPEED_CONTROL(void)
{
	Chassis.Speed_Multiplier = 3;
	int16_t res1 = 3000;
	int16_t res2 = 5000;
	int16_t Average_Speed = (Motor[0].Rospeed + Motor[1].Rospeed + Motor[2].Rospeed + Motor[3].Rospeed)/4;
	if(KEY_SHIFT == 1)
	{
	  Chassis.Speed_Multiplier = 10;
	}
	else
	{
		if(Average_Speed>res1 || Average_Speed<-res1)
		{
			 Chassis.Speed_Multiplier = 5;
		}
		else if(Average_Speed>res2 || Average_Speed<-res2)
		{
			 Chassis.Speed_Multiplier = 7;
		}
	}
}

void MOVE_CONTROL(void)
{
	if(KEY_W == 1)
	{
		Chassis.Vy =  -1000*Chassis.Speed_Multiplier;
	}
	else if(KEY_S == 1)
	{
		Chassis.Vy =   1000*Chassis.Speed_Multiplier;
	}
	else 
	{
		Chassis.Vy = 0;	
	}
	if(KEY_W == 1 && KEY_S == 1)
	{
		Chassis.Vy = 0;
	}

	if(KEY_A == 1)
	{
		Chassis.Vx =   -1000*Chassis.Speed_Multiplier;
	}
	else if(KEY_D == 1)
	{
		Chassis.Vx =    1000*Chassis.Speed_Multiplier;
	}
	else 
	{
		Chassis.Vx = 0;	
	}
	if(KEY_A == 1 && KEY_D == 1)
	{
		Chassis.Vx = 0;
	}
}



void JUDEG_CHASSIS_ONLINE(void)
{
	if(Chassis.Flag.b %2 == 1)      
	{
			Chassis.Flag.cha   = OPEN;
			Chassis.Pluck.flag = OPEN;	
			Chassis.Flag.off   = OPEN;		
	}	
	else
	{
			Chassis.Flag.cha   = CLOSE;
			Chassis.Pluck.flag = CLOSE;
			Chassis.Flag.off   = CLOSE;		
	}
}

void HANG_SHOT_EXECUTE(void)
{
	Chassis.Motor_zq_target = 0;
	Chassis.Motor_yq_target = 0;
	Chassis.Motor_yh_target = 0;
	Chassis.Motor_zh_target = 0;
}

void SMALL_SPIN_TOPS(void)
{
	Chassis.W = 2000;
	Chassis.Vy_g =  Chassis.Vx*sin((Motor[5].err/8191.f)*2*3.1415926f)-Chassis.Vy*cos((Motor[5].err/8191.f)*2*3.1415926f);
	Chassis.Vx_g = -Chassis.Vx*cos((Motor[5].err/8191.f)*2*3.1415926f)-Chassis.Vy*sin((Motor[5].err/8191.f)*2*3.1415926f);
	Chassis.Motor_zq_target =  (Chassis.Vy_g-Chassis.Vx_g)+Chassis.W;
	Chassis.Motor_yq_target = -(Chassis.Vy_g+Chassis.Vx_g)+Chassis.W;
	Chassis.Motor_yh_target = -(Chassis.Vy_g-Chassis.Vx_g)+Chassis.W;
	Chassis.Motor_zh_target =  (Chassis.Vy_g+Chassis.Vx_g)+Chassis.W;
}

void CHASSIS_FOLLOW(void)
{
	Chassis.W = 0;
	Chassis.W = PID_realize(12,0,Motor[5].err);
	Chassis.Motor_zq_target = -(Chassis.Vy-Chassis.Vx)+Chassis.W;
	Chassis.Motor_yq_target =  (Chassis.Vy+Chassis.Vx)+Chassis.W;
	Chassis.Motor_yh_target =  (Chassis.Vy-Chassis.Vx)+Chassis.W;
	Chassis.Motor_zh_target = -(Chassis.Vy+Chassis.Vx)+Chassis.W;
}

void PLUCK(void)
{
	if(RC_Ctl.mouse.press_l == OPEN)
	{
		Chassis.Pluck.cnt++;
		if(Chassis.Pluck.cnt>5)
		{
			Chassis.Pluck.cnt = 2;
		}
		if(Chassis.Pluck.cnt == 1)
		{
			Chassis.Motor_bd_target = -8191*6;
			Chassis.Pluck.flag = OPEN;
		}	
	}
	else if(KEY_X == OPEN)
	{
			Chassis.Motor_bd_target =  8191*2;
			Chassis.Pluck.flag = OPEN;
	}
	else if(RC_Ctl.mouse.press_l == CLOSE)
	{
			Motor[4].round = 0;
			Chassis.Motor_bd_target = 0;
			Chassis.Pluck.cnt = 0;
	}
}



void KEY_CONTROL(void)
{
	int8_t key_err_z;
//	int8_t key_err_q;
	int8_t key_err_e;
	
	key_err_z = KEY_Z - RC_Ctl.last.z;      
	RC_Ctl.last.z = KEY_Z;
	key_err_e = KEY_E - RC_Ctl.last.e;      
	RC_Ctl.last.e = KEY_E;

	if(key_err_z == -1)
	{
		Chassis.Flag.Han = 1;
		Chassis.Flag.Sma = 0;		
	}
	if(key_err_e == -1)
	{
		Chassis.Flag.Sma += 1;
	}
	
	if(Chassis.Flag.Han  %2 ==  1)      //µõÉäÄ£Ê½
	{
		HANG_SHOT_EXECUTE();
		Chassis.Flag.state = 1;
	}
	else if(Chassis.Flag.Sma %2 == 1)      //Ð¡ÍÓÂÝÄ£Ê½
	{
		SMALL_SPIN_TOPS();
		Chassis.Flag.state = 3;
	}
	else
	{
		CHASSIS_FOLLOW();
	}
}



void JUDEG_MODE_KEY(void)
{
	JUDEG_CHASSIS_ONLINE();	
		
	if(Chassis.Flag.b %2 == 1)      
	{
		SPEED_CONTROL();
		MOVE_CONTROL();
	  KEY_CONTROL();
		PLUCK();
	}
}



void JUDGE_MODE_RC(void)
{
	uint8_t num = 8;
	Chassis.Vx =  (RC_Ctl.rc.ch2/660.0f)*num*1000;
	Chassis.Vy = -(RC_Ctl.rc.ch3/660.0f)*num*1000;
	Chassis.Flag.cha = 1;
	 	switch(RC_Ctl.rc.s1)
	{
		case 1:
			Chassis.Flag.cha   = CLOSE;
		  Chassis.Pluck.flag = CLOSE;
			Chassis.Flag.off   = CLOSE;
//			Chassis.Motor_bd_target = 0;
		break;
		case 3:
			Chassis.Flag.cha 	 = OPEN;
		  Chassis.Pluck.flag = OPEN;
			Chassis.Flag.off   = OPEN;
			 switch(RC_Ctl.rc.s2)
			 {
				 case 1:
						Chassis.W = 0;
						Chassis.W = PID_realize(12,0,Motor[5].err);
						Chassis.Motor_zq_target = -(Chassis.Vy-Chassis.Vx)+Chassis.W;
						Chassis.Motor_yq_target =  (Chassis.Vy+Chassis.Vx)+Chassis.W;
						Chassis.Motor_yh_target =  (Chassis.Vy-Chassis.Vx)+Chassis.W;
						Chassis.Motor_zh_target = -(Chassis.Vy+Chassis.Vx)+Chassis.W;
				 break;
				 case 3:
					  Chassis.W = 0;
						Chassis.Motor_zq_target = -(Chassis.Vy-Chassis.Vx)+Chassis.W;
						Chassis.Motor_yq_target =  (Chassis.Vy+Chassis.Vx)+Chassis.W;
						Chassis.Motor_yh_target =  (Chassis.Vy-Chassis.Vx)+Chassis.W;
						Chassis.Motor_zh_target = -(Chassis.Vy+Chassis.Vx)+Chassis.W;
				 break;
				 case 2:
						Chassis.W = 2000;
						Chassis.Vy_g =  Chassis.Vx*sin((Motor[5].err/8191.f)*2*3.1415926f)-Chassis.Vy*cos((Motor[5].err/8191.f)*2*3.1415926f);
						Chassis.Vx_g = -Chassis.Vx*cos((Motor[5].err/8191.f)*2*3.1415926f)-Chassis.Vy*sin((Motor[5].err/8191.f)*2*3.1415926f);
						Chassis.Motor_zq_target =  (Chassis.Vy_g-Chassis.Vx_g)+Chassis.W;
						Chassis.Motor_yq_target = -(Chassis.Vy_g+Chassis.Vx_g)+Chassis.W;
						Chassis.Motor_yh_target = -(Chassis.Vy_g-Chassis.Vx_g)+Chassis.W;
						Chassis.Motor_zh_target =  (Chassis.Vy_g+Chassis.Vx_g)+Chassis.W;
				break;
			 }
		break;
		case 2:
			Chassis.Flag.cha 	 = OPEN;
		  Chassis.Pluck.flag = OPEN;
			Chassis.Flag.off   = OPEN;
				switch(RC_Ctl.rc.s2)
				{
					case RC_SW_UP:
						Chassis.Pluck.cnt++;
						if(Chassis.Pluck.cnt>5)
						{
							Chassis.Pluck.cnt = 2;
						}
						if(Chassis.Pluck.cnt == 1)
							{
								Chassis.Motor_bd_target = -8191*6;
								Chassis.Pluck.flag = OPEN;
							}	
					break;
					case RC_SW_MID:
						Motor[4].round = 0;
				  	Chassis.Motor_bd_target = 0;
						Chassis.Pluck.cnt = 0;
					break;
					case RC_SW_DOWN:
						Chassis.Motor_bd_target =  8191*2;
					  Chassis.Pluck.flag = OPEN;
					break;
					default:
						Chassis.Pluck.flag = CLOSE;
					break;
				}
				if(Chassis.Microswitches.err == 1)
				{
					Chassis.Pluck.flag = CLOSE;
				}
		break;
		default:
				Chassis.Flag.cha	 = CLOSE;
				Chassis.Pluck.flag = CLOSE;
		    Chassis.W = 0;
		break;		
	}
}

void CHASSIS_OFFICE(void)
{
	Chassis.time++;
	if(Chassis.time > CHASSIS_OFFICE_VALUE)
	{
		Chassis.Flag.cha      	= CLOSE;
		Chassis.Flag.Han			 	= CLOSE;
		Chassis.Flag.off        = CLOSE;
		Chassis.Pluck.flag      = CLOSE;
		Chassis.Flag.Sma      	= CLOSE;
		Chassis.Flag.tcf			 	= OPEN;
		Chassis.Flag.state      = 2;
	}
}

void MODE_TOGGLE(void)
{
	if(Chassis.Flag.b %2 == 1)
	{
		JUDEG_MODE_KEY();		
	}
	else
	{
		JUDGE_MODE_RC();		
	}
}

void chassis_control(void)
{	
		 Chassis.Microswitches.err  = Chassis.Microswitches.now - Chassis.Microswitches.last;
		 Chassis.Microswitches.last =  Chassis.Microswitches.now;

		 MODE_TOGGLE();
//		 Chassis_Power_Control();
		 CHASSIS_OFFICE();
			

}


void office_control(int16_t sz[],uint8_t Flag)
{
	if(Flag == CLOSE)
	{
		sz[0] = 0;
		sz[1] = 0;
		sz[2] = 0;
		sz[3] = 0;
	}
}
  

void chassis_can1_tx(void)
{
	int16_t temp_bd;
	
	CAN.can1_tx_data[0] = PID_realize(6,Chassis.Motor_zq_target,Motor[0].Rospeed);
	CAN.can1_tx_data[1] = PID_realize(7,Chassis.Motor_yq_target,Motor[1].Rospeed); 
	CAN.can1_tx_data[2] = PID_realize(8,Chassis.Motor_yh_target,Motor[2].Rospeed);
	CAN.can1_tx_data[3] = PID_realize(9,Chassis.Motor_zh_target,Motor[3].Rospeed);
	office_control(CAN.can1_tx_data,Chassis.Flag.cha);
	office_control(CAN.can1_tx_data,Chassis.Flag.off);
	CAN1_Tx(CAN.can1_tx_data,0x200);

  CAN.can1_tx_data[0] = 0;
	CAN.can1_tx_data[1] = 0;
	temp_bd = PID_realize(4,Chassis.Motor_bd_target,Motor[4].total_angle);
	CAN.can1_tx_data[2] = PID_realize(5,temp_bd,Motor[4].Rospeed);
	CAN.can1_tx_data[3] = 0;
	office_control(CAN.can1_tx_data,Chassis.Pluck.flag);
	office_control(CAN.can1_tx_data,Chassis.Flag.off);
	CAN1_Tx(CAN.can1_tx_data,0x1FF);
	
}


void chassis_whole(void)
{
	motor_angle(5);
	motor_angle(4);
	chassis_control();
	chassis_can1_tx();
//	SendWave();
}



