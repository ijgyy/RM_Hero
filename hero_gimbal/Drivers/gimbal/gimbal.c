#include "gimbal.h"

gimbal Gimbal;

void GIMBAL_INITIALIZA(void)
{
		Gimbal.Flag.gim = CLOSE;
		Gimbal.Flag.fri = CLOSE;
		Gimbal.Flag.off = CLOSE;
		Gimbal.Flag.han = CLOSE;
		Gimbal.clear_cha_time = 0;
		RC_Ctl.last.w    = 0;
		RC_Ctl.last.s    = 0;
		RC_Ctl.last.a    = 0;
		RC_Ctl.last.d    = 0;
	  Gimbal.Flag.b    = 0;
		Gimbal.rc_time   = 0;
		Gimbal.gyro_time = 0;
	
		pid[0].kp = 15;                 //pitch_jd
		pid[0].ki = 0;
		pid[0].kd = 0;
		pid[0].err_dead     = 0.05;
	  pid[0].integral_max = 10000;
  	pid[0].output_max   = 20000;
	
		pid[1].kp = 280;                //pitch_sd
		pid[1].ki = 0.8;
		pid[1].kd = 0;
		pid[1].err_dead     = 0;
	  pid[1].integral_max = 10000;
  	pid[1].output_max   = 23000;
		
		pid[2].kp = 13;                 //yaw_jd
		pid[2].ki = 0;
		pid[2].kd = 0;
		pid[2].err_dead     = 0.05;
	  pid[2].integral_max = 10000;
  	pid[2].output_max   = 20000;
	
		pid[3].kp = 330;                 //yaw_sd
		pid[3].ki = 1;
		pid[3].kd = 0;
		pid[3].err_dead     = 0;
	  pid[3].integral_max = 10000;
  	pid[3].output_max   = 23000;
	
		pid[10].kp = 7;                 //ÓÒÄ¦²ÁÂÖ
		pid[10].ki = 0;
		pid[10].kd = 0;
		pid[10].err_dead     = 0;
	  pid[10].integral_max = 3000;
  	pid[10].output_max   = 16000;
	
		pid[11].kp = 7;                 //×óÄ¦²ÁÂÖ
		pid[11].ki = 0;
		pid[11].kd = 0;
		pid[11].err_dead     = 0;
	  pid[11].integral_max = 3000;
  	pid[11].output_max   = 16000;
}



void pitch_limit(int32_t num_s,int32_t num_x)
{
	if(Gimbal.pitch_target>num_s)
	{
		Gimbal.pitch_target = num_s;
	}
	if(Gimbal.pitch_target<(num_x))
	{
		Gimbal.pitch_target = (num_x);
	}					
}

void Offline_Processing(void)
{
	Gimbal.rc_time++;
	Gimbal.gyro_time++;
	if(Gimbal.rc_time >= RC_Office_value || Gimbal.gyro_time >= GYRO_Office_value)
	{
		Gimbal.Flag.gim = CLOSE;
		Gimbal.Flag.fri = CLOSE;
		Gimbal.Flag.off = CLOSE;
		Gimbal.Flag.han = CLOSE;
		Gimbal.clear_cha_time = 0;
		RC_Ctl.last.w    = 0;
		RC_Ctl.last.s    = 0;
		RC_Ctl.last.a    = 0;
		RC_Ctl.last.d    = 0;
	  Gimbal.Flag.b    = 0;
		Gimbal.rc_time   = 0;
		Gimbal.gyro_time = 0;
		Gimbal.yaw_target		  = gyro.total_angle;
		Gimbal.pitch_target		= gyro.Eular[0];
		
		if(Gimbal.rc_time > 500)
		{
			Gimbal.rc_time = 400;
		}
		if(Gimbal.gyro_time > 500)
		{
			Gimbal.gyro_time = 400;
		}
	}
}

void LowPassFilter(int16_t *filtered, int16_t *raw)
{
		float alpha = 0.2f;
    *filtered = (*filtered) * (1.0f - alpha) + (*raw) * alpha;
}

void NORMAL(void)
{
		LowPassFilter(&RC_Ctl.mouse.x_filter, &RC_Ctl.mouse.x);
		LowPassFilter(&RC_Ctl.mouse.y_filter, &RC_Ctl.mouse.y);
		Gimbal.yaw_target   -= (RC_Ctl.mouse.x_filter/80.0f);
		Gimbal.pitch_target -= (RC_Ctl.mouse.y_filter/100.0f);
}

