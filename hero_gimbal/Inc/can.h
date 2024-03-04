/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.h
  * @brief   This file contains all the function prototypes for
  *          the can.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "motor.h"
/* USER CODE END Includes */

extern CAN_HandleTypeDef hcan1;

extern CAN_HandleTypeDef hcan2;

/* USER CODE BEGIN Private defines */
typedef struct
{
	CAN_RxHeaderTypeDef can1_Rx;
	CAN_TxHeaderTypeDef can1_Tx;
	uint8_t can1_rx_data[8];
	int16_t can1_tx_data[4];
	CAN_RxHeaderTypeDef can2_Rx;
	CAN_TxHeaderTypeDef can2_Tx;
	uint8_t can2_rx_data[8];
	int16_t can2_tx_data[4];
	uint8_t can2_rx_data_u8[8];
}can;
/* USER CODE END Private defines */

void MX_CAN1_Init(void);
void MX_CAN2_Init(void);

/* USER CODE BEGIN Prototypes */
void CAN1_Tx(int16_t out[],uint32_t STD);
void CAN2_Tx(int16_t out[],uint32_t STD);
void CAN_Init(void);
void CAN2_Tx_u8(uint8_t out[],uint32_t STD);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */

