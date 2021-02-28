/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include <math.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct {
	GPIO_TypeDef * ports[12];
	uint16_t pos[12];
}PORTS;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
volatile uint16_t counter = 0;
volatile uint16_t service = 0;
volatile double globalTime = 20000;
int i,j;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
int pulseTime();
void setLeds(PORTS *PORTS);
void timeSet(int number);
void runMode(PORTS *ports);
void setMode(PORTS *ports);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int pulseTime(){
	double time;
	if(!HAL_GPIO_ReadPin(buttonPin_GPIO_Port, buttonPin_Pin)){
		time=globalTime;
		while(!HAL_GPIO_ReadPin(buttonPin_GPIO_Port, buttonPin_Pin)){
			timeSet(60);
		}
		if((globalTime-time)>5){
			return 5;
		}
		else if ((globalTime-time)<=1.5) {
			return 1;
		}
		return 0;
	}
	else{
		return 0;
	}
}

void setLeds(PORTS *PORTS){
	PORTS->ports[0]=ledPin_11_GPIO_Port;
	PORTS->ports[1]=ledPin_10_GPIO_Port;
	PORTS->ports[2]=ledPin_9_GPIO_Port;
	PORTS->ports[3]=ledPin_8_GPIO_Port;
	PORTS->ports[4]=ledPin_7_GPIO_Port;
	PORTS->ports[5]=ledPin_6_GPIO_Port;
	PORTS->ports[6]=ledPin_5_GPIO_Port;
	PORTS->ports[7]=ledPin_4_GPIO_Port;
	PORTS->ports[8]=ledPin_3_GPIO_Port;
	PORTS->ports[9]=ledPin_2_GPIO_Port;
	PORTS->ports[10]=ledPin_1_GPIO_Port;
	PORTS->ports[11]=ledPin_12_GPIO_Port;
	PORTS->pos[0]=ledPin_11_Pin;
	PORTS->pos[1]=ledPin_10_Pin;
	PORTS->pos[2]=ledPin_9_Pin;
	PORTS->pos[3]=ledPin_8_Pin;
	PORTS->pos[4]=ledPin_7_Pin;
	PORTS->pos[5]=ledPin_6_Pin;
	PORTS->pos[6]=ledPin_5_Pin;
	PORTS->pos[7]=ledPin_4_Pin;
	PORTS->pos[8]=ledPin_3_Pin;
	PORTS->pos[9]=ledPin_2_Pin;
	PORTS->pos[10]=ledPin_1_Pin;
	PORTS->pos[11]=ledPin_12_Pin;
	for (int i = 0; i < 12; ++i) {
		HAL_GPIO_WritePin(PORTS->ports[i], PORTS->pos[i], GPIO_PIN_SET);
		timeSet(20);
		HAL_GPIO_WritePin(PORTS->ports[i], PORTS->pos[i], GPIO_PIN_RESET);
		timeSet(1);
	}
	for (int i = 0; i < 12; ++i) {
		HAL_GPIO_WritePin(PORTS->ports[i], PORTS->pos[i], GPIO_PIN_SET);
		timeSet(20);
		HAL_GPIO_WritePin(PORTS->ports[i], PORTS->pos[i], GPIO_PIN_RESET);
		timeSet(1);
	}
	for (int i = 11	; i >= 0; i--) {
		HAL_GPIO_WritePin(PORTS->ports[i], PORTS->pos[i], GPIO_PIN_SET);
		timeSet(20);
		HAL_GPIO_WritePin(PORTS->ports[i], PORTS->pos[i], GPIO_PIN_RESET);
		timeSet(1);
	}
}

void timeSet(int number){
	for(service=0;service<=number;){
	}
}

void runMode(PORTS *ports){
	double minutes,integer;
	minutes=modf((globalTime/3600),&integer);
	  for (j = 0; j < 5; ++j) {
		  //Se imprimen los LEDS intermitentemente 5 veces.
		  for (i = 0; i <= 11; ++i) {
			  if((globalTime/(3600*(i+1)))>(1)){
				  HAL_GPIO_WritePin(ports->ports[i], ports->pos[i], GPIO_PIN_SET);
				  //HAL_Delay(500);
			  }
			  //HAL_GPIO_WritePin(ports.ports[i], ports.pos[i], GPIO_PIN_RESET);
		  }
		  timeSet(300);
		  for (i = 0; i <= 11; ++i) {
			  HAL_GPIO_WritePin(ports->ports[i], ports->pos[i], GPIO_PIN_RESET);
		  }
		  timeSet(300);
	  }
	  //Se encienden los LEDS en tiempo de minutos.
	  for (i = 0; i <= 11; ++i) {
		  if (((minutes*60)/(5*(i+1)))>1) {
			  HAL_GPIO_WritePin(ports->ports[i], ports->pos[i], GPIO_PIN_SET);
		  }
	 }
	  timeSet(1500);
	  for (i = 0; i <= 11; ++i) {
		  HAL_GPIO_WritePin(ports->ports[i], ports->pos[i], GPIO_PIN_RESET);
	  }
}

