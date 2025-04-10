/*
 * spi1.c
 *
 *  Created on: Mar 4, 2025
 *      Author: user
 */

#include <work_rfid_pn532.h>
#include "pn532_stm32f1.h"

//#define SPI_BUFFER_SIZE 10
//uint8_t spiRx;

PN532 pn532;

uint8_t buff[255];
uint8_t uid[MIFARE_UID_MAX_LENGTH];
int32_t uid_len = 0;

void InitRfidPn532Work()
{
	//HAL_SPI_Receive_IT(&hspi1, &spiRx, 1);

	  printf("Hello!\r\n");

	  PN532_SPI_Init(&pn532);
	  PN532_GetFirmwareVersion(&pn532, buff);
	  if (PN532_GetFirmwareVersion(&pn532, buff) == PN532_STATUS_OK) {
	    printf("Found PN532 with firmware version: %d.%d\r\n", buff[1], buff[2]);
	  } else {
	    return;
	  }
	  PN532_SamConfiguration(&pn532);
	  printf("Waiting for RFID/NFC card...\r\n");
}

/*
volatile uint8_t spi_rx_buff[128];
volatile uint8_t spi_rx_ridx;
volatile uint8_t spi_rx_widx;

static void PutRxByte(uint8_t rx)
{
	spi_rx_buff[spi_rx_widx] = rx;
	spi_rx_widx = (spi_rx_widx + 1) % sizeof(spi_rx_buff);
}

static uint8_t GetRxByte(uint8_t* rx)
{
	if (spi_rx_ridx != spi_rx_widx)
	{
		*rx = spi_rx_buff[spi_rx_ridx];
		spi_rx_ridx = (spi_rx_ridx + 1) % sizeof(spi_rx_buff);
		return 1;
	}
	else
		return 0;
}


void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi) {
    if (hspi->Instance == SPI1) {
    	PutRxByte(spiRx);
        HAL_SPI_Receive_IT(&hspi1, &spiRx, 1); // 계속 수신 대기
    }
}
*/

void DoRfidPn532Work()
{
	//uint8_t rx;
	//if (GetRxByte(&rx))
	//{
	//	printf("%02X ", rx);
	//}

	/*
	uint8_t rx_buff[8] = {0};
	uint8_t ret = HAL_SPI_Receive(&hspi1, rx_buff, 8, 500);
	printf("Ret=%d, Data=", ret);

	for(int i = 0; i < sizeof(rx_buff); i++)
		printf("%02X ", rx_buff[i]);
	printf("\n");
	*/

    uid_len = PN532_ReadPassiveTarget(&pn532, uid, PN532_MIFARE_ISO14443A, 1000);
    if (uid_len == PN532_STATUS_ERROR) {
      printf(".");
    } else {
      printf("Found card with UID: ");
      for (uint8_t i = 0; i < uid_len; i++) {
        printf("%02x ", uid[i]);
      }
      printf("\r\n");
    }

}
