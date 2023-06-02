#include <hal/hal_gpio.h>
#include <hal/hal_type.h>
#include <hal/hal.h>

/*
 * Peripheral clock setup
 * */
/************************************************************************
 * @fn             - hal_gpio_periClockControl
 * @brief          - This function enables or disables peripheral clock
 *                   for the given gpio port
 * @param[in]      - pGPIOx
 * @param[in]      - permission
 * @return         - none
 * @note           - none
 ************************************************************************/
void hal_gpio_periClockControl(GPIO_RegDef_t *pGPIOx, u8 permission)
{
    if(permission == ENABLE)
    {
        switch(pGpiox)
        {
            case GPIOA:
                GPIOA_PCLK_EN();
                break;
            case GPIOB:
                GPIOB_PCLK_EN();
                break;
            case GPIOC:
                GPIOC_PCLK_EN();
                break;
            case GPIOD:
                GPIOD_PCLK_EN();
                break;
            case GPIOE:
                GPIOE_PCLK_EN();
                break;
            case GPIOF:
                GPIOF_PCLK_EN();
                break;
            case GPIOG:
                GPIOG_PCLK_EN();
                break;
            case GPIOH:
                GPIOH_PCLK_EN();
                break;
            case GPIOI:
                GPIOI_PCLK_EN();
                break;
            default:
                break;
        }
    }
    else
    {
        switch(pGpiox)
        {
            case GPIOA:
                GPIOA_PCLK_DI();
                break;
            case GPIOB:
                GPIOB_PCLK_DI();
                break;
            case GPIOC:
                GPIOC_PCLK_DI();
                break;
            case GPIOD:
                GPIOD_PCLK_DI();
                break;
            case GPIOE:
                GPIOE_PCLK_DI();
                break;
            case GPIOF:
                GPIOF_PCLK_DI();
                break;
            case GPIOG:
                GPIOG_PCLK_DI();
                break;
            case GPIOH:
                GPIOH_PCLK_DI();
                break;
            case GPIOI:
                GPIOI_PCLK_DI();
                break;
            default:
                break;
        }
    }
}

/*
 * Init and deinit
 * */

/************************************************************************
 * @fn             - hal_gpio_init
 * @brief          - This function enables or disables peripheral clock
 *                   for the given gpio port
 * @param[in]      - pGPIOHandle
 * @return         - none
 * @note           - none
 ************************************************************************/
void hal_gpio_init(GPIO_Handle_t *pGPIOHandle)
{
    /* 1. configure the mode of the gpio pin */

    /* 2. configure the speed */

    /* 3. configure the pupd setting */

    /* 4. configure the optype */

    /* 5. configure the alt functionality */

}
void hal_gpio_deInit(GPIO_RegDef_t *pGPIOx)
{

}

/*
 * Data read and write
 * */
u8 hal_gpio_readFromInputPin(GPIO_RegDef_t *pGPIOx, u8 pin_number)
{
    return 0;
}
u16 hal_gpio_readFromInputPort(GPIO_RegDef_t *pGPIOx)
{
    return 0;
}
void hal_gpio_writeToOutputPin(GPIO_RegDef_t *pGPIOx, u8 pin_number, u8 value)
{

}
void hal_gpio_writeToOutputPort(GPIO_RegDef_t *pGPIOx, u8 value)
{

}
void hal_gpio_toggleOutputPin(GPIO_RegDef_t *pGPIOx, u8 pin_number)
{

}

/*
 * IRQ configuration and isr handling
 * */
void hal_gpio_irqConfig(u8 irq_number, u8 irq_priority, u8 EnorDi)
{

}
void hal_gpio_irqHandling(u8 pin_number)
{

}