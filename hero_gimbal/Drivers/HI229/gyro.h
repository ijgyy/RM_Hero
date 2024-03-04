#ifndef __GYRO_H__
#define __GYRO_H__


#include "main.h"
#include "packet.h"
#include "imu_data_decode.h"

void GYRO_Init(void);
void imu_data(void);
void get_total_angle(void);

typedef struct
{
	float angle;
	float angle_last;
	float total_angle;
	float angle_first;
	int8_t round;
	uint8_t flag_gyro;
	uint8_t ID;
	int16_t Acc[3];
	int16_t Gyo[3];
	int16_t Mag[3];
	float Eular[3];
	float Quat[4];
	int32_t Pressure;
}Gyro;



extern UART_HandleTypeDef huart5;
extern IWDG_HandleTypeDef hiwdg;


#endif

