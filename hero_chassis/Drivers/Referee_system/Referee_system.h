#ifndef _REFEREE_SYSTEM_H
#define _REFEREE_SYSTEM_H

#include "stm32f4xx.h"	
#include <stdbool.h>


#define JUDGE_BUFFER_LEN 200              //����������

#define JUDGE_FRAME_HEADER  0xA5           //֡ͷ

#define    JUDGE_DATA_ERROR      0
#define    JUDGE_DATA_CORRECT    1     //����ϵͳ���Բ�������

#define shoot_speed_limit 20;

#define TRUE 1
#define FALSE 0

#define BLUE 0
#define RED 1

//���ȸ���Э�鶨��,���ݶγ���Ϊn��Ҫ����֡ͷ�ڶ��ֽ�����ȡ
#define    LEN_HEADER    5        //֡ͷ��
#define    LEN_CMDID     2        //�����볤��
#define    LEN_TAIL      2	      //֡βCRC16

/* RFID������ */
#define    CARD_ATTACK        ((uint8_t)0x00)
#define    CARD_PROTECT       ((uint8_t)0x01)
#define    CARD_BLOOD_RED     ((uint8_t)0x02)
#define    CARD_BLOOD_BLUE    ((uint8_t)0x03)
#define    CARD_HEAL_RED      ((uint8_t)0x04)
#define    CARD_HEAL_BLUE     ((uint8_t)0x05)
#define    CARD_COLD_RED      ((uint8_t)0x06)
#define    CARD_COLD_BLUE     ((uint8_t)0x07)
#define    CARD_FORT          ((uint8_t)0x08)


//#define    LEN_HEADER    5        //֡ͷ��
//#define    LEN_CMDID     2        //�����볤��
//#define    LEN_TAIL      2	      //֡βCRC16

/*����*/
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
	SOF          = 0,//��ʼλ
	DATA_LENGTH  = 1,//֡�����ݳ���,�����������ȡ���ݳ���
	SEQ          = 3,//�����
	CRC8         = 4 //CRC8	
}	FrameHeaderOffset;

typedef enum
{
	ID_game_state       									= 0x0001,               //����״̬����   3Hz
	ID_game_result      									= 0x0002,               //�����������   ����
	ID_game_robot_hp    									= 0x0003, 						  //������Ѫ������ 3Hz

	ID_event_data 												= 0x0101,            	  //�����¼�����   3Hz
	ID_supply_projectile_action						= 0x0102,							  //����վ������ʶ����   ����վ�����ͷ�ʱ��������
	ID_supply_warm 												= 0x0104,						    //����ϵͳ��������     �����з�/�и�ʱ��������
	ID_missile_shoot_time 								= 0x0105,               //���ڷ���ʱ������     3Hz
	
	ID_robot_status    								    = 0x0201,							  //������������ϵ����   10Hz
	ID_power_heat_data    								= 0x0202,							  //ʵʱ������������     50Hz
	ID_game_robot_pos        							= 0x0203,							  //������λ������       10Hz
	ID_buff_musk													= 0x0204,							  //��������������       3Hz
	ID_Air_support_time_data							= 0x0205,							  //����֧Ԯʱ������     10Hz
	ID_robot_hurt													= 0x0206,								//�˺�״̬����         �˺���������
	ID_shoot_data													= 0x0207,								//ʵʱ�������         ���跢�����
	ID_Allowable_ammo_volume    					= 0x0208,								//��������           10Hz
	ID_rfid_status												= 0x0209,								//������RFID״̬       3Hz
	ID_dart_client_directive    					= 0x020A,								//���ڻ����˿ͻ���ָ������, 10Hz
	ID_Ground_robot_pos_data    					= 0x020B,               //���������λ�����ݣ��̶� 1Hz Ƶ�ʷ���
  ID_Radar_marker_data    							= 0x020C,               //�״��ǽ������ݣ��̶� 1Hz Ƶ�ʷ���
	ID_Sentinel_aut_dec_inf_syn						= 0x020D,               //�ڱ��������������Ϣͬ�����̶� 1Hz Ƶ�ʷ���
	ID_Radar_aut_dec_inf_syn							= 0x020E,               //�״�����������Ϣͬ�����̶�1Hz Ƶ�ʷ���
																														
	ID_robot_interactive_header_data			= 0x0301,								//�����˽������ݣ����ͷ��������ͣ�Ƶ������Ϊ 10Hz
	ID_controller_interactive_header_data = 0x0302,								//�Զ���������������ݽӿڣ�ͨ�������ͻ��˴����������� 30Hz
	ID_map_interactive_header_data        = 0x0303,								//ѡ�ֶ�С��ͼ�������ݣ������������͡���
	ID_keyboard_information               = 0x0304,								//����ң�����ݣ��̶� 30Hz Ƶ�ʷ���
	ID_map_interactive_Receive_radar_data = 0x0305,               //ѡ�ֶ�С��ͼ�����״����ݣ�Ƶ������Ϊ10Hz
	ID_controller_interacts_player        = 0x0306,               //�Զ����������ѡ�ֶ˽������ݣ����ͷ��������ͣ�Ƶ������Ϊ 30Hz
	ID_player_minimap_receive_sentry_data = 0x0307,               //ѡ�ֶ�С��ͼ�����ڱ����ݣ�Ƶ������Ϊ1Hz
	ID_player_minimap_receive_bot_message = 0x0308                //ѡ�ֶ�С��ͼ���ջ�������Ϣ��Ƶ������Ϊ 3Hz
	
}CmdID;

