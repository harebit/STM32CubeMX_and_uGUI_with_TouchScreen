/*
 * ugui_ST7735.h
 *
 *  Created on: 26.12.2018
 *      Author: Hare
 */

#ifndef UGUI_ST7789_H_
#define UGUI_ST7789_H_

#include "ugui.h"

/* *** Configuration. *** */

    /* Set here the name you have given to display CD and RESET signals in your schematic. */
#define DISPLAY_RESET           GraphicLCDIntf_Write8(0, 0x01)
#define DISPLAY_CD              DISP_CD

    /* Set here your display resolution. */
#define DISPLAY_WIDTH           240
#define DISPLAY_HEIGHT          320


#define CONCATENATE(name, function)                 CONCAT(name, function)
#define CONCAT(name, function)                      name##function

#define mmDisplayReset_Write(value) CONCATENATE(DISPLAY_RESET, _Write(value))
#define mmDisplayCD_Write(value)    CONCATENATE(DISPLAY_CD, _Write(value))

/* *** Glogal GUI structure for this. *** */
UG_GUI guiST7735;

/* *** Function prototypes. *** */
void parallelWriteDC0(uint8_t eightbit);
void parallelWriteDC1(uint8_t eightbit);
void parallelMultiWriteDC1(uint8_t *p_eightbit, int numItems);
void Display_Init();
void Display_PSet(UG_S16 x, UG_S16 y, UG_COLOR c);
void Display_WindowSet(unsigned int s_x,unsigned int e_x,unsigned int s_y,unsigned int e_y);

    // Accelerators.
UG_RESULT HW_FillFrame(UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR c);
UG_RESULT HW_DrawLine(UG_S16 x1 , UG_S16 y1 , UG_S16 x2 , UG_S16 y2 , UG_COLOR c );
UG_RESULT HW_DrawImage(UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, uint16_t *image, uint16_t pSize);

/* [] END OF FILE */


#endif /* UGUI_ST7789_H_ */
