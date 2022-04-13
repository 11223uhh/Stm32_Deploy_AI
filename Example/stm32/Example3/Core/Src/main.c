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
#include "stdio.h"
#include "mode1.h"
#include "ai.h"


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
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart3;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
#define RXBUFFERSIZE  256     //�������ֽ���
uint8_t RxBuffer[RXBUFFERSIZE];   //��������
int aRxBuffer;			//�����жϻ���
uint8_t Uart1_Rx_Cnt = 0;		//���ջ������

const q7_t conv1_wt[CONV_IM_CH_0 * CONV_KER_DIM_0 * CONV_KER_DIM_0 * CONV_OUT_CH_0] = Conv2D_0_weight;
 const q7_t conv1_bias[CONV_OUT_CH_0] = Conv2D_0bias;


const  q7_t conv2_wt[CONV_IM_CH_2 * CONV_KER_DIM_2 * CONV_KER_DIM_2 * CONV_OUT_CH_2] = Conv2D_1_weight;
 const q7_t conv2_bias[CONV_OUT_CH_2] = Conv2D_1bias;


 q7_t ip1_wt[256 * 10] = Dense_2_weight;

q7_t ip1_bias[IP1_OUT_4] = Dense_2bias;

q7_t      col_buffer[256*120];//�洢���Ǿ��������

q7_t      scratch_buffer[15*24*24];

uint8_t  Image_array[28*28];   //��������
q7_t output_data[10];
int run_flag=0;
int tim_ms=0;
void AI_run();
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
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer, 1);

  /* USER CODE END 2 */
  
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
     if(run_flag==1)
	    {
	 	   run_flag=0;
	 	   AI_run();
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 384;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  RCC_OscInitStruct.PLL.PLLR = 2;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48CLKSOURCE_PLLQ;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	 
	  
	  tim_ms++;
	  if(tim_ms>10000000)
			tim_ms=0;
}

