#ifndef __HAL_RCC__
#define __HAL_RCC__

#include <hal/hal_reg.h>

#define RCC_CLK_16M             16000000
#define RCC_CLK_8M              8000000

u32 hal_rcc_getPclk1Value(void);
u32 hal_rcc_getPclk2Value(void);
u32 hal_rcc_getPllOutputClk(void);

#endif