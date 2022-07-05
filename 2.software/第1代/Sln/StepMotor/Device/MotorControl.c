/********************************************************************************************************
**                                 Copyright (c)          MEI15
**                                                 All Rights Reserved
**  
**                                 Email:                     QQ:729527658
**-------------------------------------------------------------------------------------------------------
**  MCU        : STM32F407VG (STMicroelectronics)
**  Compiler   : Keil uVision 5.10
**  Module Name: 
**  Module Date: 2016-2
**  Module Auth: 
**  Description: 
**  Version    : V1.0
**  Notes      : 
**-------------------------------------------------------------------------------------------------------

********************************************************************************************************/
/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "MotorControl.h"
/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/
const int MotorSub = 1600;  //步进电机细分数
//====================================================加减速曲线参数
//空转90度
#define KZ90AcNum  98
int KZAc90[98]={
93,75,63,55,50,45,42,39,36,34,33,31,30,28,27,26,25,25,24,23,22,22,21,
21,20,20,19,19,19,18,18,18,17,17,17,16,16,16,16,15,15,15,15,15,14,14,14,14,
14,14,13,13,13,13,13,13,13,12,12,12,12,12,12,12,12,12,12,11,11,11,11,11,11,
11,11,11,11,11,11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,9,8,8,8
};
#define KZ90DecNum  98
int KZDec90[98]={
93,75,63,55,50,45,42,39,36,34,33,31,30,28,27,26,25,25,24,23,22,22,21,
21,20,20,19,19,19,18,18,18,17,17,17,16,16,16,16,15,15,15,15,15,14,14,14,14,
14,14,13,13,13,13,13,13,13,12,12,12,12,12,12,12,12,12,12,11,11,11,11,11,11,
11,11,11,11,11,11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,9,8,8,8
};
//空转180度
#define KZ180AcNum  98
int KZAc180[98]={
93,75,63,55,50,45,42,39,36,34,33,31,30,28,27,26,25,25,24,23,22,22,21,
21,20,20,19,19,19,18,18,18,17,17,17,16,16,16,16,15,15,15,15,15,14,14,14,14,
14,14,13,13,13,13,13,13,13,12,12,12,12,12,12,12,12,12,12,11,11,11,11,11,11,
11,11,11,11,11,11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,9,8,8,8
};
#define KZ180DecNum  98
int KZDec180[98]={
93,75,63,55,50,45,42,39,36,34,33,31,30,28,27,26,25,25,24,23,22,22,21,
21,20,20,19,19,19,18,18,18,17,17,17,16,16,16,16,15,15,15,15,15,14,14,14,14,
14,14,13,13,13,13,13,13,13,12,12,12,12,12,12,12,12,12,12,11,11,11,11,11,11,
11,11,11,11,11,11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,9,8,8,8
};
//拧动90度
#define ND90AcNum  108
int NDAc90[108]={
91,73,62,54,48,44,41,38,35,33,32,30,29,28,27,26,25,24,23,22,22,21,21,
20,20,19,19,18,18,18,17,17,17,16,16,16,16,15,15,15,15,15,14,14,14,14,14,13,
13,13,13,13,13,13,12,12,12,12,12,12,12,12,12,11,11,11,11,11,11,11,11,11,11,
11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
9,9,9,9,9,9,9,9,9,9
};
#define ND90DecNum  108
int NDDec90[108]={
91,73,62,54,48,44,41,38,35,33,32,30,29,28,27,26,25,24,23,22,22,21,21,
20,20,19,19,18,18,18,17,17,17,16,16,16,16,15,15,15,15,15,14,14,14,14,14,13,
13,13,13,13,13,13,12,12,12,12,12,12,12,12,12,11,11,11,11,11,11,11,11,11,11,
11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
9,9,9,9,9,9,9,9,9,9
};
//拧动180度
#define ND180AcNum  108
int NDAc180[108]={
91,73,62,54,48,44,41,38,35,33,32,30,29,28,27,26,25,24,23,22,22,21,21,
20,20,19,19,18,18,18,17,17,17,16,16,16,16,15,15,15,15,15,14,14,14,14,14,13,
13,13,13,13,13,13,12,12,12,12,12,12,12,12,12,11,11,11,11,11,11,11,11,11,11,
11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
9,9,9,9,9,9,9,9,9,9
};
#define ND180DecNum  108
int NDDec180[108]={
91,73,62,54,48,44,41,38,35,33,32,30,29,28,27,26,25,24,23,22,22,21,21,
20,20,19,19,18,18,18,17,17,17,16,16,16,16,15,15,15,15,15,14,14,14,14,14,13,
13,13,13,13,13,13,12,12,12,12,12,12,12,12,12,11,11,11,11,11,11,11,11,11,11,
11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
9,9,9,9,9,9,9,9,9,9
};
//带动90度
#define DD90AcNum  183
int DDAc90[183]={
96,91,87,83,80,77,74,72,70,68,66,64,62,
61,59,58,56,55,54,53,52,51,50,49,48,47,47,46,45,45,44,43,43,42,41,41,40,40,
39,39,38,38,38,37,37,36,36,36,35,35,35,34,34,34,33,33,33,32,32,32,32,31,31,
31,31,30,30,30,30,29,29,29,29,29,28,28,28,28,28,27,27,27,27,27,27,26,26,26,
26,26,26,26,25,25,25,25,25,25,25,24,24,24,24,24,24,24,24,24,23,23,23,23,23,
23,23,23,23,22,22,22,22,22,22,22,22,22,22,22,21,21,21,21,21,21,21,21,21,21,
21,21,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,19,19,19,19,19,19,19,19,
19,19,19,19,19,19,19,19,19,18,18,18,18,18,18,18,18,18,18,18
};
#define DD90DecNum  183
int DDDec90[183]={
96,91,87,83,80,77,74,72,70,68,66,64,62,
61,59,58,56,55,54,53,52,51,50,49,48,47,47,46,45,45,44,43,43,42,41,41,40,40,
39,39,38,38,38,37,37,36,36,36,35,35,35,34,34,34,33,33,33,32,32,32,32,31,31,
31,31,30,30,30,30,29,29,29,29,29,28,28,28,28,28,27,27,27,27,27,27,26,26,26,
26,26,26,26,25,25,25,25,25,25,25,24,24,24,24,24,24,24,24,24,23,23,23,23,23,
23,23,23,23,22,22,22,22,22,22,22,22,22,22,22,21,21,21,21,21,21,21,21,21,21,
21,21,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,19,19,19,19,19,19,19,19,
19,19,19,19,19,19,19,19,19,18,18,18,18,18,18,18,18,18,18,18
};
//带动180度
#define DD180AcNum  183
int DDAc180[183]={
96,91,87,83,80,77,74,72,70,68,66,64,62,
61,59,58,56,55,54,53,52,51,50,49,48,47,47,46,45,45,44,43,43,42,41,41,40,40,
39,39,38,38,38,37,37,36,36,36,35,35,35,34,34,34,33,33,33,32,32,32,32,31,31,
31,31,30,30,30,30,29,29,29,29,29,28,28,28,28,28,27,27,27,27,27,27,26,26,26,
26,26,26,26,25,25,25,25,25,25,25,24,24,24,24,24,24,24,24,24,23,23,23,23,23,
23,23,23,23,22,22,22,22,22,22,22,22,22,22,22,21,21,21,21,21,21,21,21,21,21,
21,21,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,19,19,19,19,19,19,19,19,
19,19,19,19,19,19,19,19,19,18,18,18,18,18,18,18,18,18,18,18
};
#define DD180DecNum  183
int DDDec180[183]={
96,91,87,83,80,77,74,72,70,68,66,64,62,
61,59,58,56,55,54,53,52,51,50,49,48,47,47,46,45,45,44,43,43,42,41,41,40,40,
39,39,38,38,38,37,37,36,36,36,35,35,35,34,34,34,33,33,33,32,32,32,32,31,31,
31,31,30,30,30,30,29,29,29,29,29,28,28,28,28,28,27,27,27,27,27,27,26,26,26,
26,26,26,26,25,25,25,25,25,25,25,24,24,24,24,24,24,24,24,24,23,23,23,23,23,
23,23,23,23,22,22,22,22,22,22,22,22,22,22,22,21,21,21,21,21,21,21,21,21,21,
21,21,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,19,19,19,19,19,19,19,19,
19,19,19,19,19,19,19,19,19,18,18,18,18,18,18,18,18,18,18,18
};
//加减速过程
/*----------------------------------------  F U N C T I O N S  ----------------------------------------*/
//接下来考虑急加速缓减速

