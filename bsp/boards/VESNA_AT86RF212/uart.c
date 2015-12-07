/**
\brief VESNA SNC-STM32 definition of the "uart" bsp module (based on openmoteSTM32 code).

\author Chang Tengfei <tengfei.chang@gmail.com>,  July 2012.
\author Alaeddine Weslati <alaeddine.weslati@inria.fr>,  January 2014.
*/

#include "stm32f10x_lib.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "uart.h"
#include "leds.h"

#include "rcc.h"
#include "nvic.h"

//=========================== defines =========================================

//=========================== variables =======================================

volatile uart_vars_t uart_vars;

//=========================== prototypes ======================================

//=========================== public ==========================================

void uart_init() 
{
  // reset local variables
  memset(&uart_vars,0,sizeof(uart_vars_t));

  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  uart_vars.isFirst = TRUE;
  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 

  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode            = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin             = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed           = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USART Rx as input floating */
  GPIO_InitStructure.GPIO_Mode            = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin             = GPIO_Pin_10;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate              = 115200;
  USART_InitStructure.USART_WordLength            = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits              = USART_StopBits_1;
  USART_InitStructure.USART_Parity                = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl   = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode                  = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStructure);

  USART_Cmd(USART1, ENABLE); // enable USART1
}

void uart_setCallbacks(uart_tx_cbt txCb, uart_rx_cbt rxCb) 
{
  uart_vars.txCb = txCb;
  uart_vars.rxCb = rxCb;
  
  //enable nvic uart.
  NVIC_uart();
}

void uart_enableInterrupts()
{
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

void uart_disableInterrupts()
{
	USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
}

void uart_clearRxInterrupts()
{
  USART_ClearFlag(USART1, USART_FLAG_RXNE);
}

void uart_clearTxInterrupts()
{
  USART_ClearFlag(USART1, USART_FLAG_TXE);
}

void uart_writeByte(uint8_t byteToWrite)
{
	if ((uart_vars.rxCb==NULL)&&(uart_vars.txCb==NULL)){
		//polling
		USART_SendData(USART1, byteToWrite);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		return;
	}
	if(uart_vars.isFirst){
		USART_SendData(USART1, byteToWrite);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		uart_vars.isFirst = FALSE;
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	}
	else {
		USART_SendData(USART1, byteToWrite);
	}
}

uint8_t uart_readByte()
{
  uint16_t temp;
  temp = USART_ReceiveData(USART1);
  return (uint8_t)temp;
}
//=========================== interrupt handlers ==============================

kick_scheduler_t uart_tx_isr() 
{
  uart_vars.txCb();
  return DO_NOT_KICK_SCHEDULER;
}

kick_scheduler_t uart_rx_isr() 
{
  uart_vars.rxCb();
  return DO_NOT_KICK_SCHEDULER;
}

