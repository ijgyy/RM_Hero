/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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
/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */
can CAN;
/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 6;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_4TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_4TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = ENABLE;
  hcan1.Init.AutoWakeUp = ENABLE;
  hcan1.Init.AutoRetransmission = ENABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */
	CAN_FilterTypeDef CAN1_Filter_Struct;
	
	CAN1_Filter_Struct.FilterBank = 1;
	CAN1_Filter_Struct.FilterScale = CAN_FILTERSCALE_32BIT ;
	CAN1_Filter_Struct.FilterMode = CAN_FILTERMODE_IDMASK ;//掩码模式
	CAN1_Filter_Struct.FilterFIFOAssignment = CAN_FilterFIFO0 ; //报文存储在FIFO 0
	CAN1_Filter_Struct.FilterActivation = ENABLE ;
	
	CAN1_Filter_Struct.FilterIdHigh = 0;//(((uint32_t)0x1314<<3|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF0000) >>16;
	CAN1_Filter_Struct.FilterIdLow = 0;//((uint32_t)0x1314<<3|CAN_ID_EXT|CAN_RTR_DATA)&0x0000FFFF;
	CAN1_Filter_Struct.FilterMaskIdHigh = 0;//0xFFFF;
	CAN1_Filter_Struct.FilterMaskIdLow =0;// 0x00;	

  HAL_CAN_ConfigFilter(&hcan1, &CAN1_Filter_Struct);
  /* USER CODE END CAN1_Init 2 */

}
/* CAN2 init function */
void MX_CAN2_Init(void)
{

  /* USER CODE BEGIN CAN2_Init 0 */

  /* USER CODE END CAN2_Init 0 */

  /* USER CODE BEGIN CAN2_Init 1 */

  /* USER CODE END CAN2_Init 1 */
  hcan2.Instance = CAN2;
  hcan2.Init.Prescaler = 6;
  hcan2.Init.Mode = CAN_MODE_NORMAL;
  hcan2.Init.SyncJumpWidth = CAN_SJW_4TQ;
  hcan2.Init.TimeSeg1 = CAN_BS1_4TQ;
  hcan2.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan2.Init.TimeTriggeredMode = DISABLE;
  hcan2.Init.AutoBusOff = ENABLE;
  hcan2.Init.AutoWakeUp = ENABLE;
  hcan2.Init.AutoRetransmission = ENABLE;
  hcan2.Init.ReceiveFifoLocked = DISABLE;
  hcan2.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN2_Init 2 */
	CAN_FilterTypeDef CAN2_Filter_Struct;
	
	CAN2_Filter_Struct.FilterBank = 15;
	CAN2_Filter_Struct.FilterScale = CAN_FILTERSCALE_32BIT ;
	CAN2_Filter_Struct.FilterMode = CAN_FILTERMODE_IDMASK ;//掩码模式
	CAN2_Filter_Struct.FilterFIFOAssignment = CAN_FilterFIFO0 ; //报文存储在FIFO 0
	CAN2_Filter_Struct.FilterActivation = ENABLE ;
	
	CAN2_Filter_Struct.FilterIdHigh = 0;//(((uint32_t)0x1314<<3|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF0000) >>16;
	CAN2_Filter_Struct.FilterIdLow = 0;//((uint32_t)0x1314<<3|CAN_ID_EXT|CAN_RTR_DATA)&0x0000FFFF;
	CAN2_Filter_Struct.FilterMaskIdHigh = 0;//0xFFFF;
	CAN2_Filter_Struct.FilterMaskIdLow =0;// 0x00;	

  HAL_CAN_ConfigFilter(&hcan2, &CAN2_Filter_Struct);
  /* USER CODE END CAN2_Init 2 */

}

