/*
 * led.c
 *
 *  Created on: Mar 4, 2025
 *      Author: user
 */

#include "led.h"




void SetLedD1(uint8_t on)
{
	if(on)
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
}

void ToggleLedD1()
{
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
}

void SetLedD2(uint8_t on)
{
	if(on)
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
}

void ToggleLedD2()
{
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15);
}


uint32_t tm_run_led = 0;

void ToggleRunLed()
{
	if(GetElapsedTick(tm_run_led) >= 500)
	{
		tm_run_led = HAL_GetTick();

		// RUN LED Toggle
		ToggleLedD2();
	}
}


void DoLedWork()
{
	ToggleRunLed();
}

