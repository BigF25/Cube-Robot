// dvrssw.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "dvrssw.h"
#include "VideoStreamShow.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CdvrsswApp

BEGIN_MESSAGE_MAP(CdvrsswApp, CWinApp)
END_MESSAGE_MAP()
//----------------------------------------------------
Video_Parame g_VideoSystemParamter;
CVideoStreamShow m_VideoStream;
//--------------------------------------------------
// CdvrsswApp ����

CdvrsswApp::CdvrsswApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CdvrsswApp ����

CdvrsswApp theApp;


// CdvrsswApp ��ʼ��

BOOL CdvrsswApp::InitInstance()
{
	CWinApp::InitInstance();
	Set_Default_Config_Setting();
	return TRUE;
}
//--------------
void WINAPI DebugString(LPCSTR format, ...)
{
va_list arglist;
char buffer[1024];
va_start (arglist,format);
vsprintf(buffer, format, arglist);
va_end (arglist);
char buffer2[1024];
COleDateTime datetime = COleDateTime::GetCurrentTime();
sprintf(buffer2,"[MVServ:%s]-%s ",datetime.Format((_T("%Y-%m-%d %H:%M:%S"))),buffer);
OutputDebugString (buffer2);
#if 0
FILE *fp;
fp = fopen("MVLOG.txt","ab+");
if(fp != NULL)
{
	fwrite((void*)&buffer2,strlen(buffer2),1,fp);
}
fclose(fp);
#endif 
}
//------------------------------------------------
void Set_Default_Config_Setting(void)
{

	for(int i = 0;i<MAX_VIDEO_CHANNEL;i++)
	{
		
		g_VideoSystemParamter.m_Video_Format_size[i]=3;
		g_VideoSystemParamter.m_Video_Stand_mode[i]=0;
		g_VideoSystemParamter.m_FrameRatePos[i]=25;
		g_VideoSystemParamter.m_Video_Full_Size[i] = 0;
		g_VideoSystemParamter.m_VideoQualityLev[i] =0;
		g_VideoSystemParamter.m_VideoDeinterlaceEn[i] = 0;
		g_VideoSystemParamter.m_bSupportFullFrameRec[i] =0;
		g_VideoSystemParamter.m_RecFrameRatePos[i] = 12;
	}
}
//--export funtion
DVRSSW_API  int   __stdcall InitDVRS(void)
{
	
	m_VideoStream.m_Current = 0;
	int nRet = m_VideoStream.VideoSystemInit();
	return nRet;
}
DVRSSW_API  int   __stdcall ExitDVRS(void)
{
	m_VideoStream.VideoSystemExit();
	return 0;
}
DVRSSW_API  int __stdcall OpenVideoPreview(int hChannel,HWND WndHandle, RECT *rect)
{
		int ret = 0;
		if(m_VideoStream.m_hDSP[hChannel]!= (HANDLE) 0xffffffff)
		{
			
			StartVideoPreview(m_VideoStream.m_hDSP[hChannel],WndHandle,rect,false,0,0);
			
		}
		else
		{
			ret = -1;
		}
	return ret;
}

DVRSSW_API  int __stdcall SaveCaptureImage(int index,char *path)
{

	return(m_VideoStream.CaptureImage(index,path));
}
DVRSSW_API  void  __stdcall SaveOneCaptureVideo(int index,char *dirstr)
{
	m_VideoStream.StartSaveOneCapture(index,dirstr);
}
DVRSSW_API  void  __stdcall StopOneCaptureVideo(int index)
{
	m_VideoStream.StopSaveFile(index);
}
DVRSSW_API  int  __stdcall GetSysTotalChannels(void)
{
	return(m_VideoStream.m_TotalChannel);
}

DVRSSW_API   int __stdcall SetChangeVideoSize(int hChannel,int sizeindex)
{
	m_VideoStream.SetChangeVideoSize(hChannel,sizeindex);
	return 0;
}
DVRSSW_API   int __stdcall SetVideoCHName(int hChannel,char* namestr)
{
	m_VideoStream.SetOSD(hChannel,namestr);
	return 0;
}
DVRSSW_API  int __stdcall SetColorParameter(int hChannel,int br,int co,int sa,int hu)
{
	m_VideoStream.SetColorParameter( hChannel, br, co, sa, hu);
	return 0;
}