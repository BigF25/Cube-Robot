/********************************************************************************************************
**                                 Copyright (c)          MEI15
**                                                 All Rights Reserved
**  
**                                 Email:                           QQ:
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
**  Version    : 
**  Modified By: 
**  Date       : 
**  Content    : 
**  Notes      : 
********************************************************************************************************/
#ifndef __MAIN_H
#define __MAIN_H

/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "Global.h"
/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/
//气缸
#define R_AIR_OPEN          GPIO_SetBits(GPIOA, GPIO_Pin_2)
#define R_AIR_CLOSE         GPIO_ResetBits(GPIOA, GPIO_Pin_2)
#define L_AIR_OPEN          GPIO_SetBits(GPIOA, GPIO_Pin_1)
#define L_AIR_CLOSE         GPIO_ResetBits(GPIOA, GPIO_Pin_1)
//步进电机脉冲
#define R_PUL_UP            GPIO_SetBits(GPIOB, GPIO_Pin_5)
#define R_PUL_DOWN          GPIO_ResetBits(GPIOB, GPIO_Pin_5)
#define L_PUL_UP            GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define L_PUL_DOWN          GPIO_ResetBits(GPIOB, GPIO_Pin_7)
//步进电机方向
#define R_DIR_P             GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define R_DIR_N             GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define L_DIR_P             GPIO_SetBits(GPIOB, GPIO_Pin_8)
#define L_DIR_N             GPIO_ResetBits(GPIOB, GPIO_Pin_8)

/*-------------------------------------------  M A C R O S  -------------------------------------------*/
//==================================双臂当前开合信息
#define CLOSE               0
#define OPEN                1 

typedef struct
{
	u8 LeftHand;
	u8 RightHand;
	u16 LeftDir;
	u16 RightDir;
}Hand;
/*--------------------------------------  D E C L A R A T I O N  --------------------------------------*/
/* Internal Variable */

/* External Variable */

/* Internal Function */

/* External Function */
extern Hand g_RobotHand;
#endif /*__MAIN_H*/
//===========================================  End Of File  ===========================================//
