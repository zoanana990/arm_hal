#include <hal/hal_gpio.h>
#include <hal/hal_type.h>
#include "hal/hal_reg.h"

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
        if(pGPIOx == GPIOA)
        {
            GPIOA_PCLK_EN();
        }
        else if (pGPIOx == GPIOB)
        {
            GPIOB_PCLK_EN();
        }
        else if (pGPIOx == GPIOC)
        {
            GPIOC_PCLK_EN();
        }
        else if (pGPIOx == GPIOD)
        {
            GPIOD_PCLK_EN();
        }
        else if (pGPIOx == GPIOE)
        {
            GPIOE_PCLK_EN();
        }
        else if (pGPIOx == GPIOF)
        {
            GPIOF_PCLK_EN();
        }
        else if (pGPIOx == GPIOG)
        {
            GPIOG_PCLK_EN();
        }
        else if (pGPIOx == GPIOH)
        {
            GPIOH_PCLK_EN();
        }
        else if (pGPIOx == GPIOI)
        {
            GPIOI_PCLK_EN();
        }
    }
    else
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_PCLK_DI();
        }
        else if (pGPIOx == GPIOB)
        {
            GPIOB_PCLK_DI();
        }
        else if (pGPIOx == GPIOC)
        {
            GPIOC_PCLK_DI();
        }
        else if (pGPIOx == GPIOD)
        {
            GPIOD_PCLK_DI();
        }
        else if (pGPIOx == GPIOE)
        {
            GPIOE_PCLK_DI();
        }
        else if (pGPIOx == GPIOF)
        {
            GPIOF_PCLK_DI();
        }
        else if (pGPIOx == GPIOG)
        {
            GPIOG_PCLK_DI();
        }
        else if (pGPIOx == GPIOH)
        {
            GPIOH_PCLK_DI();
        }
        else if (pGPIOx == GPIOI)
        {
            GPIOI_PCLK_DI();
        }
    }
}

/*
 * Init and deinit
 * */

/************************************************************************
 * @fn             - hal_gpio_init
 * @brief          -
 * @param[in]      - pGPIOHandle
 * @return         - none
 * @note           - none
 ************************************************************************/
void hal_gpio_init(GPIO_Handle_t *pGPIOHandle)
{
    u32 temp = 0;

    /* 1. configure the mode of the gpio pin */
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= HAL_GPIO_MODE_ANALOG)
    {
        /* the non-interrupt mode */
        temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <<
                (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        pGPIOHandle->pGPIOx->moder &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        pGPIOHandle->pGPIOx->moder |= temp;
    }
    else
    {
        if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == HAL_GPIO_MODE_IT_FT)
        {
            /* configure the FTSR */
            EXTI->ftsr |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

            /* clear the corresponding RTSR bit */
            EXTI->rtsr &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }
        else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == HAL_GPIO_MODE_IT_RT)
        {
            /* configure the RTSR */
            EXTI->rtsr |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

            /* clear the corresponding FTSR bit */
            EXTI->ftsr &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }
        else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == HAL_GPIO_MODE_IT_RFT)
        {
            /* configure the FTSR and RTSR */
            EXTI->ftsr |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            EXTI->rtsr |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }

        /* Configure the GPIO port selection in SYSCFG_EXTICR */
        u8 index, bit, portcode;
        index = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
        bit = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
        portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
        SYSCFG_PCLK_EN();
        SYSCFG->exticr[index] = portcode << (bit * 4);

        /* Enable the exti interrupt delivery using IMR */
        EXTI->imr |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    }

    temp = 0;
    /* 2. configure the speed */
    temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed <<
            (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->ospeedr &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->ospeedr |= temp;

    temp = 0;

    /* 3. configure the pupd setting */
    temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinPupdControl <<
            (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->pupdr &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->pupdr |= temp;

    temp = 0;
    /* 4. configure the optype */
    temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinOpType <<
            pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
    pGPIOHandle->pGPIOx->otyper &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->otyper |= temp;

    temp = 0;
    /* 5. configure the alt functionality */
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == HAL_GPIO_MODE_ALTEN)
    {
        /* configure the alternative function */
        u8 index, bit;
        index = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
        bit = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
        pGPIOHandle->pGPIOx->afr[index] &= ~(0xf << (4 * bit));
        pGPIOHandle->pGPIOx->afr[index] |=
                (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunc << (4 * bit));

    }
}
void hal_gpio_deInit(GPIO_RegDef_t *pGPIOx)
{
    if(pGPIOx == GPIOA)
    {
        GPIOA_REG_RESET();
    }
    else if (pGPIOx == GPIOB)
    {
        GPIOB_REG_RESET();
    }
    else if (pGPIOx == GPIOC)
    {
        GPIOC_REG_RESET();
    }
    else if (pGPIOx == GPIOD)
    {
        GPIOD_REG_RESET();
    }
    else if (pGPIOx == GPIOE)
    {
        GPIOE_REG_RESET();
    }
    else if (pGPIOx == GPIOF)
    {
        GPIOF_REG_RESET();
    }
    else if (pGPIOx == GPIOG)
    {
        GPIOG_REG_RESET();
    }
    else if (pGPIOx == GPIOH)
    {
        GPIOH_REG_RESET();
    }
    else if (pGPIOx == GPIOI)
    {
        GPIOI_REG_RESET();
    }
}

