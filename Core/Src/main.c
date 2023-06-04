#include <hal/hal_reg.h>
#include <hal/hal_gpio.h>
#include <hal/hal_uart.h>
#include <string.h>

#define HIGH                    1
#define BTN_PRESSED             HIGH

c8 msg[1024] = "HAPPY USART DAY ... \n\r";

USART_Handle_t usart2_handle;

void USART2_init(void)
{
    usart2_handle.pUSARTx = USART2;
    usart2_handle.USART_Config.USART_Baud = USART_STD_BAUD_115200;
    usart2_handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
    usart2_handle.USART_Config.USART_Mode = USART_MODE_ONLY_TX;
    usart2_handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
    usart2_handle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
    usart2_handle.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
    hal_usart_init(&usart2_handle);
}

void USART2_GPIO_init(void)
{
    GPIO_Handle_t usart_gpio;
    usart_gpio.pGPIOx = GPIOA;
    usart_gpio.GPIO_PinConfig.GPIO_PinMode = HAL_GPIO_MODE_ALTEN;
    usart_gpio.GPIO_PinConfig.GPIO_PinOpType = HAL_GPIO_OP_TYPE_PP;
    usart_gpio.GPIO_PinConfig.GPIO_PinPupdControl = HAL_GPIO_PU;
    usart_gpio.GPIO_PinConfig.GPIO_PinSpeed = HAL_GPIO_SPEED_HIGH;
    usart_gpio.GPIO_PinConfig.GPIO_PinAltFunc = 7;

    /* usart2 TX */
    usart_gpio.GPIO_PinConfig.GPIO_PinNumber = HAL_GPIO_PIN_2;
    hal_gpio_init(&usart_gpio);

    /* usart2 RX */
    usart_gpio.GPIO_PinConfig.GPIO_PinNumber = HAL_GPIO_PIN_3;
    hal_gpio_init(&usart_gpio);
}

int main(void)
{
    USART2_GPIO_init();
    USART2_init();
    hal_usart_peripheralControl(USART2, ENABLE);
    hal_usart_SendData(&usart2_handle, (u8 *)msg, strlen(msg));


    while(1);
    return 0;
}


