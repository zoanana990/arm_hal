#include <hal/hal_lcd.h>
#include <hal/hal_reg.h>
#include <hal/hal_utils.h>
#include <hal/hal_gpio.h>
#include <hal/hal_ili9341_reg.h>

/**
 * SPI
 */
#define HAL_LCD_SPI             SPI5
#define HAL_LCD_SCL_PIN         HAL_GPIO_PIN_7
#define HAL_LCD_SCL_PORT        GPIOF
#define HAL_LCD_SDA_PIN         HAL_GPIO_PIN_9
#define HAL_LCD_SDA_PORT        GPIOF

/**
 * GPIO
 */
#define HAL_LCD_RESX_PIN        HAL_GPIO_PIN_7
#define HAL_LCD_RESX_PORT       GPIOA
#define HAL_LCD_CSX_PIN         HAL_GPIO_PIN_2
#define HAL_LCD_CSX_PORT        GPIOC
#define HAL_LCD_WRX_DCX_PIN     HAL_GPIO_PIN_13
#define HAL_LCD_WRX_DCX_PORT    GPIOD

/**
 * Common Used macro in HAL_LCD
 */
#define HAL_LCD_RESX_HIGH()     HAL_REG_SET_BIT(HAL_LCD_RESX_PORT->ODR, HAL_LCD_RESX_PIN);
#define HAL_LCD_RESX_LOW()      HAL_REG_CLR_BIT(HAL_LCD_RESX_PORT->ODR, HAL_LCD_RESX_PIN);

#define HAL_LCD_CSX_HIGH()      HAL_REG_SET_BIT(HAL_LCD_CSX_PORT->ODR, HAL_LCD_CSX_PIN);
#define HAL_LCD_CSX_LOW()       HAL_REG_CLR_BIT(HAL_LCD_CSX_PORT->ODR, HAL_LCD_CSX_PIN);

#define HAL_LCD_DCX_HIGH()      HAL_REG_SET_BIT(HAL_LCD_WRX_DCX_PORT->ODR, HAL_LCD_WRX_DCX_PIN);
#define HAL_LCD_DCX_LOW()       HAL_REG_CLR_BIT(HAL_LCD_WRX_DCX_PORT->ODR, HAL_LCD_WRX_DCX_PIN);

GPIO_RegDef_t *hal_ltdc_io_port[] = {
    HAL_LCD_DATA_R2_PORT,
    HAL_LCD_DATA_R3_PORT,
};

const u8 ltdc_pins[] = {
    HAL_LCD_DATA_R2_PIN,
    HAL_LCD_DATA_R3_PIN,
};

#define HAL_LCD_TOTAL_PINS      (sizeof(ltdc_pins) / sizeof(ltdc_pins))
const u8 total_ltdc_pins = HAL_LCD_TOTAL_PINS;

void _HAL_LCD_writeCmd(u8 cmd);
void _HAL_LCD_writeData(u8 *buf, u32 len);

void delay(void)
{
    u32 wait = 0xFFFF * 20;
    for(u32 i = 0; i < wait; i++); /* 50 ms */
}

