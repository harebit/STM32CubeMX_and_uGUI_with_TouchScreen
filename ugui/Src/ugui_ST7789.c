/*
 * ugui_ST7735.c
 *
 *  Created on: 26.12.2018
 *      Author: Harebit
 */

#include <ugui_ST7789.h>
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"

#include "ugui.h"

#define HDP (DISPLAY_WIDTH - 1)
#define VDP (DISPLAY_HEIGHT - 1)

void parallelWriteDC0(uint8_t eightbit){
//	printf("GPIO_pin: com  ");
HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_SET); // idle = high
HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_SET); // idle = high
HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET); // low = command

HAL_GPIO_WritePin(LCD_D0_GPIO_Port, LCD_D0_Pin, (eightbit & 1) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin(LCD_D1_GPIO_Port, LCD_D1_Pin, (eightbit & 2) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin(LCD_D2_GPIO_Port, LCD_D2_Pin, (eightbit & 4) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin(LCD_D3_GPIO_Port, LCD_D3_Pin, (eightbit & 8) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, (eightbit & 16) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (eightbit & 32) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (eightbit & 64) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, (eightbit & 128) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
//    printf ("eightbit: %X\n",eightbit);
HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_SET); // raising edge
}

void parallelWriteDC1(uint8_t eightbit){
//	printf("GPIO_pin: data  ");
HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_SET); // idle = high
HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_SET); // idle = high
HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET); // high = data

