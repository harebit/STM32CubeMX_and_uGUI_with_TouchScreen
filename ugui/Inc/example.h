/*
 * example.h
 *
 *  Created on: 27.12.2018
 *      Author: Harebit
 */


#ifndef EXAMPLE_H_
#define EXAMPLE_H_

#include <ugui_ST7789.h>
#include "main.h"
//#include "stm32f1xx_hal.h"
#include "ugui.h"
#include "Touch.h"

#define MAX_OBJECTS 10
#define BuffOUT     40

char bufferOut[BuffOUT];

uint16_t Px, Py, PosX, PosY;

UG_WINDOW window_1;
UG_BUTTON button_0;
UG_BUTTON button_1;
UG_BUTTON button_2;
UG_BUTTON button_3;
UG_TEXTBOX textbox_1;
UG_IMAGE image_1;

UG_COLOR color[3];

UG_OBJECT obj_buff_wnd_1[MAX_OBJECTS];

void window_1_callback(UG_MESSAGE *msg);

void begin (void);
void loop (void);

extern uint8_t ugui_TOUCH_StateZ(void);
extern int16_t ugui_TOUCH_Px(void);
extern int16_t ugui_TOUCH_Py(void);
extern int16_t ugui_TOUCH_MeasureZ(void);

const UG_BMP hare;
extern const uint16_t hare_bmp[];



#endif /* EXAMPLE_H_ */
