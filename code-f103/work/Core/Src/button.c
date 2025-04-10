/*
 * button.c
 *
 *  Created on: Mar 4, 2025
 *      Author: user
 */

#include "button.h"

uint8_t btn1_pushed = 0;
uint8_t btn2_pushed = 0;

uint32_t tm_sw4=0;
uint8_t old_sw4=0;
uint8_t sw4_cnt=0;
uint8_t tmp_sw4=0;

uint32_t tm_sw5=0;
uint8_t old_sw5=0;
uint8_t sw5_cnt=0;
uint8_t tmp_sw5=0;

void ReadButton()
{
	// 10msec마다 sw4상태를 읽고 3번 연속 같은 값이면 입력 처리
	if(GetElapsedTick(tm_sw4) >= 10) {
		tm_sw4 = HAL_GetTick();
		tmp_sw4 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12);

		if(old_sw4 != tmp_sw4) {
			old_sw4 = tmp_sw4;
			sw4_cnt = 3;
		} else {
			if(sw4_cnt) {
				sw4_cnt--;
				if(sw4_cnt == 0) {
					// pushed down
					if (tmp_sw4 == 0)
					{
						btn1_pushed = 1;
						printf("Button1 pushed\r\n");
					}
				}
			}
		}
	}

	// 10msec마다 sw5상태를 읽고 3번 연속 같은 값이면 입력 처리
	if(GetElapsedTick(tm_sw5) >= 10) {
		tm_sw5 = HAL_GetTick();
		tmp_sw5 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);

		if(old_sw5 != tmp_sw5) {
			old_sw5 = tmp_sw5;
			sw5_cnt = 3;
		} else {
			if(sw5_cnt) {
				sw5_cnt--;
				if(sw5_cnt == 0) {
					// pushed down
					if (tmp_sw5 == 0)
					{
						btn2_pushed = 1;
						printf("Bbutton2 pushed\r\n");
					}
				}
			}
		}
	}
}


void DoButtonWork()
{
	ReadButton();
}
