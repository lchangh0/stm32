/*
 * work.c
 *
 *  Created on: Feb 15, 2025
 *      Author: user
 */

#include "work.h"


extern CAN_HandleTypeDef hcan;

void InitWork()
{
	HAL_CAN_Start(&hcan);
}

uint32_t tm=0;
uint8_t old_sw4=0;
uint8_t sw4_cnt=0;
uint8_t tmp=0;

void ReadButton()
{
	if(HAL_GetTick() - tm >= 10) {
	  tm = HAL_GetTick();

	  tmp = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12);
	  if(old_sw4 != tmp) {
		  old_sw4 = tmp;
		  sw4_cnt = 3;
	  } else {
		  if(sw4_cnt) {
			  sw4_cnt--;
			  if(sw4_cnt == 0) {
				  //changed!
				  //printf("%s\n", sw4?"push":"pull");

				  SendCanMessageButton(tmp);
			  }
		  }
	  }
	}
}

uint32_t tm_run_led = 0;

void ToggleRunLed()
{
	if(HAL_GetTick() - tm_run_led >= 1000)
	{
	  // LED Toggle
	  tm_run_led = HAL_GetTick();
	  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15);

	  SendCanMessagePoll();
	}
}


int SendCanFrame(uint32_t id, int data_len, uint8_t data[])
{
	CAN_TxHeaderTypeDef can_tx_header;
	uint8_t             can_tx_data[8];
	uint32_t            can_tx_mailbox;

	can_tx_header.StdId = id;
	can_tx_header.RTR = CAN_RTR_DATA;
	can_tx_header.IDE = CAN_ID_STD;
	can_tx_header.DLC = data_len;
	can_tx_header.TransmitGlobalTime = DISABLE;

	for(int i = 0; i < data_len; i++)
		can_tx_data[i] = data[i];

	if (HAL_CAN_AddTxMessage(&hcan, &can_tx_header, can_tx_data, &can_tx_mailbox) != HAL_OK)
	{
		return -1;
	}
	return 0;
}

int iPollCnt;

int SendCanMessagePoll()
{
	iPollCnt += 100000;

	uint8_t can_tx_data[8];

	can_tx_data[0] = 0;
	can_tx_data[1] = 0;
	can_tx_data[2] = 0;
	can_tx_data[3] = 0;
	can_tx_data[4] = (uint8_t)((iPollCnt >> 24) & 0xff);
	can_tx_data[5] = (uint8_t)((iPollCnt >> 16) & 0xff);
	can_tx_data[6] = (uint8_t)((iPollCnt >> 8) & 0xff);
	can_tx_data[7] = (uint8_t)(iPollCnt & 0xff);
	return SendCanFrame(0x03, 8, can_tx_data);
}

int SendCanMessageButton(uint8_t button)
{
	uint8_t can_tx_data[8];

	can_tx_data[0] = 0;
	can_tx_data[1] = 0;
	can_tx_data[2] = 0;
	can_tx_data[3] = 0;
	can_tx_data[4] = 0;
	can_tx_data[5] = 0;
	can_tx_data[6] = 0;
	can_tx_data[7] = button;
	return SendCanFrame(0x04, 8, can_tx_data);
}