void HAL_LCD_pinInit(void)
{
    GPIO_RegDef_t *pGPIOA = GPIOA, *pGPIOC = GPIOC, 
                  *pGPIOD = GPIOD, *pGPIOF = GPIOF;
    RCC_RegDef_t  *pRCC = RCC;
    
    /*********************** FOR GPIO PIN ***********************/
    /* Enable the cloeck for GPIOA, GPIOC and GPIOD peripherals */
    HAL_REG_SET_BIT(pRCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN_Pos);
    HAL_REG_SET_BIT(pRCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN_Pos);
    HAL_REG_SET_BIT(pRCC->AHB1ENR, RCC_AHB1ENR_GPIODEN_Pos);

    /* Configure the pin to output mode (A7, C2, D13) */
    HAL_REG_SET_VAL(pGPIOA->MODER, 0x01, 0x03, GPIO_MODER_MODER7_Pos);
    HAL_REG_SET_VAL(pGPIOC->MODER, 0x01, 0x03, GPIO_MODER_MODER2_Pos);
    HAL_REG_SET_VAL(pGPIOD->MODER, 0x01, 0x03, GPIO_MODER_MODER13_Pos);

    /* Configure the pin to output type (open drain or push-pull) */
    HAL_REG_CLR_BIT(pGPIOA->OTYPER, GPIO_OTYPER_OT7_Pos);
    HAL_REG_CLR_BIT(pGPIOC->OTYPER, GPIO_OTYPER_OT2_Pos);
    HAL_REG_CLR_BIT(pGPIOD->OTYPER, GPIO_OTYPER_OT13_Pos);

    /* Configure the output speed */
    HAL_REG_SET_VAL(pGPIOA->OSPEEDR, 0x02, 0x03, GPIO_OSPEEDR_OSPEED7_Pos);
    HAL_REG_SET_VAL(pGPIOC->OSPEEDR, 0x02, 0x03, GPIO_OSPEEDR_OSPEED2_Pos);
    HAL_REG_SET_VAL(pGPIOD->OSPEEDR, 0x02, 0x03, GPIO_OSPEEDR_OSPEED13_Pos);

    /* Set RESX = HIGH, that is, GPIOA pin 7 */
    HAL_REG_CLR_BIT(pGPIOA->OTYPER, GPIO_ODR_OD7_Pos);
    
    /* Set CSX = HIGH, that is, GPIOC pin 2 */
    HAL_REG_CLR_BIT(pGPIOC->OTYPER, GPIO_ODR_OD2_Pos);
    
    /* Set D/CX = HIGH, that is, GPIOD pin 13 */
    HAL_REG_CLR_BIT(pGPIOD->OTYPER, GPIO_ODR_OD13_Pos);


    /*********************** FOR GPIO PIN ***********************/
    /************************ FOR SPI PIN ***********************/
    /* Enable the cloeck for GPIOF peripherals */
    HAL_REG_SET_BIT(pRCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN_Pos);

    /* Configure the pin to alternative mode (F7, F9) */
    HAL_REG_SET_VAL(pGPIOF->MODER, 0x02, 0x03, GPIO_MODER_MODER7_Pos);
    HAL_REG_SET_VAL(pGPIOF->MODER, 0x02, 0x03, GPIO_MODER_MODER9_Pos);

    /* Configure the pin to output type (open drain or push-pull) */
    HAL_REG_CLR_BIT(pGPIOF->OTYPER, GPIO_OTYPER_OT7_Pos);
    HAL_REG_CLR_BIT(pGPIOF->OTYPER, GPIO_OTYPER_OT9_Pos);

    /* Configure the output speed */
    HAL_REG_SET_VAL(pGPIOF->OSPEEDR, 0x02, 0x03, GPIO_OSPEEDR_OSPEED7_Pos);
    HAL_REG_SET_VAL(pGPIOF->OSPEEDR, 0x02, 0x03, GPIO_OSPEEDR_OSPEED9_Pos);

    /* Configure alternative function AF5 (F7, F9) */
    HAL_REG_SET_VAL(pGPIOF->AFR[0], 0x05, 0x0F, GPIO_AFRL_AFSEL7_Pos);
    HAL_REG_SET_VAL(pGPIOF->AFR[1], 0x05, 0x0F, GPIO_AFRH_AFSEL9_Pos);
    /************************ FOR SPI PIN ***********************/
}

void HAL_LCD_SPI_Enable(void)
{
    SPI_RegDef_t *pSPI = HAL_LCD_SPI;
    HAL_REG_SET_BIT(pSPI->CR1, SPI_CR1_SPE_Pos);
}

