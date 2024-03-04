#include "vision.h"


extern Gyro gyro;
vision Vision;
vision_f pitch,yaw;




void VisionDataProgress(uint8_t *pData)
{
	if(pData[0] == 0x70)
	{
		 if(pData[12] == 0x6f)
		 {
			memcpy(&Vision.yaw,pData+1,4);
			memcpy(&Vision.pitch,pData+5,4);
			memcpy(&Vision.Distact[0],pData+9,1);
			memcpy(&Vision.Distact[1],pData+10,1);
			Vision.Distact[2] = Vision.Distact[0]*100 + Vision.Distact[1]; 
			memcpy(&Vision.state,pData+11,1);			 
			Vision.pitch_last = Vision.pitch;
			Vision.yaw_last = Vision.yaw;
		 }
		 else
		{
			Vision.pitch = 0;
			Vision.yaw = 0;
		}
		if(Vision.Distact[2] == 0 || Vision.Distact[2] == 24855)
		{
			Vision.pitch = 0;
			Vision.yaw = 0;
		}
	}
	else
		{
			Vision.pitch = 0;
			Vision.yaw = 0;
		}
}

void Vision_Send(void)
{
	pitch.f = gyro.Eular[0];
	yaw.f   = gyro.Eular[2];
	
	Vision.vision_tx[0]  = 0x80;
	Vision.vision_tx[1]  = 0;
	Vision.vision_tx[2]  = 30;
	memcpy(Vision.vision_tx+3,pitch.vision,4);
	memcpy(Vision.vision_tx+7,yaw.vision,4);
	Vision.vision_tx[11] = 112;
	Vision.vision_tx[12] = 0x7f;	
	
  HAL_UART_Transmit(&huart4,Vision.vision_tx,13,0xffff);
}




