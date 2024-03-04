#ifndef _REFEREE_SYSTEM_H
#define _REFEREE_SYSTEM_H

#include "stm32f4xx.h"	
#include <stdbool.h>


#define JUDGE_BUFFER_LEN 200              //缓存区长度

#define JUDGE_FRAME_HEADER  0xA5           //帧头

#define    JUDGE_DATA_ERROR      0
#define    JUDGE_DATA_CORRECT    1     //裁判系统可以不可以用

#define shoot_speed_limit 20;

#define TRUE 1
#define FALSE 0

#define BLUE 0
#define RED 1

//长度根据协议定义,数据段长度为n需要根据帧头第二字节来获取
#define    LEN_HEADER    5        //帧头长
#define    LEN_CMDID     2        //命令码长度
#define    LEN_TAIL      2	      //帧尾CRC16

/* RFID卡类型 */
#define    CARD_ATTACK        ((uint8_t)0x00)
#define    CARD_PROTECT       ((uint8_t)0x01)
#define    CARD_BLOOD_RED     ((uint8_t)0x02)
#define    CARD_BLOOD_BLUE    ((uint8_t)0x03)
#define    CARD_HEAL_RED      ((uint8_t)0x04)
#define    CARD_HEAL_BLUE     ((uint8_t)0x05)
#define    CARD_COLD_RED      ((uint8_t)0x06)
#define    CARD_COLD_BLUE     ((uint8_t)0x07)
#define    CARD_FORT          ((uint8_t)0x08)


//#define    LEN_HEADER    5        //帧头长
//#define    LEN_CMDID     2        //命令码长度
//#define    LEN_TAIL      2	      //帧尾CRC16

/*心跳*/
bool Judge_IF_Refer_Normal(void);
#define     IF_REFER_NORMAL      Judge_IF_Refer_Normal()

#define YES true
#define NO  false

typedef enum  
{
	FRAME_HEADER         = 0,
	CMD_ID               = 5,
	DATA                 = 7,
	
}JudgeFrameOffset;

typedef enum
{
	SOF          = 0,//起始位
	DATA_LENGTH  = 1,//帧内数据长度,根据这个来获取数据长度
	SEQ          = 3,//包序号
	CRC8         = 4 //CRC8	
}	FrameHeaderOffset;

typedef enum
{
	ID_game_state       									= 0x0001,               //比赛状态数据   3Hz
	ID_game_result      									= 0x0002,               //比赛结果数据   结束
	ID_game_robot_hp    									= 0x0003, 						  //机器人血量数据 3Hz

	ID_event_data 												= 0x0101,            	  //场地事件数据   3Hz
	ID_supply_projectile_action						= 0x0102,							  //补给站动作标识数据   补给站弹丸释放时触发发送
	ID_supply_warm 												= 0x0104,						    //裁判系统警告数据     己方判罚/判负时触发发送
	ID_missile_shoot_time 								= 0x0105,               //飞镖发射时间数据     3Hz
	
	ID_robot_status    								    = 0x0201,							  //机器人性能体系数据   10Hz
	ID_power_heat_data    								= 0x0202,							  //实时功率热量数据     50Hz
	ID_game_robot_pos        							= 0x0203,							  //机器人位置数据       10Hz
	ID_buff_musk													= 0x0204,							  //机器人增益数据       3Hz
	ID_Air_support_time_data							= 0x0205,							  //空中支援时间数据     10Hz
	ID_robot_hurt													= 0x0206,								//伤害状态数据         伤害发生后发送
	ID_shoot_data													= 0x0207,								//实时射击数据         弹丸发射后发送
	ID_Allowable_ammo_volume    					= 0x0208,								//允许发弹量           10Hz
	ID_rfid_status												= 0x0209,								//机器人RFID状态       3Hz
	ID_dart_client_directive    					= 0x020A,								//飞镖机器人客户端指令数据, 10Hz
	ID_Ground_robot_pos_data    					= 0x020B,               //地面机器人位置数据，固定 1Hz 频率发送
  ID_Radar_marker_data    							= 0x020C,               //雷达标记进度数据，固定 1Hz 频率发送
	ID_Sentinel_aut_dec_inf_syn						= 0x020D,               //哨兵自主决策相关信息同步，固定 1Hz 频率发送
	ID_Radar_aut_dec_inf_syn							= 0x020E,               //雷达自主决策信息同步，固定1Hz 频率发送
																														
	ID_robot_interactive_header_data			= 0x0301,								//机器人交互数据，发送方触发发送，频率上限为 10Hz
	ID_controller_interactive_header_data = 0x0302,								//自定义控制器交互数据接口，通过——客户端触发——发送 30Hz
	ID_map_interactive_header_data        = 0x0303,								//选手端小地图交互数据，——触发发送——
	ID_keyboard_information               = 0x0304,								//键鼠遥控数据，固定 30Hz 频率发送
	ID_map_interactive_Receive_radar_data = 0x0305,               //选手端小地图接收雷达数据，频率上限为10Hz
	ID_controller_interacts_player        = 0x0306,               //自定义控制器与选手端交互数据，发送方触发发送，频率上限为 30Hz
	ID_player_minimap_receive_sentry_data = 0x0307,               //选手端小地图接收哨兵数据，频率上限为1Hz
	ID_player_minimap_receive_bot_message = 0x0308                //选手端小地图接收机器人消息，频率上限为 3Hz
	
}CmdID;

