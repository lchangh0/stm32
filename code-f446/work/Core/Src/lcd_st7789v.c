/*
 * lcd_st7789v.c
 *
 *  Created on: Mar 2, 2025
 *      Author: user
 */

#include "lcd_st7789v.h"


// ST7789V 핀 정의
#define ST7789_CS_PIN    GPIO_PIN_8
#define ST7789_CS_PORT   GPIOC
#define ST7789_DC_PIN    GPIO_PIN_5
#define ST7789_DC_PORT   GPIOC
#define ST7789_RST_PIN   GPIO_PIN_6
#define ST7789_RST_PORT  GPIOC

// ST7789V 명령어
#define ST7789_SWRESET   0x01
#define ST7789_SLPOUT    0x11
#define ST7789_COLMOD    0x3A
#define ST7789_MADCTL    0x36
#define ST7789_DISPON    0x29
#define ST7789_CASET     0x2A
#define ST7789_RASET     0x2B
#define ST7789_RAMWR     0x2C

// GPIO 제어 매크로
#define ST7789_CS_LOW()  HAL_GPIO_WritePin(ST7789_CS_PORT, ST7789_CS_PIN, GPIO_PIN_RESET)
#define ST7789_CS_HIGH() HAL_GPIO_WritePin(ST7789_CS_PORT, ST7789_CS_PIN, GPIO_PIN_SET)
#define ST7789_DC_LOW()  HAL_GPIO_WritePin(ST7789_DC_PORT, ST7789_DC_PIN, GPIO_PIN_RESET)
#define ST7789_DC_HIGH() HAL_GPIO_WritePin(ST7789_DC_PORT, ST7789_DC_PIN, GPIO_PIN_SET)
#define ST7789_RST_LOW() HAL_GPIO_WritePin(ST7789_RST_PORT, ST7789_RST_PIN, GPIO_PIN_RESET)
#define ST7789_RST_HIGH() HAL_GPIO_WritePin(ST7789_RST_PORT, ST7789_RST_PIN, GPIO_PIN_SET)


// SPI 데이터 전송 함수
void ST7789_SendCommand(uint8_t cmd) {
    ST7789_DC_LOW();  // Command 모드
    ST7789_CS_LOW();
    HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
    ST7789_CS_HIGH();
}

void ST7789_SendData(uint8_t *data, uint16_t len) {
    ST7789_DC_HIGH();  // Data 모드
    ST7789_CS_LOW();
    HAL_SPI_Transmit(&hspi1, data, len, HAL_MAX_DELAY);
    ST7789_CS_HIGH();
}

// ST7789V 초기화 함수
void ST7789_Init(void) {
    // 하드웨어 리셋
    ST7789_RST_HIGH();
    HAL_Delay(10);
    ST7789_RST_LOW();
    HAL_Delay(10);
    ST7789_RST_HIGH();
    HAL_Delay(120);

    // 소프트웨어 리셋
    ST7789_SendCommand(ST7789_SWRESET);
    HAL_Delay(150);

    // Sleep 모드 해제
    ST7789_SendCommand(ST7789_SLPOUT);
    HAL_Delay(10);

    // 색상 모드 설정 (16비트 RGB565)
    ST7789_SendCommand(ST7789_COLMOD);
    uint8_t colmod_data = 0x55;  // 16-bit/pixel
    ST7789_SendData(&colmod_data, 1);

    // 디스플레이 방향 설정
    ST7789_SendCommand(ST7789_MADCTL);
    uint8_t madctl_data = 0x00;  // 기본 방향 (조정 가능)
    ST7789_SendData(&madctl_data, 1);

    // 디스플레이 켜기
    ST7789_SendCommand(ST7789_DISPON);
    HAL_Delay(10);
}

// 화면 영역 설정 함수
void ST7789_SetWindow(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end) {
    uint8_t data[4];

    ST7789_SendCommand(ST7789_CASET); // 열 주소 설정
    data[0] = (x_start >> 8) & 0xFF;
    data[1] = x_start & 0xFF;
    data[2] = (x_end >> 8) & 0xFF;
    data[3] = x_end & 0xFF;
    ST7789_SendData(data, 4);

    ST7789_SendCommand(ST7789_RASET); // 행 주소 설정
    data[0] = (y_start >> 8) & 0xFF;
    data[1] = y_start & 0xFF;
    data[2] = (y_end >> 8) & 0xFF;
    data[3] = y_end & 0xFF;
    ST7789_SendData(data, 4);

    ST7789_SendCommand(ST7789_RAMWR); // 메모리 쓰기 준비
}

// 화면을 단색으로 채우는 함수
void ST7789_FillColor(uint16_t color) {
    uint8_t color_data[2] = {(color >> 8) & 0xFF, color & 0xFF};
    uint32_t pixel_count = 240 * 240; // 240x240 디스플레이 가정

    ST7789_SetWindow(0, 0, 239, 239); // 전체 화면 설정

    ST7789_DC_HIGH();
    ST7789_CS_LOW();
    for (uint32_t i = 0; i < pixel_count; i++) {
        HAL_SPI_Transmit(&hspi1, color_data, 2, HAL_MAX_DELAY);
    }
    ST7789_CS_HIGH();
}


void InitLcdWork()
{
	ST7789_Init(); // 디스플레이 초기화
	ST7789_FillColor(0xF800); // 화면을 빨간색으로 채움 (RGB565 형식)
}

void DoLcdWork()
{
}