void MoveL1(int AcDelay[],int DecDelay[],u16 AcNum,u16 DecNum)
{
	  int i;
	  int totalPulse=MotorSub/4;

		L_DIR_P;
	  delay_5us(20);
	
		for(i=0;i<AcNum;i++)                     //加速阶段
		{
			L_PUL_UP;
			delay_5us((int)(AcDelay[i]));
			L_PUL_DOWN;
			delay_5us((int)(AcDelay[i]));
		}
		
		for(i=AcNum;i<totalPulse-DecNum;i++)           //匀速阶段
		{
			L_PUL_UP;
			delay_5us(AcDelay[AcNum-1]);
			L_PUL_DOWN;
			delay_5us(AcDelay[AcNum-1]);
		}

		for(i=totalPulse-DecNum;i<totalPulse;i++)  //减速阶段
		{
			L_PUL_UP;
			delay_5us((int)(DecDelay[totalPulse-i-1]));
			L_PUL_DOWN;
			delay_5us((int)(DecDelay[totalPulse-i-1]));
		}
		g_RobotHand.LeftDir += 1;
}
void MoveL2(int AcDelay[],int DecDelay[],u16 AcNum,u16 DecNum)
{
	  int i;
	  int totalPulse=MotorSub/2;
	
	  if(SysTime_5us%2==0)		L_DIR_P;
	  else                    L_DIR_N;
	  delay_5us(20);
	
		for(i=0;i<AcNum;i++)                     //加速阶段
		{
			L_PUL_UP;
			delay_5us((int)(AcDelay[i]));
			L_PUL_DOWN;
			delay_5us((int)(AcDelay[i]));
		}
		
		for(i=AcNum;i<totalPulse-DecNum;i++)           //匀速阶段
		{
			L_PUL_UP;
			delay_5us(AcDelay[AcNum-1]);
			L_PUL_DOWN;
			delay_5us(AcDelay[AcNum-1]);
		}

		for(i=totalPulse-DecNum;i<totalPulse;i++)  //减速阶段
		{
			L_PUL_UP;
			delay_5us((int)(DecDelay[totalPulse-i-1]));
			L_PUL_DOWN;
			delay_5us((int)(DecDelay[totalPulse-i-1]));
		}
		g_RobotHand.LeftDir += 2;
}
void MoveL3(int AcDelay[],int DecDelay[],u16 AcNum,u16 DecNum)
{
	  int i;
	  int totalPulse=MotorSub/4;

		L_DIR_N;
	  delay_5us(20);
	
		for(i=0;i<AcNum;i++)                     //加速阶段
		{
			L_PUL_UP;
			delay_5us((int)(AcDelay[i]));
			L_PUL_DOWN;
			delay_5us((int)(AcDelay[i]));
		}
		
		for(i=AcNum;i<totalPulse-DecNum;i++)           //匀速阶段
		{
			L_PUL_UP;
			delay_5us(AcDelay[AcNum-1]);
			L_PUL_DOWN;
			delay_5us(AcDelay[AcNum-1]);
		}

		for(i=totalPulse-DecNum;i<totalPulse;i++)  //减速阶段
		{
			L_PUL_UP;
			delay_5us((int)(DecDelay[totalPulse-i-1]));
			L_PUL_DOWN;
			delay_5us((int)(DecDelay[totalPulse-i-1]));
		}
		g_RobotHand.LeftDir += 3;
}
void MoveR1(int AcDelay[],int DecDelay[],u16 AcNum,u16 DecNum)
{
	  int i;
	  int totalPulse=MotorSub/4;

		R_DIR_P;
	  delay_5us(20);
	
		for(i=0;i<AcNum;i++)                     //加速阶段
		{
			R_PUL_UP;
			delay_5us((int)(AcDelay[i]));
			R_PUL_DOWN;
			delay_5us((int)(AcDelay[i]));
		}
		
		for(i=AcNum;i<totalPulse-DecNum;i++)           //匀速阶段
		{
			R_PUL_UP;
			delay_5us(AcDelay[AcNum-1]);
			R_PUL_DOWN;
			delay_5us(AcDelay[AcNum-1]);
		}

		for(i=totalPulse-DecNum;i<totalPulse;i++)  //减速阶段
		{
			R_PUL_UP;
			delay_5us((int)(DecDelay[totalPulse-i-1]));
			R_PUL_DOWN;
			delay_5us((int)(DecDelay[totalPulse-i-1]));
		}
		g_RobotHand.RightDir += 1;
}
void MoveR2(int AcDelay[],int DecDelay[],u16 AcNum,u16 DecNum)
{
	  int i;
	  int totalPulse=MotorSub/2;
	
	  if(SysTime_5us%2==0)		R_DIR_P;
	  else                    R_DIR_N;
	  delay_5us(20);
	
		for(i=0;i<AcNum;i++)                     //加速阶段
		{
			R_PUL_UP;
			delay_5us((int)(AcDelay[i]));
			R_PUL_DOWN;
			delay_5us((int)(AcDelay[i]));
		}
		
		for(i=AcNum;i<totalPulse-DecNum;i++)           //匀速阶段
		{
			R_PUL_UP;
			delay_5us(AcDelay[AcNum-1]);
			R_PUL_DOWN;
			delay_5us(AcDelay[AcNum-1]);
		}

		for(i=totalPulse-DecNum;i<totalPulse;i++)  //减速阶段
		{
			R_PUL_UP;
			delay_5us((int)(DecDelay[totalPulse-i-1]));
			R_PUL_DOWN;
			delay_5us((int)(DecDelay[totalPulse-i-1]));
		}
		g_RobotHand.RightDir += 2;
}
void MoveR3(int AcDelay[],int DecDelay[],u16 AcNum,u16 DecNum)
{
	  int i;
	  int totalPulse=MotorSub/4;

		R_DIR_N;
	  delay_5us(20);
	
		for(i=0;i<AcNum;i++)                     //加速阶段
		{
			R_PUL_UP;
			delay_5us((int)(AcDelay[i]));
			R_PUL_DOWN;
			delay_5us((int)(AcDelay[i]));
		}
		
		for(i=AcNum;i<totalPulse-DecNum;i++)           //匀速阶段
		{
			R_PUL_UP;
			delay_5us(AcDelay[AcNum-1]);
			R_PUL_DOWN;
			delay_5us(AcDelay[AcNum-1]);
		}
		
		for(i=totalPulse-DecNum;i<totalPulse;i++)  //减速阶段
		{
			R_PUL_UP;
			delay_5us((int)(DecDelay[totalPulse-i-1]));
			R_PUL_DOWN;
			delay_5us((int)(DecDelay[totalPulse-i-1]));
		}
		g_RobotHand.RightDir += 3;
}
//=========================延时时间常数，单位ms
u16   OpenHand_TIM                 =   40;    //气缸打开
u16   CloseHand_TIM                =   80;    //气缸关闭
u16   MotorMove_TIM                =   0;     

