#include "vofa.h"

extern UART_HandleTypeDef huart6;
extern motor_t Motor[6];
uint8_t tempData[20];
float b[4];



typedef union test
{
	float f;
	uint8_t arr[4];
}test_f;


test_f a1,a2,a3,a4;
void sum_arr(uint8_t a[],uint8_t b[],uint8_t c[],uint8_t d[])
{
	for(int i=0;i<16;i++)
	{
		if(i<4)
		{
			tempData[i] = a[i];
		}
		else if(i<8 && i>=4)
		{
			tempData[i] = b[i-4];
		}
		else if(i<12 && i>=8)
		{
			tempData[i] = c[i-8];
		}
		else if(i<16 && i>=12)
		{
			tempData[i] = d[i-12];
		}
	}

}

void SendWave(void)
{
	b[0] = 7;
	b[1] = 0;//motor[6].Rospeed;
	b[2] = 0;//motor[7].Rospeed;
	b[3] = 0;//motor[8].Rospeed;
	a1.f = b[0];
	a2.f = b[1];
	a3.f = b[2];
	a4.f = b[3];
	

	sum_arr(a1.arr,a2.arr,a3.arr,a4.arr);
	tempData[16] = 0x00;
	tempData[17] = 0x00;
	tempData[18] = 0x80;
	tempData[19] = 0x7f;

//	HAL_UART_Transmit(&huart6,tempData,20,HAL_MAX_DELAY);

}