HAL_GPIO_WritePin(LCD_D0_GPIO_Port, LCD_D0_Pin, (eightbit & 1) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin(LCD_D1_GPIO_Port, LCD_D1_Pin, (eightbit & 2) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin(LCD_D2_GPIO_Port, LCD_D2_Pin, (eightbit & 4) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin(LCD_D3_GPIO_Port, LCD_D3_Pin, (eightbit & 8) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, (eightbit & 16) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (eightbit & 32) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (eightbit & 64) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, (eightbit & 128) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
//     printf ("eightbit: %X\n",eightbit);
HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_SET); // raising edge
}

void parallelMultiWriteDC1(uint8_t *p_eightbit, int numItems) {

	for (int i = 0; i < numItems; i++)
	parallelWriteDC1(p_eightbit[i]);

}

inline void Display_WriteCommand(uint8_t command)
{
    parallelWriteDC0(command);
}

inline void Display_WriteData(uint8_t data)
{
    parallelWriteDC1(data);
}

inline void Display_WriteMultiData(uint8_t *data, uint16_t size)
{
//	printf ("data: %X, %X, %X, %X\n",data[0],data[1],data[2],data[3]);
    parallelMultiWriteDC1(data, size);
}

inline void Display_Reset()
{
    parallelWriteDC0(0x01);         //Software reset
    HAL_Delay(10);
}

void Display_Init()
{
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(15);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(15);

	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_SET);


    parallelWriteDC0(0x01);   //Software Reset
    HAL_Delay(200);

    parallelWriteDC0(0x28);   // Display off

    parallelWriteDC0(0x3A);   // Pixel Format
    parallelWriteDC1(0x55);   // 565, 16-bit

    parallelWriteDC0(0xBB);   // VCOMS
    parallelWriteDC1(0x2B);   //  1,175

    parallelWriteDC0(0xC3);   // VRHS
    parallelWriteDC1(0x11);   //   4,4V

    parallelWriteDC0(0xD0);   // PWCTRL
    parallelWriteDC1(0xA4);   //
    parallelWriteDC1(0xA1);   // VDD=2,3V; AVCL=4,8V; AVDD=6,8V

    parallelWriteDC0(0x11);   // Exit Sleep
    HAL_Delay(120);

    parallelWriteDC0(0x29);   // Display on

    parallelWriteDC0(0x2c);   // Memory Write

    HAL_Delay(50);

    // Initialize global structure and set PSET to this.PSET.
    UG_Init(&guiST7735, Display_PSet, DISPLAY_WIDTH, DISPLAY_HEIGHT);

    // Register accelerators.
    UG_DriverRegister(DRIVER_FILL_FRAME, (void*)HW_FillFrame);
    UG_DriverRegister(DRIVER_DRAW_LINE, (void*)HW_DrawLine);
    UG_DriverRegister(DRIVER_DRAW_IMAGE, (void*)HW_DrawImage);
}

void Display_WindowSet(unsigned int s_x,unsigned int e_x,unsigned int s_y,unsigned int e_y)
{
    uint8_t data[4];

    data[0] = ((s_x)>>8);                   //SET start column address
    data[1] = (s_x);
    data[2] = ((e_x)>>8);			        //SET end column address
    data[3] = (e_x);
	Display_WriteCommand(0x2a);		        //SET column address
//	printf ("data: %X, %X, %X, %X\n",data[0],data[1],data[2],data[3]);
    Display_WriteMultiData(data, 4);


    data[0] = ((s_y)>>8);                   //SET start row address
    data[1] = (s_y);
    data[2] = ((e_y)>>8);			        //SET end row address
    data[3] = (e_y);
	Display_WriteCommand(0x2b);		        //SET row address
    Display_WriteMultiData(data, 4);
}

void Display_PSet(UG_S16 x, UG_S16 y, UG_COLOR c)
{
    if((x < 0) ||(x >= DISPLAY_WIDTH) || (y < 0) || (y >= DISPLAY_HEIGHT)) return;

    Display_WindowSet(x, x + 1, y, y + 1);
    Display_WriteCommand(0x2c);

#ifdef USE_COLOR_RGB888 // 24-bit colour 8*Red-8*Green-8*Blue

        	uint8_t data[3];

            data[0] = (c >> 16);
            data[1] = (c >> 8);
            data[2] = (c);

            Display_WriteMultiData(data, 3);
#endif
#ifdef USE_COLOR_RGB565 // 16-bit colour 5*Red-6*Green-5*Blue

        	uint8_t data[2];

            data[0] = (c >> 8);
            data[1] = (c);

            Display_WriteMultiData(data, 2);

#endif


}

UG_RESULT HW_FillFrame(UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR c)
{
    uint16_t loopx, loopy;

    if((x1 < 0) ||(x1 >= DISPLAY_WIDTH) || (y1 < 0) || (y1 >= DISPLAY_HEIGHT)) return UG_RESULT_FAIL;
    if((x2 < 0) ||(x2 >= DISPLAY_WIDTH) || (y2 < 0) || (y2 >= DISPLAY_HEIGHT)) return UG_RESULT_FAIL;

    Display_WindowSet(x1,x2,y1,y2);

    Display_WriteCommand(0x2c);
    for (loopx = x1; loopx < x2 + 1; loopx++)
    {
        for (loopy = y1; loopy < y2 + 1; loopy++)
        {
#ifdef USE_COLOR_RGB888 // 24-bit colour 8*Red-8*Green-8*Blue

        	uint8_t data[3];

            data[0] = (c >> 16);
            data[1] = (c >> 8);
            data[2] = (c);

            Display_WriteMultiData(data, 3);
#endif
#ifdef USE_COLOR_RGB565 // 16-bit colour 5*Red-6*Green-5*Blue

        	uint8_t data[2];

            data[0] = (c >> 8);
            data[1] = (c);

            Display_WriteMultiData(data, 2);
#endif
        }
    }

    return UG_RESULT_OK;
}

UG_RESULT HW_DrawLine( UG_S16 x1 , UG_S16 y1 , UG_S16 x2 , UG_S16 y2 , UG_COLOR c )
{
    if((x1 < 0) ||(x1 >= DISPLAY_WIDTH) || (y1 < 0) || (y1 >= DISPLAY_HEIGHT)) return UG_RESULT_FAIL;
    if((x2 < 0) ||(x2 >= DISPLAY_WIDTH) || (y2 < 0) || (y2 >= DISPLAY_HEIGHT)) return UG_RESULT_FAIL;

    // If it is a vertical or a horizontal line, draw it.
    // If not, then use original drawline routine.
    if ((x1 == x2) || (y1 == y2))
    {
        HW_FillFrame(x1, y1, x2, y2, c);
        return UG_RESULT_OK;
    }

    return UG_RESULT_FAIL;
}

UG_RESULT HW_DrawImage(UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, uint16_t *image, uint16_t pSize)
{

    if((x1 < 0) ||(x1 >= DISPLAY_WIDTH) || (y1 < 0) || (y1 >= DISPLAY_HEIGHT)) return UG_RESULT_FAIL;
    if((x2 < 0) ||(x2 >= DISPLAY_WIDTH) || (y2 < 0) || (y2 >= DISPLAY_HEIGHT)) return UG_RESULT_FAIL;

    Display_WindowSet(x1,x2,y1,y2);

#ifdef USE_COLOR_RGB888 // 24-bit colour 8*Red-8*Green-8*Blue

    Display_WriteCommand(0x2c);
    Display_WriteMultiData(image, pSize*3);

#endif
#ifdef USE_COLOR_RGB565 // 16-bit colour 5*Red-6*Green-5*Blue

    Display_WriteCommand(0x2c);

    uint16_t i;
    uint16_t buffer[(pSize-1)];
    uint16_t *ptr = image;
    uint8_t data[2];

    for(i=0 ;i < pSize; i++)
    {
    	buffer[i] = *(ptr++);

            data[0] = (buffer[i] >> 8);
            data[1] = (buffer[i]);
 //           printf("data: %X, %X\n",data[0],data[1]);
            Display_WriteMultiData(data, 2);
    }
#endif
    return UG_RESULT_OK;
}

/* [] END OF FILE */
