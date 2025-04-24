/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#define check GPIOC -> ODR ^= (1<<13)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
char rx_data[4];
int flag = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1, (uint8_t*)rx_data, sizeof(rx_data));
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(flag == 0){
		  off();
	  }

	  if(!(GPIOB->IDR & (1<<6))){
	  	while (!(GPIOB->IDR & (1 << 6)));
	  	HAL_Delay(100);
	  	collect_password('1');
	  	check;
	  }
	  if(!(GPIOB->IDR & (1<<7))){
	  	while (!(GPIOB->IDR & (1 << 7)));
	  	HAL_Delay(100);
	  	collect_password('2');
	  	check;
	  }
	  if(!(GPIOB->IDR & (1<<8))){
	  	while (!(GPIOB->IDR & (1 << 8)));
	  	HAL_Delay(100);
	  	collect_password('3');
	  	check;
	  }
	  if(!(GPIOB->IDR & (1<<9))){
	  	while (!(GPIOB->IDR & (1 << 9)));
	  	HAL_Delay(100);
	  	check;
	  	send_password();
	  }

	  		  		  }


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */


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
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 6199;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_DISABLE;
  sSlaveConfig.InputTrigger = TIM_TS_ITR0;
  if (HAL_TIM_SlaveConfigSynchro(&htim2, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 PC14 PC15 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PD0 PD1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 PA5 PA6 PA7
                           PA8 PA11 PA12 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10
                           PB11 PB12 PB13 PB14
                           PB15 PB3 PB4 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB6 PB7 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure peripheral I/O remapping */
  __HAL_AFIO_REMAP_PD01_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void change_leds(int times){
	for(int i = 0; i < times; i++){
		GPIOB->ODR ^= (1 << 12);  GPIOA->ODR ^= (1 << 0);   GPIOB->ODR ^= (1 << 13);  GPIOA->ODR ^= (1 << 1);
		GPIOB->ODR ^= (1 << 14);  GPIOA->ODR ^= (1 << 2);   GPIOB->ODR ^= (1 << 15);  GPIOA->ODR ^= (1 << 3);
		GPIOA->ODR ^= (1 << 8);   GPIOA->ODR ^= (1 << 4);   GPIOA->ODR ^= (1 << 5);   GPIOA->ODR ^= (1 << 6);
		GPIOA->ODR ^= (1 << 11);  GPIOA->ODR ^= (1 << 7);   GPIOA->ODR ^= (1 << 12);  GPIOB->ODR ^= (1 << 0);
		GPIOA->ODR ^= (1 << 13);  GPIOB->ODR ^= (1 << 1);   GPIOA->ODR ^= (1 << 14);  GPIOB->ODR ^= (1 << 10);
		GPIOA->ODR ^= (1 << 15);  GPIOB->ODR ^= (1 << 11);  GPIOB->ODR ^= (1 << 3);   GPIOB->ODR ^= (1 << 4);
		GPIOB->ODR ^= (1 << 5);
	}
}
void on(){
	GPIOB->ODR &= ~(1 << 12);  GPIOA->ODR &= ~(1 << 0);   GPIOB->ODR &= ~(1 << 13);  GPIOA->ODR &= ~(1 << 1);
	GPIOB->ODR &= ~(1 << 14);  GPIOA->ODR &= ~(1 << 2);   GPIOB->ODR &= ~(1 << 15);  GPIOA->ODR &= ~(1 << 3);
	GPIOA->ODR &= ~(1 << 8);   GPIOA->ODR &= ~(1 << 4);   GPIOA->ODR &= ~(1 << 5);   GPIOA->ODR &= ~(1 << 6);
	GPIOA->ODR &= ~(1 << 11);  GPIOA->ODR &= ~(1 << 7);   GPIOA->ODR &= ~(1 << 12);  GPIOB->ODR &= ~(1 << 0);
	GPIOA->ODR &= ~(1 << 13);  GPIOB->ODR &= ~(1 << 1);   GPIOA->ODR &= ~(1 << 14);  GPIOB->ODR &= ~(1 << 10);
	GPIOA->ODR &= ~(1 << 15);  GPIOB->ODR &= ~(1 << 11);  GPIOB->ODR &= ~(1 << 3);   GPIOB->ODR &= ~(1 << 4);
	GPIOB->ODR &= ~(1 << 5);
}
void off(){
	GPIOB->ODR |= (1 << 12);  GPIOA->ODR |= (1 << 0);   GPIOB->ODR |= (1 << 13);  GPIOA->ODR |= (1 << 1);
	GPIOB->ODR |= (1 << 14);  GPIOA->ODR |= (1 << 2);   GPIOB->ODR |= (1 << 15);  GPIOA->ODR |= (1 << 3);
	GPIOA->ODR |= (1 << 8);   GPIOA->ODR |= (1 << 4);   GPIOA->ODR |= (1 << 5);   GPIOA->ODR |= (1 << 6);
	GPIOA->ODR |= (1 << 11);  GPIOA->ODR |= (1 << 7);   GPIOA->ODR |= (1 << 12);  GPIOB->ODR |= (1 << 0);
	GPIOA->ODR |= (1 << 13);  GPIOB->ODR |= (1 << 1);   GPIOA->ODR |= (1 << 14);  GPIOB->ODR |= (1 << 10);
	GPIOA->ODR |= (1 << 15);  GPIOB->ODR |= (1 << 11);  GPIOB->ODR |= (1 << 3);   GPIOB->ODR |= (1 << 4);
	GPIOB->ODR |= (1 << 5);
}


void send(data) {
	int size = sizeof(data);
	HAL_UART_Transmit_IT(&huart1, (uint8_t*)data, (uint16_t*)size);
	check;
}
char password[]="0000";
void collect_password(uint8_t num) {
    if (password[0] == '0') {
        password[0] = num;
    } else {
        if (password[1] == '0') {
            password[1] = num;
        } else {
            if (password[2] == '0') {
                password[2] = num;
            } else {
                if (password[3] == '0') {
                    password[3] = num;
                }
            }
        }
    }
}

void send_password(){
    if(password[3] != '0'){
        send(password);
        check;
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1) {
        for(int i = 0; i < sizeof(password); i++) {
            password[i] = '0';
        }
    }
}
void control_leds(){
	flag = 1;
	on();
	while (GPIOB->IDR & (1 << 9));
	while (!GPIOB->IDR & (1 << 9));
	flag = 0;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
    	//char itog[]={'q','w','e','r','t','y'}; - работает
    	//char itog[]="qwerty"; - тоже работает
    	if (memcmp("2132", rx_data, sizeof(rx_data)) == 0)
    	{

    	for(int i = 0; i<sizeof(rx_data); i++){
    		rx_data[i]='0';
    	}
        // Перезапускаем приёма
        HAL_UART_Receive_IT(&huart1, (uint8_t*)rx_data, sizeof(rx_data));
        control_leds();
    }
}
}
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
