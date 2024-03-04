#include "Referee_system.h"
#include <string.h>


//crc8 generator polynomial:G(x)=x8+x5+x4+1 
const unsigned char CRC8_INIT = 0xff; 
const unsigned char CRC8_TAB[256] = 
{ 
0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83, 0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41, 
0x9d, 0xc3, 0x21, 0x7f, 0xfc, 0xa2, 0x40, 0x1e, 0x5f, 0x01, 0xe3, 0xbd, 0x3e, 0x60, 0x82, 0xdc, 0x23, 
0x7d, 0x9f, 0xc1, 0x42, 0x1c, 0xfe, 0xa0, 0xe1, 0xbf, 0x5d, 0x03, 0x80, 0xde, 0x3c, 0x62, 0xbe, 0xe0, 
0x02, 0x5c, 0xdf, 0x81, 0x63, 0x3d, 0x7c, 0x22, 0xc0, 0x9e, 0x1d, 0x43, 0xa1, 0xff, 0x46, 0x18, 0xfa, 
0xa4, 0x27, 0x79, 0x9b, 0xc5, 0x84, 0xda, 0x38, 0x66, 0xe5, 0xbb, 0x59, 0x07, 0xdb, 0x85, 0x67, 
0x39, 0xba, 0xe4, 0x06, 0x58, 0x19, 0x47, 0xa5, 0xfb, 0x78, 0x26, 0xc4, 0x9a, 0x65, 0x3b, 0xd9, 0x87, 
0x04, 0x5a, 0xb8, 0xe6, 0xa7, 0xf9, 0x1b, 0x45, 0xc6, 0x98, 0x7a, 0x24, 0xf8, 0xa6, 0x44, 0x1a, 0x99, 
0xc7, 0x25, 0x7b, 0x3a, 0x64, 0x86, 0xd8, 0x5b, 0x05, 0xe7, 0xb9, 
0x8c, 0xd2, 0x30, 0x6e, 0xed, 0xb3, 0x51, 0x0f, 0x4e, 0x10, 0xf2, 0xac, 0x2f, 0x71, 0x93, 0xcd, 0x11, 
0x4f, 0xad, 0xf3, 0x70, 0x2e, 0xcc, 0x92, 0xd3, 0x8d, 0x6f, 0x31, 0xb2, 0xec, 0x0e, 0x50, 0xaf, 0xf1, 
0x13, 0x4d, 0xce, 0x90, 0x72, 0x2c, 0x6d, 0x33, 0xd1, 0x8f, 0x0c, 0x52, 0xb0, 0xee, 0x32, 0x6c, 0x8e, 
0xd0, 0x53, 0x0d, 0xef, 0xb1, 0xf0, 0xae, 0x4c, 0x12, 0x91, 0xcf, 0x2d, 0x73, 0xca, 0x94, 0x76, 0x28, 
0xab, 0xf5, 0x17, 0x49, 0x08, 0x56, 0xb4, 0xea, 0x69, 0x37, 0xd5, 0x8b, 0x57, 0x09, 0xeb, 0xb5, 
0x36, 0x68, 0x8a, 0xd4, 0x95, 0xcb, 0x29, 0x77, 0xf4, 0xaa, 0x48, 0x16, 0xe9, 0xb7, 0x55, 0x0b, 0x88, 
0xd6, 0x34, 0x6a, 0x2b, 0x75, 0x97, 0xc9, 0x4a, 0x14, 0xf6, 0xa8, 
0x74, 0x2a, 0xc8, 0x96, 0x15, 0x4b, 0xa9, 0xf7, 0xb6, 0xe8, 0x0a, 0x54, 0xd7, 0x89, 0x6b, 0x35, 
};
unsigned char Get_CRC8_Check_Sum(unsigned char *pchMessage,unsigned int dwLength,unsigned char ucCRC8)
{ 
unsigned char ucIndex; 
while (dwLength--)
{ 
ucIndex = ucCRC8^(*pchMessage++); 
ucCRC8 = CRC8_TAB[ucIndex]; 
} 
return(ucCRC8); 
}
/* 
** Descriptions: CRC8 Verify function 
** Input: Data to Verify,Stream length = Data + checksum 
** Output: True or False (CRC Verify Result)
*/ 
unsigned int Verify_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength)
{ 
unsigned char ucExpected = 0;
if ((pchMessage == 0) || (dwLength <= 2)) return 0; 
ucExpected = Get_CRC8_Check_Sum (pchMessage, dwLength-1, CRC8_INIT); 
return ( ucExpected == pchMessage[dwLength-1] ); 
} 
/* 
** Descriptions: append CRC8 to the end of data 
** Input: Data to CRC and append,Stream length = Data + checksum 
** Output: True or False (CRC Verify Result)
*/ 
void Append_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength)
{ 
unsigned char ucCRC = 0; 
if ((pchMessage == 0) || (dwLength <= 2)) return; 
ucCRC = Get_CRC8_Check_Sum ( (unsigned char *)pchMessage, dwLength-1, CRC8_INIT); 
pchMessage[dwLength-1] = ucCRC; 
}
uint16_t CRC_INIT = 0xffff; 
const uint16_t wCRC_Table[256] = 
{ 
0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf, 
0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7, 
0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e, 
0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876, 
0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd, 
0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5, 
0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c, 
0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974, 
0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb, 
0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3, 
0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72, 
0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9, 
0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1, 
0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738, 
0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70, 
0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7, 
0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff, 
0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036, 
0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e, 
0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5, 
0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd, 
0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134, 
0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c, 
0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3, 
0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb, 
0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232, 
0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a, 
0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1, 
0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9, 
0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330, 
0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};
/* 
** Descriptions: CRC16 checksum function 
** Input: Data to check,Stream length, initialized checksum 
** Output: CRC checksum 
*/ 
uint16_t Get_CRC16_Check_Sum(uint8_t *pchMessage,uint32_t dwLength,uint16_t wCRC)
{ 
uint8_t chData; 
if (pchMessage == NULL)
{ 
return 0xFFFF; 
} 
while(dwLength--)
{ 
chData = *pchMessage++;
(wCRC) = ((uint16_t)(wCRC) >> 8) ^ wCRC_Table[((uint16_t)(wCRC) ^ (uint16_t)(chData)) & 0x00ff]; 
} 
return wCRC; 
}
/* 
** Descriptions: CRC16 Verify function 
** Input: Data to Verify,Stream length = Data + checksum 
** Output: True or False (CRC Verify Result)
*/ 
uint32_t Verify_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength)
{ 
uint16_t wExpected = 0; 
if ((pchMessage == NULL) || (dwLength <= 2))
{ 
return 0; 
} 
wExpected = Get_CRC16_Check_Sum ( pchMessage, dwLength - 2, CRC_INIT); 
return ((wExpected & 0xff) == pchMessage[dwLength - 2] && ((wExpected >> 8) & 0xff) == pchMessage[dwLength - 1]);
}
/* 
** Descriptions: append CRC16 to the end of data 
** Input: Data to CRC and append,Stream length = Data + checksum 
** Output: True or False (CRC Verify Result)
*/ 
void Append_CRC16_Check_Sum(uint8_t * pchMessage,uint32_t dwLength)
{ 
uint16_t wCRC = 0; 
if ((pchMessage == NULL) || (dwLength <= 2))
{ 
return;
} 
wCRC = Get_CRC16_Check_Sum ( (uint8_t *)pchMessage, dwLength-2, CRC_INIT ); 
pchMessage[dwLength-2] = (uint8_t)(wCRC & 0x00ff); 
pchMessage[dwLength-1] = (uint8_t)((wCRC >> 8)& 0x00ff);
}






