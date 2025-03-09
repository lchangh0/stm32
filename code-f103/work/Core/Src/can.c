/*
 * can.c
 *
 *  Created on: Mar 4, 2025
 *      Author: user
 */


#include "can.h"


#define MAX_CAN_RX_FRAMES 50

typedef struct {
	CAN_RxHeaderTypeDef header;
	uint8_t data[8];
} can_rx_frame_t;

can_rx_frame_t can_rx_frames[MAX_CAN_RX_FRAMES];
volatile uint8_t can_rx_in = 0;
volatile uint8_t can_rx_out = 0;

// CAN RX_FIFO0 인터럽트 핸들러
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0,
			&can_rx_frames[can_rx_in].header,
			can_rx_frames[can_rx_in].data) == HAL_OK)
	{
		can_rx_in = (can_rx_in + 1) % MAX_CAN_RX_FRAMES;
	}
	else
	{
		printf("CAN RX Error\r\n");
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

int SendCanMessageButton1(uint8_t button)
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

int SendCanMessageButton2(uint8_t button)
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
	return SendCanFrame(0x05, 8, can_tx_data);
}


void InitCanWork()
{
	// CAN 통신
	HAL_CAN_Start(&hcan);
	if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
	{
		printf("CAN Activate Error\r\n");
	}
}

void DoCanWork()
{

}

