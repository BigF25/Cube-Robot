#ifndef _DMOTION_ANAY_SDK_H_
#define _DMOTION_ANAY_SDK_H_
#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展
#define DMOTION_API __declspec(dllexport)
#ifdef __cplusplus
extern "C"
{
# endif 
	DMOTION_API void  __stdcall SetcvVideoStitcher(BYTE *buf1,BYTE *buf2,BYTE*buf3,int w,int h);
	DMOTION_API void  __stdcall SetcvVideoStitcherHWND(HWND hwnd, RECT *rect);
	DMOTION_API  int   __stdcall SetcvVideoMotion(int index ,BYTE *YUVBuffer,int width,int height);
	DMOTION_API  void  __stdcall SetcvVideoHWND(int index ,HWND hwnd, RECT *rect);
	DMOTION_API void  __stdcall SetcvSearchRect(CRect rc,int index,int x0,int x1,int y0,int y1);
	DMOTION_API void  __stdcall SetcvMotionSelectMenuIndex(int index,int menuindex);
	DMOTION_API void  __stdcall SetcvSearchArea(int index,int x0,int x1,int y0,int y1);
	DMOTION_API void  __stdcall SetcvMinTargetArea(int index,int x0,int x1,int y0,int y1);
	DMOTION_API void  __stdcall GetcvSearchArea(int index,int* x0,int* x1,int* y0,int* y1);
	DMOTION_API void  __stdcall GetcvMinTargetArea(int index,int* x0,int* x1,int* y0,int* y1);
	DMOTION_API void  __stdcall ReleasecvImageBuffer();

# ifdef __cplusplus
}
# endif

#endif 