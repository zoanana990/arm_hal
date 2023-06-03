#ifndef __HAL_STM32F4__
#define __HAL_STM32F4__

#include <hal/hal_type.h>
#include <hal/hal.h>

/*
 * Some common macros
 * */
#define __vo                        volatile
#define ENABLE                      1
#define DISABLE                     0
#define SET                         ENABLE
#define RESET                       DISABLE
#define GPIO_PIN_SET                SET
#define GPIO_PIN_RESET              RESET

/************************************* Processor Specific **************************************
 * ARM Cortex M4 Processor NVIC ISERx register address
 * */
#define NVIC_ISER0                  ((__vo u32 *) 0xE000E100)
#define NVIC_ISER1                  ((__vo u32 *) 0xE000E104)
#define NVIC_ISER2                  ((__vo u32 *) 0xE000E108)
#define NVIC_ISER3                  ((__vo u32 *) 0xE000E10C)
#define NVIC_ISER4                  ((__vo u32 *) 0xE000E110)
#define NVIC_ISER5                  ((__vo u32 *) 0xE000E114)
#define NVIC_ISER6                  ((__vo u32 *) 0xE000E118)
#define NVIC_ISER7                  ((__vo u32 *) 0xE000E11C)

/*
 * ARM Cortex M4 Processor NVIC ICER register address
 * */
#define NVIC_ICER0                  ((__vo u32 *) 0xE000E180)
#define NVIC_ICER1                  ((__vo u32 *) 0xE000E184)
#define NVIC_ICER2                  ((__vo u32 *) 0xE000E188)
#define NVIC_ICER3                  ((__vo u32 *) 0xE000E18C)
#define NVIC_ICER4                  ((__vo u32 *) 0xE000E190)
#define NVIC_ICER5                  ((__vo u32 *) 0xE000E194)
#define NVIC_ICER6                  ((__vo u32 *) 0xE000E198)
#define NVIC_ICER7                  ((__vo u32 *) 0xE000E19C)

/*
 * ARM Cortex M4 Processor NVIC IPR register address
 * */
#define NVIC_PR_BASE_ADDR           ((__vo u32 *) 0xE000E400)

#define NO_PR_BITS_IMPLEMENTED      4

/********************************** End of Processor Specific **********************************
 * */
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

#define RCC_BASEADDR                (AHB1PERIF_BASE + 0x3800)


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
#define EXTI_BASEADDR               (APB2PERIF_BASE + 0x3C00)
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
    __vo u32 moder;     /* mode register */
    __vo u32 otyper;    /* output type register */
    __vo u32 ospeedr;   /* output speed register */
    __vo u32 pupdr;     /* pull-up/pull-down register */
    __vo u32 idr;       /* input data register */
    __vo u32 odr;       /* output data register */
    __vo u32 bsrr;      /* set/reset register*/
    __vo u32 lckr;      /* configuration lock register */
    __vo u32 afr[2];    /* [0]: alternate function low register */
                        /* [1]: alternate function high register */
} GPIO_RegDef_t;

