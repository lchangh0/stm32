/*
 * hc-sr04.c
 *
 *  Created on: Feb 23, 2025
 *      Author: user
 */

#include "hc-sr04.h"
#include "basic.h"

void Trigger_HCSR04()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
}


uint8_t is_capture_done;
uint32_t rising_time;
uint32_t falling_time;

// TIM1 CC 인터럽트 핸들러
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM1 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
	{
		if ((TIM1->CCER & TIM_CCER_CC3P) == 0)	// Rising Edge 감지
		{
			rising_time = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);
			// 다음에 Falling Edge 감지
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_FALLING);
		}
		else	// Falling Edge 감지
		{
			falling_time = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);
			// 다음에 Rising Edge 감지
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_RISING);
			is_capture_done = 1;
		}
	}
}

// 거리 계산
uint32_t Calculate_Distance()
{
	uint32_t pulse_width;

	if (falling_time > rising_time)
		pulse_width = falling_time - rising_time;
	else
		pulse_width = (0xffff - falling_time) + rising_time;

	return (pulse_width * 0.0343) / 2;	// cm단위
}


uint32_t tm_sonic;
uint32_t sonic_distance;

void RunSonicSensor()
{
	if (GetElapsedTick(tm_sonic) >= 200)
	{
		tm_sonic = HAL_GetTick();

		Trigger_HCSR04();

		if (is_capture_done)
		{
			sonic_distance = Calculate_Distance();
			printf("Distance: %lu cm\r\n", sonic_distance);
			is_capture_done = 0;
		}
	}
}
