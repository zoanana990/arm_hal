#ifndef __HAL_LCD_H__
#define __HAL_LCD_H__

#include <hal/hal_type.h>
#include <hal/hal_gpio.h>
#include <hal/hal_reg.h>

#define HAL_LCD_HSW                  10
#define HAL_LCD_HBP                  20
#define HAL_LCD_HFP                  10

#define HAL_LCD_VSW                  2
#define HAL_LCD_VBP                  2
#define HAL_LCD_VFP                  4

#define HAL_LCD_WIDTH                240
#define HAL_LCD_HEIGHT               320

/* Select the orientation */
#define PORTRAIT                     0
#define LANDSCAPE                    1
#define HAL_LCD_ORIENTATION          PORTRAIT

#if(HAL_LCD_ORIENTATION == PORTRAIT)
    #define HAL_LCD_ACTIVE_WIDTH     HAL_LCD_WIDTH
    #define HAL_LCD_ACTIVE_HEIGHT    HAL_LCD_HEIGHT
#elif(HAL_LCD_ORIENTATION == LANDSCAPE)
    #define HAL_LCD_ACTIVE_WIDTH     HAL_LCD_HEIGHT
    #define HAL_LCD_ACTIVE_HEIGHT    HAL_LCD_WIDTH
#endif

#define HAL_LTDC_LAYER_WIDTH         HAL_LCD_ACTIVE_WIDTH
#define HAL_LTDC_LAYER_HEIGHT        HAL_LCD_ACTIVE_HEIGHT
#define HAL_LTDC_LAYER_H_START       0
#define HAL_LTDC_LAYER_H_STOP        HAL_LTDC_LAYER_WIDTH
#define HAL_LTDC_LAYER_V_START       0
#define HAL_LTDC_LAYER_V_STOP        HAL_LTDC_LAYER_HEIGHT

/* Select Pixel Format */
#define HAL_LCD_PIXEL_FMT_L8         1
#define HAL_LCD_PIXEL_FMT_RGB565     2
#define HAL_LCD_PIXEL_FMT_RGB666     3
#define HAL_LCD_PIXEL_FMT_RGB888     4
#define HAL_LCD_PIXEL_FMT            HAL_LCD_PIXEL_FMT_RGB565

/**
 * Pin Definition
 * Board Schematic: STM32F429 DISCO E01
 * */
#define HAL_LCD_DATA_R2_PIN          HAL_GPIO_PIN_10
#define HAL_LCD_DATA_R3_PIN          HAL_GPIO_PIN_0
#define HAL_LCD_DATA_R4_PIN          HAL_GPIO_PIN_11
#define HAL_LCD_DATA_R5_PIN          HAL_GPIO_PIN_12
#define HAL_LCD_DATA_R6_PIN          HAL_GPIO_PIN_1
#define HAL_LCD_DATA_R7_PIN          HAL_GPIO_PIN_6

#define HAL_LCD_DATA_G2_PIN          HAL_GPIO_PIN_6
#define HAL_LCD_DATA_G3_PIN          HAL_GPIO_PIN_10
#define HAL_LCD_DATA_G4_PIN          HAL_GPIO_PIN_10
#define HAL_LCD_DATA_G5_PIN          HAL_GPIO_PIN_11
#define HAL_LCD_DATA_G6_PIN          HAL_GPIO_PIN_7
#define HAL_LCD_DATA_G7_PIN          HAL_GPIO_PIN_3

#define HAL_LCD_DATA_B2_PIN          HAL_GPIO_PIN_6
#define HAL_LCD_DATA_B3_PIN          HAL_GPIO_PIN_11
#define HAL_LCD_DATA_B4_PIN          HAL_GPIO_PIN_12
#define HAL_LCD_DATA_B5_PIN          HAL_GPIO_PIN_3
#define HAL_LCD_DATA_B6_PIN          HAL_GPIO_PIN_8
#define HAL_LCD_DATA_B7_PIN          HAL_GPIO_PIN_9

#define HAL_LCD_HSYNC_PIN            HAL_GPIO_PIN_6
#define HAL_LCD_VSYNC_PIN            HAL_GPIO_PIN_4
#define HAL_LCD_DE_PIN               HAL_GPIO_PIN_10
#define HAL_LCD_DOTCLK_PIN           HAL_GPIO_PIN_7

/**
 * Port Definition
 * Board Schematic: STM32F429 DISCO E01
 */

#define HAL_LCD_DATA_R2_PORT         GPIOC
#define HAL_LCD_DATA_R3_PORT         GPIOB
#define HAL_LCD_DATA_R4_PORT         GPIOA
#define HAL_LCD_DATA_R5_PORT         GPIOA
#define HAL_LCD_DATA_R6_PORT         GPIOB
#define HAL_LCD_DATA_R7_PORT         GPIOG

#define HAL_LCD_DATA_G2_PORT         GPIOA
#define HAL_LCD_DATA_G3_PORT         GPIOG
#define HAL_LCD_DATA_G4_PORT         GPIOB
#define HAL_LCD_DATA_G5_PORT         GPIOB
#define HAL_LCD_DATA_G6_PORT         GPIOC
#define HAL_LCD_DATA_G7_PORT         GPIOD

#define HAL_LCD_DATA_B2_PORT         GPIOD
#define HAL_LCD_DATA_B3_PORT         GPIOG
#define HAL_LCD_DATA_B4_PORT         GPIOG
#define HAL_LCD_DATA_B5_PORT         GPIOA
#define HAL_LCD_DATA_B6_PORT         GPIOB
#define HAL_LCD_DATA_B7_PORT         GPIOB

#define HAL_LCD_HSYNC_PORT           GPIOC
#define HAL_LCD_VSYNC_PORT           GPIOA
#define HAL_LCD_DE_PORT              GPIOF
#define HAL_LCD_DOTCLK_PORT          GPIOG

extern GPIO_RegDef_t *hal_ltdc_io_port[];
extern u8 hal_fb[];
extern const u8 ltdc_pins[];
extern const u8 total_ltdc_pins;

void HAL_LCD_Init(void);
u32 hal_lcd_get_fb_address(void);
u16 Convert_RGB888_to_RGB565(u32 rgb888);
void write_to_fb_rgb565(u16 *fb_ptr,u32 n_pixels, u16 rgb565);
void write_to_fb_rgb888(u32 rgb888);
void write_to_fb_rgb666(u32 rgb666);
void hal_lcd_set_fb_background_color(u32 rgb888);
void hal_lcd_fill_rect(u32 rgb888, u32 x_start, u32 x_width,u32 y_start,u32 y_width);
#endif