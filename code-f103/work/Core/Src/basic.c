/*
 * basic.c
 *
 *  Created on: Mar 4, 2025
 *      Author: user
 */

#include "basic.h"

uint8_t rx1data;
volatile uint8_t rx1_buff[256];	// 링버퍼
volatile uint16_t rx1_w_idx = 0;
volatile uint16_t rx1_r_idx = 0;


void InitBasic()
{
	// UART1 RX 인터럽트 활성
	HAL_UART_Receive_IT(&huart1, &rx1data, 1);
}


uint32_t GetElapsedTick(uint32_t start)
{
	uint32_t now = HAL_GetTick();

	if (now >= start)
		return now - start;
	else
		return (0xffff - start) + now;
}


int __io_putchar(int ch)
{
	// printf()함수를 실행했을 때 UART로 출력
	HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 0xffff);
	return ch;
}



// UART1 RX 인터럽트 핸들러
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		rx1_buff[rx1_w_idx] = rx1data;
		rx1_w_idx = (rx1_w_idx + 1) % sizeof(rx1_buff);

		// UART1 RX 인터럽트 활성
		HAL_UART_Receive_IT(&huart1, &rx1data, 1);
	}
}


uint16_t GetUart1RxCount()
{
	if (rx1_w_idx >= rx1_r_idx)
	{
		return rx1_w_idx - rx1_r_idx;
	}
	else
	{
		return sizeof(rx1_buff) - rx1_r_idx + rx1_w_idx;
	}
}

uint8_t ReadUart1Byte()
{
	uint8_t data = rx1_buff[rx1_r_idx];
	rx1_r_idx = (rx1_r_idx + 1) % sizeof(rx1_buff);
	return data;
}

void WriteUart1Bytes(uint8_t* buff, int len)
{
	HAL_UART_Transmit(&huart1, buff, len, 0xffff);
}


