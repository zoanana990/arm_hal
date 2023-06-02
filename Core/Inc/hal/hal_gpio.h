#ifndef __HAL_GPIO__
#define __HAL_GPIO__

#include <hal/hal.h>
#include <hal/hal_type.h>

typedef struct
{
    u8 GPIO_PinNumber;
    u8 GPIO_PinMode;
    u8 GPIO_PinSpeed;
    u8 GPIO_PinOpType;
    u8 GPIO_PinAltFunc;
} GPIO_PinConfig_t;

typedef struct
{
    /* a pointer to hold the base address of the GPIO peripheral */
    GPIO_RegDef_t *pGPIOx;             /* This holds the base address of the GPIO port to which the pin belongs */
    GPIO_PinConfig_t GPIO_PinConfig;
} GPIO_Handle_t;

/*
 * gpio pin possible modes
 * */
typedef enum {
    HAL_GPIO_MODE_IN = 0,
    HAL_GPIO_MODE_OUT,
    HAL_GPIO_MODE_ALTEN,
    HAL_GPIO_MODE_ANALOG,
    HAL_GPIO_MODE_IT_FT,
    HAL_GPIO_MODE_IT_RT,
    HAL_GPIO_MODE_IT_RFT,
    HAL_GPIO_MODE_LAST
} GPIO_Mode_t;

/*
 * gpio pin possible output type
 * */
typedef enum {
    HAL_GPIO_OP_TYPE_PP = 0,
    HAL_GPIO_OP_TYPE_OD,
    HAL_GPIO_OP_TYPE_LAST
} GPIO_OP_Type_t;

/*****************************************************************************************
 *                              API DECLARATION IN GPIO
 *****************************************************************************************/

/*
 * Peripheral clock setup
 * */
void hal_gpio_periClockControl(GPIO_RegDef_t *pGPIOx, u8 EnorDi);

/*
 * Init and deinit
 * */
void hal_gpio_init(GPIO_Handle_t *pGPIOHandle);
void hal_gpio_deInit(GPIO_RegDef_t *pGPIOx);

/*
 * Data read and write
 * */
u8 hal_gpio_readFromInputPin(GPIO_RegDef_t *pGPIOx, u8 pin_number);
u16 hal_gpio_readFromInputPort(GPIO_RegDef_t *pGPIOx);
void hal_gpio_writeToOutputPin(GPIO_RegDef_t *pGPIOx, u8 pin_number, u8 value);
void hal_gpio_writeToOutputPort(GPIO_RegDef_t *pGPIOx, u8 value);
void hal_gpio_toggleOutputPin(GPIO_RegDef_t *pGPIOx, u8 pin_number);

/*
 * IRQ configuration and isr handling
 * */
void hal_gpio_irqConfig(u8 irq_number, u8 irq_priority, u8 EnorDi);
void hal_gpio_irqHandling(u8 pin_number);

#endif
