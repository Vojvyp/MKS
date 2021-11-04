/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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

#include "sct.h"
#include "1wire.h"
#define CONVERT_T_DELAY 750


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
int16_t temp;
int16_t temp_18b20;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
int16_t temp_NTC[1024] = {1689,1670,1651,1633,1615,1597,1580,1563,1547,1531,
		1515,1499,1484,1469,1455,1440,1426,1413,1399,1386,1373,1360,1348,1335,
		1323,1312,1300,1289,1278,1267,1256,1246,1236,1226,1216,1206,1197,1188,
		1178,1170,1161,1152,1144,1136,1127,1119,1112,1104,1097,1089,1082,1075,
		1068,1061,1054,1048,1041,1035,1029,1022,1016,1010,1005,999,993,988,982,
		977,972,967,962,957,952,947,942,937,933,928,924,919,915,911,907,902,898,
		894,890,886,883,879,875,871,868,864,860,857,854,850,847,843,840,837,834,
		830,827,824,821,818,815,812,809,806,803,801,798,795,792,789,787,784,781,
		779,776,774,771,768,766,763,761,758,756,753,751,749,746,744,742,739,737,
		735,732,730,728,726,723,721,719,717,715,712,710,708,706,704,702,700,698,
		696,693,691,689,687,685,683,681,679,677,675,673,671,669,668,666,664,662,
		660,658,656,654,652,651,649,647,645,643,641,639,638,636,634,632,631,629,
		627,625,623,622,620,618,617,615,613,611,610,608,606,605,603,601,600,598,
		596,595,593,591,590,588,587,585,583,582,580,579,577,576,574,572,571,569,
		568,566,565,563,562,560,559,557,556,554,553,551,550,548,547,546,544,543,
		541,540,538,537,536,534,533,531,530,529,527,526,525,523,522,521,519,518,
		517,515,514,513,511,510,509,508,506,505,504,502,501,500,499,497,496,495,
		494,493,491,490,489,488,487,485,484,483,482,481,479,478,477,476,475,474,
		472,471,470,469,468,467,466,465,463,462,461,460,459,458,457,456,455,454,
		452,451,450,449,448,447,446,445,444,443,442,441,440,439,438,437,436,435,
		434,433,432,430,429,428,427,426,425,424,423,422,421,420,419,418,417,416,
		415,414,413,413,412,411,410,409,408,407,406,405,404,403,402,401,400,399,
		398,397,396,395,394,393,392,391,390,389,388,387,387,386,385,384,383,382,
		381,380,379,378,377,376,375,374,373,372,372,371,370,369,368,367,366,365,
		364,363,362,361,360,359,359,358,357,356,355,354,353,352,351,350,349,348,
		347,347,346,345,344,343,342,341,340,339,338,337,336,335,335,334,333,332,
		331,330,329,328,327,326,325,325,324,323,322,321,320,319,318,317,316,315,
		315,314,313,312,311,310,309,308,307,306,306,305,304,303,302,301,300,299,
		298,297,297,296,295,294,293,292,291,290,289,289,288,287,286,285,284,283,
		282,281,281,280,279,278,277,276,275,274,274,273,272,271,270,269,268,267,
		267,266,265,264,263,262,261,261,260,259,258,257,256,255,255,254,253,252,
		251,250,249,249,248,247,246,245,244,244,243,242,241,240,239,239,238,237,
		236,235,234,234,233,232,231,230,229,229,228,227,226,225,224,224,223,222,
		221,220,220,219,218,217,216,216,215,214,213,212,212,211,210,209,208,208,
		207,206,205,204,204,203,202,201,200,200,199,198,197,196,196,195,194,193,
		193,192,191,190,189,189,188,187,186,186,185,184,183,182,182,181,180,179,
		179,178,177,176,175,175,174,173,172,171,171,170,169,168,168,167,166,165,
		164,164,163,162,161,161,160,159,158,157,157,156,155,154,154,153,152,151,
		150,150,149,148,147,146,146,145,144,143,142,142,141,140,139,138,138,137,
		136,135,134,134,133,132,131,130,130,129,128,127,126,126,125,124,123,122,
		121,121,120,119,118,117,117,116,115,114,113,112,111,111,110,109,108,107,
		106,106,105,104,103,102,101,100,100,99,98,97,96,95,94,94,93,92,91,90,89,
		88,87,86,86,85,84,83,82,81,80,79,78,78,77,76,75,74,73,72,71,70,69,68,68,
		67,66,65,64,63,62,61,60,59,58,57,56,56,55,54,53,52,51,50,49,48,47,46,45,
		44,43,42,41,40,39,38,37,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,
		21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,-1,-2,-3,-4,-5,
		-6,-7,-8,-9,-10,-11,-12,-13,-14,-15,-16,-17,-18,-19,-20,-21,-22,-23,-24,
		-26,-27,-28,-29,-30,-31,-32,-33,-34,-35,-36,-37,-38,-39,-40,-41,-42,-44,
		-45,-46,-47,-48,-49,-50,-51,-52,-53,-54,-56,-57,-58,-59,-60,-61,-62,-63,
		-65,-66,-67,-68,-69,-70,-71,-73,-74,-75,-76,-77,-79,-80,-81,-82,-83,-85,
		-86,-87,-88,-90,-91,-92,-93,-95,-96,-97,-98,-100,-101,-102,-104,-105,-106,
		-108,-109,-110,-112,-113,-114,-116,-117,-119,-120,-121,-123,-124,-126,-127,
		-129,-130,-132,-133,-135,-136,-138,-139,-141,-142,-144,-146,-147,-149,-150,
		-152,-154,-155,-157,-159,-161,-162,-164,-166,-167,-169,-171,-173,-175,-176,
		-178,-180,-182,-184,-186,-188,-190,-192,-194,-196,-197,-199,-202,-204,-206,
		-208,-210,-212,-214,-216,-218,-220,-223,-225,-227,-229,-231,-234,-236,-238,
		-240,-243,-245,-247,-250,-252,-255,-257,-259,-262,-264,-267,-269,-272,-274,
		-277,-279,-282,-284,-287,-290,-292,-295,-297};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC_Init(void);
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
  MX_USART2_UART_Init();
  MX_ADC_Init();

  /* USER CODE BEGIN 2 */
  sct_init();
  OWInit();

  HAL_ADCEx_Calibration_Start(&hadc);
  HAL_ADC_Start(&hadc);



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */



	  //temp = HAL_ADC_GetValue(&hadc);
	  //sct_value(temp_NTC[temp],0);

	  static uint32_t last_time;
	  uint32_t time;


	  	static enum {DS18B20, NTC} state = DS18B20;


	  	if(HAL_GPIO_ReadPin(S1_GPIO_Port, S1_Pin)==0)
	  	{
	  	  //last_time = HAL_GetTick();
	  	  state = DS18B20;
	  	  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
	      HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);



	  	}

	  	if(HAL_GPIO_ReadPin(S2_GPIO_Port, S2_Pin)==0)
	  	{
	  	  //last_time = HAL_GetTick();
	  	  state = NTC;
	  	  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
	      HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
	  	}


	  	if (state==DS18B20)
	  	{

	  		//sct_value(temp_18b20/10, 0);
	  		time = HAL_GetTick();

	  		if (last_time+CONVERT_T_DELAY<time)
	  		{
	  			OWConvertAll();
	  			OWReadTemperature(&temp_18b20);
	  			sct_value(temp_18b20/10, 0);
	  			last_time = HAL_GetTick();
	  		}

	  	}

	  	else if (state==NTC)
	  	{
	  		//temp = HAL_ADC_GetValue(&hadc);
	  		//sct_value(temp_NTC[temp],0);
	  		time = HAL_GetTick();

	  		if (last_time+CONVERT_T_DELAY<time)
	  		{

	  			temp = HAL_ADC_GetValue(&hadc);
	  			sct_value(temp_NTC[temp],0);
	  			last_time = HAL_GetTick();

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_10B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = ENABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

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
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED1_Pin|LD2_Pin|DQ_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED2_Pin|SCT_NOE_Pin|SCT_CLK_Pin|SCT_SDI_Pin
                          |SCT_NLA_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : S2_Pin S1_Pin */
  GPIO_InitStruct.Pin = S2_Pin|S1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LED1_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LED1_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED2_Pin SCT_NOE_Pin SCT_CLK_Pin SCT_SDI_Pin
                           SCT_NLA_Pin */
  GPIO_InitStruct.Pin = LED2_Pin|SCT_NOE_Pin|SCT_CLK_Pin|SCT_SDI_Pin
                          |SCT_NLA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : DQ_Pin */
  GPIO_InitStruct.Pin = DQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DQ_GPIO_Port, &GPIO_InitStruct);

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
