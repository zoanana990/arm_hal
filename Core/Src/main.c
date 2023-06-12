#include <hal/hal_type.h>
#include <hal/hal_utils.h>
#include <hal/hal_reg.h>

void SystemClock_Setup(void);

int main()
{
    
    while(1);

    return 0;
}

void SystemClock_Setup(void)
{
    RCC_RegDef_t *pRCC = RCC;

    /* 1. Setting up the main PLL */
}