typedef enum
{
	/* Std */
	LEN_FRAME_HEAD 	                	 =  5,	// 帧头长度
	LEN_CMD_ID 		                  	 =  2,	// 命令码长度
	LEN_FRAME_TAIL 	                	 =  2,	// 帧尾CRC16
	/* Ext */  

	LEN_game_state       							 =  11,	//0x0001
	LEN_game_result       						 =  1,	//0x0002
	LEN_game_robot_hp       	 				 =  32,	//0x0003  
	
	LEN_event_data  									 =  4,	//0x0101 
	LEN_supply_projectile_action       =  4,	//0x0102
	LEN_supply_warm       						 =  2,  //0x0104
	LEN_missile_shoot_time      			 =	1,  //0x0105
	
	LEN_robot_status    						   = 27,	//0x0201 
	LEN_power_heat_data   						 = 16,	//0x0202
	LEN_game_robot_pos        				 = 16,	//0x0203
	LEN_buff_musk        						   =  1,	//0x0204
	LEN_Air_support_time_data        	 =  1,	//0x0205
	LEN_robot_hurt        						 =  1,	//0x0206
	LEN_shoot_data       							 =  7,	//0x0207
	LEN_Allowable_ammo_volume          =  6,  //0x0208
	LEN_rfid_status             			 =  4,  //0x0209  
	LEN_dart_client_directive        	 =  6,  //0x020A
	LEN_Ground_robot_pos_data          =  40, //0x020B 
	LEN_Radar_marker_data         		 =  6,  //0x020C 	
	LEN_Sentinel_aut_dec_inf_syn       =  4,  //0x020D 
	LEN_Radar_aut_dec_inf_syn          =  1,  //0x020E 
	// 0x030x
	//LEN_robot_interactive_header_data      = n,  //0x0301
	LEN_controller_interactive_header_data   = 30, //0x0302
	LEN_map_interactive_header_data          = 15, //0x0303
	LEN_keyboard_information                 = 12, //0x0304
	LEN_map_interactive_Receive_radar_data   = 10, //0x0305
	LEN_controller_interacts_player          = 8,	 //0x0306
	LEN_player_minimap_receive_sentry_data   = 103,//0x0307
	LEN_player_minimap_receive_bot_message   = 34 ,//0x0308
}JudgeDataLength;

/* 自定义帧头 */
typedef __packed struct
{
	uint8_t  SOF;
	uint16_t DataLength;
	uint8_t  Seq;
	uint8_t  CRC8;
	
}	xFrameHeader;

/* ID: 0x0001  Byte:  11    比赛状态数据 */
typedef __packed struct 
{ 
	uint8_t game_type : 4;
	uint8_t game_progress : 4;
	uint16_t stage_remain_time;
  uint64_t SyncTimeStamp;
} ext_game_state_t; 

/* ID: 0x0002  Byte:  1    比赛结果数据 */
typedef __packed struct 
{ 
	uint8_t winner;
} ext_game_result_t; 

