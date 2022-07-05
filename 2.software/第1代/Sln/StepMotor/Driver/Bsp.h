/********************************************************************************************************
**                                 Copyright (c)          MEI16
**                                                 All Rights Reserved
**  
**                                 Email: 1569783114@QQ.com      QQ:1569783114
**-------------------------------------------------------------------------------------------------------
**  MCU        : STM32F103RBT6 (STMicroelectronics)
**  Compiler   : Keil uVision 5.16
**  Module Name: 
**  Module Date: 2016-9-30
**  Module Auth: 
**  Description: 
**  Version    : V1.0
**  Notes      : 
**-------------------------------------------------------------------------------------------------------
**  Version    : 
**  Modified By: 
**  Date       : 
**  Content    : 
**  Notes      : 
********************************************************************************************************/
#ifndef __BSP_H
#define __BSP_H

/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "Global.h"
/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/
#define RX_BUF_SIZE 300          //USART1_DMA收数缓冲大小
/*-------------------------------------------  M A C R O S  -------------------------------------------*/


/*--------------------------------------  D E C L A R A T I O N  --------------------------------------*/
/* Internal Variable */

/* External Variable */
extern u32 SysTime_5us;
extern u8 DMAbuffer[RX_BUF_SIZE];
/* Internal Function */
void Bsp_GPIOInit(void);
void Bsp_USARTInit(void);    //串口初始化
void Bsp_TimerInit(void);
void Bsp_DMAInit(void);
/* External Function */
extern void Bsp_Init(void);     
extern void USARTSend(USART_TypeDef *com,char Data); //发送8位数据
#endif /*__BSP_H*/
//===========================================  End Of File  ===========================================//
