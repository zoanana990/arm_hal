/**
 * hal_uart
 * target:
 *  USART Mode
 *  USART baud rate
 *  USART no stop bits
 *  USART word length
 *  USART parity control
 *  USART hardware flow control
 * APIs:
 *  USART initialization / peripheral clock control
 *  USART TX
 *  USART RX
 *  USART interrupt configuration and irq handling
 *  USART management APIs
 * */

#ifndef __HAL_USART__
#define __HAL_USART__

#include <hal/hal_reg.h>
#include <hal/hal_type.h>

/*
 * Configuration structure for USARTx peripheral
 */
typedef struct
{
    u8 USART_Mode;
    u32 USART_Baud;
    u8 USART_NoOfStopBits;
    u8 USART_WordLength;
    u8 USART_ParityControl;
    u8 USART_HWFlowControl;
}USART_Config_t;

/*
 * Handle structure for USARTx peripheral
 */
typedef struct
{
    USART_RegDef_t *pUSARTx;
    USART_Config_t  USART_Config;
    u8             *pTxBuffer;
    u8             *pRxBuffer;
    u32             TxLen;
    u32             RxLen;
    u8              TxBusyState;
    u8              RxBusyState;
} USART_Handle_t;

/*
 *@USART_Mode
 *Possible options for USART_Mode
 */
#define USART_MODE_ONLY_TX 0
#define USART_MODE_ONLY_RX 1
#define USART_MODE_TXRX    2

/*
 *@USART_Baud
 *Possible options for USART_Baud
 */
#define USART_STD_BAUD_1200					1200
#define USART_STD_BAUD_2400					400
#define USART_STD_BAUD_9600					9600
#define USART_STD_BAUD_19200 				19200
#define USART_STD_BAUD_38400 				38400
#define USART_STD_BAUD_57600 				57600
#define USART_STD_BAUD_115200 				115200
#define USART_STD_BAUD_230400 				230400
#define USART_STD_BAUD_460800 				460800
#define USART_STD_BAUD_921600 				921600
#define USART_STD_BAUD_2M 					2000000
#define SUART_STD_BAUD_3M 					3000000

/*
 *@USART_ParityControl
 *Possible options for USART_ParityControl
 */
#define USART_PARITY_EN_ODD                 2
#define USART_PARITY_EN_EVEN                1
#define USART_PARITY_DISABLE                0

/*
 *@USART_WordLength
 *Possible options for USART_WordLength
 */
#define USART_WORDLEN_8BITS                 0
#define USART_WORDLEN_9BITS                 1

/*
 *@USART_NoOfStopBits
 *Possible options for USART_NoOfStopBits
 */
#define USART_STOPBITS_1                    0
#define USART_STOPBITS_0_5                  1
#define USART_STOPBITS_2                    2
#define USART_STOPBITS_1_5                  3

/*
 *@USART_HWFlowControl
 *Possible options for USART_HWFlowControl
 */
#define USART_HW_FLOW_CTRL_NONE    	        0
#define USART_HW_FLOW_CTRL_CTS    	        1
#define USART_HW_FLOW_CTRL_RTS    	        2
#define USART_HW_FLOW_CTRL_CTS_RTS	        3

/*
 * Bit position
 * */
typedef enum
{
    HAL_USART_CR1_SBK = 0,
    HAL_USART_CR1_RWU,
    HAL_USART_CR1_RE,
    HAL_USART_CR1_TE,
    HAL_USART_CR1_IDLEIE,
    HAL_USART_CR1_RXNEIE,
    HAL_USART_CR1_TCIE,
    HAL_USART_CR1_TXEIE,
    HAL_USART_CR1_PEIE,
    HAL_USART_CR1_PS,
    HAL_USART_CR1_PCE,
    HAL_USART_CR1_WAKE,
    HAL_USART_CR1_M,
    HAL_USART_CR1_UE,
    HAL_USART_CR1_OVER8 = 15
} HAL_USART_CR1_t;

typedef enum
{
    HAL_USART_CR2_ADD = 0,
    HAL_USART_CR2_LBDL = 5,
    HAL_USART_CR2_LBDIE,
    HAL_USART_CR2_LBCL = 8,
    HAL_USART_CR2_CPHA,
    HAL_USART_CR2_CPOL,
    HAL_USART_CR2_CLKEN,
    HAL_USART_CR2_STOP,
    HAL_USART_CR2_LINEN = 14
} HAL_USART_CR2_t;