// 裁判系统信息
Referee_info_t 	REF = {
  .IF_REF_ONL = NO,
};


bool Judge_Data_TF = FALSE;//裁判数据是否可用,辅助函数调用
uint8_t Judge_Self_ID;//当前机器人的ID
uint16_t Judge_SelfClient_ID;//发送者机器人对应的客户端ID

/**************裁判系统数据辅助****************/
uint16_t ShootNum;//统计发弹量,0x0003触发一次则认为发射了一颗
bool Hurt_Data_Update = FALSE;//装甲板伤害数据是否更新,每受一次伤害置TRUE,然后立即置FALSE,给底盘闪避用

/**
  * @brief  读取裁判数据,loop中循环调用此函数来读取数据
  * @param  缓存数据
  * @retval 是否对正误判断做处理
  * @attention  在此判断帧头和CRC校验,无误再写入数据
  */

void Judege_read_data(uint8_t *ReadFromUsart )
{
  bool retval_tf = FALSE;//数据正确与否标志,每次调用读取裁判系统数据函数都先默认为错误
	
	uint16_t judge_length;//统计一帧数据长度 
	
	int CmdID = 0;//数据命令码解析	
	
	if(ReadFromUsart == NULL)
	{
		return;
	}
	else
	{
		memcpy(&REF.FrameHeader,ReadFromUsart,LEN_HEADER);   //储存帧头数据
	
		if(ReadFromUsart[SOF] == JUDGE_FRAME_HEADER)                   //判断帧头是否为0xA5
		{
			if(Verify_CRC8_Check_Sum( ReadFromUsart, LEN_HEADER ) == TRUE)  //帧头CRC校验
			{
				judge_length = ReadFromUsart[DATA_LENGTH] + LEN_HEADER + LEN_CMDID + LEN_TAIL;	//统计一帧数据长度,用于CR16校验
				
				if(Verify_CRC16_Check_Sum(ReadFromUsart,judge_length) == TRUE)//帧尾CRC16校验
				{
					retval_tf = TRUE;//数据可用
					
					CmdID = (ReadFromUsart[6] << 8 | ReadFromUsart[5]);//解析数据命令码,将数据拷贝到相应结构体中(注意拷贝数据的长度)
					
					switch(CmdID)
					{
						case ID_game_state:     //0x0001
								 memcpy(&REF.GameState, (ReadFromUsart + DATA), LEN_game_state);
								 break;
						
						case ID_game_result:    //0x0002
								 memcpy(&REF.GameResult, (ReadFromUsart + DATA), LEN_game_result);
								 break;
						
						case ID_game_robot_hp:    //0x0003
								 memcpy(&REF.GameRobotHP, (ReadFromUsart + DATA), LEN_game_robot_hp);
								 break;

						case ID_event_data:    //0x0101
								 memcpy(&REF.EventData, (ReadFromUsart + DATA), LEN_event_data);
								 break;
						
						case ID_supply_projectile_action:    //0x0102
								 memcpy(&REF.SupplyProjectileAction, (ReadFromUsart + DATA), LEN_supply_projectile_action);
								 break;
						
						case ID_supply_warm:    //0x0104
								 memcpy(&REF.RefereeWarning, (ReadFromUsart + DATA), LEN_supply_warm);
								 break;
						
						case ID_missile_shoot_time:    //0x0105
								 memcpy(&REF.missile_shoot_time, (ReadFromUsart + DATA), LEN_missile_shoot_time);
								 break;
						
						case ID_robot_status:    //0x0201
	               Determine_ID();
	///*1*/          Referee_Update(GameRobotStat_ID);
								 memcpy(&REF.GameRobotStat, (ReadFromUsart + DATA), LEN_robot_status);
								 break;
					
						case ID_power_heat_data:    //0x0202
	///*2*/          Referee_Update(PowerHeatData_ID);
								 memcpy(&REF.PowerHeatData, (ReadFromUsart + DATA), LEN_power_heat_data);
								 break;
						
						case ID_game_robot_pos:    //0x0203
								 memcpy(&REF.GameRobotPos, (ReadFromUsart + DATA), LEN_game_robot_pos);
								 break;
						
						case ID_buff_musk:    //0x0204
								 memcpy(&REF.Buff, (ReadFromUsart + DATA), LEN_buff_musk);
								 break;
						
						case ID_Air_support_time_data:    //0x0205
								 memcpy(&REF.AirRobotSupport, (ReadFromUsart + DATA), LEN_Air_support_time_data);
								 break;
						
						case ID_robot_hurt:      			//0x0206
								memcpy(&REF.RobotHurt, (ReadFromUsart + DATA), LEN_robot_hurt);
	//							if(REF.RobotHurt.hurt_type == 0)//非装甲板离线造成伤害
	//							{	
	//								Hurt_Data_Update = TRUE;
	//							}//装甲数据每更新一次则判定为受到一次伤害
								break;
						case ID_shoot_data:      			   //0x0207
	///*3*/          Referee_Update(ShootSpeed_ID);
								 memcpy(&REF.ShootData, (ReadFromUsart + DATA), LEN_shoot_data);
								 break;	
						
						case ID_Allowable_ammo_volume:   //0x0208
								 memcpy(&REF.bullet_remaining, (ReadFromUsart + DATA), LEN_Allowable_ammo_volume);
								 break;
						
						case ID_rfid_status:             //0x0209
								 memcpy(&REF.rfid_status, (ReadFromUsart+DATA), LEN_rfid_status);
								 break;
								
						case ID_dart_client_directive:   //0x020A
								 memcpy(&REF.dart_client,(ReadFromUsart+DATA),LEN_dart_client_directive);
								 break;
						
						case ID_Ground_robot_pos_data:   //0x020B
								 memcpy(&REF.ground_robot_position,(ReadFromUsart+DATA),LEN_Ground_robot_pos_data);
								 break;
						
						case ID_Radar_marker_data:       //0x020C
								 memcpy(&REF.radar_mark_data,(ReadFromUsart+DATA),LEN_Radar_marker_data);
								 break;
						
						case ID_player_minimap_receive_sentry_data:   //0x020D
								 memcpy(&REF.sentry_info,(ReadFromUsart+DATA),LEN_Sentinel_aut_dec_inf_syn);
								 break;
						
						case ID_player_minimap_receive_bot_message:       //0x020E
								 memcpy(&REF.radar_info,(ReadFromUsart+DATA),LEN_Radar_aut_dec_inf_syn);
								 break;							
					}
						
				}
			}
			//首地址加帧长度,指向CRC16下一字节,用来判断是否为0xA5,用来判断一个数据包是否有多帧数据
			if(*(ReadFromUsart + sizeof(xFrameHeader) + LEN_CMDID + REF.FrameHeader.DataLength + LEN_TAIL) == 0xA5)
			{
				//如果一个数据包出现了多帧数据,则再次读取
				Judege_read_data(ReadFromUsart + sizeof(xFrameHeader) + LEN_CMDID + REF.FrameHeader.DataLength + LEN_TAIL);
			}
		}
	}

	if (retval_tf == TRUE)
	{
		Judge_Data_TF = TRUE;//辅助函数用
	}
	else		//只要CRC16校验不通过就为FALSE
	{
		Judge_Data_TF = FALSE;//辅助函数用
	}	
}

