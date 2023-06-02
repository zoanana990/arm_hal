#ifndef __HAL_STM32F4__
#define __HAL_STM32F4__

#include <hal_type.h>

#define __vo volatile

/*
 * Memory map
 * */
#define FLASH_BASE_ADDR             (0x08000000UL)
#define SRAM1_BASE_ADDR             (0x20000000UL)
#define SRAM2_BASE_ADDR             (0x2001C000UL)
#define SRAM3_BASE_ADDR             (0x20020000UL)
#define ROM_BASE_ADDR               (0x1FFF0000UL)

/* main SRAM address */
#define SRAM                        SRAM1_BASE_ADDR

/*
 * AHBx and APBx Bus Peripheral base address
 * */
#define PERIF_BASE                  (0x40000000UL)
#define APB1PERIF_BASE              PERIF_BASE
#define APB2PERIF_BASE              (0x40010000UL)
#define AHB1PERIF_BASE              (0x40020000UL)
#define AHB2PERIF_BASE              (0x50000000UL)
#define AHB3PERIF_BASE              (0xA0000000UL)

/*
 * Base address of peripherals which are hanging on AHB1 Bus
 * */
#define GPIOA_BASEADDR              (AHB1PERIF_BASE + 0x0000)
#define GPIOB_BASEADDR              (AHB1PERIF_BASE + 0x0400)
#define GPIOC_BASEADDR              (AHB1PERIF_BASE + 0x0800)
#define GPIOD_BASEADDR              (AHB1PERIF_BASE + 0x0C00)
#define GPIOE_BASEADDR              (AHB1PERIF_BASE + 0x1000)
#define GPIOF_BASEADDR              (AHB1PERIF_BASE + 0x1400)
#define GPIOG_BASEADDR              (AHB1PERIF_BASE + 0x1800)
#define GPIOH_BASEADDR              (AHB1PERIF_BASE + 0x1C00)
#define GPIOI_BASEADDR              (AHB1PERIF_BASE + 0x2000)
#define GPIOJ_BASEADDR              (AHB1PERIF_BASE + 0x2400)
#define GPIOK_BASEADDR              (AHB1PERIF_BASE + 0x2800)

/*
 * Base addresses of peripherals which are hanging on APB1 bus
 * */
#define I2C1_BASEADDR               (APB1PERIF_BASE + 0x5400)
#define I2C2_BASEADDR               (APB1PERIF_BASE + 0x5C00)
#define I2C3_BASEADDR               (APB1PERIF_BASE + 0x6400)

#define SPI2_BASEADDR               (APB1PERIF_BASE + 0x3800)
#define SPI3_BASEADDR               (APB1PERIF_BASE + 0x3C00)

#define USART2_BASEADDR             (APB1PERIF_BASE + 0x4400)
#define USART3_BASEADDR             (APB1PERIF_BASE + 0x4800)
#define UART4_BASEADDR              (APB1PERIF_BASE + 0x4C00)
#define UART5_BASEADDR              (APB1PERIF_BASE + 0x5000)

/*
 * Base addresses of peripherals which are hanging on APB2 bus
 * */
#define EXT1_BASEADDR               (APB2PERIF_BASE + 0x3C00)
#define SPI1_BASEADDR               (APB2PERIF_BASE + 0x3000)
#define SYSCFG_BASEADDR             (APB2PERIF_BASE + 0x3800)

#define USART1_BASEADDR             (APB2PERIF_BASE + 0x1000)
#define USART6_BASEADDR             (APB2PERIF_BASE + 0x1400)


/*************** PERIPHERAL REGISTER DEFINITION STRUCTURES ***************/
/*
 * Note: registers of a peripheral are specific to MCU
 * e.g.: Number of registers of SPI peripheral of STM32F4x family of MCUs may be different
 * Compared to number of registers of SPI peripheral of STM32Lx or STM32F0x MCUs
 * */
typedef struct
{
    __vo u32 moder;   /* mode register */
    __vo u32 otyper;  /* output type register */
    __vo u32 ospeedr; /* output speed register */
    __vo u32 pupdr;   /* pull-up/pull-down register */
    __vo u32 idr;     /* input data register */
    __vo u32 odr;     /* output data register */
    __vo u32 bsrr;    /* set/reset register*/
    __vo u32 lckr;    /* configuration lock register */
    __vo u32 afrl;    /* alternate function low register */
    __vo u32 afrh;    /* alternate function high register */
} GPIO_RegDef_t;

/* Need to notice which the target is */
#ifdef STM32F407
typedef struct {

} RCC_RegDef_t;
#else
typedef struct {

} RCC_RegDef_t;
#endif

/*
 * Peripheral definition:
 *  Peripheral base address type casted to xxx_RegDef_t
 * */
#define GPIOA               ((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOB               ((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define GPIOC               ((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD               ((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define GPIOE               ((GPIO_RegDef_t *)GPIOE_BASEADDR)
#define GPIOF               ((GPIO_RegDef_t *)GPIOF_BASEADDR)
#define GPIOG               ((GPIO_RegDef_t *)GPIOG_BASEADDR)
#define GPIOH               ((GPIO_RegDef_t *)GPIOH_BASEADDR)
#define GPIOI               ((GPIO_RegDef_t *)GPIOI_BASEADDR)
#define GPIOJ               ((GPIO_RegDef_t *)GPIOJ_BASEADDR)
#define GPIOK               ((GPIO_RegDef_t *)GPIOK_BASEADDR)

#endif