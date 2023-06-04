#include <hal/hal_uart.h>
#include <hal/hal_type.h>
#include <hal/hal_reg.h>

/*
 * Peripheral Clock setup
 */
/************************************************************************
 * @fn             - hal_usart_periClockControl
 * @brief          - This function enables or disables peripheral clock
 *                   for the given gpio port
 * @param[in]      - pGPIOx
 * @param[in]      - permission
 * @return         - none
 * @note           - none
 ************************************************************************/
void hal_usart_periClockControl(USART_RegDef_t *pUSARTx, u8 permission)
{
    if(permission == ENABLE)
    {
        if(pUSARTx == USART1)
        {
            USART1_PCLK_EN();
        }
        else if(pUSARTx == USART2)
        {
            USART2_PCLK_EN();
        }
        else if(pUSARTx == USART3)
        {
            USART3_PCLK_EN();
        }
        else if(pUSARTx == UART4)
        {
            UART4_PCLK_EN();
        }
        else if(pUSARTx == UART5)
        {
            UART5_PCLK_EN();
        }
        else if(pUSARTx == USART6)
        {
            USART6_PCLK_EN();
        }
    }
    else
    {
        if(pUSARTx == USART1)
        {
            USART1_PCLK_DI();
        }
        else if(pUSARTx == USART2)
        {
            USART2_PCLK_DI();
        }
        else if(pUSARTx == USART3)
        {
            USART3_PCLK_DI();
        }
        else if(pUSARTx == UART4)
        {
            UART4_PCLK_DI();
        }
        else if(pUSARTx == UART5)
        {
            UART5_PCLK_DI();
        }
        else if(pUSARTx == USART6)
        {
            USART6_PCLK_DI();
        }
    }
}

/*
 * Init and De-init
 */
void hal_usart_init(USART_Handle_t *pUSARTHandle)
{
    //Temporary variable
    u32 tempreg=0;
/******************************** Configuration of CR1******************************************/

    //Implement the code to enable the Clock for given USART peripheral
    hal_usart_periClockControl(pUSARTHandle->pUSARTx, ENABLE);

    //Enable USART Tx and Rx engines according to the USART_Mode configuration item
    if ( pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_RX)
    {
        //Implement the code to enable the Receiver bit field 
        tempreg|= (1 << HAL_USART_CR1_RE);
    }else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_TX)
    {
        //Implement the code to enable the Transmitter bit field 
        tempreg |= (1 << HAL_USART_CR1_TE);

    }else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX)
    {
        //Implement the code to enable the both Transmitter and Receiver bit fields 
        tempreg |= (( 1 << HAL_USART_CR1_RE) | ( 1 << HAL_USART_CR1_TE) );
    }

    //Implement the code to configure the Word length configuration item 
    tempreg |= pUSARTHandle->USART_Config.USART_WordLength << HAL_USART_CR1_M ;


    //Configuration of parity control bit fields
    if ( pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_EVEN)
    {
        //Implement the code to enale the parity control 
        tempreg |= ( 1 << HAL_USART_CR1_PCE);

        //Implement the code to enable EVEN parity 
        //Not required because by default EVEN parity will be selected once you enable the parity control 

    }else if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_ODD )
    {
        //Implement the code to enable the parity control 
        tempreg |= ( 1 << HAL_USART_CR1_PCE);

        //Implement the code to enable ODD parity 
        tempreg |= ( 1 << HAL_USART_CR1_PS);

    }

    //Program the CR1 register 
    pUSARTHandle->pUSARTx->cr1 = tempreg;

/******************************** Configuration of CR2******************************************/

    tempreg=0;

    // Implement the code to configure the number of stop bits inserted during 
    // USART frame transmission 
    tempreg |= pUSARTHandle->USART_Config.USART_NoOfStopBits << HAL_USART_CR2_STOP;

    //Program the CR2 register 
    pUSARTHandle->pUSARTx->cr2 = tempreg;

/******************************** Configuration of CR3******************************************/

    tempreg=0;

    //Configuration of USART hardware flow control 
    if ( pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
    {
        //Implement the code to enable CTS flow control 
        tempreg |= (1 << HAL_USART_CR3_CTSE);


    }else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
    {
        //Implement the code to enable RTS flow control 
        tempreg |= (1 << HAL_USART_CR3_RTSE);

    }else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
    {
        //Implement the code to enable both CTS and RTS Flow control 
        tempreg |= (1 << HAL_USART_CR3_CTSE);
        tempreg |= (1 << HAL_USART_CR3_RTSE);
    }


    pUSARTHandle->pUSARTx->cr3 = tempreg;

/******************************** Configuration of BRR(Baudrate register)******************************************/

    //Implement the code to configure the baud rate
    //We will cover this in the lecture. No action required here 
}

void hal_usart_deinit(USART_RegDef_t *pUSARTx)
{

}

/*
 * Data Send and Receive
 */