void HANG_SHOT_EXECUTE(void)
{
	int8_t key_err_w;
	int8_t key_err_s;
	int8_t key_err_a;
	int8_t key_err_d;
	
	key_err_w = KEY_W - RC_Ctl.last.w;
  RC_Ctl.last.w = KEY_W;
	key_err_s = KEY_S - RC_Ctl.last.s;
  RC_Ctl.last.s = KEY_S;
	key_err_a = KEY_A - RC_Ctl.last.a;
  RC_Ctl.last.a = KEY_A;
	key_err_d = KEY_D - RC_Ctl.last.d;
  RC_Ctl.last.d = KEY_D;	
	
	if(key_err_w == -1)
	{
		Gimbal.pitch_target += 1;
	}
	if(key_err_s == -1)
	{
	  Gimbal.pitch_target -= 1;
	}
	if(key_err_a == -1)
	{
 	  Gimbal.yaw_target   += 1; 
	}
	if(key_err_d == -1)
	{
	  Gimbal.yaw_target   -= 1;
	}
}

void JUDEG_HANG_SHOT(void)
{
	int8_t key_err_z;
	int8_t key_err_e;
	
	key_err_z = KEY_Z - RC_Ctl.last.z;      
  RC_Ctl.last.z = KEY_Z;
	key_err_e = KEY_E - RC_Ctl.last.e;      
  RC_Ctl.last.e = KEY_E;

	if(key_err_z == -1)
	{
		Gimbal.Flag.han += 1;
	}
	else if(key_err_e == -1)
	{
		if(Gimbal.Flag.han %2 == OPEN)
		{
		 	Gimbal.Flag.han = CLOSE;
		}
	}
	if(Gimbal.Flag.han %2 == OPEN)      //µõÉäÄ£Ê½
	{
		HANG_SHOT_EXECUTE();
	}
}


void JUDEG_GIMBAL_ONLINE(void)
{
	if(Gimbal.Flag.b % 2 == 1)      
	{
			Gimbal.Flag.gim = OPEN;
			Gimbal.Flag.fri = OPEN;	
			Gimbal.Flag.off = OPEN;			
	}	
	else
	{
			Gimbal.Flag.gim = CLOSE;
			Gimbal.Flag.fri = CLOSE;
			Gimbal.Flag.off = CLOSE;
			Gimbal.yaw_target		  = gyro.total_angle;
		 	Gimbal.pitch_target		= gyro.Eular[0];
	}
}

void JUDGE_MODE_KEY(void)
{	
	JUDEG_GIMBAL_ONLINE();
	
	if(Gimbal.Flag.b %2 == 1)      
	{
		if(RC_Ctl.mouse.press_r == 1)
		{
			Gimbal.pitch_target  = gyro.Eular[0] + Vision.pitch;
			Gimbal.yaw_target    = gyro.total_angle + Vision.yaw;	
			Gimbal.Flag.sel = OPEN;
		}
		else
		{
		  NORMAL();
		  JUDEG_HANG_SHOT();
			Gimbal.Flag.sel = CLOSE;
		}
	}
}

void JUDGE_MODE_RC(void)
{	
				switch(RC_Ctl.rc.s1)
		{
			case 1:
				Gimbal.Flag.fri		  = CLOSE;
				Gimbal.Flag.gim 		= CLOSE;
				Gimbal.yaw_target		= gyro.total_angle;
			break;
			case 3:		
			case 2:			
				Gimbal.yaw_target   -= (RC_Ctl.rc.ch0*0.0005f);	
				Gimbal.pitch_target -= (RC_Ctl.rc.ch1*0.0005f);
				Gimbal.zm_target    = -6000;
				Gimbal.ym_target    =  6000;
				Gimbal.Flag.fri     = OPEN;
				Gimbal.Flag.gim     = OPEN;
			break;
			default:
				Gimbal.yaw_target   = OPEN;
				Gimbal.pitch_target = OPEN;
				Gimbal.Flag.fri     = CLOSE;
				Gimbal.Flag.gim     = CLOSE;
			break;
		}
}

void MODE_TOGGLE(void)
{
	int8_t key_err_b;
	
	key_err_b = KEY_B - RC_Ctl.last.b;
  RC_Ctl.last.b = KEY_B;

	if(key_err_b == -1)
	{
			Gimbal.Flag.b += 1;
	}
	
	if(Gimbal.Flag.b % 2 == 1)
	{
		JUDGE_MODE_KEY();		
	}
	else
	{
		JUDGE_MODE_RC();	
	}
}

