#include <iostream>
#include <string>
using namespace std;
/*************************************************************************************************/
/*程序功能：生成转换算法的搜索库，生成的库将被放入转换算法sln的Data.c文件中                      */
/*************************************************************************************************/
/*
异常判断：
1、两个手爪同时打开
2、两个手爪同时在1位置
3、上一步为打开或者关闭某手爪，而这一步为打开或者关闭此手爪
4、上一步为拧动某手爪，这一步也是拧动此手爪
5、手爪同时闭合时拧动手爪
6、手爪已经闭合时闭合手爪，手爪已经打开时候打开手爪
7、执行当前操作后的状态，曾经发生过
完成搜索目标判断：
1、无异常
2、两个手爪同时闭合
3、目标方位在F面或者R面
4、将要拧动的手爪的另一个手爪状态为0(即nice)
什么时候魔方朝向改变：
一个手爪闭合，另一个打开，闭合的那个拧动
*/
//定义初始手臂状态
struct HandState
{
	int IsLeftOpen = 0;  //0为闭合
	int IsRightOpen = 0;

	int LeftNotNice = 0; //0为nice
	int RightNotNice = 0;

	void Set(int _IsLeftOpen, int _IsRightOpen, int _LeftNotNice, int _RightNotNice)
	{
		IsLeftOpen = _IsLeftOpen;
		IsRightOpen = _IsRightOpen;
		LeftNotNice = _LeftNotNice;
		RightNotNice = _RightNotNice;
	}
}g_HandState;
//定义旋转变换矩阵
struct Rot
{
	int a[3][3];
	void Set(int row0, int num0, int row1, int num1, int row2, int num2)
	{
		for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			a[i][j] = 0;

		a[row0][0] = num0;
		a[row1][1] = num1;
		a[row2][2] = num2;
	}
}R_x1, R_x2, R_x3, R_y1, R_y2, R_y3, R_z1, R_z2, R_z3, R_org, g_CubeRot;
//定义空间点
struct Point3
{
	int a[3][1];
	string name;
}P_F,P_R,P_U,P_B,P_L,P_D;
//=========================================宏
#define L1 0
#define L2 1
#define L3 2
#define LC 3
#define LO 4
#define R1 5
#define R2 6
#define R3 7
#define RC 8
#define RO 9

