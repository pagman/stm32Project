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
int send_at_command_and_check_response(const char* at_command, const char* expected_response, char* received_data) {
  uint8_t tx_data[strlen(at_command)+1]; // Add space for null terminator
  uint8_t rx_data[strlen(expected_response)+30];
  HAL_StatusTypeDef status;
  char *ret;

  // Copy AT command to transmit buffer (including null terminator)
  strcpy((char*)tx_data, at_command);

  // Send AT command
  status = HAL_UART_Transmit(&huart1, tx_data, strlen((char*)tx_data),1000);
  if (status != HAL_OK) {
    return -1; // Error during transmission
  }

  // clear buffer
  memset(rx_data, 0, sizeof(rx_data));
  memset(received_data, 0, sizeof(received_data));
  // Start receiving response with timeout
  HAL_UART_Receive(&huart1, rx_data, strlen(expected_response)+30,1000);

  // Copy received data to output buffer
   strncpy(received_data, (char*)rx_data, 100); // Ensure null-termination


  ret = strstr((char*)rx_data, expected_response);
  if(ret=='\0'){
	     HAL_Delay(500);
         return -2;
     }

  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  HAL_Delay(1000);
  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  return 0; // Success
}

void replace_zeros_with_A(char *buffer, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (buffer[i] == 'Q') {
            buffer[i] = 'A';
        }
    }
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
  char rx_buffer[104];
  char gp_buffer[104];
  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
  HAL_Delay(2000);
  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
  check = send_at_command_and_check_response("AT\r\n", "AT\r\r\nOK\r\n", rx_buffer);
  check = send_at_command_and_check_response("AT+CPIN?\r\n", "READY", rx_buffer);
  check = send_at_command_and_check_response("AT+CGNSPWR?\r\n", "OK\r\n", rx_buffer);
  check = send_at_command_and_check_response("AT+CGNSPWR=1\r\n", "OK\r\n", rx_buffer);
  check = send_at_command_and_check_response("AT+CGNSIPR=9600\r\n", "OK\r\n", rx_buffer);
  check = send_at_command_and_check_response("AT+CGNSSEQ=\"RMC\"\r\n", "OK\r\n", rx_buffer);
  while (1)
  {
//	  check = send_at_command_and_check_response("AT\r\n", "AT\r\r\nOK\r\n", rx_buffer);
	  memset(gp_buffer, "Q", sizeof(gp_buffer));
	  check = send_at_command_and_check_response("AT+CGNSINF\r\n", "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", rx_buffer);
	  strcpy(gp_buffer, rx_buffer);
//	  replace_zeros_with_A(gp_buffer, sizeof(gp_buffer));
    /* USER CODE END WHILE */


    /* USER CODE BEGIN 3 */

	  //debug start new module
//	  count++;



//	  if(check!=0){ //doesnt even reply to the most basic command so do system rst
//		  NVIC_SystemReset();
//
//	  }
//	  check = send_at_command_and_check_response("AT+CPIN?\r\n", "READY", rx_buffer);
	  check = send_at_command_and_check_response("AT+CSQ\r\n", "OK\r\n", rx_buffer);
	  check = send_at_command_and_check_response("AT+CREG?\r\n", "OK\r\n", rx_buffer);
	  check = send_at_command_and_check_response("AT+CGATT?\r\n", "OK\r\n", rx_buffer);
	  check = send_at_command_and_check_response("AT+CGATT=1\r\n", "AT+CGATT=1\r\r\n+CGATT: 1\r\n\r\nOK\r\n", rx_buffer);
//	  /*
//	   * check if there is no IP then send APN  and register request
//	   */
	  check = send_at_command_and_check_response("AT+CIFSR\r\n", "ERROR", rx_buffer);
	  if(check ==0){ //means it find error in CIFSR so needs to set APN and CIICR
	   check = send_at_command_and_check_response("AT+CSTT=\"TM\"\r\n", "OK\r\n", rx_buffer);
	   check = send_at_command_and_check_response("AT+CIICR\r\n", "OK\r\n", rx_buffer);
	  }
	  check = send_at_command_and_check_response("AT+CIFSR\r\n", "ERROR", rx_buffer);
	  check = send_at_command_and_check_response("AT+CIPSTART=\"TCP\",\"45.154.87.237\",\"1887\"\r\n", "AT+CIPSTART=\"TCP\",\"45.154.87.237\",\"1887\"\r\r\nOK\r\n", rx_buffer);
	  check = send_at_command_and_check_response("AT+CIPSEND=100\r\n", "AT+CIPSEND=100\r\r\n>", rx_buffer);
	  check = send_at_command_and_check_response(gp_buffer, "test\r\r\nSEND", rx_buffer);
	  HAL_Delay(2000);

//	  for(int i=0;i<=10;i++){

//	  }


	  if(check!=0){
		  //means doesn't have error in the response so it can proceed with the connection



	  }
	  /*
	   * GPS
	   */



//	  HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
//	  HAL_Delay(2000);
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
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED2_Pin */
  GPIO_InitStruct.Pin = LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED2_GPIO_Port, &GPIO_InitStruct);

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