/* ID: 0x0003  Byte:  32    比赛机器人血量数据 */
typedef __packed struct 
{ 
 uint16_t red_1_robot_HP;
 uint16_t red_2_robot_HP;
 uint16_t red_3_robot_HP;
 uint16_t red_4_robot_HP;
 uint16_t red_5_robot_HP;
 uint16_t red_7_robot_HP;
 uint16_t red_outpost_HP;
 uint16_t red_base_HP;
 uint16_t blue_1_robot_HP;
 uint16_t blue_2_robot_HP;
 uint16_t blue_3_robot_HP;
 uint16_t blue_4_robot_HP;
 uint16_t blue_5_robot_HP;
 uint16_t blue_7_robot_HP;
 uint16_t blue_outpost_HP;
 uint16_t blue_base_HP;   
}ext_game_robot_HP_t; 

/* ID: 0x0101  Byte:  4    场地事件数据 */
typedef __packed struct
{
 uint32_t event_data;
}ext_event_data_t;

/* ID: 0x0102  Byte:  4    补给站动作标识数据 */
typedef __packed struct
{
 uint8_t supply_projectile_id;
 uint8_t supply_robot_id;
 uint8_t supply_projectile_step;
 uint8_t supply_projectile_num;
} ext_supply_projectile_action_t;

/* ID: 0x0104  Byte:  2    裁判系统警告数据 */
typedef __packed struct
{
 uint8_t level;
 uint8_t offending_robot_id;
}ext_referee_warning_t;

/* ID: 0x0105  Byte:  1    飞镖发射时间数据 */
typedef __packed struct
{
 uint32_t event_data;
}ext_missile_shoot_time_t;

/* ID: 0x0201  Byte:  27    机器人性能体系数据 */
typedef __packed struct
{
 uint8_t robot_id;
 uint8_t robot_level;
 uint16_t current_HP;
 uint16_t maximum_HP;
 uint16_t shooter_id1_17mm_barrel_cooling_value;
 uint16_t shooter_id1_17mm_barrel_heat_limit;
 uint16_t shooter_id1_17mm_initial_launching_speed_limit;
 uint16_t shooter_id2_17mm_barrel_cooling_valuecooling_rate;
 uint16_t shooter_id2_17mm_barrel_heatcooling_limit; 
 uint16_t shooter_id2_17mm_initial_launching_speed_limit;
 uint16_t shooter_id1_42mm_barrel_cooling_value;
 uint16_t shooter_id1_42mm_barrel_heat_cooling_limit;
 uint16_t shooter_id1_42mm_initial_launching_speed_limit;
 uint16_t chassis_power_limit;
 uint8_t power_management_gimbal_output : 1;
 uint8_t power_management_chassis_output : 1;
 uint8_t power_management_shooter_output : 1;
}ext_robot_status_t;


/* ID: 0x0202  Byte:  16    实时功率热量数据 */
typedef __packed struct
{
 uint16_t chassis_voltage;
 uint16_t chassis_current;
 float chassis_power;
 uint16_t buffer_energy;
 uint16_t shooter_17mm_1_barrel_heat;
 uint16_t shooter_17mm_2_barrel_heat;
 uint16_t shooter_42mm_barrel_heat;
}ext_power_heat_data_t;


/* ID: 0x0203  Byte:  16    机器人位置数据 */
typedef __packed struct
{
 float x;
 float y;
 float z;
 float angle;
}ext_robot_pos_t;

/* ID: 0x0204  Byte:  1    机器人增益数据 */
typedef __packed struct
{
 uint8_t recovery_buff;
 uint8_t cooling_buff;
 uint8_t defence_buff;
 uint16_t attack_buff;
}ext_buff_musk_t;

/* ID: 0x0205  Byte:  1    空中支援时间数据 */
typedef __packed struct
{
 uint8_t airforce_status;
 uint8_t time_remain;
}ext_air_support_data_t;

/* ID: 0x0206  Byte:  1    伤害状态数据 */
typedef __packed struct
{
 uint8_t armor_id : 4;
 uint8_t HP_deduction_reason : 4;
}ext_hurt_data_t;

