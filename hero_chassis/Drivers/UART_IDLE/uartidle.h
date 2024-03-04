#ifndef __UART_IDLE_H
#define __UART_IDLE_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include <string.h>
#include "Referee_system.h"


void IDLE_UART_IRQHandler(UART_HandleTypeDef *huart);
void USART1_Init(void);
#endif
