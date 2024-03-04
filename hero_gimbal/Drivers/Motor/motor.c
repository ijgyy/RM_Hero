#include "motor.h"



motor_t Motor[4];

extern can CAN;


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
				get_motor(&Motor[1],CAN.can1_rx_data);
		break;
		case 0x202:
				get_motor(&Motor[2],CAN.can1_rx_data);
		break;
		case 0x206:
				get_motor(&Motor[3],CAN.can1_rx_data);
		break;
	}
	  switch(CAN.can2_Rx.StdId)
	{
		case 0x205:
				get_motor(&Motor[0],CAN.can2_rx_data);
		break;
	}
}	

//void get_first_total_angle(uint8_t motor_num)
//{
//			Motor[motor_num].flag_total_angle++;
//		if(Motor[motor_num].flag_total_angle==1)
//		{
//			Motor[motor_num].total_angle_last = Motor[motor_num].total_angle;
//		}
//		else if(Motor[motor_num].flag_total_angle>2)
//		{
//			Motor[motor_num].flag_total_angle = 2;
//		}
//}

//void get_first_angle(uint8_t motor_num)
//{
//			Motor[motor_num].flag_angle++;
//		if(Motor[motor_num].flag_angle==1)
//		{
//			Motor[motor_num].angle_last       = Motor[motor_num].angle;
//			Motor[motor_num].first_angle      = Motor[motor_num].angle;
//		}
//		else if(Motor[motor_num].flag_angle>2)
//		{
//			Motor[motor_num].flag_angle = 2;
//		}
//}


//void motor_angle(uint8_t num)
//{

//	if(Motor[num].angle!=0)
//	{
//			 get_first_angle(num);
//			if(Motor[num].angle - Motor[num].angle_last > 4096)
//			{
//				Motor[num].round--;
//			}
//			else if (Motor[num].angle - Motor[num].angle_last < -4096)
//			{
//				Motor[num].round++;
//			}
//				Motor[num].total_angle = Motor[num].round*8191 + Motor[num].angle;
//				Motor[num].angle_last  = Motor[num].angle;

//			
////		 	get_first_total_angle(num);
////			if(Motor[num].total_angle - Motor[num].total_angle_last > 4096)
////			{
////				Motor[num].sj_round--;
////			}
////			else if (Motor[num].total_angle - Motor[num].total_angle_last < -4096)
////			{
////				Motor[num].sj_round++;
////			}
////			Motor[num].total_angle_last = Motor[num].total_angle;
//	}
//}