void AI_run()
{
	 long int ALL_timecnt;

   long int timecnt1;
   long int timecnt2;

   long int timecnt3;
   long int timecnt4;
   long int timecnt5;
	 double time1;
	 double time2;
	 double time3;
	 double time4;

	q7_t     *img_buffer1 = scratch_buffer;
  q7_t     *img_buffer2 = img_buffer1 + CONV_OUT_CH_0 * CONV_OUT_DIM_0 * CONV_OUT_DIM_0;//+ CONV1_OUT_CH * CONV1_OUT_DIM * CONV1_OUT_DIMΪ�����������������Ĳ���
  q7_t     *temp_po;
  for (int i=0;i<28*28*1; i++)
	{
    img_buffer2[i] =(q7_t)Image_array[i];//��һ������� Ӧ���������������
  }
   ALL_timecnt = tim_ms;

	 	arm_convolve_HWC_q7_basic(img_buffer2,
													CONV_IM_DIM_0, CONV_IM_CH_0, conv1_wt,
													CONV_OUT_CH_0,
										      CONV_KER_DIM_0, CONV_PADDING_0,CONV_STRIDE_0,
													conv1_bias,
													CONV_BIAS_LSHIFT_0, CONV_OUT_RSHIFT_0,
													img_buffer1,
													CONV_OUT_DIM_0,
                          (q15_t *) col_buffer, NULL);

	 arm_relu_q7(img_buffer1, CONV_OUT_DIM_0 * CONV_OUT_DIM_0 * CONV_OUT_CH_0);
	   timecnt1 = tim_ms;

	 arm_maxpool_q7_HWC(img_buffer1, CONV_OUT_DIM_0, CONV_OUT_CH_0, POOL_KER_DIM_1,
                     POOL_PADDING_1, POOL_STRIDE_1, POOL_OUT_DIM_1, NULL, img_buffer2);

   timecnt2 = tim_ms;

	 arm_convolve_HWC_q7_basic(img_buffer2, CONV_IM_DIM_2, CONV_IM_CH_2, conv2_wt, CONV_OUT_CH_2, CONV_KER_DIM_2,
                           CONV_PADDING_2, CONV_STRIDE_2, conv2_bias, CONV_BIAS_LSHIFT_2 ,CONV_OUT_RSHIFT_2, img_buffer1,
                           CONV_OUT_DIM_2, (q15_t *) col_buffer, NULL);
													 
												 
	  arm_relu_q7(img_buffer1, CONV_OUT_DIM_2 * CONV_OUT_DIM_2 * CONV_OUT_CH_2);
	  timecnt3 = tim_ms;

		arm_maxpool_q7_HWC(img_buffer1, CONV_OUT_DIM_2, CONV_OUT_CH_2, POOL_KER_DIM_3,
                     POOL_PADDING_3, POOL_STRIDE_3, POOL_OUT_DIM_3, NULL, img_buffer2);
timecnt4= tim_ms;
  arm_fully_connected_q7(img_buffer2, ip1_wt, IP1_DIM_4, IP1_OUT_4, Dense_BIAS_LSHIFT_4, Dense_OUT_RSHIFT_4, ip1_bias,
                             output_data, (q15_t *) img_buffer1);

  arm_softmax_q7(output_data, 10, output_data);
  timecnt5= tim_ms;
	for (int i = 0; i < 10; i++)
		{
			printf("%d: %d\r\n", i, output_data[i]);
		}
int max_temp=0;
  int lable=0;                             
  for (int i = 0; i < 10; i++)
    {
      if(output_data[i]>max_temp)
      {
        lable=i;
        max_temp=output_data[i];
      }
    }
		time1=(timecnt1-ALL_timecnt)*0.01;
		time2=(timecnt3-timecnt2)*0.01;
		time3=(timecnt5-timecnt4)*0.01;
		time4=(timecnt5-ALL_timecnt)*0.01;

        printf("conv1_time  %.2f  theor_time %.2f ms\r\n",time1,      (230400/1800.00)); // @suppress("Float formatting support")

		printf("conv2_time  %.2f   theor_time %.2f  ms\r\n",time2,    (204800/3900.00)); // @suppress("Float formatting support")
		printf("fully_time  %.2f    theor_time %.2f   ms\r\n",time3,  (2560/10800.00));// @suppress("Float formatting support")
		printf("all_time    %.2f                    ms\r\n",time4);// @suppress("Float formatting support")

		printf("the numer in picture is %d",lable);

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	int data_actu;
	static int count;

  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_UART_TxCpltCallback could be implemented in the user file
   */

	if(Uart1_Rx_Cnt >= 255)  //����ж�
	{
		Uart1_Rx_Cnt = 0;
		memset(RxBuffer,0x00,sizeof(RxBuffer));
		HAL_UART_Transmit(&huart3, (uint8_t *)"�������", 10,0xFFFF);

	}
	else
	{
		RxBuffer[Uart1_Rx_Cnt++] = aRxBuffer;   //��������ת��



		if((RxBuffer[Uart1_Rx_Cnt-1] == 0x0A)&&(RxBuffer[Uart1_Rx_Cnt-2] == 0x0D)) //�жϽ���λ
		{


			switch(Uart1_Rx_Cnt){
        case 5: data_actu=(RxBuffer[Uart1_Rx_Cnt-3]-48)+(RxBuffer[Uart1_Rx_Cnt-4]-48)*10+(RxBuffer[Uart1_Rx_Cnt-5]-48)*100; break;
        case 4: data_actu=(RxBuffer[Uart1_Rx_Cnt-3]-48)+(RxBuffer[Uart1_Rx_Cnt-4]-48)*10; break;
        case 3: data_actu=(RxBuffer[Uart1_Rx_Cnt-3]-48); break;

			}
			Image_array[count]=data_actu;
			if(count==(28*28-1))
			{
				run_flag=1;
				count=0;
			}
			count++;
			Uart1_Rx_Cnt=0;
			memset(RxBuffer,0x00,sizeof(RxBuffer)); //�������
		}
	}

	HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer, 1);   //�ٿ��������ж�
}

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART3 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
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
  htim2.Init.Prescaler = 95;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
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
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 6;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.battery_charging_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

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