#define F 0
#define R 1
#define U 2
#define B 3
#define L 4
#define D 5
//=========================================全局常量
const string moveStr[10] = { "M_L1", "M_L2", "M_L3", "M_LC", "M_LO", "M_R1", "M_R2", "M_R3", "M_RC", "M_RO" };
const string faceStr[6] = { "F", "R", "U", "B", "L", "D" };
//=========================================函数声明
void dfs(int step);
void RotInit(void);
void PointInit(void);
void UpdateHandAndCubeRot(int mov);
bool CaseHasHappened(int step);
Point3 RotMtplPoint3(Rot l, Point3 r);
Rot RotMtplRot(Rot l, Rot r);
//=========================================全局变量
int g_buff[100];
Rot g_CubeRotList[100];
HandState g_HandStateList[100];
//参数调整  F 1 L0R0 0
Point3 g_face;
int g_RotDistance;
int g_SearchDepth;
int g_SloveNum;
void main(void)
{
	//初始化
	RotInit();     //xyz旋转矩阵
	PointInit();   //FRUBLD中心点的空间坐标
	g_HandState.IsLeftOpen = 0;
	g_HandState.IsRightOpen = 0;
	g_CubeRot.Set(0,1,1,1,2,1);  //立方体朝向
	g_SloveNum = 0;
	//更改区
	g_face = P_D;                    //要转哪一面
	g_RotDistance = 3;               //要转多少度
	g_HandState.LeftNotNice = 1;
	g_HandState.RightNotNice = 0;  //手爪状态
	g_SearchDepth = 9;  //搜索深度
	//F1_L0R0_0
	cout << g_face.name << g_RotDistance << "_";
	cout << "L" << g_HandState.LeftNotNice;
	cout << "R" << g_HandState.RightNotNice;
	cout << endl;

	dfs(0);
	cout << "g_SloveNum=" << g_SloveNum << endl;
	system("pause");
}
//=====================================================================深搜
void dfs(int step)
{
	Point3 tempPoint3 = RotMtplPoint3(g_CubeRot, g_face);
	//要拧动的面已经拧动到F位置
	if ((g_HandState.IsLeftOpen == 0) && (g_HandState.IsRightOpen == 0)&&(g_HandState.RightNotNice==0) && (tempPoint3.a[0][0]==1))
	{
		//保存当前状态
		HandState tempHandState = g_HandState;
		Rot tempRot = g_CubeRot;
		UpdateHandAndCubeRot(L1 + g_RotDistance-1);
		//打印此解
		cout << "\"";
		cout << " step: " << (step + 1) / 10 << (step + 1) % 10;
		cout << " hand: " << g_HandState.LeftNotNice << g_HandState.RightNotNice;
		cout << " rot: ";
		for (int j = 0; j < 3; j++)  //列
		{
			for (int i = 0; i < 3; i++)  //行
			{
				if (g_CubeRot.a[i][j] == 1)
				{
					cout << i<<"," << " 1," << "  ";
					break;
				}
				else if (g_CubeRot.a[i][j] == -1)
				{
					cout << i << "," << "-1," << "  ";
					break;
				}
			}
		}
		cout << "  ";
		for (int i = 0; i < step; i++)
		{
			cout << moveStr[g_buff[i]] << ", ";
		}
		cout << "M_L" << g_RotDistance << ", M_END";
		cout << "\"," << endl;
		//恢复手臂与旋转状态
		g_HandState = tempHandState;
		g_CubeRot = tempRot;
		//g_SloveNum自增
		g_SloveNum++;
		//返回
		if (step!=0)return;
	}
	//要拧动的面已经拧动到R位置
	else if ((g_HandState.IsLeftOpen == 0) && (g_HandState.IsRightOpen == 0) && (g_HandState.LeftNotNice == 0) && (tempPoint3.a[1][0] == 1)) 
	{
		//保存当前状态
		HandState tempHandState = g_HandState;
		Rot tempRot = g_CubeRot;
		UpdateHandAndCubeRot(R1 + g_RotDistance - 1);
		//打印此解
		cout << "\"";
		cout << " step: " << (step + 1) / 10 << (step + 1) % 10;
		cout << " hand: " << g_HandState.LeftNotNice << g_HandState.RightNotNice;
		cout << " rot: ";
		for (int j = 0; j < 3; j++)  //列
		{
			for (int i = 0; i < 3; i++)  //行
			{
				if (g_CubeRot.a[i][j] == 1)
				{
					cout << i << "," << " 1," << "  ";
					break;
				}
				else if (g_CubeRot.a[i][j] == -1)
				{
					cout << i << "," << "-1," << "  ";
					break;
				}
			}
		}
		cout << "  ";
		for (int i = 0; i < step; i++)
		{
			cout << moveStr[g_buff[i]] << ", ";
		}
		cout << "M_R" << g_RotDistance<<", M_END";
		cout << "\","<<endl;
		//恢复手臂与旋转状态
		g_HandState = tempHandState;
		g_CubeRot = tempRot;
		//g_SloveNum自增
		g_SloveNum++;
		//返回
		if (step != 0)return;
	}
	else if (step == g_SearchDepth)  //到达深度
	{
		return;
	}
	//不满足条件，进入下一层
	for (int i = L1; i <= RO; i++)
	{
		//异常判断
		//*俩个手抓同时打开
		if ((i == RO) && (g_HandState.IsLeftOpen == 1))continue;
		if ((i == LO) && (g_HandState.IsRightOpen == 1))continue;
		//*两个手爪同时在1位置
		//if (((i == R1) || (i == R2) || (i == R3)) && (g_HandState.LeftNotNice == 1))continue;
		//if (((i == L1) || (i == L2) || (i == L3)) && (g_HandState.RightNotNice == 1))continue;

		if (step > 0)
		{
			//*上一步为打开或者关闭某手爪，而这一步为打开或者关闭此手爪
			if (((g_buff[step - 1] == RO) || (g_buff[step - 1] == RC)) && ((i == RC) || (i == RO)))continue;
			if (((g_buff[step - 1] == LO) || (g_buff[step - 1] == LC)) && ((i == LC) || (i == LO)))continue;
			//*
			//*上一步为拧动某手爪，这一步也是拧动此手爪
			if (((g_buff[step - 1] == R1) || (g_buff[step - 1] == R2) || (g_buff[step - 1] == R3))
				&& ((i == R1) || (i == R2) || (i == R3)))continue;

			if (((g_buff[step - 1] == L1) || (g_buff[step - 1] == L2) || (g_buff[step - 1] == L3))
				&& ((i == L1) || (i == L2) || (i == L3)))continue;
		}
		//*手爪同时闭合时拧动手爪
		if (((g_HandState.IsLeftOpen == 0) && (g_HandState.IsRightOpen == 0))
			&& ((i == R1) || (i == R2) || (i == R3) || (i == L1) || (i == L2) || (i == L3)))continue;
		//*手爪已经闭合时闭合手爪，手爪已经打开时候打开手爪
		if ((g_HandState.IsLeftOpen == 1) && (i == LO))continue;
		if ((g_HandState.IsLeftOpen == 0) && (i == LC))continue;
		if ((g_HandState.IsRightOpen == 1) && (i == RO))continue;
		if ((g_HandState.IsRightOpen == 0) && (i == RC))continue;

		//*执行当前操作后的状态曾经发生过
		HandState tempHandState = g_HandState;
		Rot tempRot = g_CubeRot;
		UpdateHandAndCubeRot(i);

		if (CaseHasHappened(step))
		{
			g_HandState = tempHandState;
			g_CubeRot = tempRot;
			continue;
		}

		//状态入栈
		g_buff[step] = i;
		g_HandStateList[step] = g_HandState;
		g_CubeRotList[step] = g_CubeRot;
		//进入下一层
		dfs(step + 1);
		//复原进入下一层之前的状态
		g_HandState = tempHandState;
		g_CubeRot = tempRot;
	}
}
//==========================================================旋转矩阵相关函数
Rot RotMtplRot(Rot l, Rot r)
{
	Rot temp;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			temp.a[i][j] = l.a[i][0] * r.a[0][j] + l.a[i][1] * r.a[1][j] + l.a[i][2] * r.a[2][j];
		}
	}
	return temp;
}
Point3 RotMtplPoint3(Rot l, Point3 r)
{
	Point3 temp;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			temp.a[i][j] = l.a[i][0] * r.a[0][j] + l.a[i][1] * r.a[1][j] + l.a[i][2] * r.a[2][j];
		}
	}
	return temp;
}
//x1 x2 x3 y1 y2 y3 z1 z2 z3
void RotInit(void)
{
	R_x1.a[0][0] = 1;
	R_x1.a[2][1] = -1;
	R_x1.a[1][2] = 1;
	R_x2 = RotMtplRot(R_x1, R_x1);
	R_x3 = RotMtplRot(R_x1, R_x2);

	R_y1.a[2][0] = 1;
	R_y1.a[1][1] = 1;
	R_y1.a[0][2] = -1;
	R_y2 = RotMtplRot(R_y1, R_y1);
	R_y3 = RotMtplRot(R_y1, R_y2);

	R_z1.a[1][0] = -1;
	R_z1.a[0][1] = 1;
	R_z1.a[2][2] = 1;
	R_z2 = RotMtplRot(R_z1, R_z1);
	R_z2 = RotMtplRot(R_z1, R_z2);

	R_org.a[0][0] = 1;
	R_org.a[1][1] = 1;
	R_org.a[2][2] = 1;
}
void PointInit(void)
{
	P_F.a[0][0] = 1;
	P_F.a[1][0] = 0;
	P_F.a[2][0] = 0;
	P_F.name = "F";

	P_R.a[0][0] = 0;
	P_R.a[1][0] = 1;
	P_R.a[2][0] = 0;
	P_R.name = "R";

	P_U.a[0][0] = 0;
	P_U.a[1][0] = 0;
	P_U.a[2][0] = 1;
	P_U.name = "U";

	P_B.a[0][0] = -1;
	P_B.a[1][0] = 0;
	P_B.a[2][0] = 0;
	P_B.name = "B";

	P_L.a[0][0] = 0;
	P_L.a[1][0] = -1;
	P_L.a[2][0] = 0;
	P_L.name = "L";

	P_D.a[0][0] = 0;
	P_D.a[1][0] = 0;
	P_D.a[2][0] = -1;
	P_D.name = "D";
}
//=========================================================更新手臂状态与立方体旋转矩阵
void UpdateHandAndCubeRot(int mov)
{
	//手臂状态
	//*手爪打开或者合上
	if (mov == LC)g_HandState.IsLeftOpen = 0;
	else if (mov == LO)g_HandState.IsLeftOpen = 1;
	else if (mov == RC)g_HandState.IsRightOpen = 0;
	else if (mov == RO)g_HandState.IsRightOpen = 1;
	//*手爪拧动
	else if (mov == L1)
	{
		//**是否nice
		if (g_HandState.LeftNotNice == 1)g_HandState.LeftNotNice = 0;
		else if (g_HandState.LeftNotNice == 0)g_HandState.LeftNotNice = 1;
		//**Right打开，立方体旋转
		if (g_HandState.IsRightOpen == 1)g_CubeRot = RotMtplRot(R_x1, g_CubeRot);
	}
	else if (mov == L2)
	{
		//**是否nice
		/*if (g_HandState.LeftNotNice == 1)g_HandState.LeftNotNice = 0;
		else if (g_HandState.LeftNotNice == 0)g_HandState.LeftNotNice = 1;*/
		//**Right打开，立方体旋转
		if (g_HandState.IsRightOpen == 1)g_CubeRot = RotMtplRot(R_x2, g_CubeRot);
	}
	else if (mov == L3)
	{
		//**是否nice
		if (g_HandState.LeftNotNice == 1)g_HandState.LeftNotNice = 0;
		else if (g_HandState.LeftNotNice == 0)g_HandState.LeftNotNice = 1;
		//**Right打开，立方体旋转
		if (g_HandState.IsRightOpen == 1)g_CubeRot = RotMtplRot(R_x3, g_CubeRot);
	}
	else if (mov == R1)
	{
		//**是否nice
		if (g_HandState.RightNotNice == 1)g_HandState.RightNotNice = 0;
		else if (g_HandState.RightNotNice == 0)g_HandState.RightNotNice = 1;
		//**Left打开，立方体旋转
		if (g_HandState.IsLeftOpen == 1)g_CubeRot = RotMtplRot(R_y1, g_CubeRot);
	}
	else if (mov == R2)
	{
		//**是否nice
		/*if (g_HandState.RightNotNice == 1)g_HandState.RightNotNice = 0;
		else if (g_HandState.RightNotNice == 0)g_HandState.RightNotNice = 1;*/
		//**Left打开，立方体旋转
		if (g_HandState.IsLeftOpen == 1)g_CubeRot = RotMtplRot(R_y2, g_CubeRot);
	}
	else if (mov == R3)
	{
		//**是否nice
		if (g_HandState.RightNotNice == 1)g_HandState.RightNotNice = 0;
		else if (g_HandState.RightNotNice == 0)g_HandState.RightNotNice = 1;
		//**Left打开，立方体旋转
		if (g_HandState.IsLeftOpen == 1)g_CubeRot = RotMtplRot(R_y3, g_CubeRot);
	}
}
//========================================================判断case是否重复
bool CaseHasHappened(int step)
{
	if (step == 0)return false;  //第一层搜索,不可能重复
	else
	{
		for (int i = 0; i < step; i++)
		{
			//若有任何不一样，continue
			if (g_HandStateList[i].IsLeftOpen != g_HandState.IsLeftOpen)continue;
			if (g_HandStateList[i].IsRightOpen != g_HandState.IsRightOpen)continue;
			if (g_HandStateList[i].LeftNotNice != g_HandState.LeftNotNice)continue;
			if (g_HandStateList[i].RightNotNice != g_HandState.RightNotNice)continue;

			//执行到此处说明gHandleState是一样的
			bool IsSame = true; //若有任何不一样，置为false
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					if (g_CubeRot.a[j][k] != g_CubeRotList[step].a[j][k]) IsSame = false;
				}
			}
			if (IsSame) return true;
			else continue;
		}
	}
	return false;
}