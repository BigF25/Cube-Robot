// malib.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "malib.h"
#include "..\api\Motionlib.h"
#include "VideoMotion.h"
#include "VideoStitcher.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVideoMotion g_VideoMotion[MAX_VIDEO_CHANNEL];
CVideoStitcher g_VideoStitcher;
BEGIN_MESSAGE_MAP(CmalibApp, CWinApp)
END_MESSAGE_MAP()


// CmalibApp 构造

CmalibApp::CmalibApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CmalibApp 对象

CmalibApp theApp;


// CmalibApp 初始化

BOOL CmalibApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
DMOTION_API  int   __stdcall SetcvVideoMotion(int index ,BYTE *YUVBuffer,int width,int height)
{
	int ret ;
	//g_VideoMotionCritical[index].Lock();
	ret = g_VideoMotion[index].SetVideoMotion(YUVBuffer,width,height);
	//g_VideoMotionCritical[index].Unlock();
	return (ret);


}
DMOTION_API  void  __stdcall SetcvVideoHWND(int index ,HWND hwnd, RECT *rect)
{
	//g_VideoMotionCritical[index].Lock();
	g_VideoMotion[index].m_ndImageHandle = hwnd;
	if(rect != NULL)
	{
		g_VideoMotion[index].m_ImageRect = *rect;
	}
	//g_VideoMotionCritical[index].Unlock();
}

DMOTION_API void  __stdcall SetcvSearchRect(CRect rc, int index,int x0,int x1,int y0,int y1)
{
	//g_VideoMotionCritical[index].Lock();
	g_VideoMotion[index].SetcvSearchRect(rc,x0,x1,y0,y1);
	//g_VideoMotionCritical[index].Unlock();
}
DMOTION_API void  __stdcall SetcvMotionSelectMenuIndex(int index,int menuindex)
{
	//g_VideoMotionCritical[index].Lock();
	g_VideoMotion[index].SetMotionSelectMenuIndex(menuindex);
	//g_VideoMotionCritical[index].Unlock();
}
DMOTION_API void  __stdcall SetcvSearchArea(int index,int x0,int x1,int y0,int y1)
{
	//g_VideoMotionCritical[index].Lock();
	g_VideoMotion[index].SetcvSearchArea(x0,x1,y0,y1);
	//g_VideoMotionCritical[index].Unlock();
}
DMOTION_API void  __stdcall SetcvMinTargetArea(int index,int x0,int x1,int y0,int y1)
{
	//g_VideoMotionCritical[index].Lock();
	g_VideoMotion[index].SetcvMinTargetArea(x0,x1,y0,y1);
	//g_VideoMotionCritical[index].Unlock();
}
DMOTION_API void  __stdcall GetcvSearchArea(int index,int* x0,int* x1,int* y0,int* y1)
{
	//g_VideoMotionCritical[index].Lock();
	g_VideoMotion[index].GetcvSearchArea(x0,x1,y0,y1);
	//g_VideoMotionCritical[index].Unlock();
}
DMOTION_API void  __stdcall GetcvMinTargetArea(int index,int* x0,int* x1,int* y0,int* y1)
{
	//g_VideoMotionCritical[index].Lock();
	g_VideoMotion[index].GetcvMinTargetArea(x0,x1,y0,y1);
	//g_VideoMotionCritical[index].Unlock();
}

DMOTION_API void  __stdcall ReleasecvImageBuffer()
{
	
	for(int i=0; i <MAX_VIDEO_CHANNEL; i++)
	{
		//g_VideoMotionCritical[i].Lock();
		g_VideoMotion[i].ReleasecvImage();
		//g_VideoMotionCritical[i].Unlock();
	
	}
}
DMOTION_API void  __stdcall SetcvVideoStitcher(BYTE *buf1,BYTE *buf2,BYTE*buf3,int w,int h)
{
	g_VideoStitcher.cvVideoStitcher(buf1,buf2,buf3,w,h);
}
DMOTION_API  void  __stdcall SetcvVideoStitcherHWND(HWND hwnd, RECT *rect)
{
	//g_VideoMotionCritical[index].Lock();
	g_VideoStitcher.m_ndImageHandle = hwnd;
	if(rect != NULL)
	{
		g_VideoStitcher.m_ImageRect = *rect;
	}
	//g_VideoMotionCritical[index].Unlock();
}
void ChangeYUVToRGB(BYTE *yuvdata,BYTE *rgbdata,int width,int height)
{

	
		BYTE *source = yuvdata+4;
		BYTE *dest1 = rgbdata;
		int i,j;
		double R, G, B, y1,u1,v1,y2,u2,v2;
		for (i=0; i<height; i++)
			{
				
				for (j=0; j<width/2; j++)
				{
					y1 = source[0];
					y2 = source[2];
					v1 = source[3]-128;
					v2 = source[3]-128;
					u1 = source[1]-128;
					u2 = source[1]-128;

					R =(double)(y1 + 1.375 * v1);
					G =(double)(y1 - 0.34375 * u1 - 0.703125 * v1);
					B =(double)(y1 + 1.734375 * u1);
					R = MAX (0, MIN (255, R));
					G = MAX (0, MIN (255, G));
					B = MAX (0, MIN (255, B));	

					dest1[0] = (BYTE)B;
					dest1[1] = (BYTE)G;
					dest1[2] = (BYTE)R;
					dest1+=3;
					R =(double)(y2 + 1.375 * v1);
					G =(double)(y2 - 0.34375 * u1 - 0.703125 * v1);
					B =(double)(y2 + 1.734375 * u1);
					R = MAX (0, MIN (255, R));
					G = MAX (0, MIN (255, G));
					B = MAX (0, MIN (255, B));

					dest1[0] = (BYTE)B;
					dest1[1] = (BYTE)G;
					dest1[2] = (BYTE)R;
					dest1+=3;
					source += 4;
				}

			}
}