typedef enum
{
    HAL_USART_CR3_EIE = 0,
    HAL_USART_CR3_IREN,
    HAL_USART_CR3_IRLP,
    HAL_USART_CR3_HDSEL,
    HAL_USART_CR3_NACK,
    HAL_USART_CR3_SCEN,
    HAL_USART_CR3_DMAR,
    HAL_USART_CR3_DMAT,
    HAL_USART_CR3_RTSE,
    HAL_USART_CR3_CTSE,
    HAL_USART_CR3_CTSIE,
    HAL_USART_CR3_ONEBIT
} HAL_USART_CR3_t;

typedef enum
{
    HAL_USART_SR_PE = 0,
    HAL_USART_SR_FE,
    HAL_USART_SR_NF,
    HAL_USART_SR_ORE,
    HAL_USART_SR_IDLE,
    HAL_USART_SR_RXNE,
    HAL_USART_SR_TC,
    HAL_USART_SR_TXE,
    HAL_USART_SR_LBD,
    HAL_USART_SR_CTS
} HAL_USART_SR_t;

/*
 * Usart flags 
 * */
#define USART_FLAGS_PE                  (1 << HAL_USART_SR_PE)
#define USART_FLAGS_FE                  (1 << HAL_USART_SR_FE)
#define USART_FLAGS_NF                  (1 << HAL_USART_SR_NF)
#define USART_FLAGS_ORE                 (1 << HAL_USART_SR_ORE)
#define USART_FLAGS_IDLE                (1 << HAL_USART_SR_IDLE)
#define USART_FLAGS_RXNE                (1 << HAL_USART_SR_RXNE)
#define USART_FLAGS_TC                  (1 << HAL_USART_SR_TC)
#define USART_FLAGS_TXE                 (1 << HAL_USART_SR_TXE)
#define USART_FLAGS_LBD                 (1 << HAL_USART_SR_LBD)
#define USART_FLAGS_CTS                 (1 << HAL_USART_SR_CTS)

/*
 * Application states
 */
#define USART_BUSY_IN_RX 1
#define USART_BUSY_IN_TX 2
#define USART_READY 0

/******************************************************************************************
 *								    USART APIs supported
 ******************************************************************************************/
/*
 * Peripheral Clock setup
 */
void hal_usart_periClockControl(USART_RegDef_t *pUSARTx, u8 EnorDi);

/*
 * Init and De-init
 */
void hal_usart_init(USART_Handle_t *pUSARTHandle);
void hal_usart_deinit(USART_RegDef_t *pUSARTx);

/*
 * Data Send and Receive
 */
void hal_usart_SendData(USART_Handle_t *pUSARTHandle, u8 *pTxBuffer, u32 Len);
void hal_usart_ReceiveData(USART_Handle_t *pUSARTHandle, u8 *pRxBuffer, u32 Len);
u8 hal_usart_SendDataIT(USART_Handle_t *pUSARTHandle, u8 *pTxBuffer, u32 Len);
u8 hal_usart_ReceiveDataIT(USART_Handle_t *pUSARTHandle, u8 *pRxBuffer, u32 Len);

/*
 * IRQ Configuration and ISR handling
 */
void hal_usart_IRQInterruptConfig(u8 IRQNumber, u8 EnorDi);
void hal_usart_IRQPriorityConfig(u8 IRQNumber, u32 IRQPriority);
void hal_usart_IRQHandling(USART_Handle_t *pHandle);

/*
 * Other Peripheral Control APIs
 */
void hal_usart_PeripheralControl(USART_RegDef_t *pUSARTx, u8 EnOrDi);
u8 hal_usart_GetFlagStatus(USART_RegDef_t *pUSARTx , u32 FlagName);
void hal_usart_ClearFlag(USART_RegDef_t *pUSARTx, u16 StatusFlagName);

/*
 * Application callback
 */
void hal_usart_ApplicationEventCallback(USART_Handle_t *pUSARTHandle, u8 AppEv);

#endif