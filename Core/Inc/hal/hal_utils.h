#ifndef __HAL_UTIL_H__
#define __HAL_UTIL_H__

/* Register bit manipulation macros */
#define HAL_REG_WRITE(reg, val)                     ((reg) = (val))
#define HAL_REG_READ(reg)                           ((reg))
#define HAL_REG_SET_BIT(reg,pos)                    ((reg) |=  (1U << (pos)))
#define HAL_REG_CLR_BIT(reg,pos)                    ((reg) &= ~(1U << (pos)))
#define HAL_REG_READ_BIT(reg,pos)                   ((reg) &   (1U << (pos)))
#define HAL_REG_CLR_VAL(reg,clrmask,pos)            ((reg) &= ~((clrmask) << (pos)))
#define HAL_REG_SET_VAL(reg,val,setmask,pos)        do {                                 \
                                                        HAL_REGCLR_VAL(reg,setmask,pos); \
                                                        ((reg) |= ((val) << (pos)));     \
                                                    }while(0)

#define HAL_REG_READ_VAL(reg,rdmask,pos)            ((HAL_REGREAD(reg) >> (pos)) & (rdmask))


#endif /* HAL_REGUTIL_H_ */