#ifndef __HAL_LCD_H__
#define __HAL_LCD_H__

#include <hal/hal_type.h>
#include <hal/hal_gpio.h>
#include <hal/hal_reg.h>

#define HSW                         10
#define HBP                         20
#define HFP                         10

#define VSW                         2
#define VBP                         2
#define VFP                         4

#define ACTIVE_WIDTH
#define ACTIVE_HEIGHT

void HAL_LCD_Init(void);

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
extern const u8 ltdc_pins[];
extern const u8 total_ltdc_pins;

#endif