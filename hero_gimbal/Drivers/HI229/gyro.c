#include "gyro.h"


Gyro gyro;



void GYRO_Init(void)
{
	imu_data_decode_init();

}

void imu_data(void)
{
				get_raw_acc(gyro.Acc);
        get_raw_gyo(gyro.Gyo);
        get_raw_mag(gyro.Mag);
        get_eular(gyro.Eular);
        get_quat(gyro.Quat);
        get_id(&gyro.ID);
}




void get_total_angle(void)
{
	gyro.angle = gyro.Eular[2];
	if(gyro.angle - gyro.angle_last > 180)
	{
		gyro.round--;
	}
	else if (gyro.angle - gyro.angle_last < -180)
	{
		gyro.round++;
	}
		gyro.total_angle =(gyro.round) * 360 + gyro.angle;
		gyro.angle_last = gyro.Eular[2];
	
//	if(gyro.total_angle > 360 || gyro.total_angle < -360)
//	{
//		gyro.round = 0;
//		gyro.flag_gyro = 1;
//	}
//	else
//	{
//		gyro.flag_gyro = 2;	
//	}
}






