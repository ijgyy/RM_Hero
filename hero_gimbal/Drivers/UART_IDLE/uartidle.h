#ifndef __UART_IDLE_H
#define __UART_IDLE_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "vision.h"
#include "rc.h"

#define USART2_RX_DATA_FRAME_LEN	(18u)	// ����2����֡����
#define USART2_RX_BUF_LEN			(USART2_RX_DATA_FRAME_LEN + 6u)	// ����2���ջ���������

#define UART4_RX_DATA_FRAME_LEN	  (13u)	// ����2����֡����
#define UART4_RX_BUF_LEN	    (UART4_RX_DATA_FRAME_LEN + 6u)	// ����4����֡����

void IDLE_UART_IRQHandler(UART_HandleTypeDef *huart);
void USART2_Init(void);
void USART4_Init(void);
#endif
