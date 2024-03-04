#ifndef __UART_IDLE_H
#define __UART_IDLE_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "vision.h"
#include "rc.h"

#define USART2_RX_DATA_FRAME_LEN	(18u)	// 串口2数据帧长度
#define USART2_RX_BUF_LEN			(USART2_RX_DATA_FRAME_LEN + 6u)	// 串口2接收缓冲区长度

#define UART4_RX_DATA_FRAME_LEN	  (13u)	// 串口2数据帧长度
#define UART4_RX_BUF_LEN	    (UART4_RX_DATA_FRAME_LEN + 6u)	// 串口4数据帧长度

void IDLE_UART_IRQHandler(UART_HandleTypeDef *huart);
void USART2_Init(void);
void USART4_Init(void);
#endif
