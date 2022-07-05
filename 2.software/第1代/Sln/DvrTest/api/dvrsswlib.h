#ifndef _DVRSSW_LIB_H_
#define _DVRSSW_LIB_H_

#define DVRSSW_API __declspec(dllexport)
#ifdef __cplusplus
extern "C"
{
# endif 
	DVRSSW_API  int   __stdcall InitDVRS(void);
	DVRSSW_API  int   __stdcall ExitDVRS(void);
	DVRSSW_API  int __stdcall OpenVideoPreview(int hChannel,HWND WndHandle, RECT *rect);
	DVRSSW_API  int __stdcall SaveCaptureImage(int index,char *path);
	DVRSSW_API  void  __stdcall SaveOneCaptureVideo(int index,char *dirstr);
	DVRSSW_API  void  __stdcall StopOneCaptureVideo(int index);
	DVRSSW_API  int  __stdcall  GetSysTotalChannels(void);
	DVRSSW_API  int __stdcall SetChangeVideoSize(int hChannel,int sizeindex);
	DVRSSW_API  int __stdcall SetVideoCHName(int hChannel,char* namestr);
	DVRSSW_API  int __stdcall SetColorParameter(int hChannel,int br,int co,int sa,int hu);
# ifdef __cplusplus
}
# endif

#endif 