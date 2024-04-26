/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>
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
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int send_at_command_and_check_response(const char* at_command, const char* expected_response) {
  uint8_t tx_data[strlen(at_command)+1]; // Add space for null terminator
  uint8_t rx_data[strlen(expected_response)+20];
  HAL_StatusTypeDef status;

  // Copy AT command to transmit buffer (including null terminator)
  strcpy((char*)tx_data, at_command);

  // Send AT command
  status = HAL_UART_Transmit(&huart1, tx_data, strlen((char*)tx_data),1000);
  if (status != HAL_OK) {
    return -1; // Error during transmission
  }

  // Start receiving response with timeout
  HAL_UART_Receive(&huart1, rx_data, strlen(expected_response),1000);
  //HAL_UART_Receive_IT(&huart1, rx_data, strlen(expected_response));



  // Check if received data matches expected response
//  while (rx_len < strlen(expected_response) && HAL_UART_GetState(&huart1) != HAL_UART_STATE_TIMEOUT) {
//    if (HAL_UART_Receive(&huart1, rx_data + rx_len, 1,10) == HAL_OK) {
//      rx_len++;
//    }
//  }


//  if ( strcmp(response+strlen(response)-4, expected_response+strlen(expected_response)-4) != 0 ) {
//      return -2; // Response timeout or mismatch
//    }
  if (strncmp((char*)rx_data, expected_response, strlen(expected_response)) != 0) {
    return -2; // Response timeout or mismatch
  }

  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  HAL_Delay(1000);
  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  return 0; // Success
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int count = 0;
  char hello[] = "hello world";
  char buffer [10] = "hello\r\n";
  uint8_t numarray[10];
  static char msg[16];
  uint8_t Rx_data[10];
  int check;
  sprintf(buffer,"Hello %d\r\n",count);//  creating a buffer of 10 bytes
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  count++;
	  check = send_at_command_and_check_response("AT\r\n", "AT\r\r\nOK\r\n");
	  check = send_at_command_and_check_response("AT\r\n", "AT\r\r\nOK\r\n");
	  //check = send_at_command_and_check_response("AT+CFUN=1\r\n", "AT+CFUN=1\r\r\nOK\r\n");
	  check = send_at_command_and_check_response("AT+CPIN?\r\n", "AT+CPIN?\r\r\n+CPIN: READY\r\n\r\nOK\r\n");
	  check = send_at_command_and_check_response("AT+CSQ\r\n", "AT+CSQ\r\r\n+CSQ: 21,0\r\n\r\nOK\r\n");
//	  for (int i=0; i<=2;i++){
//		  HAL_Delay(1000);
//		  check = send_at_command_and_check_response("AT\r\n", "AT\r\r\nOK\r\n");
//		  check = send_at_command_and_check_response("AT+CSQ\r\n", "AT+CSQ\r\r\n+CSQ: 21,0\r\n\r\nOK\r\n");
//
//
//	  }
	  check = send_at_command_and_check_response("AT+CREG?\r\n", "AT+CREG?\r\r\n+CREG: 0,5\r\n\r\nOK\r\n");
	  check = send_at_command_and_check_response("AT+CGATT?\r\n", "AT+CGATT?\r\r\n+CGATT: 1\r\n\r\nOK\r\n");
	  /*
	   * run AT+CSTT only if AT+CGAT =0
	   */
	  //check = send_at_command_and_check_response("AT+CSTT=\"TM\",\"\",\"\"\r\n", "AT+CSTT=\"TM\",\"\",\"\"\r\r\nOK\r\n");
	  check = send_at_command_and_check_response("AT+CIICR\r\n", "AT+CIICR\r\r\nOK\r\n");
	  check = send_at_command_and_check_response("AT+CIFSR\r\n", "AT+CIFSR\r\r\n10.5.126.144\r\n");

	  //check = send_at_command_and_check_response("AT+CFUN=0\r\n", "AT+CFUN=0\r\r\nOK\r\n");
	  //HAL_UART_Transmit(&huart1,(uint8_t*)buffer,strlen((const char*)buffer),10);
	  HAL_Delay(1000);
	  //HAL_UART_Receive_IT(&huart1, buffer, 10);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
