/*
 * led.c
 *
 *  Created on: Feb 26, 2025
 *      Author: user
 */

#include "led.h"

#define RUN_LED_PORT GPIOB
#define RUN_LED_PIN GPIO_PIN_9

#define RGB_LED_PORT GPIOB
#define RGB_LED_R_PIN GPIO_PIN_10
#define RGB_LED_G_PIN GPIO_PIN_1
#define RGB_LED_B_PIN GPIO_PIN_2


void ToggleRunLed()
{
	HAL_GPIO_TogglePin(RUN_LED_PORT, RUN_LED_PIN);
}

uint32_t tm_run_led = 0;
uint32_t run_led_interval = 500;

void ChangeRunLed()
{
	if (GetElapsedTick(tm_run_led) >= run_led_interval)
	{
		tm_run_led = HAL_GetTick();
		ToggleRunLed();
	}
}

uint8_t rgb_led_out;

void TurnRgbLed(uint8_t value)
{
	if (value & 0x01)
		HAL_GPIO_WritePin(RGB_LED_PORT, RGB_LED_R_PIN, 1);
	else
		HAL_GPIO_WritePin(RGB_LED_PORT, RGB_LED_R_PIN, 0);

	if (value & 0x02)
		HAL_GPIO_WritePin(RGB_LED_PORT, RGB_LED_G_PIN, 1);
	else
		HAL_GPIO_WritePin(RGB_LED_PORT, RGB_LED_G_PIN, 0);

	if (value & 0x04)
		HAL_GPIO_WritePin(RGB_LED_PORT, RGB_LED_B_PIN, 1);
	else
		HAL_GPIO_WritePin(RGB_LED_PORT, RGB_LED_B_PIN, 0);

	rgb_led_out = value;
}


uint8_t rgb_led;	// bit0:Red, bit1:Green, bit2:Blue, bit3:Blink
uint32_t tm_rgb_led_blink;
uint8_t rgb_led_toggle;


void ChangeRgbLed()
{
	uint8_t rgb = rgb_led & 0x07;

	// Blink
	if (rgb_led & 0x08)
	{
		if (GetElapsedTick(tm_rgb_led_blink) >= 500)
		{
			tm_rgb_led_blink = HAL_GetTick();
			rgb_led_toggle = (rgb_led_toggle + 1) % 2;

			if (rgb_led_toggle)
				rgb = 0;
			else
				rgb = rgb_led & 0x07;
		}
		else
			rgb = rgb_led_out;
	}

	if (rgb != rgb_led_out)
	{
		TurnRgbLed(rgb);
	}
}


void InitLedWork()
{
}


void DoLedWork()
{
	ChangeRunLed();

	//ChangeRgbLed();
}
