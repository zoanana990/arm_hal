#include <hal/hal_reg.h>
#include <hal/hal_gpio.h>

#define HIGH            1
#define BTN_PRESSED     HIGH

void delay(void)
{
    for(u32 i = 0; i < 500000/2; i++);
}

int main(void)
{
    GPIO_Handle_t GpioLed, GpioBtn;
    GpioLed.pGPIOx = GPIOG;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber = HAL_GPIO_PIN_13;
    GpioLed.GPIO_PinConfig.GPIO_PinMode = HAL_GPIO_MODE_OUT;
    GpioLed.GPIO_PinConfig.GPIO_PinSpeed = HAL_GPIO_SPEED_HIGH;
    GpioLed.GPIO_PinConfig.GPIO_PinOpType = HAL_GPIO_OP_TYPE_PP;
    GpioLed.GPIO_PinConfig.GPIO_PinPupdControl = HAL_GPIO_NO_PUPD;

    hal_gpio_periClockControl(GPIOG, ENABLE);
    hal_gpio_init(&GpioLed);

    GpioBtn.pGPIOx = GPIOA;
    GpioBtn.GPIO_PinConfig.GPIO_PinNumber = HAL_GPIO_PIN_0;
    GpioBtn.GPIO_PinConfig.GPIO_PinMode = HAL_GPIO_MODE_IN;
    GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = HAL_GPIO_SPEED_HIGH;
    GpioBtn.GPIO_PinConfig.GPIO_PinPupdControl = HAL_GPIO_NO_PUPD;

    hal_gpio_periClockControl(GPIOA, ENABLE);
    hal_gpio_init(&GpioLed);

    while(1)
    {
        if(BTN_PRESSED == hal_gpio_readFromInputPin(GPIOA, HAL_GPIO_PIN_0))
        {
            delay();
            hal_gpio_toggleOutputPin(GPIOG, HAL_GPIO_PIN_13);
        }
    }
    return 0;
}


