#ifndef _VISION_H_
#define _VISION_H_

#include "main.h"
#include <stdio.h>
#include <string.h>
#include "gyro.h"


typedef struct 
{
	float pitch;
	float yaw;
	int16_t Distact[3];
	int16_t state;
	float pitch_last;
  float yaw_last;
	uint8_t vision_tx[13];
	uint8_t vision_rx[13];
}vision;

typedef union 
{
	float f;
	uint8_t vision[4];
}vision_f;


void VisionDataProgress(uint8_t *pData);
void Vision_pass(void);
void Vision_Send(void);
#endif //_VISION_H_

