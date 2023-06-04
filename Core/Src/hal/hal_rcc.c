#include <hal/hal_rcc.h>
#include <hal/hal_reg.h>
#include <hal/hal_type.h>

u16 hal_ahb_PreScaler[8] =  {  2,    4,   8,  16,
                              64,  128, 256, 512};

u8  hal_apb1_PreScaler[4] = {  2,    4,   8,  16};
u8  hal_apb2_PreScaler[4] = {  2,    4,   8,  16};

u32 _hal_rcc_getSysClk(void)
{
    u8 clk_src = (RCC->cfgr >> 2) & 0x3;

    if(clk_src == 0)
    {
        return RCC_CLK_16M;
    }
    /* HSE Oscillator */
    else if(clk_src == 1)
    {
        return RCC_CLK_8M;
    }
    /* PLL Ocsilator */
    else
    {
        return hal_rcc_getPllOutputClk();
    }
}

u32 hal_rcc_getPclk1Value(void)
{
    u32 pclk1, system_clk;
    u8  tmp, ahbp, apb1p;

    RCC_RegDef_t *pRCC = RCC;

    system_clk = _hal_rcc_getSysClk();

    /* for ahb bus */
    tmp = ((pRCC->cfgr >> 4) & 0xf);
    if(tmp < 8)
    {
        ahbp = 1;
    }
    else
    {
        /* Get the AHB bus clock divider */
        ahbp = hal_ahb_PreScaler[tmp - 8];
    }

    /* for apb1 bus */
    tmp = ((pRCC->cfgr >> 10) & 0x7);
    if(tmp < 4)
    {
        apb1p = 1;
    }
    else
    {
        apb1p = hal_apb1_PreScaler[tmp - 4];
    }

    pclk1 = (system_clk / ahbp) / apb1p;

    return pclk1;
}

u32 hal_rcc_getPclk2Value(void)
{
    u32 pclk2, system_clk;
    u8  tmp, ahbp, apb2p;

    RCC_RegDef_t *pRCC = RCC;

    system_clk = _hal_rcc_getSysClk();

    /* for ahb bus */
    tmp = ((pRCC->cfgr >> 4) & 0xf);
    if(tmp < 8)
    {
        ahbp = 1;
    }
    else
    {
        /* Get the AHB bus clock divider */
        ahbp = hal_ahb_PreScaler[tmp - 8];
    }

    /* for apb2 bus */
    tmp = ((pRCC->cfgr >> 13) & 0x7);
    if(tmp < 4)
    {
        apb2p = 1;
    }
    else
    {
        apb2p = hal_apb2_PreScaler[tmp - 4];
    }

    pclk2 = (system_clk / ahbp) / apb2p;

    return pclk2;
}

u32 hal_rcc_getPllOutputClk(void)
{
    return 0;
}