void gimbal_control(void)
{
		MODE_TOGGLE();
		Offline_Processing();
		pitch_limit(40,-15);
		

		Gimbal.Microswitches = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6);
	
}

void gimbal_office(int16_t sz[],uint8_t Flag)
{
	if(Flag == CLOSE)
	{
		sz[0] = 0;
		sz[1] = 0;
		sz[2] = 0;
		sz[3] = 0;
	}
}

void gimbal_can1_tx(void)
{
	int16_t temp_pitch;

	CAN.can1_tx_data[0] = PID_realize(10,Gimbal.ym_target,Motor[1].Rospeed);  //ym
	CAN.can1_tx_data[1] = PID_realize(11,Gimbal.zm_target,Motor[2].Rospeed); //zm
	CAN.can1_tx_data[2] = 0;
	CAN.can1_tx_data[3] = 0;
	gimbal_office(CAN.can1_tx_data,Gimbal.Flag.fri);
	gimbal_office(CAN.can1_tx_data,Gimbal.Flag.gim);
	CAN1_Tx(CAN.can1_tx_data,0x200);

	CAN.can1_tx_data[0] = 0; 	
	temp_pitch          = PID_realize(0,Gimbal.pitch_target,gyro.Eular[0]); //pitch
	CAN.can1_tx_data[1] = PID_realize(1,temp_pitch,(gyro.Gyo[1]/10)); 
	CAN.can1_tx_data[2] = 0;
	CAN.can1_tx_data[3] = 0;
	gimbal_office(CAN.can1_tx_data,Gimbal.Flag.gim);
	CAN1_Tx(CAN.can1_tx_data,0x1FF);
}
//float p1,i1,d1;
//float p2,i2,d2;
//void pid_cs(void)
//{
//	p1 = 13;
//	i1 = 0;
//	d1 = 0;
//	p2 = 330;
//	i2 = 2;
//	d2 = 0;
//}

void gimbal_can2_tx(void)
{
	int16_t temp_yaw;

	temp_yaw        = PID_realize(2,Gimbal.yaw_target,gyro.total_angle); //yaw
	CAN.can2_tx_data[0] = PID_realize(3,temp_yaw,(gyro.Gyo[2]/10)); 	
	CAN.can2_tx_data[1] = 0; 
	CAN.can2_tx_data[2] = 0;
	CAN.can2_tx_data[3] = 0;
	gimbal_office(CAN.can2_tx_data,Gimbal.Flag.gim);
	CAN2_Tx(CAN.can2_tx_data,0x1FF);
	
	
	CAN.can2_tx_data[0] = RC_Ctl.rc.ch0;
	CAN.can2_tx_data[1] = RC_Ctl.rc.ch1; 
	CAN.can2_tx_data[2] = RC_Ctl.rc.ch2;
	CAN.can2_tx_data[3] = RC_Ctl.rc.ch3;
	gimbal_office(CAN.can2_tx_data,Gimbal.Flag.gim);
	CAN2_Tx(CAN.can2_tx_data,0x101);	
//=================================	
//	can2_rx_data_u8[0] = mouse.press_l;
//	can2_rx_data_u8[1] = mouse.press_r; 
//	can2_rx_data_u8[2] = key.v >> 8;
//	can2_rx_data_u8[3] = key.v;
//=================================	
	CAN.can2_rx_data_u8[0] = Gimbal.clear_cha_time;
	CAN.can2_rx_data_u8[1] = Gimbal.Flag.han; 
	CAN.can2_rx_data_u8[2] = RC_Ctl.key.key_code >> 8;
	CAN.can2_rx_data_u8[3] = RC_Ctl.key.key_code;
	CAN.can2_rx_data_u8[4] = Gimbal.Flag.b;
	CAN.can2_rx_data_u8[5] = Gimbal.Microswitches; 
	CAN.can2_rx_data_u8[6] = RC_Ctl.rc.s2;
	if(Gimbal.Flag.b %2 == 1)
	{
	  CAN.can2_rx_data_u8[7] = RC_Ctl.mouse.press_l;		
	}
	else if(Gimbal.Flag.b %2 == 0)
	{
   	CAN.can2_rx_data_u8[7] = RC_Ctl.rc.s1;
	}	
	gimbal_office(CAN.can2_tx_data,Gimbal.Flag.gim);
	CAN2_Tx_u8(CAN.can2_rx_data_u8,0x102);
	
}

void gimbal_TX(void)
{
	 gimbal_can2_tx();
	 gimbal_can1_tx();
}

void gimbal_whole(void)
{
	 get_total_angle();
	 gimbal_control();
	 gimbal_TX();
}

