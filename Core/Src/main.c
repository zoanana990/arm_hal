#include <hal/hal_reg.h>
#include <hal/hal_gpio.h>

void delay(void)
{
    for(u32 i = 0; i < 500000; i++);
}

int main(void)
{
    GPIO_Handle_t GpioLed;
    GpioLed.pGPIOx = GPIOG;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber = HAL_GPIO_PIN_13;
    GpioLed.GPIO_PinConfig.GPIO_PinMode = HAL_GPIO_MODE_OUT;
    GpioLed.GPIO_PinConfig.GPIO_PinSpeed = HAL_GPIO_SPEED_HIGH;
    GpioLed.GPIO_PinConfig.GPIO_PinOpType = HAL_GPIO_OP_TYPE_OD;
    GpioLed.GPIO_PinConfig.GPIO_PinPupdControl = HAL_GPIO_NO_PUPD;

    hal_gpio_periClockControl(GPIOG, ENABLE);
    hal_gpio_init(&GpioLed);

    while(1)
    {
        hal_gpio_toggleOutputPin(GPIOG, HAL_GPIO_PIN_13);
        delay();
    }
    return 0;
}


