#include "st7796.h"
#include "math.h"
static void ST7796_Select(void) {
HAL_GPIO_WritePin(ST7796_CS_PORT, ST7796_CS_PIN, GPIO_PIN_RESET);
}

static void ST7796_Unselect(void) {
    HAL_GPIO_WritePin(ST7796_CS_PORT, ST7796_CS_PIN, GPIO_PIN_SET);
}

static void ST7796_Command(uint8_t cmd) {
    HAL_GPIO_WritePin(ST7796_DC_PORT, ST7796_DC_PIN, GPIO_PIN_RESET); // DC=0
    HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
}

static void ST7796_Data(uint8_t* buff, size_t buff_size) {
    HAL_GPIO_WritePin(ST7796_DC_PORT, ST7796_DC_PIN, GPIO_PIN_SET); // DC=1
    HAL_SPI_Transmit(&hspi1, buff, buff_size, HAL_MAX_DELAY);
}

static void ST7796_Reset(void) {
    HAL_GPIO_WritePin(ST7796_RST_PORT, ST7796_RST_PIN, GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(ST7796_RST_PORT, ST7796_RST_PIN, GPIO_PIN_SET);
    HAL_Delay(150);
}

void ST7796_Init(void) {
    ST7796_Select();
    ST7796_Reset();
	  //HAL_Delay(130);

    ST7796_Command(ST7796_SWRESET); HAL_Delay(150);
    ST7796_Command(ST7796_SLPOUT); HAL_Delay(500);

    uint8_t data;

    ST7796_Command(ST7796_COLMOD);
    data = 0x55; // 16bit
    ST7796_Data(&data, 1);
    HAL_Delay(10);

    ST7796_Command(ST7796_DISPON);
    HAL_Delay(100);

    ST7796_Unselect();
}

void ST7796_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    uint8_t data[4];

    ST7796_Command(ST7796_CASET); 
    data[0] = x0 >> 8; data[1] = x0 & 0xFF;
    data[2] = x1 >> 8; data[3] = x1 & 0xFF;
    ST7796_Data(data, 4);

    ST7796_Command(ST7796_RASET); // ???????
    data[0] = y0 >> 8; data[1] = y0 & 0xFF;
    data[2] = y1 >> 8; data[3] = y1 & 0xFF;
    ST7796_Data(data, 4);

    ST7796_Command(ST7796_RAMWR); 
}

void ST7796_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    uint8_t data[2];
    data[0] = color >> 8;
    data[1] = color & 0xFF;

    ST7796_Select();
    ST7796_SetAddressWindow(x, y, x, y);
    ST7796_Data(data, 2);
    ST7796_Unselect();
}

void ST7796_FillScreen(uint16_t color) {
    uint8_t data[2] = { color >> 8, color & 0xFF };

    ST7796_Select();
    ST7796_SetAddressWindow(0, 0, 319, 479); 

    HAL_GPIO_WritePin(ST7796_DC_PORT, ST7796_DC_PIN, GPIO_PIN_SET);
    for (uint32_t i = 0; i < 320UL * 480UL; i++) {
        HAL_SPI_Transmit(&hspi1, data, 2, HAL_MAX_DELAY);
    }

    ST7796_Unselect();
}


void ST7796_Drawshape(uint16_t x, uint16_t y,uint16_t x1, uint16_t y1, uint16_t color)  {
    uint8_t data[2] = { color >> 8, color & 0xFF };

    ST7796_Select();
    ST7796_SetAddressWindow(x, y, x1, y1);

    HAL_GPIO_WritePin(ST7796_DC_PORT, ST7796_DC_PIN, GPIO_PIN_SET);
    for (uint32_t i = 0; i < 320UL * 480UL; i++) {
        HAL_SPI_Transmit(&hspi1, data, 2, HAL_MAX_DELAY);
    }

    ST7796_Unselect();
}


// void ST7796_Drawcircuit(uint16_t x, uint16_t y,uint16_t r, uint16_t color)  {
//    uint8_t data[2] = { color >> 8, color & 0xFF };
// 		uint16_t x1,y1,z;
// 		x1=sin(x)*r;
// 		y1=cos(y)*r;
		
//  ST7796_Select();
		
		
		
// 		ST7796_SetAddressWindow(x1, y1, x, y);
//  ST7796_Data(data, 2);
// ST7796_SetAddressWindow(sin(x),cos(y), x1, y1); 
//    HAL_GPIO_WritePin(ST7796_DC_PORT, ST7796_DC_PIN, GPIO_PIN_SET);
//    for (uint32_t i = 0; i < 320UL * 480UL; i++) {
//        HAL_SPI_Transmit(&hspi1, data, 2, HAL_MAX_DELAY);
//    }

//    ST7796_Unselect();
// }