void HAL_LCD_SPI_Init(void)
{
    SPI_RegDef_t *pSPI = HAL_LCD_SPI;
    RCC_RegDef_t *pRCC = RCC;

    /* Activate SPI5 clock */
    HAL_REG_SET_BIT(pRCC->APB2ENR, RCC_APB2ENR_SPI5EN_Pos);

    /*
     * SPI mode: Half-duplex controller
     * Data format: 8 bit, msb first
     * CPOL and CPHA: Check the peripheral datasheet to obtain the correct setting it requires
     * SPI clock: Check the peripheral datasheet and obtain the max speed it can support
     * Chip select is handled by the software
     */
    HAL_REG_SET_BIT(pSPI->CR1, SPI_CR1_MSTR_Pos);       /* We are Master */
    HAL_REG_SET_BIT(pSPI->CR1, SPI_CR1_BIDIMODE_Pos);   /* We only use one line */
    HAL_REG_SET_BIT(pSPI->CR1, SPI_CR1_BIDIOE_Pos);
    HAL_REG_CLR_BIT(pSPI->CR1, SPI_CR1_DFF_Pos);        /* Data format is 8 bit */
    HAL_REG_SET_BIT(pSPI->CR1, SPI_CR1_SSM_Pos);
    HAL_REG_SET_BIT(pSPI->CR1, SPI_CR1_SSI_Pos);
    HAL_REG_CLR_BIT(pSPI->CR1, SPI_CR1_LSBFIRST_Pos);   /* MSB first */
    HAL_REG_SET_VAL(pSPI->CR1, 0x3, 0x7, SPI_CR1_BR_Pos); /* Set the SPI clock */
    HAL_REG_CLR_BIT(pSPI->CR1, SPI_CR1_CPOL_Pos);       /* clear CPOL and CPHA */
    HAL_REG_CLR_BIT(pSPI->CR1, SPI_CR1_CPHA_Pos);
    HAL_REG_CLR_BIT(pSPI->CR2, SPI_CR2_FRF_Pos);
}

void HAL_LCD_Reset(void)
{
    HAL_LCD_RESX_LOW();
    delay();
    HAL_LCD_RESX_HIGH();
    delay();
}

void HAL_LCD_Config(void)
{
    u8 params[15];
    _HAL_LCD_writeCmd(ILI9341_SWRESET);
    _HAL_LCD_writeCmd(ILI9341_POWERB);
    params[0] = 0x00;
    params[1] = 0xD9;
    params[2] = 0x30;
    _HAL_LCD_writeData(params, 3);

    _HAL_LCD_writeCmd(ILI9341_POWER_SEQ);
    params[0]= 0x64;
    params[1]= 0x03;
    params[2]= 0X12;
    params[3]= 0X81;
    _HAL_LCD_writeData(params, 4);

    _HAL_LCD_writeCmd(ILI9341_DTCA);
    params[0]= 0x85;
    params[1]= 0x10;
    params[2]= 0x7A;
    _HAL_LCD_writeData(params, 3);

    _HAL_LCD_writeCmd(ILI9341_POWERA);
    params[0]= 0x39;
    params[1]= 0x2C;
    params[2]= 0x00;
    params[3]= 0x34;
    params[4]= 0x02;
    _HAL_LCD_writeData(params, 5);

    _HAL_LCD_writeCmd(ILI9341_PRC);
    params[0]= 0x20;
    _HAL_LCD_writeData(params, 1);

    _HAL_LCD_writeCmd(ILI9341_DTCB);
    params[0]= 0x00;
    params[1]= 0x00;
    _HAL_LCD_writeData(params, 2);

    _HAL_LCD_writeCmd(ILI9341_POWER1);
    params[0]= 0x1B;
    _HAL_LCD_writeData(params, 1);

    _HAL_LCD_writeCmd(ILI9341_POWER2);
    params[0]= 0x12;
    _HAL_LCD_writeData(params, 1);

    _HAL_LCD_writeCmd(ILI9341_VCOM1);
    params[0]= 0x08;
    params[1]= 0x26;
    _HAL_LCD_writeData(params, 2);

    _HAL_LCD_writeCmd(ILI9341_VCOM2);
    params[0]= 0XB7;
    _HAL_LCD_writeData(params, 1);


    _HAL_LCD_writeCmd(ILI9341_PIXEL_FORMAT);
    params[0]= 0x55; //select RGB565
    _HAL_LCD_writeData(params, 1);

    _HAL_LCD_writeCmd(ILI9341_FRMCTR1);
    params[0]= 0x00;
    params[1]= 0x1B;//frame rate = 70
    _HAL_LCD_writeData(params, 2);

    _HAL_LCD_writeCmd(ILI9341_DFC);    // Display Function Control
    params[0]= 0x0A;
    params[1]= 0xA2;
    _HAL_LCD_writeData(params, 2);

    _HAL_LCD_writeCmd(ILI9341_3GAMMA_EN);    // 3Gamma Function Disable
    params[0]= 0x02;
    _HAL_LCD_writeData(params, 1);

    _HAL_LCD_writeCmd(ILI9341_GAMMA);
    params[0]= 0x01;
    _HAL_LCD_writeData(params, 1);

    _HAL_LCD_writeCmd(ILI9341_PGAMMA);    //Set Gamma
    params[0]= 0x0F;
    params[1]= 0x1D;
    params[2]= 0x1A;
    params[3]= 0x0A;
    params[4]= 0x0D;
    params[5]= 0x07;
    params[6]= 0x49;
    params[7]= 0X66;
    params[8]= 0x3B;
    params[9]= 0x07;
    params[10]= 0x11;
    params[11]= 0x01;
    params[12]= 0x09;
    params[13]= 0x05;
    params[14]= 0x04;
    _HAL_LCD_writeData(params, 15);

    _HAL_LCD_writeCmd(ILI9341_NGAMMA);
    params[0]= 0x00;
    params[1]= 0x18;
    params[2]= 0x1D;
    params[3]= 0x02;
    params[4]= 0x0F;
    params[5]= 0x04;
    params[6]= 0x36;
    params[7]= 0x13;
    params[8]= 0x4C;
    params[9]= 0x07;
    params[10]= 0x13;
    params[11]= 0x0F;
    params[12]= 0x2E;
    params[13]= 0x2F;
    params[14]= 0x05;
    _HAL_LCD_writeData(params, 15);

    _HAL_LCD_writeCmd(ILI9341_RGB_INTERFACE);
    params[0] = 0xC2; //Data is fetched during falling edge of DOTCLK
    _HAL_LCD_writeData(params, 1);

    _HAL_LCD_writeCmd(ILI9341_INTERFACE);
    params[0] = 0x00;
    params[1] = 0x00;
    params[2] = 0x06;
    _HAL_LCD_writeData(params, 3);

    _HAL_LCD_writeCmd(ILI9341_SLEEP_OUT); //Exit Sleep
    delay();
    delay();
    _HAL_LCD_writeCmd(ILI9341_DISPLAY_ON); //display on
}

