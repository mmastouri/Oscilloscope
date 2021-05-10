/******************************************************************************
 *
 * @brief     This file is part of the TouchGFX 4.6.0 evaluation distribution.
 *
 * @author    Draupner Graphics A/S <http://www.touchgfx.com>
 *
 ******************************************************************************
 *
 * @section Copyright
 *
 * This file is free software and is provided for example purposes. You may
 * use, copy, and modify within the terms and conditions of the license
 * agreement.
 *
 * This is licensed software for evaluation use, any use must strictly comply
 * with the evaluation license agreement provided with delivery of the
 * TouchGFX software.
 *
 * The evaluation license agreement can be seen on www.touchgfx.com
 *
 * @section Disclaimer
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Draupner Graphics A/S has
 * no obligation to support this software. Draupner Graphics A/S is providing
 * the software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Draupner Graphics A/S can not be held liable for any consequential,
 * incidental, or special damages, or any other relief, or for any claim by
 * any third party, arising from your use of this software.
 *
 *****************************************************************************/

 /*
  * Include Section
  */
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/hal/BoardConfiguration.hpp>

#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>

#include <gui/model/Model.hpp>
#include <gui\model\ModelListener.hpp>

#include "stm32f7xx_hal.h"

#include <gui\common\main_header.h>

using namespace touchgfx;

/*
 * Kernel includes.
 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include <stdlib.h>
#include <string.h>

 /* Private variables ---------------------------------------------------------*/



/*
 * Define const/macros
 */
#define ULONG_MAX 0xFFFFFFFFUL 
#define  ADC_BUFF_SIZ   2000
#define configGUI_TASK_PRIORITY                 ( tskIDLE_PRIORITY + 3 )
#define configGUI_TASK_STK_SIZE                 ( 1000 )
#define CANVAS_BUFFER_SIZE (4000)

#ifdef __GNUC__
 /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
	set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/*
 * Define variables
 */

uint16_t adc_chn1_buffer[ADC_BUFF_SIZ];
uint16_t adc_chn2_buffer[ADC_BUFF_SIZ]; 

uint16_t adc_chn1_readptr = 0;
uint16_t adc_chn2_readptr = 0;

ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc3;

DMA_HandleTypeDef hdma_adc1;
DMA_HandleTypeDef hdma_adc3;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart2;

 /*
  * Fuction prototypes
  */
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_ADC3_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM2_Init_Mod(int period, int pulse);
static void MX_TIM4_Init_Mod(int period, int pulse);
static void MX_TIM4_Init(void);
static void MX_USART2_UART_Init(void);

/*
 *  Free RTOS Task Section
 */
static void GUITask(void* params)
{
	touchgfx::HAL::getInstance()->taskEntry();
}

/*
 *  Main Section
 */
int main(void)
{

	hw_init();
	touchgfx_init();


	MX_GPIO_Init();
	MX_DMA_Init();
	MX_ADC1_Init();
	MX_ADC3_Init();
	MX_TIM2_Init();
	MX_TIM4_Init();

	HAL_UART_Init(&huart2);
	printf("hello \n");

	static uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
	CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

	xTaskCreate(GUITask, (TASKCREATE_NAME_TYPE)"GUITask",
		configGUI_TASK_STK_SIZE,
		NULL,
		configGUI_TASK_PRIORITY,
		NULL);


	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_chn1_buffer, ADC_BUFF_SIZ);
	HAL_ADC_Start_DMA(&hadc3, (uint32_t*)adc_chn2_buffer, ADC_BUFF_SIZ);


	HAL_TIM_OC_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_4);

	vTaskStartScheduler();

	for (;;);

}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{

	if (hadc->Instance == ADC1)
	{
		adc_chn1_readptr = 0;
	}
	else if (hadc->Instance == ADC3)
	{
		adc_chn2_readptr = 0;
	}

}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if (hadc->Instance == ADC1)
	{
		adc_chn1_readptr = ADC_BUFF_SIZ/2;
	}
	else if (hadc->Instance == ADC3)
	{
		adc_chn2_readptr = ADC_BUFF_SIZ/2;
	}
}


uint16_t* PushDaTaToModel_1(void)
{
	return &adc_chn1_buffer[adc_chn1_readptr];

}

uint16_t* PushDaTaToModel_2(void)
{
	return &adc_chn2_buffer[adc_chn2_readptr];

}

/* ADC1 init function */
static void MX_ADC1_Init(void)
{

	ADC_ChannelConfTypeDef sConfig;

	/**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	*/
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
	hadc1.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T2_CC2;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = ENABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if (HAL_ADC_Init(&hadc1) != HAL_OK)
	{
		Error_Handler();
	}

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	*/
	sConfig.Channel = ADC_CHANNEL_0;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}

}