/* ID: 0x0207  Byte:  7    实时射击数据 */
typedef __packed struct
{
 uint8_t bullet_type;
 uint8_t shooter_number;
 uint8_t launching_frequency;
 float initial_speed;
}ext_shoot_data_t;

/* ID: 0x0208  Byte:  6    允许发弹量 */
typedef __packed struct
{
 uint16_t projectile_allowance_17mm;
 uint16_t projectile_allowance_42mm;
 uint16_t remaining_gold_coin;
}ext_projectile_allowance_t;

/* ID: 0x0209  Byte:  4    机器人RFID状态 */
typedef __packed struct
{
 uint32_t rfid_status;
}ext_rfid_status_t;


/* ID: 0x020A  Byte:  6    飞镖机器人客户端指令数据 */
typedef __packed struct
{
 uint8_t dart_launch_opening_status;
 uint8_t dart_attack_target;
 uint16_t target_change_time;
 uint16_t latest_launch_cmd_time;
}ext_dart_client_cmd_t;

/* ID: 0x020B  Byte:  40    地面机器人位置数据 */
typedef __packed struct
{
 float hero_x;
 float hero_y;
 float engineer_x;
 float engineer_y;
 float standard_3_x;
 float standard_3_y;
 float standard_4_x;
 float standard_4_y;
 float standard_5_x;
 float standard_5_y;
}ext_ground_robot_position_t;

/* ID: 0x020C  Byte:  6    雷达标记进度数据 */
typedef __packed struct
{
 uint8_t mark_hero_progress;
 uint8_t mark_engineer_progress;
 uint8_t mark_standard_3_progress;
 uint8_t mark_standard_4_progress;
 uint8_t mark_standard_5_progress;
 uint8_t mark_sentry_progress;
}ext_radar_mark_data_t;

/* ID: 0x020D  Byte:  4    选手端小地图接收哨兵数据 */
typedef __packed struct
{
 uint32_t sentry_info;
} sentry_info_t;

/* ID: 0x020E  Byte:  1    选手端小地图接收机器人数据 */
typedef __packed struct
{
 uint8_t radar_info;
} radar_info_t;
/* 
	
	交互数据，包括一个统一的数据段头结构，
	包含了内容 ID，发送者以及接受者的 ID 和内容数据段，
	整个交互数据的包总共长最大为 128 个字节，
	减去 frame_header,cmd_id,frame_tail 以及数据段头结构的 6 个字节，
	故而发送的内容数据段最大为 113。
	整个交互数据 0x0301 的包上行频率为 10Hz。

	机器人 ID：
	1，英雄(红)；
	2，工程(红)；
	3/4/5，步兵(红)；
	6，空中(红)；
	7，哨兵(红)；
	101，英雄(蓝)；
	102，工程(蓝)；
	103/104/105，步兵(蓝)；
	106，空中(蓝)；
	107，哨兵(蓝)。 
	客户端 ID： 
	0x0101 为英雄操作手客户端( 红) ；
	0x0102 ，工程操作手客户端 ((红 )；
	0x0103/0x0104/0x0105，步兵操作手客户端(红)；
	0x0106，空中操作手客户端((红)； 
	0x0165，英雄操作手客户端(蓝)；
	0x0166，工程操作手客户端(蓝)；
	0x0167/0x0168/0x0169，操作手客户端步兵(蓝)；
	0x0169A，空中操作手客户端(蓝)。 
*/

/* 交互数据接收信息：0x0301  */
typedef __packed struct 
{ 
	uint16_t data_cmd_id;    
	uint16_t send_ID;    
	uint16_t receiver_ID; 
} ext_student_interactive_header_data_t; 

enum judge_robot_ID{
	hero_red       = 1,
	engineer_red   = 2,
	infantry3_red  = 3,
	infantry4_red  = 4,
	infantry5_red  = 5,
	plane_red      = 6,
	
	hero_blue      = 101,
	engineer_blue  = 102,
	infantry3_blue = 103,
	infantry4_blue = 104,
	infantry5_blue = 105,
	plane_blue     = 106,
};

