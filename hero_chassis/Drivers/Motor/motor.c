#include "motor.h"



motor_t Motor[6];
float err;
float Yaw;
extern can CAN;
extern rc_crl_t RC_Ctl;
extern chassis Chassis;


void get_motor(motor_t *ptr,uint8_t can_rx_data[])                                    
{                                                                   
	ptr->angle 				= (can_rx_data[0]<<8 | can_rx_data[1]);																
	ptr->Rospeed 			= (can_rx_data[2]<<8 | can_rx_data[3]);  
	ptr->Torque 			= (can_rx_data[4]<<8 | can_rx_data[5]);  
	ptr->temperature 	= (can_rx_data[6]);                
}

void MSP_motor(void)
{ 
		switch(CAN.can1_Rx.StdId)
	{
		case 0x201:
				get_motor(&Motor[0],CAN.can1_rx_data);
		break;
		case 0x202:
				get_motor(&Motor[1],CAN.can1_rx_data);
		break;
		case 0x203:
				get_motor(&Motor[2],CAN.can1_rx_data);
		break;
		case 0x204:
				get_motor(&Motor[3],CAN.can1_rx_data);
		break;
		case 0x207:
				get_motor(&Motor[4],CAN.can1_rx_data);
		break;
	}
		switch(CAN.can2_Rx.StdId)
	{
		case 0x205:
				get_motor(&Motor[5],CAN.can2_rx_data);
		break;
		case 0x101:
				RC_Ctl.rc.ch0 							= (CAN.can2_rx_data[0]<<8 | CAN.can2_rx_data[1]);
				RC_Ctl.rc.ch1  			 			 	= (CAN.can2_rx_data[2]<<8 | CAN.can2_rx_data[3]);
				RC_Ctl.rc.ch2 							= (CAN.can2_rx_data[4]<<8 | CAN.can2_rx_data[5]);
				RC_Ctl.rc.ch3 							= (CAN.can2_rx_data[6]<<8 | CAN.can2_rx_data[7]);
		break;
		case 0x102:
				Chassis.time                = (CAN.can2_rx_data[0]);
				Chassis.Flag.Han            = (CAN.can2_rx_data[1]);
				RC_Ctl.key.key_code 				= (CAN.can2_rx_data[2]<<8 | CAN.can2_rx_data[3]);
				Chassis.Flag.b 					  	= (CAN.can2_rx_data[4]);
				Chassis.Microswitches.now		= (CAN.can2_rx_data[5]);
				RC_Ctl.rc.s2 								= (CAN.can2_rx_data[6]);
				if(Chassis.Flag.b %2 == 1)
				{
			  	RC_Ctl.mouse.press_l 				= (CAN.can2_rx_data[7]);
				  RC_Ctl.rc.s1 								= 0;					
				}
				else if(Chassis.Flag.b %2 == 0)
				{
				  RC_Ctl.rc.s1 								= (CAN.can2_rx_data[7]);
					RC_Ctl.mouse.press_l        = 0;
				}
		break;	
	}
}	


void get_first_last(uint8_t motor_num)
{
			Motor[motor_num].flag_angle++;
		if(Motor[motor_num].flag_angle==1)
		{
			Motor[motor_num].angle_last    = Motor[motor_num].angle;
			Motor[motor_num].Pos_dir_angle = Motor[motor_num].angle;
		}
		else if(Motor[motor_num].flag_angle>2)
		{
			Motor[motor_num].flag_angle = 2;
		}
		
}


void motor_angle(uint8_t motor_num)
{
	if(Motor[motor_num].angle!=0)
	{
			 get_first_last(motor_num);
			if(Motor[motor_num].angle - Motor[motor_num].angle_last > 4096)
			{
				Motor[motor_num].round--;
			}
			else if (Motor[motor_num].angle - Motor[motor_num].angle_last < -4096)
			{
				Motor[motor_num].round++;
			}
			Motor[motor_num].total_angle =(Motor[motor_num].round) * 8191 + Motor[motor_num].angle;
			Motor[motor_num].angle_last = Motor[motor_num].angle;
//			
//			if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5) == 0)
//			{
//				Motor[5].Pos_dir_angle = Motor[5].angle;
//			}
			Motor[5].err = (Motor[5].total_angle - Motor[5].Pos_dir_angle); 
			if(Motor[5].err > 8190)
			{
				Motor[5].err -= 8190;
			}
			else if(Motor[5].err < -8190)
			{
				Motor[5].err += 8190;
			}
	}
}


