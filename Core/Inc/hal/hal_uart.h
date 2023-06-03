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
    USART_Config_t   USART_Config;
}USART_Handle_t;



/*
 *@USART_Mode
 *Possible options for USART_Mode
 */
#define USART_MODE_ONLY_TX 0
#define USART_MODE_ONLY_RX 1
#define USART_MODE_TXRX  2

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
#define USART_PARITY_EN_ODD   2
#define USART_PARITY_EN_EVEN  1
#define USART_PARITY_DISABLE  0

/*
 *@USART_WordLength
 *Possible options for USART_WordLength
 */
#define USART_WORDLEN_8BITS  0
#define USART_WORDLEN_9BITS  1

/*
 *@USART_NoOfStopBits
 *Possible options for USART_NoOfStopBits
 */
#define USART_STOPBITS_1     0
#define USART_STOPBITS_0_5   1
#define USART_STOPBITS_2     2
#define USART_STOPBITS_1_5   3

/*
 *@USART_HWFlowControl
 *Possible options for USART_HWFlowControl
 */
#define USART_HW_FLOW_CTRL_NONE    	0
#define USART_HW_FLOW_CTRL_CTS    	1
#define USART_HW_FLOW_CTRL_RTS    	2
#define USART_HW_FLOW_CTRL_CTS_RTS	3

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
void hal_usart_Init(USART_Handle_t *pUSARTHandle);
void hal_usart_DeInit(USART_RegDef_t *pUSARTx);


/*
 * Data Send and Receive
 */
void hal_usart_SendData(USART_RegDef_t *pUSARTx,u8 *pTxBuffer, u32 Len);
void hal_usart_ReceiveData(USART_RegDef_t *pUSARTx, u8 *pRxBuffer, u32 Len);
u8 hal_usart_SendDataIT(USART_Handle_t *pUSARTHandle,u8 *pTxBuffer, u32 Len);
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