typedef struct{
	uint16_t teammate_hero;
	uint16_t teammate_engineer;
	uint16_t teammate_infantry3;
	uint16_t teammate_infantry4;
	uint16_t teammate_infantry5;
	uint16_t teammate_plane;
	uint16_t teammate_sentry;
	
	uint16_t client_hero;
	uint16_t client_engineer;
	uint16_t client_infantry3;
	uint16_t client_infantry4;
	uint16_t client_infantry5;
	uint16_t client_plane;
} ext_interact_id_t;

/* 
	学生机器人间通信 cmd_id 0x0301，内容 ID:0x0200~0x02FF
	交互数据 机器人间通信：0x0301。
	发送频率：上限 10Hz  

	字节偏移量 	大小 	说明 			备注 
	0 			2 		数据的内容 ID 	0x0200~0x02FF 
										可以在以上 ID 段选取，具体 ID 含义由参赛队自定义 
	
	2 			2 		发送者的 ID 	需要校验发送者的 ID 正确性， 
	
	4 			2 		接收者的 ID 	需要校验接收者的 ID 正确性，
										例如不能发送到敌对机器人的ID 
	
	6 			n 		数据段 			n 需要小于 113 

*/
typedef __packed struct 
{ 
	uint8_t data[113]; //数据段,n需要小于113
} robot_interactive_data_t;


/**
  * @brief  读取裁判数据,loop中循环调用此函数来读取数据
  * @param  缓存数据
  * @retval 是否对正误判断做处理
  * @attention  在此判断帧头和CRC校验,无误再写入数据
  */


typedef struct judge_info_struct {
	xFrameHeader							      FrameHeader;				// 帧头信息
	
	ext_game_state_t 								GameState;				// 0x0001           比赛状态数据
	ext_game_result_t 							GameResult;				// 0x0002         比赛结果数据
	ext_game_robot_HP_t 						GameRobotHP;			// 0x0003         机器人血量数据
	
	ext_event_data_t								EventData;					// 0x0101         场地事件数据
	ext_supply_projectile_action_t	SupplyProjectileAction;		// 0x0102 补给站动作标识
	ext_referee_warning_t						RefereeWarning;		// 0x0104         裁判警告信息
	ext_missile_shoot_time_t				missile_shoot_time;// 0x0105         飞镖发射时间数据
	
	ext_robot_status_t							GameRobotStat;			// 0x0201         机器人性能体系数据
	ext_power_heat_data_t						PowerHeatData;		// 0x0202         实时功率热量数据
	ext_robot_pos_t									GameRobotPos;			// 0x0203         机器人位置
	ext_buff_musk_t											Buff;								// 0x0204     机器人增益
	ext_air_support_data_t				 AirRobotSupport;     // 0x0205             空中支援时间数据
	ext_hurt_data_t								  RobotHurt;					// 0x0206         伤害状态
	ext_shoot_data_t								ShootData;					// 0x0207         实时射击信息(射频  射速  子弹信息)
	ext_projectile_allowance_t			bullet_remaining;		// 0x0208	        允许发弹量
	ext_rfid_status_t								rfid_status;				// 0x0209	        RFID信息
	ext_dart_client_cmd_t           dart_client;        // 0x020A         飞镖客户端
	ext_ground_robot_position_t     ground_robot_position;  //0x020B        地面机器人位置数据
	ext_radar_mark_data_t           radar_mark_data;        //0x020C        雷达标记进度数据
	sentry_info_t                   sentry_info;         //0x020D        选手端小地图接收哨兵数据
	radar_info_t                    radar_info;       	 //0x020E        选手端小地图接收机器人数据

	ext_interact_id_t								ids;								//与本机交互的机器人id
	uint16_t                        self_client;        //本机客户端
	bool	 		IF_REF_ONL;

} Referee_info_t;