static uint32_t HAL_RCC_CAN1_CLK_ENABLED=0;

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 7, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspInit 0 */

  /* USER CODE END CAN2_MspInit 0 */
    /* CAN2 clock enable */
    __HAL_RCC_CAN2_CLK_ENABLE();
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN2 GPIO Configuration
    PB12     ------> CAN2_RX
    PB13     ------> CAN2_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* CAN2 interrupt Init */
    HAL_NVIC_SetPriority(CAN2_RX0_IRQn, 8, 0);
    HAL_NVIC_EnableIRQ(CAN2_RX0_IRQn);
  /* USER CODE BEGIN CAN2_MspInit 1 */

  /* USER CODE END CAN2_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_CAN1_CLK_ENABLED--;
    if(HAL_RCC_CAN1_CLK_ENABLED==0){
      __HAL_RCC_CAN1_CLK_DISABLE();
    }

    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspDeInit 0 */

  /* USER CODE END CAN2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN2_CLK_DISABLE();
    HAL_RCC_CAN1_CLK_ENABLED--;
    if(HAL_RCC_CAN1_CLK_ENABLED==0){
      __HAL_RCC_CAN1_CLK_DISABLE();
    }

    /**CAN2 GPIO Configuration
    PB12     ------> CAN2_RX
    PB13     ------> CAN2_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12|GPIO_PIN_13);

    /* CAN2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN2_RX0_IRQn);
  /* USER CODE BEGIN CAN2_MspDeInit 1 */

  /* USER CODE END CAN2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void CAN_Init(void)
{
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
  HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);  
  HAL_CAN_Start(&hcan1);
	HAL_CAN_Start(&hcan2);
}
void CAN_Receive(CAN_HandleTypeDef *hcan)
{
		if(hcan->Instance == CAN1)
	{
	  HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&CAN.can1_Rx, CAN.can1_rx_data);
	}
		if(hcan->Instance == CAN2)
	{
	  HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&CAN.can2_Rx, CAN.can2_rx_data);
	}
}
void CAN1_Tx(int16_t out[],uint32_t STD)
{
	uint8_t Tx_Data[8];
	uint32_t mailbox1;
	CAN.can1_Tx.StdId = STD;
	CAN.can1_Tx.ExtId = 0;
	CAN.can1_Tx.IDE = CAN_ID_STD;
	CAN.can1_Tx.RTR = CAN_RTR_DATA;
	CAN.can1_Tx.DLC = 8;
	CAN.can1_Tx.TransmitGlobalTime = DISABLE;
	Tx_Data[0] = out[0] >> 8;
	Tx_Data[1] = out[0];
	Tx_Data[2] = out[1] >> 8;
	Tx_Data[3] = out[1];
	Tx_Data[4] = out[2] >> 8;
	Tx_Data[5] = out[2];
	Tx_Data[6] = out[3] >> 8;
	Tx_Data[7] = out[3];
	HAL_CAN_AddTxMessage(&hcan1, &CAN.can1_Tx, Tx_Data, &mailbox1);
}


void CAN2_Tx(int16_t out[],uint32_t STD)
{
	uint8_t Tx_Data[8];
	uint32_t mailbox2;
	CAN.can2_Tx.StdId = STD;
	CAN.can2_Tx.ExtId = 0;
	CAN.can2_Tx.IDE = CAN_ID_STD;
	CAN.can2_Tx.RTR = CAN_RTR_DATA;
	CAN.can2_Tx.DLC = 8;
	CAN.can2_Tx.TransmitGlobalTime = DISABLE;
	Tx_Data[0] = out[0] >> 8;
	Tx_Data[1] = out[0];
	Tx_Data[2] = out[1] >> 8;
	Tx_Data[3] = out[1];
	Tx_Data[4] = out[2] >> 8;
	Tx_Data[5] = out[2];
	Tx_Data[6] = out[3] >> 8;
	Tx_Data[7] = out[3];
	HAL_CAN_AddTxMessage(&hcan2, &CAN.can2_Tx, Tx_Data, &mailbox2);
}

void CAN2_Tx_u8(uint8_t out[],uint32_t STD)
{
	uint8_t Tx_Data[8];
	uint32_t mailbox2;
	CAN.can2_Tx.StdId = STD;
	CAN.can2_Tx.ExtId = 0;
	CAN.can2_Tx.IDE = CAN_ID_STD;
	CAN.can2_Tx.RTR = CAN_RTR_DATA;
	CAN.can2_Tx.DLC = 8;
	CAN.can2_Tx.TransmitGlobalTime = DISABLE;
	Tx_Data[0] = out[0];
	Tx_Data[1] = out[1];
	Tx_Data[2] = out[2];
	Tx_Data[3] = out[3];
	Tx_Data[4] = out[4];
	Tx_Data[5] = out[5];
	Tx_Data[6] = out[6];
	Tx_Data[7] = out[7];
	HAL_CAN_AddTxMessage(&hcan2, &CAN.can2_Tx, Tx_Data, &mailbox2);
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	CAN_Receive(hcan);
	MSP_motor();
}

/* USER CODE END 1 */
