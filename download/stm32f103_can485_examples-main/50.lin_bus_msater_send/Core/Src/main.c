/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#define OPEN_LIN_MAX_FRAME_LENGTH 0x8u
#define OPEN_LIN_SYNCH_BYTE 0x55u
#define OPEN_LIN_GET_PID_BIT(x,y) (((x) >> (y)) & 0x01u)
#define OPEN_LIN_ID_MASK 0x3Fu
#define OPEN_LIN_P0_FLAG 6
#define OPEN_LIN_P1_FLAG 7

#define OPEN_LIN_DIAG_REQUEST 0x3C
#define OPEN_LIN_DIAG_RESPONSE 0x3D

typedef uint8_t open_lin_pid_t;
typedef uint8_t open_lin_checksum_t;
open_lin_pid_t open_lin_data_layer_parity(open_lin_pid_t pid) {
	open_lin_pid_t result = 0;
	result = (open_lin_pid_t)(OPEN_LIN_GET_PID_BIT(pid,0) ^ OPEN_LIN_GET_PID_BIT(pid,1) ^
			 OPEN_LIN_GET_PID_BIT(pid,2) ^ OPEN_LIN_GET_PID_BIT(pid,4)) << OPEN_LIN_P0_FLAG;

    result |= (open_lin_pid_t)(~(OPEN_LIN_GET_PID_BIT(pid,1) ^ OPEN_LIN_GET_PID_BIT(pid,3) ^
    			  OPEN_LIN_GET_PID_BIT(pid,4) ^ OPEN_LIN_GET_PID_BIT(pid,5)) << OPEN_LIN_P1_FLAG);

    result |= (open_lin_pid_t)(OPEN_LIN_ID_MASK & pid);
    return result;
}

open_lin_checksum_t open_lin_data_layer_checksum(open_lin_pid_t pid, uint8_t lenght, const uint8_t* data_ptr)
{
	uint8_t i = 0;
	uint16_t result;

	/* diagnostic request have classic checksum */
	if ((pid == OPEN_LIN_DIAG_REQUEST) || (pid == OPEN_LIN_DIAG_RESPONSE))
	{
		result = 0;
	} else {
		result = open_lin_data_layer_parity(pid);
	}

	for (i = 0; i < lenght; i++)
	{
		result += data_ptr[i];
		if (result > 0xFF)
		{
			result -= 0xFF;
		} else
		{
			/* do nothing */
		}
	}
	return (open_lin_checksum_t)(~result);
}

uint8_t open_lin_hw_tx_byte(uint8_t byte)
{
	HAL_UART_Transmit(&huart2, &byte, 1, 0xffff);
    return 1;

}

uint8_t open_lin_master_data_tx_data(uint8_t pid, uint8_t *data_ptr, uint8_t data_length)
{
	uint8_t i = 0;
	uint8_t result = 1;
	for (i = 0; i < data_length; i++)
	{
		result = (open_lin_hw_tx_byte(data_ptr[i])) && result;
	}

	result = (open_lin_hw_tx_byte(open_lin_data_layer_checksum(pid, data_length, data_ptr))) && result;
	return result;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint32_t tm=0;
	uint8_t old_sw4=0;
	uint8_t sw4_cnt=0;
	uint8_t tmp=0;

	uint8_t sync = 0x55;
	uint8_t datas[5] = {0x11, 0x12, 0x13, 0x14, 0x15};

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
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
					  //changed! and pushed
					  if(tmp == 0) {
						  HAL_LIN_SendBreak(&huart2);
						  HAL_UART_Transmit(&huart2, &sync, 1, 0xffff);
						  tmp = open_lin_data_layer_parity(0x02);
						  HAL_UART_Transmit(&huart2, &tmp, 1, 0xffff);
						  open_lin_master_data_tx_data(0x02, datas, 5);
					  }
				  }
			  }

		  }
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 20000;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  if (HAL_LIN_Init(&huart2, UART_LINBREAKDETECTLENGTH_10B) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