/*
 * Data read and write
 * */
u8 hal_gpio_readFromInputPin(GPIO_RegDef_t *pGPIOx, u8 pin_number)
{
    return (u8)((pGPIOx->idr >> pin_number) & 0x1);
}
u16 hal_gpio_readFromInputPort(GPIO_RegDef_t *pGPIOx)
{
    return (u16)pGPIOx->idr;
}
void hal_gpio_writeToOutputPin(GPIO_RegDef_t *pGPIOx, u8 pin_number, u8 value)
{
    if(value == GPIO_PIN_SET)
    {
        /* write 1 */
        pGPIOx->odr |= (1 << pin_number);
    }
    else
    {
        /* write 0 */
        pGPIOx->odr &= ~(1 << pin_number);
    }
}
void hal_gpio_writeToOutputPort(GPIO_RegDef_t *pGPIOx, u8 value)
{
    pGPIOx->odr = value;
}
void hal_gpio_toggleOutputPin(GPIO_RegDef_t *pGPIOx, u8 pin_number)
{
    pGPIOx->odr ^= (1 << pin_number);
}

/*
 * IRQ configuration and isr handling
 * */

/**
 * GPIO pin interrupt configuration
 * 1. Pin must be input configuration
 * 2. Configure the edge trigger (RT, FT, RFT)
 * 3. Enable interrupt delivery from peripheral to the processor (on peripheral side)
 * 4. Identify the IRQ number on which the processor accepts the interrupt from that pin
 * 5. Configure the IRQ priority for the identified IRQ number
 * 6. Enable interrupt reception on that IRQ number
 * 7. Implement IRQ number
 * */
void hal_gpio_irqInterruptConfig(u8 irq_number, u8 permission)
{
    if(permission == ENABLE)
    {
        if(irq_number <= 31)
        {
            /* use ISER0 register */
            *NVIC_ISER0 |= (1 << irq_number);
        }
        else if(irq_number > 31 && irq_number < 64)
        {
            /* use ISER1 register */
            *NVIC_ISER1 |= (1 << (irq_number % 32));
        }
        else if(irq_number >= 64 && irq_number < 96)
        {
            /* use ISER2 register */
            *NVIC_ISER2 |= (1 << (irq_number % 64));
        }
    }
    else
    {
        if(irq_number <= 31)
        {
            /* use ICER0 register */
            *NVIC_ICER0 |= (1 << irq_number);
        }
        else if(irq_number > 31 && irq_number < 64)
        {
            /* use ICER1 register */
            *NVIC_ICER1 |= (1 << (irq_number % 32));
        }
        else if(irq_number >= 64 && irq_number < 96)
        {
            /* use ICER2 register */
            *NVIC_ICER2 |= (1 << (irq_number % 64));
        }
    }
}

void hal_gpio_irqPriorityConfig(u8 irq_number, u8 irq_priority)
{
    /* first, find out the ipr register */
    u8 iprx = irq_number / 4;
    u8 iprx_section = irq_number % 4;

    u8 shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

    *(NVIC_PR_BASE_ADDR + (iprx * 4)) |= (irq_priority << shift_amount);
}

void hal_gpio_irqHandling(u8 pin_number)
{

}