//裁判系统发过来的数据暂存在这里
uint8_t  Judge_Buffer[ JUDGE_BUFFER_LEN ] = {0};


float REF_Report_CHAS_Power(void)   //4
{
  return REF.PowerHeatData.chassis_power;
}

uint16_t REF_Report_CHAS_Power_Buffer(void)   //2
{
  return REF.PowerHeatData.buffer_energy;
}  

//uint16_t REF_Report_Shooter_Heat(void)    //2
//{
//  return REF.PowerHeatData.shooter_17mm_1_barrel_heat;
//}
////------------ShootInfo----------------//
//float REF_Report_RealShootSpeed(void)
//{
//  return REF.ShootData.initial_speed;
//}
//uint8_t REF_Report_IF_shooter_output(void)
//{
//  return REF.GameRobotStat.power_management_shooter_output;
//}

////------------GameRobotStat------------//
//uint8_t REF_Report_robot_ID(void)   //1
//{
//  return REF.GameRobotStat.robot_id;
//}

//uint8_t REF_Report_Shoot_SpeedLimit(void)  //1
//{
//  return REF.GameRobotStat.shooter_id1_17mm_initial_launching_speed_limit;
//}

//uint16_t REF_Report_Shoot_CoolingLimit(void)  //2
//{
//  return REF.GameRobotStat.shooter_id1_17mm_barrel_heat_limit;
//}