///******************************客户端交互数据**************************************/
enum
{
	//0x200-0x02ff 	队伍自定义命令 格式  INTERACT_ID_XXXX
	INTERACT_ID_delete_graphic 			= 0x0100,	/*客户端删除图层*/
	INTERACT_ID_draw_one_graphic 		= 0x0101,	/*客户端绘制1个图形*/
	INTERACT_ID_draw_two_graphic 		= 0x0102,	/*客户端绘制2个图形*/
	INTERACT_ID_draw_five_graphic 	= 0x0103,	/*客户端绘制5个图形*/
	INTERACT_ID_draw_seven_graphic 	= 0x0104,	/*客户端绘制7个图形*/
	INTERACT_ID_draw_char_graphic 	= 0x0110,	/*客户端绘制字符图形*/
	INTERACT_ID_bigbome_num					= 0x02ff
};
enum
{
	LEN_INTERACT_delete_graphic     = 8,  //删除图层 2(数据内容ID)+2(发送者ID)+2（接收者ID）+2（数据内容）  
	LEN_INTERACT_draw_one_graphic   = 21, // 以上2+2+2+15
	LEN_INTERACT_draw_two_graphic   = 36, //6+15*2
	LEN_INTERACT_draw_five_graphic  = 81, //6+15*5
	LEN_INTERACT_draw_seven_graphic = 111,//6+15*7
	LEN_INTERACT_draw_char_graphic  = 51, //6+15+30（字符串内容）
};

//****************************绘图的数据段内容****************************/
typedef __packed struct//图形
{                          
	uint8_t graphic_name[3]; 
	uint32_t operate_tpye:3; 
	uint32_t graphic_tpye:3; //直线  矩形  正圆  椭圆  圆弧  浮点  整型  字符
	uint32_t layer:4;        
	uint32_t color:4;        
	uint32_t start_angle:9;  //空    空    空    空    角度  大小  大小  大小
	uint32_t end_angle:9;    //空    空    空    空          位数  空    长度
	uint32_t width:10;       
	uint32_t start_x:11;     //起点  起点  圆心  圆心  圆心  起点  起点  起点
	uint32_t start_y:11;     //
	uint32_t radius:10;      //空    空    半径  空    空    、    、    空
	uint32_t end_x:11;       //终点  对顶  空    半轴  半轴  、    、    空
	uint32_t end_y:11;       //                              数    数    空
} graphic_data_struct_t;
typedef __packed struct//浮点数
{                          
	uint8_t graphic_name[3]; 
	uint32_t operate_tpye:3; 
	uint32_t graphic_tpye:3; 
	uint32_t layer:4;        
	uint32_t color:4;        
	uint32_t Font_size:9;      
	uint32_t width:10;       
	uint32_t start_x:11;    
	uint32_t start_y:11;     
  float number;       
} Float_data_struct_t;
typedef __packed struct//整型数
{                          
	uint8_t graphic_name[3]; 
	uint32_t operate_tpye:3; 
	uint32_t graphic_tpye:3; 
	uint32_t layer:4;        
	uint32_t color:4;        
	uint32_t Font_size:9;     
	uint32_t width:10;       
	uint32_t start_x:11;    
	uint32_t start_y:11;     
  int number;       
} Int_data_struct_t;
/* data_ID: 0X0100  Byte:  2	    客户端删除图形*/
typedef __packed struct
{
uint8_t operate_type;
uint8_t layer; //图层数：0~9
}interaction_layer_delete_t;

typedef enum
{
	NONE_delete    = 0,
	GRAPHIC_delete = 1,
	ALL_delete     = 2
}delete_Graphic_Operate;//ext_client_custom_graphic_delete_t：uint8_t operate_type
/*图层删除操作*/

//bit 0-2
typedef enum
{
	NONE   = 0,/*空操作*/
	ADD    = 1,/*增加图层*/
	MODIFY = 2,/*修改图层*/
	DELETE = 3,/*删除图层*/
}Graphic_Operate;//graphic_data_struct_t：uint32_t operate_tpye
/*图层操作*/
//bit3-5
typedef enum
{
	LINE      = 0,//直线
	RECTANGLE = 1,//矩形
	CIRCLE    = 2,//正圆
	OVAL      = 3,//椭圆
	ARC       = 4,//圆弧
	FLOAT     = 5,//浮点数
	INT       = 6,//整型数
	CHAR      = 7 //字符
}Graphic_Type;
/*图层类型*/
//bit 6-9图层数 最大为9，最小0
//bit 10-13颜色
typedef enum
{
	RED_BLUE  = 0,//红蓝主色	
	YELLOW    = 1,
	GREEN     = 2,
	ORANGE    = 3,
	FUCHSIA   = 4,	/*紫红色*/
	PINK      = 5,
	CYAN_BLUE = 6,	/*青色*/
	BLACK     = 7,
	WHITE     = 8
}Graphic_Color;

