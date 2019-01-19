/*
 * Touch.h
 *
 *  Created on: 28.10.2018
 *      Author: Harebit
 */

#ifndef TOUCH_H_
#define TOUCH_H_

#ifdef __cplusplus
 extern "C" {
#endif

//#include "main.h"
#include "stm32f1xx_hal.h"

//TIM_HandleTypeDef htim3;

// Physical display size -> the same as in LCDConf.c

#define XSIZE_PHYS  320 // To be adapted to x-screen size
#define YSIZE_PHYS  240 // To be adapted to y-screen size
#define MIN_PRESSURE 100 // To be adapted to touch screen

volatile static int16_t pressure;

#define TOUCH_AD_LEFT 3400
#define TOUCH_AD_RIGHT 400
#define TOUCH_AD_TOP 3550
#define TOUCH_AD_BOTTOM 610

void Touch_Init(void);

static void MX_ADC1_Init(void);
static void MX_ADC2_Init(void);

#define XP_Pin GPIO_PIN_10  //PB10
#define XP_GPIO_Port GPIOB
#define YM_Pin GPIO_PIN_8	//PA8
#define YM_GPIO_Port GPIOA
#define YP_Pin GPIO_PIN_1	//PA1
#define YP_GPIO_Port GPIOA
#define XM_Pin GPIO_PIN_4	//PA4
#define XM_GPIO_Port GPIOA

#define NUMSAMPLES 5

void Touch_ADC_Init(void);

uint8_t ugui_TOUCH_StateZ(void);
int16_t ugui_TOUCH_Px(void);
int16_t ugui_TOUCH_Py(void);

uint16_t ugui_TOUCH_MeasureX(void);
uint16_t ugui_TOUCH_MeasureY(void);
int16_t ugui_TOUCH_MeasureZ(void);
void GPIO_X_MeasurementSetup(void);
void GPIO_Y_MeasurementSetup(void);
void GPIO_Z_MeasurementSetup(void);
uint16_t GPIO_X_Measurement(void);
uint16_t GPIO_Y_Measurement(void);
int16_t GPIO_Z_Measurement(void);
void GPIO_Restore_Outputs(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* TOUCH_H_ */
