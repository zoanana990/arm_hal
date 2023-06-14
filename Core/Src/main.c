#include <hal/hal_type.h>
#include <hal/hal_utils.h>
#include <hal/hal_reg.h>
#include <hal/hal_lcd.h>

void SystemClock_Setup(void);

int main()
{
    SystemClock_Setup();
    HAL_LCD_Init();
    while(1);
    return 0;
}

void SystemClock_Setup(void)
{
    RCC_RegDef_t   *pRCC = RCC;
    FLASH_RegDef_t *pFlash = FLASH;
    PWR_RegDef_t   *pPWR = PWR;

    /**
     * 1. Program flash wait states
     */
    HAL_REG_SET_VAL(pFlash->ACR, 0x5U, 0xFU, FLASH_ACR_LATENCY_Pos);

    /**
     * 2. Over drive settings, e.g. power register etc.
     */
    HAL_REG_SET_BIT(pRCC->APB1ENR, RCC_APB1ENR_PWREN_Pos);      /* Enable Clock for Power register access */
    HAL_REG_SET_VAL(pPWR->CR, 0x3, 0x3, PWR_CR_VOS_Pos);        /* VOS = 0b11, adjust to Power Scale 1*/
    HAL_REG_SET_BIT(pPWR->CR, PWR_CR_ODEN_Pos);                 /* Set over-drive enable */
    while(!HAL_REG_READ_BIT(pPWR->CSR, PWR_CSR_ODRDY_Pos));     /* Wait for over-drive already */
    HAL_REG_SET_BIT(pPWR->CR, PWR_CR_ODSWEN_Pos);               /* Over drive Enable */


    /* 
     * 3. Setting up the main PLL 
     *    config PLL_M, PLL_N, PLL_P
     */
    HAL_REG_SET_VAL(pRCC->PLLCFGR, 0x8U, 0x3F, RCC_PLLCFGR_PLLM_Pos);
    HAL_REG_SET_VAL(pRCC->PLLCFGR, 180U, 0x1FF, RCC_PLLCFGR_PLLN_Pos);
    HAL_REG_SET_VAL(pRCC->PLLCFGR, 0x0U, 0x3, RCC_PLLCFGR_PLLP_Pos);

    /* 
     * 4. Setting up the LCD_CLK using PLLSAI block 
     */
    HAL_REG_SET_VAL(pRCC->PLLSAICFGR, 50U, 0x1FFU, RCC_PLLSAICFGR_PLLSAIN_Pos);
    HAL_REG_SET_VAL(pRCC->PLLSAICFGR, 0x02U, 0x7U, RCC_PLLSAICFGR_PLLSAIR_Pos);

    /* LCD_CLK = 6.25MHz */
    HAL_REG_SET_VAL(pRCC->DCKCFGR, 0x08U, 0x3U, RCC_DCKCFGR_PLLSAIDIVR_Pos);

    /**
     * 5. Setting AHB and APB clocks
     *    main clock: 180 MHz, APB1: 45Mhz, APB2: 90MHz
     */
    HAL_REG_SET_VAL(pRCC->CFGR, 0x0U, 0xFU, RCC_CFGR_HPRE_Pos);
    HAL_REG_SET_VAL(pRCC->CFGR, 0x5U, 0x7U, RCC_CFGR_PPRE1_Pos);
    HAL_REG_SET_VAL(pRCC->CFGR, 0x4U, 0x7U, RCC_CFGR_PPRE2_Pos);

    /**
     * 6. Turn on the main PLL
     *    Wait until PLLCLK is ready
     */
    HAL_REG_SET_BIT(pRCC->CR, RCC_CR_PLLON_Pos);
    while(!HAL_REG_READ_BIT(pRCC->CR, RCC_CR_PLLRDY_Pos));

    /**
     * 7. Switch PLLCLK as SYSCLK
     *    Wait for switch status
     */
    HAL_REG_SET_VAL(pRCC->CFGR, 0x2, 0x3, RCC_CFGR_SW_Pos);
    while(!(HAL_REG_READ_VAL(pRCC->CFGR, 0x3U, RCC_CFGR_SWS_Pos) == 0x2U));
}