void _HAL_LCD_writeCmd(u8 cmd)
{
    SPI_RegDef_t *pSPI = HAL_LCD_SPI;
    HAL_LCD_CSX_LOW();
    HAL_LCD_DCX_LOW();
    while(!(HAL_REG_READ_BIT(pSPI->SR, SPI_SR_TXE_Pos))); /* Wait for send data*/
    HAL_REG_WRITE(pSPI->DR, cmd);
    while(!(HAL_REG_READ_BIT(pSPI->SR, SPI_SR_TXE_Pos)));
    while(HAL_REG_READ_BIT(pSPI->SR, SPI_SR_BSY_Pos)); /* The data is sent */
    HAL_LCD_CSX_HIGH();
    HAL_LCD_DCX_HIGH();
}

void _HAL_LCD_writeData(u8 *buf, u32 len)
{
    SPI_RegDef_t *pSPI = HAL_LCD_SPI;
    for(int i = 0; i < len; i++)
    {
        HAL_LCD_CSX_LOW();
        while(!(HAL_REG_READ_BIT(pSPI->SR, SPI_SR_TXE_Pos)));
        HAL_REG_WRITE(pSPI->DR, buf[i]);
        while(!(HAL_REG_READ_BIT(pSPI->SR, SPI_SR_TXE_Pos)));
        while(HAL_REG_READ_BIT(pSPI->SR, SPI_SR_BSY_Pos));
        HAL_LCD_CSX_HIGH();
    }
}

/***************************************************************************/
void HAL_LCD_Init()
{
    HAL_LCD_pinInit();
    HAL_LCD_SPI_Init();
    HAL_LCD_SPI_Enable();
    HAL_LCD_Reset();
    HAL_LCD_Config();
}