void MotorMove(u8 MechStep)
{
	/*
		L_C: 0		R_C: 5
		L_O: 1		R_O: 6
		L_1: 2		R_1: 7
		L_2: 3		R_2: 8
		L_3: 4		R_3: 9
	*/
	u16 AcNum=0;
	u16 DecNum=0;
	int *AcDelay;
	int *DecDelay;
  //空转90
	if(
		(((MechStep==L_1)||(MechStep==L_3)) && (g_RobotHand.LeftHand==OPEN))||
	  (((MechStep==R_1)||(MechStep==R_3)) && (g_RobotHand.RightHand==OPEN))
    )
	{
		AcNum = KZ90AcNum;
		DecNum = KZ90DecNum;
		AcDelay=KZAc90;
		DecDelay=KZDec90;
	}
  //空转180
	if(
		((MechStep==L_2) && (g_RobotHand.LeftHand==OPEN))||
	  ((MechStep==R_2) && (g_RobotHand.RightHand==OPEN))
    )
	{
  		AcNum = KZ180AcNum;
		  DecNum = KZ180DecNum;
		  AcDelay=KZAc180;
		  DecDelay=KZDec180;
	}
	//拧动90
	else if(
         ((MechStep==L_1)||(MechStep==L_3)||(MechStep==R_1)||(MechStep==R_3))&&
         ((g_RobotHand.RightHand==CLOSE)&&(g_RobotHand.LeftHand==CLOSE))
         )
	{
		AcNum = ND90AcNum;
		DecNum = ND90DecNum;
		AcDelay=NDAc90;
		DecDelay=NDDec90;
	}
	//拧动180
	else if(
         ((MechStep==L_2)||(MechStep==R_2))&&
         ((g_RobotHand.RightHand==CLOSE)&&(g_RobotHand.LeftHand==CLOSE))
         )
	{
		AcNum = ND180AcNum;
		DecNum = ND180DecNum;
		AcDelay=NDAc180;
		DecDelay=NDDec180;
	}
	//带动90
	else if(
		     (((MechStep==L_1)||(MechStep==L_3)) && ((g_RobotHand.LeftHand==CLOSE)&&(g_RobotHand.RightHand==OPEN)))||
	       (((MechStep==R_1)||(MechStep==R_3)) && ((g_RobotHand.RightHand==CLOSE)&&(g_RobotHand.LeftHand==OPEN)))
         )
	{
		AcNum = DD90AcNum;
		DecNum = DD90DecNum;
		AcDelay=DDAc90;
		DecDelay=DDDec90;
	}
	//带动180
	else if(
		     ((MechStep==L_2) && ((g_RobotHand.LeftHand==CLOSE)&&(g_RobotHand.RightHand==OPEN)))||
	       ((MechStep==R_2) && ((g_RobotHand.RightHand==CLOSE)&&(g_RobotHand.LeftHand==OPEN)))
         )
	{
		AcNum = DD180AcNum;
		DecNum = DD180DecNum;
		AcDelay=DDAc180;
		DecDelay=DDDec180;
	}  

	switch(MechStep)
	{
		case L_C:
		{
			g_RobotHand.LeftHand=CLOSE;
			L_AIR_CLOSE;
			delay_5us(CloseHand_TIM*200);
			break;
		}
		case L_O:
		{
			g_RobotHand.LeftHand=OPEN;
			L_AIR_OPEN;
			delay_5us(OpenHand_TIM*200);
			break;
		}
		case L_1:MoveL1(AcDelay,DecDelay,AcNum,DecNum);break;
		case L_2:MoveL2(AcDelay,DecDelay,AcNum,DecNum);break;
		case L_3:MoveL3(AcDelay,DecDelay,AcNum,DecNum);break;
		case R_C:
		{
			g_RobotHand.RightHand=CLOSE;
			R_AIR_CLOSE;
			delay_5us(CloseHand_TIM*200);
			break;
		}
		case R_O:
		{
			g_RobotHand.RightHand=OPEN;
			R_AIR_OPEN;
			delay_5us(OpenHand_TIM*200);
			break;
		}
		case R_1:MoveR1(AcDelay,DecDelay,AcNum,DecNum);break;
		case R_2:MoveR2(AcDelay,DecDelay,AcNum,DecNum);break;
		case R_3:MoveR3(AcDelay,DecDelay,AcNum,DecNum);break;
		default:break;
	}
}