void setMode(PORTS *ports){
	HAL_GPIO_WritePin(buzzerPin_GPIO_Port, buzzerPin_Pin, GPIO_PIN_SET);
	timeSet(300);
	HAL_GPIO_WritePin(buzzerPin_GPIO_Port, buzzerPin_Pin, GPIO_PIN_RESET);
	timeSet(300);
	HAL_GPIO_WritePin(buzzerPin_GPIO_Port, buzzerPin_Pin, GPIO_PIN_SET);
	timeSet(300);
	HAL_GPIO_WritePin(buzzerPin_GPIO_Port, buzzerPin_Pin, GPIO_PIN_RESET);
	//getOut de tipo int es la salida al modo SET.
	int menu;
	int getOut=1;
	double init=300;
	double minutes=3600;
	while(getOut){
		menu=pulseTime();
		for (i = 0; i <= 11; ++i) {
			if((minutes/(3600*(i+1)))>=(1)){
				HAL_GPIO_WritePin(ports->ports[i], ports->pos[i], GPIO_PIN_SET);
			}
		}
		if(menu==1){
			minutes+=3600;
			if(minutes>43200){
				minutes=3600;
				for (i = 0; i <= 11; ++i) {
					HAL_GPIO_WritePin(ports->ports[i], ports->pos[i], GPIO_PIN_RESET);
				}
			}
		}
		else if(menu==5) {
			globalTime=minutes;
			HAL_GPIO_WritePin(buzzerPin_GPIO_Port, buzzerPin_Pin, GPIO_PIN_SET);
			timeSet(300);
			HAL_GPIO_WritePin(buzzerPin_GPIO_Port, buzzerPin_Pin, GPIO_PIN_RESET);
			timeSet(300);
			HAL_GPIO_WritePin(buzzerPin_GPIO_Port, buzzerPin_Pin, GPIO_PIN_SET);
			timeSet(300);
			HAL_GPIO_WritePin(buzzerPin_GPIO_Port, buzzerPin_Pin, GPIO_PIN_RESET);
			timeSet(300);
			HAL_GPIO_WritePin(buzzerPin_GPIO_Port, buzzerPin_Pin, GPIO_PIN_SET);
			timeSet(300);
			HAL_GPIO_WritePin(buzzerPin_GPIO_Port, buzzerPin_Pin, GPIO_PIN_RESET);
			for (i = 0; i <= 11; ++i) {
				HAL_GPIO_WritePin(ports->ports[i], ports->pos[i], GPIO_PIN_RESET);
			}
			while(getOut){
				for (i = 0; i <= 11; ++i) {
					if (((init)/(300*(i+1)))>=1) {
						HAL_GPIO_WritePin(ports->ports[i], ports->pos[i], GPIO_PIN_SET);
					}
				}
				menu=pulseTime();
				if(menu==1){
					init+=300;
					if(init>3600){
						init=300;
						for (i = 0; i <= 11; ++i) {
							HAL_GPIO_WritePin(ports->ports[i], ports->pos[i], GPIO_PIN_RESET);
						}
					}
				}
				else if(menu==5){
					getOut=0;
					globalTime+=init;
				}
			}
		}
	}
	for (i = 0; i <= 11; ++i) {
		HAL_GPIO_WritePin(ports->ports[i], ports->pos[i], GPIO_PIN_RESET);
	}
	HAL_GPIO_WritePin(buzzerPin_GPIO_Port, buzzerPin_Pin, GPIO_PIN_SET);
	//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	timeSet(2000);
	HAL_GPIO_WritePin(buzzerPin_GPIO_Port, buzzerPin_Pin, GPIO_PIN_RESET);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	PORTS ports;
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
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  setLeds(&ports);
  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  switch ((int)pulseTime()) {
		case 1:{
			runMode(&ports);
			break;
		}
		case 5:{
			setMode(&ports);
			break;
		}
		default:{
			break;
		}
	}
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

  /** Initializes the CPU, AHB and APB busses clocks 
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
  /** Initializes the CPU, AHB and APB busses clocks 
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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 35999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, ledPin_1_Pin|ledPin_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ledPin_3_Pin|ledPin_4_Pin|ledPin_5_Pin|ledPin_6_Pin 
                          |ledPin_7_Pin|ledPin_8_Pin|ledPin_9_Pin|ledPin_10_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ledPin_11_Pin|ledPin_12_Pin|buzzerPin_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ledPin_1_Pin ledPin_2_Pin */
  GPIO_InitStruct.Pin = ledPin_1_Pin|ledPin_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : ledPin_3_Pin ledPin_4_Pin ledPin_5_Pin ledPin_6_Pin 
                           ledPin_7_Pin ledPin_8_Pin ledPin_9_Pin ledPin_10_Pin */
  GPIO_InitStruct.Pin = ledPin_3_Pin|ledPin_4_Pin|ledPin_5_Pin|ledPin_6_Pin 
                          |ledPin_7_Pin|ledPin_8_Pin|ledPin_9_Pin|ledPin_10_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : ledPin_11_Pin ledPin_12_Pin buzzerPin_Pin */
  GPIO_InitStruct.Pin = ledPin_11_Pin|ledPin_12_Pin|buzzerPin_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : buttonPin_Pin */
  GPIO_InitStruct.Pin = buttonPin_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(buttonPin_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  //UNUSED(htim);
  if (htim->Instance == TIM2) {
	if(service++ == 65535) service = 0;
	if(counter++ == 1000){
		counter = 0;
		if (globalTime++ == 43200) {
			globalTime = 0;
		}
	}
  }
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIM_PeriodElapsedCallback could be implemented in the user file
   */
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