/* ADC3 init function */
static void MX_ADC3_Init(void)
{

	ADC_ChannelConfTypeDef sConfig;

	/**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	*/
	hadc3.Instance = ADC3;
	hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hadc3.Init.Resolution = ADC_RESOLUTION_12B;
	hadc3.Init.ScanConvMode = DISABLE;
	hadc3.Init.ContinuousConvMode = DISABLE;
	hadc3.Init.DiscontinuousConvMode = DISABLE;
	hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
	//hadc3.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T4_TRGO;
	hadc3.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T4_CC4;
	hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc3.Init.NbrOfConversion = 1;
	hadc3.Init.DMAContinuousRequests = ENABLE;
	hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if (HAL_ADC_Init(&hadc3) != HAL_OK)
	{
		Error_Handler();
	}

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	*/
	sConfig.Channel = ADC_CHANNEL_8;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{
	/* DMA controller clock enable */
	__HAL_RCC_DMA2_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA2_Stream0_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
	/* DMA2_Stream4_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream4_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream4_IRQn);

}

/** Configure pins as
		* Analog
		* Input
		* Output
		* EVENT_OUT
		* EXTI
*/
static void MX_GPIO_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);

	/*Configure GPIO pin : PA10 */
	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : BUTTON_Pin */
	GPIO_InitStruct.Pin = GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* TIM2 init function */
static void MX_TIM2_Init(void)
{
	TIM_MasterConfigTypeDef sMasterConfig;
	TIM_OC_InitTypeDef sConfigOC;

	__HAL_RCC_TIM2_CLK_ENABLE();

	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 4;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 100;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

	if (HAL_TIM_OC_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}

	sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
	sConfigOC.Pulse = 13;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_OC_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
}

/* TIM4 init function */
static void MX_TIM4_Init(void)
{

	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;
	TIM_OC_InitTypeDef sConfigOC;

	__HAL_RCC_TIM4_CLK_ENABLE();

	htim4.Instance = TIM4;
	htim4.Init.Prescaler = 4;
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim4.Init.Period = 100;
	htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}

	// if (HAL_TIM_Base_Init(&htim4) != HAL_OK)	
	if (HAL_TIM_OC_Init(&htim4) != HAL_OK)
	{
		Error_Handler();
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}

	sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
	sConfigOC.Pulse = 50;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_OC_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
	{
		Error_Handler();
	}

}


/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_ODD;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}

}

/* TIM2 init function */
static void MX_TIM2_Init_Mod(int period, int pulse)
{

	__HAL_TIM_SET_AUTORELOAD(&htim2, period);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pulse);
}

static void MX_TIM4_Init_Mod(int period, int pulse)
{
	__HAL_TIM_SET_AUTORELOAD(&htim4, period);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, pulse);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler */
	/* User can add his own implementation to report the HAL error return state */
	while (1)
	{
	}
	/* USER CODE END Error_Handler */
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	static bool stop_flag = false;
	
	if (stop_flag == false)
	{
		HAL_ADC_Stop_DMA(&hadc1);
		HAL_ADC_Stop_DMA(&hadc3);

		stop_flag = true;
	}
	else
	{
		HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_chn1_buffer, ADC_BUFF_SIZ);
		HAL_ADC_Start_DMA(&hadc3, (uint32_t*)adc_chn2_buffer, ADC_BUFF_SIZ);

		stop_flag = false;

	}
}


extern "C"
{

	PUTCHAR_PROTOTYPE
	{
		/* Place your implementation of fputc here */
		/* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
		HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, 0xFFFF);

		return ch;
	}
}


void GetDataFromModel(int channel, int value)
{
	int period;
	int pulse;

	switch (value)
	{


		//Div 50us
	case 0:
		period = 12;
		pulse = 6;
		break;

		//Div 100us
	case 1:
		period = 24;
		pulse = 12;
		break;

		//Div 200us
	case 2:
		period = 48;
		pulse = 24;
		break;

		//Div 500us
	case 3:
		period = 120;
		pulse = 60;
		break;

		//Div 1ms
	case 4:
		period = 240;
		pulse = 120;
		break;

		//Div 2ms
	case 5:
		period = 480;
		pulse = 240;
		break;

		//Div 5ms
	case 6:
		period = 1200;
		pulse = 600;
		break;

		//Div 10ms
	case 7:
		period = 2400;
		pulse = 1200;
		break;

		//Div 20ms
	case 8:
		period = 4800;
		pulse = 2400;
		break;

		//Div 50ms
	case 9:
		period = 12000;
		pulse = 6000;
		break;

		//Div 100ms
	case 10:
		period = 24000;
		pulse = 12000;
		break;

		//Div 200ms
	case 11:
		period = 48000;
		pulse = 24000;
		break;

		//Div 500ms
	case 12:
		period = 120000;
		pulse = 60000;
		break;
	}
	if (channel == 0)
		MX_TIM2_Init_Mod(period, pulse);
	else
		MX_TIM4_Init_Mod(period, pulse);
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	  ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	  /* USER CODE END 6 */

}

#endif