//====================================================用于测定每个环节的耗时
int TimeCost[5]={0,0,0,0,0};
void GetTimeCost(void)
{
	int i;
	 int totalPulse;
	 int AcNum;
	 int DecNum;
	 int* AcDelay;
	 int* DecDelay;
   int j;
	//计算空转90耗时
	totalPulse=MotorSub/4;
	AcNum=KZ90AcNum;
	DecNum=KZ90DecNum;
	AcDelay=KZAc90;
	DecDelay=KZDec90;
	j=0;
		for(i=0;i<AcNum;i++)                     //加速阶段
		{
			TimeCost[j]+=AcDelay[i];
		}
		for(i=AcNum;i<totalPulse-DecNum;i++)           //匀速阶段
		{
			TimeCost[j]+=AcDelay[AcNum-1];
		}
		for(i=totalPulse-DecNum;i<totalPulse;i++)  //减速阶段
		{
			TimeCost[j]+=DecDelay[totalPulse-i-1];
		}
	//计算拧动90耗时
	totalPulse=MotorSub/4;
	AcNum=ND90AcNum;
	DecNum=ND90DecNum;
	AcDelay=NDAc90;
	DecDelay=NDDec90;
	j=1;
		for(i=0;i<AcNum;i++)                     //加速阶段
		{
			TimeCost[j]+=AcDelay[i];
		}
		for(i=AcNum;i<totalPulse-DecNum;i++)           //匀速阶段
		{
			TimeCost[j]+=AcDelay[AcNum-1];
		}
		for(i=totalPulse-DecNum;i<totalPulse;i++)  //减速阶段
		{
			TimeCost[j]+=DecDelay[totalPulse-i-1];
		}
			//计算拧动180耗时
	totalPulse=MotorSub/2;
	AcNum=ND180AcNum;
	DecNum=ND180DecNum;
	AcDelay=NDAc180;
	DecDelay=NDDec180;
	j=2;
		for(i=0;i<AcNum;i++)                     //加速阶段
		{
			TimeCost[j]+=AcDelay[i];
		}
		for(i=AcNum;i<totalPulse-DecNum;i++)           //匀速阶段
		{
			TimeCost[j]+=AcDelay[AcNum-1];
		}
		for(i=totalPulse-DecNum;i<totalPulse;i++)  //减速阶段
		{
			TimeCost[j]+=DecDelay[totalPulse-i-1];
		}
					//计算带动90耗时
	totalPulse=MotorSub/4;
	AcNum=DD90AcNum;
	DecNum=DD90DecNum;
	AcDelay=DDAc90;
	DecDelay=DDDec90;
	j=3;
		for(i=0;i<AcNum;i++)                     //加速阶段
		{
			TimeCost[j]+=AcDelay[i];
		}
		for(i=AcNum;i<totalPulse-DecNum;i++)           //匀速阶段
		{
			TimeCost[j]+=AcDelay[AcNum-1];
		}
		for(i=totalPulse-DecNum;i<totalPulse;i++)  //减速阶段
		{
			TimeCost[j]+=DecDelay[totalPulse-i-1];
		}
							//计算带动180耗时
	totalPulse=MotorSub/2;
	AcNum=DD180AcNum;
	DecNum=DD180DecNum;
	AcDelay=DDAc180;
	DecDelay=DDDec180;
	j=4;
		for(i=0;i<AcNum;i++)                     //加速阶段
		{
			TimeCost[j]+=AcDelay[i];
		}
		for(i=AcNum;i<totalPulse-DecNum;i++)           //匀速阶段
		{
			TimeCost[j]+=AcDelay[AcNum-1];
		}
		for(i=totalPulse-DecNum;i<totalPulse;i++)  //减速阶段
		{
			TimeCost[j]+=DecDelay[totalPulse-i-1];
		}
		
		//清空
		for(i=0;i<5;i++)
		{
			TimeCost[i]/=100;
		}
		
}
//===========================================  End Of File  ===========================================//