//uint16_t REF_Report_Shoot_CoolingRate(void)  //2
//{
//  return REF.GameRobotStat.shooter_id1_17mm_barrel_cooling_value;
//}

uint16_t REF_Report_CHAS_MaxPower(void)  //2
{
  return REF.GameRobotStat.chassis_power_limit;
}

//void USART1_SendChar(uint8_t cData)
//{
//	while (USART_GetFlagStatus( USART1, USART_FLAG_TC ) == RESET);
//	
//	USART_SendData( USART1, cData );   
//}


void Determine_ID(void)//判断自己是哪个队伍
{
	if(REF.GameRobotStat.robot_id < 10)//本机器人的ID，红方
	{ 
		REF.ids.teammate_hero 		 	  = 1;
		REF.ids.teammate_engineer     = 2;
		REF.ids.teammate_infantry3 		= 3;
		REF.ids.teammate_infantry4 		= 4;
		REF.ids.teammate_infantry5 		= 5;
		REF.ids.teammate_plane		 		= 6;
		REF.ids.teammate_sentry				= 7;
		
		REF.ids.client_hero 		 			= 0x0101;
		REF.ids.client_engineer  			= 0x0102;
		REF.ids.client_infantry3 			= 0x0103;
		REF.ids.client_infantry4 			= 0x0104;
		REF.ids.client_infantry5 			= 0x0105;
		REF.ids.client_plane					= 0x0106;
		
		if     (REF.GameRobotStat.robot_id == hero_red)//不断刷新放置在比赛中更改颜色
			REF.self_client = REF.ids.client_hero;
		else if(REF.GameRobotStat.robot_id == engineer_red)
			REF.self_client = REF.ids.client_engineer;
		else if(REF.GameRobotStat.robot_id == infantry3_red)
			REF.self_client = REF.ids.client_infantry3;
		else if(REF.GameRobotStat.robot_id == infantry4_red)
			REF.self_client = REF.ids.client_infantry4;
		else if(REF.GameRobotStat.robot_id == infantry5_red)
			REF.self_client = REF.ids.client_infantry5;
		else if(REF.GameRobotStat.robot_id == plane_red)
			REF.self_client = REF.ids.client_plane;
	}
	else //蓝方
	{
		REF.ids.teammate_hero 		 		= 101;
		REF.ids.teammate_engineer  		= 102;
		REF.ids.teammate_infantry3 		= 103;
		REF.ids.teammate_infantry4 		= 104;
		REF.ids.teammate_infantry5 		= 105;
		REF.ids.teammate_plane		 		= 106;
		REF.ids.teammate_sentry				= 107;
		
		REF.ids.client_hero 		 			= 0x0165;
		REF.ids.client_engineer  			= 0x0166;
		REF.ids.client_infantry3 			= 0x0167;
		REF.ids.client_infantry4 			= 0x0168;
		REF.ids.client_infantry5 			= 0x0169;
		REF.ids.client_plane					= 0x016A;
		
		if     (REF.GameRobotStat.robot_id == hero_blue)
			REF.self_client = REF.ids.client_hero;
		else if(REF.GameRobotStat.robot_id == engineer_blue)
			REF.self_client = REF.ids.client_engineer;
		else if(REF.GameRobotStat.robot_id == infantry3_blue)
			REF.self_client = REF.ids.client_infantry3;
		else if(REF.GameRobotStat.robot_id == infantry4_blue)
			REF.self_client = REF.ids.client_infantry4;
		else if(REF.GameRobotStat.robot_id == infantry5_blue)
			REF.self_client = REF.ids.client_infantry5;
		else if(REF.GameRobotStat.robot_id == plane_blue)
			REF.self_client = REF.ids.client_plane;	
	}

}