/* Need to notice which the target is */
#ifdef STM32F429
typedef struct {
    __vo u32 cr;
    __vo u32 pllcfgr;
    __vo u32 cfgr;
    __vo u32 cir;
    __vo u32 ahb1rstr;
    __vo u32 ahb2rstr;
    __vo u32 ahb3rstr;
    __vo u32 apb1rstr;
    __vo u32 apb2rstr;
    __vo u32 ahb1enr;
    __vo u32 ahb2enr;
    __vo u32 ahb3enr;
    __vo u32 apb1enr;
    __vo u32 apb2enr;
    __vo u32 ahb1lpenr;
    __vo u32 ahb2lpenr;
    __vo u32 ahb3lpenr;
    __vo u32 apb1lpenr;
    __vo u32 apb2lpenr;
    __vo u32 bdcr;
    __vo u32 csr;
    __vo u32 sscgr;
    __vo u32 plli2scfgr;
    __vo u32 pllsaicfgr;
    __vo u32 dckcfgr;
} RCC_RegDef_t;
#else
typedef struct {
    __vo u32 cr;
    __vo u32 pllcfgr;
    __vo u32 cfgr;
    __vo u32 cir;
    __vo u32 ahb1rstr;
    __vo u32 ahb2rstr;
    __vo u32 ahb3rstr;
    __vo u32 reserved0;
    __vo u32 apb1rstr;
    __vo u32 apb2rstr;
    __vo u32 reserved1[2];
    __vo u32 ahb1enr;
    __vo u32 ahb2enr;
    __vo u32 ahb3enr;
    __vo u32 reserved2;
    __vo u32 apb1enr;
    __vo u32 apb2enr;
    __vo u32 reserved3[2];
    __vo u32 ahb1lpenr;
    __vo u32 ahb2lpenr;
    __vo u32 ahb3lpenr;
    __vo u32 reserved4;
    __vo u32 apb1lpenr;
    __vo u32 apb2lpenr;
    __vo u32 reserved5[2];
    __vo u32 bdcr;
    __vo u32 csr;
    __vo u32 reserved6;
    __vo u32 sscgr;
    __vo u32 plli2scfgr;
} RCC_RegDef_t;
#endif

typedef struct
{
    __vo u32 imr;
    __vo u32 emr;
    __vo u32 rtsr;
    __vo u32 ftsr;
    __vo u32 swier;
    __vo u32 pr;
} EXTI_RegDef_t;

#ifdef STM32F429
typedef struct {
    __vo u32 memrmp;
    __vo u32 pmc;
    __vo u32 exticr[4];
    u32 reserved1[2];
    __vo u32 cmpcr;
} SYSCFG_RegDef_t;
#else
typedef struct {
    __vo u32 memrmp;
    __vo u32 pmc;
    __vo u32 exticr[4];
    u32 reserved1[2];
    __vo u32 cmpcr;
} SYSCFG_RegDef_t;
#endif

typedef struct
{
    __vo u32 sr;
    __vo u32 dr;
    __vo u32 brr;
    __vo u32 cr1;
    __vo u32 cr2;
    __vo u32 cr3;
    __vo u32 gtpr;
} USART_RegDef_t;

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

#define RCC                 ((RCC_RegDef_t *) RCC_BASEADDR)

#define EXTI                ((EXTI_RegDef_t *) EXTI_BASEADDR)

#define SYSCFG              ((SYSCFG_RegDef_t *) SYSCFG_BASEADDR)

/************************************ GPIO CLOCK MACROs ***********************************/
/*
 * Clock enable macros for GPIO peripherals
 * */
#define GPIOA_PCLK_EN()     (RCC->ahb1enr |= (1 << 0))
#define GPIOB_PCLK_EN()     (RCC->ahb1enr |= (1 << 1))
#define GPIOC_PCLK_EN()     (RCC->ahb1enr |= (1 << 2))
#define GPIOD_PCLK_EN()     (RCC->ahb1enr |= (1 << 3))
#define GPIOE_PCLK_EN()     (RCC->ahb1enr |= (1 << 4))
#define GPIOF_PCLK_EN()     (RCC->ahb1enr |= (1 << 5))
#define GPIOG_PCLK_EN()     (RCC->ahb1enr |= (1 << 6))
#define GPIOH_PCLK_EN()     (RCC->ahb1enr |= (1 << 7))
#define GPIOI_PCLK_EN()     (RCC->ahb1enr |= (1 << 8))

/*
 * Clock Disable macros for GPIO peripherals
 * */
#define GPIOA_PCLK_DI()     (RCC->ahb1enr &= ~(1 << 0))
#define GPIOB_PCLK_DI()     (RCC->ahb1enr &= ~(1 << 1))
#define GPIOC_PCLK_DI()     (RCC->ahb1enr &= ~(1 << 2))
#define GPIOD_PCLK_DI()     (RCC->ahb1enr &= ~(1 << 3))
#define GPIOE_PCLK_DI()     (RCC->ahb1enr &= ~(1 << 4))
#define GPIOF_PCLK_DI()     (RCC->ahb1enr &= ~(1 << 5))
#define GPIOG_PCLK_DI()     (RCC->ahb1enr &= ~(1 << 6))
#define GPIOH_PCLK_DI()     (RCC->ahb1enr &= ~(1 << 7))
#define GPIOI_PCLK_DI()     (RCC->ahb1enr &= ~(1 << 8))