typedef enum
{
	/* Std */
	LEN_FRAME_HEAD 	                	 =  5,	// ֡ͷ����
	LEN_CMD_ID 		                  	 =  2,	// �����볤��
	LEN_FRAME_TAIL 	                	 =  2,	// ֡βCRC16
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

/* �Զ���֡ͷ */
typedef __packed struct
{
	uint8_t  SOF;
	uint16_t DataLength;
	uint8_t  Seq;
	uint8_t  CRC8;
	
}	xFrameHeader;

/* ID: 0x0001  Byte:  11    ����״̬���� */
typedef __packed struct 
{ 
	uint8_t game_type : 4;
	uint8_t game_progress : 4;
	uint16_t stage_remain_time;
  uint64_t SyncTimeStamp;
} ext_game_state_t; 

/* ID: 0x0002  Byte:  1    ����������� */
typedef __packed struct 
{ 
	uint8_t winner;
} ext_game_result_t; 

/* ID: 0x0003  Byte:  32    ����������Ѫ������ */
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

/* ID: 0x0101  Byte:  4    �����¼����� */
typedef __packed struct
{
 uint32_t event_data;
}ext_event_data_t;

/* ID: 0x0102  Byte:  4    ����վ������ʶ���� */
typedef __packed struct
{
 uint8_t supply_projectile_id;
 uint8_t supply_robot_id;
 uint8_t supply_projectile_step;
 uint8_t supply_projectile_num;
} ext_supply_projectile_action_t;

/* ID: 0x0104  Byte:  2    ����ϵͳ�������� */
typedef __packed struct
{
 uint8_t level;
 uint8_t offending_robot_id;
}ext_referee_warning_t;

/* ID: 0x0105  Byte:  1    ���ڷ���ʱ������ */
typedef __packed struct
{
 uint32_t event_data;
}ext_missile_shoot_time_t;

/* ID: 0x0201  Byte:  27    ������������ϵ���� */
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


/* ID: 0x0202  Byte:  16    ʵʱ������������ */
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


/* ID: 0x0203  Byte:  16    ������λ������ */
typedef __packed struct
{
 float x;
 float y;
 float z;
 float angle;
}ext_robot_pos_t;

/* ID: 0x0204  Byte:  1    �������������� */
typedef __packed struct
{
 uint8_t recovery_buff;
 uint8_t cooling_buff;
 uint8_t defence_buff;
 uint16_t attack_buff;
}ext_buff_musk_t;

/* ID: 0x0205  Byte:  1    ����֧Ԯʱ������ */
typedef __packed struct
{
 uint8_t airforce_status;
 uint8_t time_remain;
}ext_air_support_data_t;

/* ID: 0x0206  Byte:  1    �˺�״̬���� */
typedef __packed struct
{
 uint8_t armor_id : 4;
 uint8_t HP_deduction_reason : 4;
}ext_hurt_data_t;

/* ID: 0x0207  Byte:  7    ʵʱ������� */
typedef __packed struct
{
 uint8_t bullet_type;
 uint8_t shooter_number;
 uint8_t launching_frequency;
 float initial_speed;
}ext_shoot_data_t;

/* ID: 0x0208  Byte:  6    �������� */
typedef __packed struct
{
 uint16_t projectile_allowance_17mm;
 uint16_t projectile_allowance_42mm;
 uint16_t remaining_gold_coin;
}ext_projectile_allowance_t;

/* ID: 0x0209  Byte:  4    ������RFID״̬ */
typedef __packed struct
{
 uint32_t rfid_status;
}ext_rfid_status_t;


/* ID: 0x020A  Byte:  6    ���ڻ����˿ͻ���ָ������ */
typedef __packed struct
{
 uint8_t dart_launch_opening_status;
 uint8_t dart_attack_target;
 uint16_t target_change_time;
 uint16_t latest_launch_cmd_time;
}ext_dart_client_cmd_t;

/* ID: 0x020B  Byte:  40    ���������λ������ */
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

/* ID: 0x020C  Byte:  6    �״��ǽ������� */
typedef __packed struct
{
 uint8_t mark_hero_progress;
 uint8_t mark_engineer_progress;
 uint8_t mark_standard_3_progress;
 uint8_t mark_standard_4_progress;
 uint8_t mark_standard_5_progress;
 uint8_t mark_sentry_progress;
}ext_radar_mark_data_t;

/* ID: 0x020D  Byte:  4    ѡ�ֶ�С��ͼ�����ڱ����� */
typedef __packed struct
{
 uint32_t sentry_info;
} sentry_info_t;

/* ID: 0x020E  Byte:  1    ѡ�ֶ�С��ͼ���ջ��������� */
typedef __packed struct
{
 uint8_t radar_info;
} radar_info_t;
/* 
	
	�������ݣ�����һ��ͳһ�����ݶ�ͷ�ṹ��
	���������� ID���������Լ������ߵ� ID ���������ݶΣ�
	�����������ݵİ��ܹ������Ϊ 128 ���ֽڣ�
	��ȥ frame_header,cmd_id,frame_tail �Լ����ݶ�ͷ�ṹ�� 6 ���ֽڣ�
	�ʶ����͵��������ݶ����Ϊ 113��
	������������ 0x0301 �İ�����Ƶ��Ϊ 10Hz��

	������ ID��
	1��Ӣ��(��)��
	2������(��)��
	3/4/5������(��)��
	6������(��)��
	7���ڱ�(��)��
	101��Ӣ��(��)��
	102������(��)��
	103/104/105������(��)��
	106������(��)��
	107���ڱ�(��)�� 
	�ͻ��� ID�� 
	0x0101 ΪӢ�۲����ֿͻ���( ��) ��
	0x0102 �����̲����ֿͻ��� ((�� )��
	0x0103/0x0104/0x0105�����������ֿͻ���(��)��
	0x0106�����в����ֿͻ���((��)�� 
	0x0165��Ӣ�۲����ֿͻ���(��)��
	0x0166�����̲����ֿͻ���(��)��
	0x0167/0x0168/0x0169�������ֿͻ��˲���(��)��
	0x0169A�����в����ֿͻ���(��)�� 
*/

/* �������ݽ�����Ϣ��0x0301  */
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
	ѧ�������˼�ͨ�� cmd_id 0x0301������ ID:0x0200~0x02FF
	�������� �����˼�ͨ�ţ�0x0301��
	����Ƶ�ʣ����� 10Hz  

	�ֽ�ƫ���� 	��С 	˵�� 			��ע 
	0 			2 		���ݵ����� ID 	0x0200~0x02FF 
										���������� ID ��ѡȡ������ ID �����ɲ������Զ��� 
	
	2 			2 		�����ߵ� ID 	��ҪУ�鷢���ߵ� ID ��ȷ�ԣ� 
	
	4 			2 		�����ߵ� ID 	��ҪУ������ߵ� ID ��ȷ�ԣ�
										���粻�ܷ��͵��жԻ����˵�ID 
	
	6 			n 		���ݶ� 			n ��ҪС�� 113 

*/
typedef __packed struct 
{ 
	uint8_t data[113]; //���ݶ�,n��ҪС��113
} robot_interactive_data_t;


/**
  * @brief  ��ȡ��������,loop��ѭ�����ô˺�������ȡ����
  * @param  ��������
  * @retval �Ƿ�������ж�������
  * @attention  �ڴ��ж�֡ͷ��CRCУ��,������д������
  */


typedef struct judge_info_struct {
	xFrameHeader							      FrameHeader;				// ֡ͷ��Ϣ
	
	ext_game_state_t 								GameState;				// 0x0001           ����״̬����
	ext_game_result_t 							GameResult;				// 0x0002         �����������
	ext_game_robot_HP_t 						GameRobotHP;			// 0x0003         ������Ѫ������
	
	ext_event_data_t								EventData;					// 0x0101         �����¼�����
	ext_supply_projectile_action_t	SupplyProjectileAction;		// 0x0102 ����վ������ʶ
	ext_referee_warning_t						RefereeWarning;		// 0x0104         ���о�����Ϣ
	ext_missile_shoot_time_t				missile_shoot_time;// 0x0105         ���ڷ���ʱ������
	
	ext_robot_status_t							GameRobotStat;			// 0x0201         ������������ϵ����
	ext_power_heat_data_t						PowerHeatData;		// 0x0202         ʵʱ������������
	ext_robot_pos_t									GameRobotPos;			// 0x0203         ������λ��
	ext_buff_musk_t											Buff;								// 0x0204     ����������
	ext_air_support_data_t				 AirRobotSupport;     // 0x0205             ����֧Ԯʱ������
	ext_hurt_data_t								  RobotHurt;					// 0x0206         �˺�״̬
	ext_shoot_data_t								ShootData;					// 0x0207         ʵʱ�����Ϣ(��Ƶ  ����  �ӵ���Ϣ)
	ext_projectile_allowance_t			bullet_remaining;		// 0x0208	        ��������
	ext_rfid_status_t								rfid_status;				// 0x0209	        RFID��Ϣ
	ext_dart_client_cmd_t           dart_client;        // 0x020A         ���ڿͻ���
	ext_ground_robot_position_t     ground_robot_position;  //0x020B        ���������λ������
	ext_radar_mark_data_t           radar_mark_data;        //0x020C        �״��ǽ�������
	sentry_info_t                   sentry_info;         //0x020D        ѡ�ֶ�С��ͼ�����ڱ�����
	radar_info_t                    radar_info;       	 //0x020E        ѡ�ֶ�С��ͼ���ջ���������

	ext_interact_id_t								ids;								//�뱾�������Ļ�����id
	uint16_t                        self_client;        //�����ͻ���
	bool	 		IF_REF_ONL;

} Referee_info_t;

///******************************�ͻ��˽�������**************************************/
enum
{
	//0x200-0x02ff 	�����Զ������� ��ʽ  INTERACT_ID_XXXX
	INTERACT_ID_delete_graphic 			= 0x0100,	/*�ͻ���ɾ��ͼ��*/
	INTERACT_ID_draw_one_graphic 		= 0x0101,	/*�ͻ��˻���1��ͼ��*/
	INTERACT_ID_draw_two_graphic 		= 0x0102,	/*�ͻ��˻���2��ͼ��*/
	INTERACT_ID_draw_five_graphic 	= 0x0103,	/*�ͻ��˻���5��ͼ��*/
	INTERACT_ID_draw_seven_graphic 	= 0x0104,	/*�ͻ��˻���7��ͼ��*/
	INTERACT_ID_draw_char_graphic 	= 0x0110,	/*�ͻ��˻����ַ�ͼ��*/
	INTERACT_ID_bigbome_num					= 0x02ff
};
enum
{
	LEN_INTERACT_delete_graphic     = 8,  //ɾ��ͼ�� 2(��������ID)+2(������ID)+2��������ID��+2���������ݣ�  
	LEN_INTERACT_draw_one_graphic   = 21, // ����2+2+2+15
	LEN_INTERACT_draw_two_graphic   = 36, //6+15*2
	LEN_INTERACT_draw_five_graphic  = 81, //6+15*5
	LEN_INTERACT_draw_seven_graphic = 111,//6+15*7
	LEN_INTERACT_draw_char_graphic  = 51, //6+15+30���ַ������ݣ�
};

//****************************��ͼ�����ݶ�����****************************/
typedef __packed struct//ͼ��
{                          
	uint8_t graphic_name[3]; 
	uint32_t operate_tpye:3; 
	uint32_t graphic_tpye:3; //ֱ��  ����  ��Բ  ��Բ  Բ��  ����  ����  �ַ�
	uint32_t layer:4;        
	uint32_t color:4;        
	uint32_t start_angle:9;  //��    ��    ��    ��    �Ƕ�  ��С  ��С  ��С
	uint32_t end_angle:9;    //��    ��    ��    ��          λ��  ��    ����
	uint32_t width:10;       
	uint32_t start_x:11;     //���  ���  Բ��  Բ��  Բ��  ���  ���  ���
	uint32_t start_y:11;     //
	uint32_t radius:10;      //��    ��    �뾶  ��    ��    ��    ��    ��
	uint32_t end_x:11;       //�յ�  �Զ�  ��    ����  ����  ��    ��    ��
	uint32_t end_y:11;       //                              ��    ��    ��
} graphic_data_struct_t;
typedef __packed struct//������
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
typedef __packed struct//������
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
/* data_ID: 0X0100  Byte:  2	    �ͻ���ɾ��ͼ��*/
typedef __packed struct
{
uint8_t operate_type;
uint8_t layer; //ͼ������0~9
}interaction_layer_delete_t;

typedef enum
{
	NONE_delete    = 0,
	GRAPHIC_delete = 1,
	ALL_delete     = 2
}delete_Graphic_Operate;//ext_client_custom_graphic_delete_t��uint8_t operate_type
/*ͼ��ɾ������*/

//bit 0-2
typedef enum
{
	NONE   = 0,/*�ղ���*/
	ADD    = 1,/*����ͼ��*/
	MODIFY = 2,/*�޸�ͼ��*/
	DELETE = 3,/*ɾ��ͼ��*/
}Graphic_Operate;//graphic_data_struct_t��uint32_t operate_tpye
/*ͼ�����*/
//bit3-5
typedef enum
{
	LINE      = 0,//ֱ��
	RECTANGLE = 1,//����
	CIRCLE    = 2,//��Բ
	OVAL      = 3,//��Բ
	ARC       = 4,//Բ��
	FLOAT     = 5,//������
	INT       = 6,//������
	CHAR      = 7 //�ַ�
}Graphic_Type;
/*ͼ������*/
//bit 6-9ͼ���� ���Ϊ9����С0
//bit 10-13��ɫ
typedef enum
{
	RED_BLUE  = 0,//������ɫ	
	YELLOW    = 1,
	GREEN     = 2,
	ORANGE    = 3,
	FUCHSIA   = 4,	/*�Ϻ�ɫ*/
	PINK      = 5,
	CYAN_BLUE = 6,	/*��ɫ*/
	BLACK     = 7,
	WHITE     = 8
}Graphic_Color;

/**********************************�ͻ��˻�ͼ************************************************/
//ɾ��ͼ��
typedef __packed struct
{
	xFrameHeader                            txFrameHeader;			
	uint16_t                                CmdID;										
	ext_student_interactive_header_data_t   dataFrameHeader;
	interaction_layer_delete_t              clientData;		
	uint16_t	                              FrameTail;								
}ext_deleteLayer_data_t;

//���ַ���
typedef __packed struct
{
	graphic_data_struct_t grapic_data_struct;
	uint8_t data[30];
} ext_client_string_t;


//�̶����ݶγ������ݰ�
typedef __packed struct
{
	xFrameHeader txFrameHeader;			//֡ͷ
	uint16_t  CmdID;										//������
	ext_student_interactive_header_data_t   dataFrameHeader;//���ݶ�ͷ�ṹ
	ext_client_string_t clientData;//���ݶ�
	uint16_t	FrameTail;								//֡β
}ext_charstring_data_t;
//������ͼ
typedef __packed struct
{
	xFrameHeader txFrameHeader;			//֡ͷ
	uint16_t  CmdID;										//������
	ext_student_interactive_header_data_t   dataFrameHeader;//���ݶ�ͷ�ṹ
	graphic_data_struct_t clientData;		//���ݶ�
	uint16_t	FrameTail;								//֡β
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
//���Ƹ�����
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
//��������
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