ext_charstring_data_t tx_client_char;
uint8_t CliendTxBuffer[200];
uint8_t TeammateTxBuffer[200];

//************************************绘制象形*******************************/
ext_graphic_seven_data_t tx_client_graphic_figure;
void Figure_Graphic(graphic_data_struct_t* graphic,//最终要发出去的数组的数据段内容
									const char* name,
									uint32_t operate_tpye,
									uint32_t graphic_tpye,//绘制什么图像
									uint32_t layer,
									uint32_t color,
									uint32_t start_angle,
									uint32_t end_angle,
									uint32_t width,
									uint32_t start_x,
									uint32_t start_y,
									uint32_t radius,
									uint32_t end_x,
									uint32_t end_y)							
{
	for(char i=0;i<3;i++)
	{
		graphic->graphic_name[i] = name[i];	//字符索引
		graphic->operate_tpye = operate_tpye; //图层操作
		graphic->graphic_tpye = graphic_tpye;         //Char型
		graphic->layer        = layer;//都在第一层
		graphic->color        = color;//变色
		graphic->start_angle  = start_angle;
		graphic->end_angle    = end_angle;	
		graphic->width        = width;
		graphic->start_x      = start_x;
		graphic->start_y      = start_y;	
		graphic->radius = radius;
		graphic->end_x  = end_x;
		graphic->end_y  = end_y;
	}
}
int update_figure_flag;
void foresight(void)
{
	 Figure_Graphic(&tx_client_graphic_figure.clientData[0],"GL1",update_figure_flag,CIRCLE,1,GREEN,0,0,5,  200+160,1080*9/12, 20,0,0);
}
void Draw_Figure_bool()
{
	foresight();
}
void Client_graphic_Info_update(void)//七个图像一起更新
{
		//帧头
		tx_client_graphic_figure.txFrameHeader.SOF = JUDGE_FRAME_HEADER;
		tx_client_graphic_figure.txFrameHeader.DataLength = sizeof(ext_student_interactive_header_data_t) + sizeof(graphic_data_struct_t)*7;
		tx_client_graphic_figure.txFrameHeader.Seq = 0;//包序号
		memcpy(CliendTxBuffer,&tx_client_graphic_figure.txFrameHeader,sizeof(xFrameHeader));
		Append_CRC8_Check_Sum(CliendTxBuffer, sizeof(xFrameHeader));//头校验

		//命令码
		tx_client_graphic_figure.CmdID = ID_robot_interactive_header_data;

		//数据段头结构
		tx_client_graphic_figure.dataFrameHeader.data_cmd_id = INTERACT_ID_draw_seven_graphic;
		tx_client_graphic_figure.dataFrameHeader.send_ID     = REF.GameRobotStat.robot_id;
		tx_client_graphic_figure.dataFrameHeader.receiver_ID = REF.self_client;
	
		//数据段
		Draw_Figure_bool();
		memcpy(CliendTxBuffer+LEN_FRAME_HEAD, (uint8_t*)&tx_client_graphic_figure.CmdID, LEN_CMD_ID+tx_client_graphic_figure.txFrameHeader.DataLength);//加上命令码长度2

		//帧尾
		Append_CRC16_Check_Sum(CliendTxBuffer,sizeof(tx_client_graphic_figure));
		
    for(int i = 0; i < sizeof(tx_client_graphic_figure); i++)
		{
//      USART1_SendChar(CliendTxBuffer[i]);
    }

}