/**********************************客户端绘图************************************************/
//删除图层
typedef __packed struct
{
	xFrameHeader                            txFrameHeader;			
	uint16_t                                CmdID;										
	ext_student_interactive_header_data_t   dataFrameHeader;
	interaction_layer_delete_t              clientData;		
	uint16_t	                              FrameTail;								
}ext_deleteLayer_data_t;

//绘字符串
typedef __packed struct
{
	graphic_data_struct_t grapic_data_struct;
	uint8_t data[30];
} ext_client_string_t;


//固定数据段长度数据包
typedef __packed struct
{
	xFrameHeader txFrameHeader;			//帧头
	uint16_t  CmdID;										//命令码
	ext_student_interactive_header_data_t   dataFrameHeader;//数据段头结构
	ext_client_string_t clientData;//数据段
	uint16_t	FrameTail;								//帧尾
}ext_charstring_data_t;
//绘象形图
typedef __packed struct
{
	xFrameHeader txFrameHeader;			//帧头
	uint16_t  CmdID;										//命令码
	ext_student_interactive_header_data_t   dataFrameHeader;//数据段头结构
	graphic_data_struct_t clientData;		//数据段
	uint16_t	FrameTail;								//帧尾
}ext_graphic_one_data_t;
typedef __packed struct
{
	xFrameHeader txFrameHeader;			
	uint16_t  CmdID;										
	ext_student_interactive_header_data_t   dataFrameHeader;
	graphic_data_struct_t clientData[2];		
	uint16_t	FrameTail;								
}ext_graphic_two_data_t;
typedef __packed struct
{
	xFrameHeader txFrameHeader;			
	uint16_t  CmdID;										
	ext_student_interactive_header_data_t   dataFrameHeader;
	graphic_data_struct_t clientData[5];		
	uint16_t	FrameTail;								
}ext_graphic_five_data_t;
typedef __packed struct
{
	xFrameHeader txFrameHeader;			
	uint16_t  CmdID;										
	ext_student_interactive_header_data_t   dataFrameHeader;
	graphic_data_struct_t clientData[7];		
	uint16_t	FrameTail;								
}ext_graphic_seven_data_t;
//绘制浮点型
typedef __packed struct
{
	xFrameHeader txFrameHeader;			
	uint16_t  CmdID;										
	ext_student_interactive_header_data_t   dataFrameHeader;
	Float_data_struct_t clientData[2];		
	uint16_t	FrameTail;								
}ext_float_two_data_t;
typedef __packed struct
{
	xFrameHeader txFrameHeader;			
	uint16_t  CmdID;										
	ext_student_interactive_header_data_t   dataFrameHeader;
	Float_data_struct_t clientData[7];		
	uint16_t	FrameTail;								
}ext_float_seven_data_t;
//绘制整型
typedef __packed struct
{
	xFrameHeader txFrameHeader;			
	uint16_t  CmdID;										
	ext_student_interactive_header_data_t   dataFrameHeader;
	Int_data_struct_t clientData[2];		
	uint16_t	FrameTail;								
}ext_int_two_data_t;
typedef __packed struct
{
	xFrameHeader txFrameHeader;			
	uint16_t  CmdID;										
	ext_student_interactive_header_data_t   dataFrameHeader;
	Int_data_struct_t clientData[7];		
	uint16_t	FrameTail;								
}ext_int_seven_data_t;


void Judege_read_data(uint8_t *ReadFromUsart );
void USART1_Init(void);
void USART1_DMA_Init(void);
void Determine_ID(void);
void foresight(void);
void Client_graphic_Info_update(void);
void USART1_SendChar(uint8_t cData);

uint16_t REF_Report_CHAS_Power_Buffer(void);
float REF_Report_CHAS_Power(void);
uint16_t REF_Report_CHAS_MaxPower(void);
#endif //_REFEREE_SYSTEM_H

