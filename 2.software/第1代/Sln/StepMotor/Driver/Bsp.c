/********************************************************************************************************
**                                 Copyright (c)  All Rights Reserved
**                                 Email:                     QQ:
**-------------------------------------------------------------------------------------------------------
**  MCU        : STM32F103RBT6 (STMicroelectronics)
**  Compiler   : Keil uVision 5.10
**  Module Name: 
**  Module Date: 2016-
**  Module Auth: 
**  Description: 
**  Version    : V1.0
**  Notes      : 
**-------------------------------------------------------------------------------------------------------
********************************************************************************************************/
/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "Bsp.h"
#include "stm32f10x_tim.h"
/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/

/*
******************************************************************************************************************
--------------------------------------------------IO口分配说明-----------------------------------------------------
******************************************************************************************************************
 步进电机：
// R_PUL      ->  PB5
// R_DIR      ->  PB6
// L_PUL      ->  PB7
// L_DIR      ->  PB8
 气缸
// R_AIR      ->  PA1
// L_AIR      ->  PA2
 串口：
 USART1_RX  ->  PA10
 USART1_TX  ->  PA9
*/
/*----------------------------------------  F U N C T I O N S  ----------------------------------------*/
void Bsp_Init(void)
{
		Bsp_GPIOInit();
    Bsp_USARTInit();
	  Bsp_TimerInit();
	  Bsp_DMAInit();
}
/*
******************************************************************************************************************
--------------------------------------------------IO口初始化----------------------------------------------------
******************************************************************************************************************
*/
void Bsp_GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
 //步进电机：
// R_PUL      ->  PB5
// R_DIR      ->  PB6
// L_PUL      ->  PB7
// L_DIR      ->  PB8
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	//气缸
// R_AIR      ->  PA1
// L_AIR      ->  PA2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  // 串口：
// USART1_RX  ->  PA10
// USART1_TX  ->  PA9
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* Configure USART1 Rx (PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/*
******************************************************************************************************************
--------------------------------------------------USART相关配置-----------------------------------------------------
******************************************************************************************************************
*/
//初始化函数
void Bsp_USARTInit()
{
	//USART1
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_DeInit(USART1);
	USART_InitStructure.USART_BaudRate = 38400;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
	USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
}

//发送函数
void USARTSend(USART_TypeDef *com,char Data)
{
    USART_SendData(com, Data);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){}
}/*
******************************************************************************************************************
--------------------------------------------------USART相关配置-----------------------------------------------------
******************************************************************************************************************
*/
u32 SysTime_5us=0;
void Bsp_TimerInit()
{
	//配置滴答定时器5us中断
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	SysTick_Config(360);  //360
}
/*
******************************************************************************************************************
--------------------------------------------------DMA相关配置-----------------------------------------------------
******************************************************************************************************************
*/
u8 DMAbuffer[RX_BUF_SIZE];
void Bsp_DMAInit(void)
{
  DMA_InitTypeDef DMA_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	//USART1_DMA
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR);
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)&DMAbuffer[0];
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_BufferSize = sizeof(DMAbuffer);
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_Low;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel5, &DMA_InitStruct);
	DMA_Cmd(DMA1_Channel5, ENABLE);
}
//===========================================  End Of File  ===========================================//