void hal_usart_SendData(USART_Handle_t *pUSARTHandle, u8 *pTxBuffer, u32 Len)
{
    u16 *pdata;
    
    //Loop over until "Len" number of bytes are transferred
	for(u32 i = 0 ; i < Len; i++)
	{
		//Implement the code to wait until TXE flag is set in the SR
		while(!hal_usart_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAGS_TXE));

         //Check the USART_WordLength item for 9BIT or 8BIT in a frame
		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
		{
			//if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits 
			pdata = (u16*) pTxBuffer;
			pUSARTHandle->pUSARTx->dr = (*pdata & (u16)0x01FF);
			
			//check for USART_ParityControl
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				//No parity is used in this transfer. so, 9bits of user data will be sent
				//Implement the code to increment pTxBuffer twice 
				pTxBuffer++;
				pTxBuffer++;
			}
			else
			{
				//Parity bit is used in this transfer. Thus, 8bits of user data will be sent
				//The 9th bit will be replaced by parity bit by the hardware
				pTxBuffer++;
			}
		}
		else
		{
			//This is 8bit data transfer 
			pUSARTHandle->pUSARTx->dr = (*pTxBuffer  & (u8)0xFF);
			
			//Implement the code to increment the buffer address
			pTxBuffer++;
		}
	}

	//Implement the code to wait till TC flag is set in the SR
	while( ! hal_usart_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAGS_TC));
}

void hal_usart_ReceiveData(USART_Handle_t *pUSARTHandle, u8 *pRxBuffer, u32 Len)
{
    //Loop over until "Len" number of bytes are transferred
	for(u32 i = 0 ; i < Len; i++)
	{
		// Implement the code to wait until RXNE flag is set in the SR
		while(!hal_usart_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAGS_RXNE));

		// Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit
		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
		{
			// We are going to receive 9bit data in a frame
			// check are we using USART_ParityControl control or not
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				// No parity is used. so, all 9bits will be of user data
				// read only first 9 bits. so, mask the DR with 0x01FF
				*((u16*) pRxBuffer) = (pUSARTHandle->pUSARTx->dr  & (u16) 0x1FF);

				// Now increment the pRxBuffer two times
				pRxBuffer++;
                pRxBuffer++;
			}
			else
			{
				// Parity is used, so, 8bits will be of user data and 1 bit is parity
				*pRxBuffer = (pUSARTHandle->pUSARTx->dr & (u8) 0xFF);
				 
				// Increment the pRxBuffer
				pRxBuffer++;
			}
		}
		else
		{
			//We are going to receive 8bit data in a frame
			//check are we using USART_ParityControl control or not
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				// No parity is used , so all 8bits will be of user data
				// read 8 bits from DR
				 *pRxBuffer = (u8) pUSARTHandle->pUSARTx->dr & (u8) 0xFF;
			}

			else
			{
				//Parity is used, so , 7 bits will be of user data and 1 bit is parity
				//read only 7 bits , hence mask the DR with 0X7F
				 *pRxBuffer = (u8) pUSARTHandle->pUSARTx->dr & (u8) 0x7F;

			}

			//increment the pRxBuffer
			pRxBuffer++;
		}
	}
}

u8 hal_usart_SendDataIT(USART_Handle_t *pUSARTHandle, u8 *pTxBuffer, u32 Len)
{
    u8 txstate = pUSARTHandle->TxBusyState;

	if(txstate != USART_BUSY_IN_TX)
	{
		pUSARTHandle->TxLen = Len;
		pUSARTHandle->pTxBuffer = pTxBuffer;
		pUSARTHandle->TxBusyState = USART_BUSY_IN_TX;

		//Implement the code to enable interrupt for TXE
		pUSARTHandle->pUSARTx->cr1 |= (1 << HAL_USART_CR1_TXEIE);

		//Implement the code to enable interrupt for TC 
		pUSARTHandle->pUSARTx->cr1 |= (1 << HAL_USART_CR1_TCIE);
	}

	return txstate;
}

u8 hal_usart_ReceiveDataIT(USART_Handle_t *pUSARTHandle, u8 *pRxBuffer, u32 Len)
{
    u8 rxstate = pUSARTHandle->RxBusyState;

	if(rxstate != USART_BUSY_IN_RX)
	{
		pUSARTHandle->RxLen = Len;
		pUSARTHandle->pRxBuffer = pRxBuffer;
		pUSARTHandle->RxBusyState = USART_BUSY_IN_RX;

		//Implement the code to enable interrupt for RXNE
        pUSARTHandle->pUSARTx->cr1 |= (1 << HAL_USART_CR1_RXNEIE);
	}

	return rxstate;
}

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

/************************************************************************
 * @fn             - hal_hal_usart_GetFlagStatus
 * @brief          - Get the flags in the status register 
 * @param[in]      - pUSARTx
 * @param[in]      - FlagName
 * @return         - 1 as the flag is Set, 0 as cleared
 * @note           - none
 ************************************************************************/
u8 hal_hal_usart_GetFlagStatus(USART_RegDef_t *pUSARTx , u32 FlagName)
{
    return pUSARTx->sr & FlagName ? 1 : 0;
}

/************************************************************************
 * @fn             - hal_usart_ClearFlag
 * @brief          - Clear the flag name
 * @param[in]      - pUSARTx
 * @param[in]      - StatusFlagName
 * @return         - 1 as the flag is Set, 0 as cleared
 * @note           - none
 ************************************************************************/
void hal_usart_ClearFlag(USART_RegDef_t *pUSARTx, u16 StatusFlagName)
{
    pUSARTx->sr &= ~(StatusFlagName);
}

/*
 * Application callback
 */
void hal_usart_ApplicationEventCallback(USART_Handle_t *pUSARTHandle, u8 AppEv)
{

}