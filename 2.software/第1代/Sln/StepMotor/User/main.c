/********************************************************************************************************
**                                 Copyright (c)          MEI16
**                                                 All Rights Reserved
**
**                                 Email:1569783114@qq.com             QQ:1569783114
**-------------------------------------------------------------------------------------------------------
**  MCU        : STM32F103RBT6 (STMicroelectronics)
**  Compiler   : Keil uVision 5.16a
********************************************************************************************************/
/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "main.h"
/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/
Hand g_RobotHand;
/*----------------------------------------  F U N C T I O N S  ----------------------------------------*/
void OtherInitial(void)
{
	g_RobotHand.LeftHand = CLOSE;
	g_RobotHand.RightHand = CLOSE;
	g_RobotHand.LeftDir = 0;
	g_RobotHand.RightDir = 0;
}
s8 MechSteps[150];
void MechStepsInit(void)
{
	int i = 0;
	for (i = 0; i < 150; i++)
	{
		MechSteps[i] = -1;
	}
}
void DMAdataInit(void)
{
	int i;
	for (i = 0; i < 300; i++)
	{
		DMAbuffer[i] = 0;
	}
}
//��һ�ν�ħ�������󣬸�λ��ץλ��
void ResetHandDir(void)
{
	g_RobotHand.LeftDir %= 4;
	g_RobotHand.RightDir %= 4;
	//���Ƚ�������ץ��λ��0��2λ��
	if (g_RobotHand.LeftDir == 1)
	{
		MotorMove(L_O);
		MotorMove(L_3);
		MotorMove(L_C);
	}
	if (g_RobotHand.LeftDir == 3)
	{
		MotorMove(L_O);
		MotorMove(L_1);
		MotorMove(L_C);
	}
	if (g_RobotHand.RightDir == 1)
	{
		MotorMove(R_O);
		MotorMove(R_3);
		MotorMove(R_C);
	}
	if (g_RobotHand.RightDir == 3)
	{
		MotorMove(R_O);
		MotorMove(R_1);
		MotorMove(R_C);
	}
	//Ȼ��2��λ��0λ��
	if (g_RobotHand.LeftDir == 2)
	{
		MotorMove(L_O);
		MotorMove(L_2);
		MotorMove(L_C);
	}
	if (g_RobotHand.RightDir == 2)
	{
		MotorMove(R_O);
		MotorMove(R_2);
		MotorMove(R_C);
	}

}
//================================================================DMA���ݰ�
#define NO_DATA      0
#define SECOND_CAP   1
#define MOVE         2
u8 ReleaseDMApack(void)
{
	//DMA���
	/*
			��ͷ: 0XAA

			����ת����
			L_C: 0		R_C: 5
			L_O: 1		R_O: 6
			L_1: 2		R_1: 7
			L_2: 3		R_2: 8
			L_3: 4		R_3: 9
		  ��Ч���ݽ�������:0xBB
		  ��β: 0xBB
	*/
	u16 i = 0;
	u16 j = 0;
	//MechStepsInit();
	for (i = 0; i <= 150; i++)
	{
		if ((DMAbuffer[i] == 0xAA) && (DMAbuffer[i + 149] == 0xBB))
		{
			if (DMAbuffer[i + 1] == 0XFF)  //�ڶ���ɨ��
			{
				return SECOND_CAP;
			}
			else
			{
				for (j = 0; j < 148; j++)
				{
					if (DMAbuffer[i + j + 1] == 0XBB)
					{
						break;
					}
					else
					{
						MechSteps[j] = DMAbuffer[i + j + 1];
					}
				}
				return MOVE;
			}
		}
	}
	return NO_DATA;
}

/********************************************************************************************************
Description  :
Inputs       : None
Outputs      : None
********************************************************************************************************/
u8 moveflag = 10;
u8 steps[] = {
M_L2,M_RO,M_L2,M_RC,M_R3,M_LO,M_R1,M_L1,M_LC,M_RO,
M_L3,M_RC,M_R2,M_RO,M_L3,M_RC,M_L3,M_R1,M_LO,M_R1,
M_LC,M_L2,M_LO,M_R3,M_LC,M_RO,M_R1,M_L2,M_RC,M_L2,
M_R1,M_LO,M_R1,M_LC,M_L3,M_RO,M_L2,M_RC,M_LO,M_L1,
M_R2,M_LC,M_R2,M_RO,M_L2,M_R1,M_RC,M_R1,M_L2,M_RO,
M_L2,M_R1,M_RC,M_R3,M_L2,M_LO,M_R1,M_LC,M_RO,M_R1,
M_L2,M_RC,M_L2,M_R2,M_L2,M_LO,M_L1,M_LC,M_RO,M_L3,
M_RC,M_R1,M_RO,M_R1,M_L2,M_RC,M_R2
};  //77
int main(void)
{
	int i = 0;
	u8 ReleaseDMApackReturn;
	Bsp_Init();
	DMAdataInit();
	//GetTimeCost();

	g_RobotHand.RightHand = CLOSE;
	g_RobotHand.LeftHand = CLOSE;
	//	while(1)
	//	{
	//		if(moveflag<10)
	//		{
	//			MotorMove(moveflag);
	//			moveflag=10;
	//		}
	//		if(moveflag==66)
	//		{
	//			moveflag=10;
	//			for(i=0;i<77;i++)
	//			{
	//				MotorMove(steps[i]);
	//			}
	//		}
	//	}
	while (1)
	{
		//��ʼ����е�����б�
		MechStepsInit();
		//DMA���
		ReleaseDMApackReturn = ReleaseDMApack();
		if (ReleaseDMApackReturn == NO_DATA)
		{
			//do nothing
		}
		else if (ReleaseDMApackReturn == SECOND_CAP)
		{
			MotorMove(R_O);
			MotorMove(L_3);
			MotorMove(R_C);
			MotorMove(L_O);
			MotorMove(L_1);
			MotorMove(L_C);
			//���ͽ�����־

			USARTSend(USART1, 0XCC);
			USARTSend(USART1, 0XCC);
			USARTSend(USART1, 0XCC);
			DMAdataInit();
		}

		else if (ReleaseDMApackReturn == MOVE)
		{
			//��ħ��
			for (i = 0; i < 150; i++)
			{
				if (MechSteps[i] == -1)
				{
					break;
				}
				else
				{
					MotorMove(MechSteps[i]);
				}
			}
			//��������ץλ��

			//���������һЩ����
			USARTSend(USART1, 0XDD);
			USARTSend(USART1, 0XDD);
			USARTSend(USART1, 0XDD);
			ResetHandDir();
			DMAdataInit();
		}
	}
}

//		//test
//	/*
//		L_C: 0		R_C: 5
//		L_O: 1		R_O: 6
//		L_1: 2		R_1: 7
//		L_2: 3		R_2: 8
//		L_3: 4		R_3: 9
//	*/ //
//		if(moveflag<10)
//		{
//			MotorMove(moveflag);
//			moveflag=10;
//		}
//		if(moveflag==66)
//		{

//			moveflag=10;
//			for(i=0;i<77;i++)
//			{
//				MotorMove(steps[i]);
//				delay_5us(200000);
//			}
//		}

//===========================================  End Of File  ===========================================//
