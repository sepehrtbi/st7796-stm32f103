#ifndef ST7796_H_
#define ST7796_H_

#include "stm32f1xx_hal.h"

extern SPI_HandleTypeDef hspi1;

#define ST7796_CS_PORT GPIOA
#define ST7796_CS_PIN GPIO_PIN_3

#define ST7796_DC_PORT GPIOA
#define ST7796_DC_PIN GPIO_PIN_1

#define ST7796_RST_PORT GPIOA
#define ST7796_RST_PIN GPIO_PIN_2

#define ST7796_SWRESET 0x01
#define ST7796_SLPOUT 0x11
#define ST7796_DISPON 0x29
#define ST7796_CASET 0x2A
#define ST7796_RASET 0x2B
#define ST7796_RAMWR 0x2C
#define ST7796_MADCTL 0x36
#define ST7796_COLMOD 0x3A

void ST7796_Init(void);
void ST7796_FillScreen(uint16_t color);
void ST7796_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ST7796_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void ST7796_Drawshape(uint16_t x, uint16_t y,uint16_t x1, uint16_t y1, uint16_t color);
// void ST7796_Drawcircuit(uint16_t x, uint16_t y,uint16_t r, uint16_t color);
#endif