/*
 * macros to reset GPIOx peripherals
 * */
#define GPIOA_REG_RESET()   do{(RCC->ahb1rstr |= (1 << 0)); (RCC->ahb1rstr &= ~(1 << 0));}while(0)
#define GPIOB_REG_RESET()   do{(RCC->ahb1rstr |= (1 << 1)); (RCC->ahb1rstr &= ~(1 << 1));}while(0)
#define GPIOC_REG_RESET()   do{(RCC->ahb1rstr |= (1 << 2)); (RCC->ahb1rstr &= ~(1 << 2));}while(0)
#define GPIOD_REG_RESET()   do{(RCC->ahb1rstr |= (1 << 3)); (RCC->ahb1rstr &= ~(1 << 3));}while(0)
#define GPIOE_REG_RESET()   do{(RCC->ahb1rstr |= (1 << 4)); (RCC->ahb1rstr &= ~(1 << 4));}while(0)
#define GPIOF_REG_RESET()   do{(RCC->ahb1rstr |= (1 << 5)); (RCC->ahb1rstr &= ~(1 << 5));}while(0)
#define GPIOG_REG_RESET()   do{(RCC->ahb1rstr |= (1 << 6)); (RCC->ahb1rstr &= ~(1 << 6));}while(0)
#define GPIOH_REG_RESET()   do{(RCC->ahb1rstr |= (1 << 7)); (RCC->ahb1rstr &= ~(1 << 7));}while(0)
#define GPIOI_REG_RESET()   do{(RCC->ahb1rstr |= (1 << 8)); (RCC->ahb1rstr &= ~(1 << 8));}while(0)

#define GPIO_BASEADDR_TO_CODE(x) ((x == GPIOA) ? 0 : \
                                  (x == GPIOB) ? 1 : \
                                  (x == GPIOC) ? 2 : \
                                  (x == GPIOD) ? 3 : \
                                  (x == GPIOE) ? 4 : \
                                  (x == GPIOF) ? 5 : \
                                  (x == GPIOG) ? 6 : \
                                  (x == GPIOH) ? 7 : \
                                  (x == GPIOI) ? 8 : -1 )

/************************************ I2C CLOCK MACROs ***********************************/
/*
 * Clock enable maros for I2C peripherals
 * */
#define I2C1_PCLK_EN()     (RCC->apb1enr |= (1 << 21))

/************************************ SPI CLOCK MACROs ***********************************/
/*
 * Clock enable maros for SPI peripherals
 * */
#define SPI1_PCLK_EN()     (RCC->apb1enr |= (1 << 12))

/************************************ USART CLOCK MACROs ***********************************/
/*
 * Clock enable macros for usart peripherals
 * */
#define USART1_PCLK_EN()     (RCC->ahb1enr |= (1 << 0))

#define USART1_PCLK_DI()     (RCC->ahb1enr &= ~(1 << 0))

#define GPIOA_REG_RESET()   do{(RCC->ahb1rstr |= (1 << 0)); (RCC->ahb1rstr &= ~(1 << 0));}while(0)


/*
 * Clock enable macros for syscfg
 * */
#define SYSCFG_PCLK_EN()   (RCC->apb2enr |= (1 << 14))

/* IRQ (Interrupt request) numbers of STM32F4 MCU
 * Note: update these macros with valid values according to your mcu
 * TODO: complete this list for other peripherals
 * */
#define IRQ_NO_EXTI0            6
#define IRQ_NO_EXTI1            7
#define IRQ_NO_EXTI2            8
#define IRQ_NO_EXTI3            9
#define IRQ_NO_EXTI4            10
#define IRQ_NO_EXTI9_5          23
#define IRQ_NO_EXTI15_10        40

#endif