/*
 * Touch.c
 *
 *  Created on: 28.10.2018
 *      Author: Harebit
 */


#include "Touch.h"
#include "ugui.h"
#include "stm32f1xx_hal_adc.h"
#include "stdlib.h"


#ifdef __cplusplus
 extern "C" {
#endif



/*void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) // activate for timer interrupt -> don't work well
{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
			GUI_TOUCH_Exec();
			GUI_Exec();
}*/

	ADC_HandleTypeDef hadc1;
	ADC_HandleTypeDef hadc2;


/* ADC1 init function */
static void MX_ADC1_Init(void)
{
  ADC_ChannelConfTypeDef sConfig;

    /**Common config
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure Regular Channel
    */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_71CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

}
/* ADC2 init function */
static void MX_ADC2_Init(void)
{
  ADC_ChannelConfTypeDef sConfig;

    /**Common config
    */
  hadc2.Instance = ADC2;
  hadc2.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure Regular Channel
    */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_71CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();

    /**ADC1 GPIO Configuration
    PA1     ------> ADC1_IN1
    */
    GPIO_InitStruct.Pin = YP_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(YP_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
  else if(adcHandle->Instance==ADC2)
  {
  /* USER CODE BEGIN ADC2_MspInit 0 */

  /* USER CODE END ADC2_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_ADC2_CLK_ENABLE();

    /**ADC2 GPIO Configuration
    PA4     ------> ADC2_IN4
    */
    GPIO_InitStruct.Pin = XM_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(XM_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN ADC2_MspInit 1 */

  /* USER CODE END ADC2_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PA1     ------> ADC1_IN1
    */
    HAL_GPIO_DeInit(YP_GPIO_Port, YP_Pin);

  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
  else if(adcHandle->Instance==ADC2)
  {
  /* USER CODE BEGIN ADC2_MspDeInit 0 */

  /* USER CODE END ADC2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC2_CLK_DISABLE();

    /**ADC2 GPIO Configuration
    PA4     ------> ADC2_IN4
    */
    HAL_GPIO_DeInit(XM_GPIO_Port, XM_Pin);

  /* USER CODE BEGIN ADC2_MspDeInit 1 */

  /* USER CODE END ADC2_MspDeInit 1 */
  }
}

int16_t ugui_TOUCH_MeasureZ(void){ // for X measurements

	GPIO_Z_MeasurementSetup();
	pressure = GPIO_Z_Measurement();
	return pressure;
}

uint16_t ugui_TOUCH_MeasureX(void){

	int xValue = 0;
	GPIO_X_MeasurementSetup();
	xValue = GPIO_X_Measurement();
	//	printf("xValue: %i\t", xValue);
	return xValue;
}

uint16_t ugui_TOUCH_MeasureY(void){

	int yValue = 0;
	GPIO_Y_MeasurementSetup();
	yValue = GPIO_Y_Measurement();
//	printf("yValue: %i\t", yValue);
	return yValue;
}
uint8_t ugui_TOUCH_StateZ(){

	pressure = ugui_TOUCH_MeasureZ();
	if(pressure > MIN_PRESSURE)
		return TOUCH_STATE_PRESSED;
	else return TOUCH_STATE_RELEASED;
}

int16_t ugui_TOUCH_Py()
{
	int16_t Py;
	Py = ((ugui_TOUCH_MeasureX())- TOUCH_AD_RIGHT)* (XSIZE_PHYS-1)/(TOUCH_AD_LEFT-TOUCH_AD_RIGHT);
	if (Py < 0) Py = 0;
	if (Py > XSIZE_PHYS) Py = XSIZE_PHYS;
	return Py;

}

/* ***** attention! ***************************************************
 * x and y turned 90° to right
*************** on Display ->  x = DISPLAY_WIDTH 240
*			  *			   |   y = DISPLAY_HEIGHT 320
*			  *            v
*			  *
*			  *
*			  *
*			  *
*			  *
*			  * 			^
*			  * Measurement |   x = XSIZE_PHYS 320
***************				->  y = YSIZE_PHYS 240
*/

int16_t ugui_TOUCH_Px()
{
	int16_t Px;
	Px = ((ugui_TOUCH_MeasureY()- TOUCH_AD_BOTTOM) * (YSIZE_PHYS-1)/(TOUCH_AD_TOP-TOUCH_AD_BOTTOM));
	if (Px < 0) Px = 0;
	if (Px > YSIZE_PHYS) Px = YSIZE_PHYS;
	return Px;

}


void Touch_ADC_Init(void){
	__HAL_RCC_ADC1_CLK_ENABLE();
	__HAL_RCC_ADC2_CLK_ENABLE();
	MX_ADC1_Init();
	MX_ADC2_Init();
	GPIO_Restore_Outputs();
	//HAL_TIM_Base_Start_IT(&htim3);
}

//GPIO_PinState P_PinState;
//GPIO_PinState M_PinState;

void GPIO_X_MeasurementSetup(void)
{
	// Y axis YP input  YM disconnect
	GPIO_InitTypeDef GPIO_InitStruct;

//	P_PinState = ((XP_GPIO_Port->ODR & XP_Pin) != 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
//	M_PinState = ((XM_GPIO_Port->ODR & XM_Pin) != 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);

	GPIO_InitStruct.Pin = YP_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(YP_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = YM_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(YM_GPIO_Port, &GPIO_InitStruct);

    // X axis output
	GPIO_InitStruct.Pin = XM_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(XM_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = XP_Pin;
	HAL_GPIO_Init(XP_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(XP_GPIO_Port, XP_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(XM_GPIO_Port, XM_Pin, GPIO_PIN_RESET);
}

uint16_t GPIO_X_Measurement(void){
	int16_t g_ADCValue;
	uint16_t sValues[NUMSAMPLES];
	uint16_t xValue;

	for (int i = 0; i < NUMSAMPLES; i++) {
		HAL_ADC_Start(&hadc1);
		if (HAL_ADC_PollForConversion(&hadc1, 1000000) == HAL_OK) {
			g_ADCValue = HAL_ADC_GetValue(&hadc1) & 0xFFF;
			sValues[i] = g_ADCValue;
		}
	}
//	HAL_GPIO_WritePin(YP_GPIO_Port, XP_Pin, P_PinState);
//	HAL_GPIO_WritePin(YM_GPIO_Port, XM_Pin, M_PinState);
	GPIO_Restore_Outputs();
	xValue =  4096-((sValues[0]+sValues[1]+sValues[2]+sValues[3]+sValues[4])/NUMSAMPLES);

	return xValue;
}
void GPIO_Y_MeasurementSetup(void)
{
	// X axis XM input  XP disconnect
	GPIO_InitTypeDef GPIO_InitStruct;

//	P_PinState = ((YP_GPIO_Port->ODR & YP_Pin) != 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
//	M_PinState = ((YM_GPIO_Port->ODR & YM_Pin) != 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);

	GPIO_InitStruct.Pin = XM_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(XM_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = XP_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(XP_GPIO_Port, &GPIO_InitStruct);

	// Y axis output
	GPIO_InitStruct.Pin = YP_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(YP_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = YM_Pin;
	HAL_GPIO_Init(YM_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(YP_GPIO_Port, YP_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(YM_GPIO_Port, YM_Pin, GPIO_PIN_RESET);
}

uint16_t GPIO_Y_Measurement(void){
	int16_t g_ADCValue;
	uint16_t sValues[NUMSAMPLES];
	uint16_t yValue;


	for (int i = 0; i < NUMSAMPLES; i++) {
		HAL_ADC_Start(&hadc2);
		if (HAL_ADC_PollForConversion(&hadc2, 1000000) == HAL_OK) {
			g_ADCValue = HAL_ADC_GetValue(&hadc2) & 0xFFF;
			sValues[i] = g_ADCValue;
		}
	}
//	HAL_GPIO_WritePin(YP_GPIO_Port, YP_Pin, P_PinState);
//	HAL_GPIO_WritePin(YM_GPIO_Port, YM_Pin, M_PinState);
	GPIO_Restore_Outputs();
	yValue = ((sValues[0]+sValues[1]+sValues[2]+sValues[3]+sValues[4])/NUMSAMPLES);

	return yValue;
}

void GPIO_Z_MeasurementSetup()
{
	// XM input YP input
	GPIO_InitTypeDef GPIO_InitStruct;

//	P_PinState = ((XP_GPIO_Port->ODR & XP_Pin) != 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
//	M_PinState = ((YM_GPIO_Port->ODR & YM_Pin) != 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);

	GPIO_InitStruct.Pin = XM_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(XM_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = YP_Pin;
	HAL_GPIO_Init(YP_GPIO_Port, &GPIO_InitStruct);

	// XP output YM output
	GPIO_InitStruct.Pin = XP_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(XP_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = YM_Pin;
	HAL_GPIO_Init(YM_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(XP_GPIO_Port, XP_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(YM_GPIO_Port, YM_Pin, GPIO_PIN_SET);

}

int16_t GPIO_Z_Measurement(void){

	uint8_t i;
	int16_t g_ADCValue1;
	int16_t g_ADCValue2;
	uint16_t sValues1[NUMSAMPLES];
	uint16_t sValues2[NUMSAMPLES];
	int16_t pressure;

	for (i = 0; i < NUMSAMPLES; i++) {
		HAL_ADC_Start(&hadc1);
		HAL_ADC_Start(&hadc2);
		if ((HAL_ADC_PollForConversion(&hadc1, 10000) == HAL_OK) &&	(HAL_ADC_PollForConversion(&hadc2, 10000) == HAL_OK)) {
			g_ADCValue1 = HAL_ADC_GetValue(&hadc1) & 0xFFF;
			g_ADCValue2 = HAL_ADC_GetValue(&hadc2) & 0xFFF;
			sValues1[i] = g_ADCValue1;
			sValues2[i] = g_ADCValue2;
		}
		else {
			sValues1[i]=4096; //the same as no pressure
			sValues2[i]=0;
		}
	}

	uint16_t z1 = (sValues1[0]+sValues1[1]+sValues1[2]+sValues1[3]+sValues1[4])/NUMSAMPLES;
	uint16_t z2 = (sValues2[0]+sValues2[1]+sValues2[2]+sValues2[3]+sValues2[4])/NUMSAMPLES;

/*	printf("z1: %i\t", z1);
	printf("z1: %i\t", z2);*/

	pressure = abs((4096+z2-z1)/2);

//	printf("pressure: %i\n", pressure);

//	HAL_GPIO_WritePin(XP_GPIO_Port, XP_Pin, P_PinState);
//	HAL_GPIO_WritePin(YM_GPIO_Port, YM_Pin, M_PinState);
	GPIO_Restore_Outputs();
	return pressure;
}

void GPIO_Restore_Outputs(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = XM_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(XM_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = YP_Pin;
	HAL_GPIO_Init(YP_GPIO_Port, &GPIO_InitStruct);


	GPIO_InitStruct.Pin = XP_Pin;
	HAL_GPIO_Init(XP_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = YM_Pin;
	HAL_GPIO_Init(YM_GPIO_Port, &GPIO_InitStruct);
}

#ifdef __cplusplus
}
#endif // __cplusplus
