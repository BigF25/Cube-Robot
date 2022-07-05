// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE ��
#include <afxodlgs.h>       // MFC OLE �Ի�����
#include <afxdisp.h>        // MFC �Զ�����
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC ���ݿ���
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO ���ݿ���
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT
//----------------------------------------------------------------
#include <Winsvc.h>
#include <setupapi.h>
#include <afxmt.h>
#pragma comment(lib, "setupapi.lib")

#include <MMSystem.h>
#pragma comment(lib, "Winmm.lib")
#include "Afxsock.h"
#include "../../api/datatype.h"
#include "../../api/dvrshw.h"
#include "../../api/dvrsswlib.h"
#pragma comment(lib, "Dvrshw.lib")
#pragma comment(lib, "JpegLib.lib")
#include <vfw.h>
#pragma comment(lib, "Vfw32.lib")
void WINAPI DebugString(LPCSTR format, ...);
CString GetLocalString(int ID);
void Get_Application_path();
BOOL IsFileExist(CString csFile);
#define MAX_VIDEO_CHANNEL 64

#define MAX_SHARE_MEM_CNT 1
#define MAX_ST_BUF_SIZE 2*1920*1080
#define MEM_SHARE_FILE_SIZE MAX_SHARE_MEM_CNT*MAX_ST_BUF_SIZE
#define SHARE_MEM_NAME "MVShareMem"

#define   WM_NOTIFYICON   WM_USER+100
#define WM_POWER_ON_SET_CLICK      WM_USER+306
#define WM_MYHOTKEY1 WM_USER+1000 
#define WM_MYHOTKEY2 WM_USER+1001 

#define WM_VIEW_CLICK      WM_USER+102
#define WM_VIEW_DBCLICK      WM_USER+101
#define TIMER_MAIN    WM_USER+104


typedef struct STRAM_VIDEO_STATUS_INFO
{
	DWORD		byLock;
	DWORD		byChannel;
	DWORD       dwWidth; 
	DWORD       dwHeight;
}ST_STATUS_INFO, *PST_STATUS_INFO;
typedef struct STRAM_VIDEO_BUF_INFO
{
	LPBYTE		mPdatabuffer;
	PST_STATUS_INFO mPVStatus;
}STRAM_VIDEO_BUF_INFO, *PSTRAM_VIDEO_BUF_INFO;



typedef struct {
	//-------------------
	int m_VideoQualityLev[MAX_VIDEO_CHANNEL];
	int m_Video_Format_size[MAX_VIDEO_CHANNEL];
	int m_Video_Stand_mode[MAX_VIDEO_CHANNEL];
	int m_FrameRatePos[MAX_VIDEO_CHANNEL];
	int m_Video_Full_Size[MAX_VIDEO_CHANNEL];
	int m_VideoDeinterlaceEn[MAX_VIDEO_CHANNEL];
	int m_VideoRecQA[MAX_VIDEO_CHANNEL];
	int m_Slider_BR[MAX_VIDEO_CHANNEL];
	int m_Slider_CO[MAX_VIDEO_CHANNEL];
	int m_Slider_SA[MAX_VIDEO_CHANNEL];
	int m_Slider_HU[MAX_VIDEO_CHANNEL];
	int m_Slider_SH[MAX_VIDEO_CHANNEL];
	int m_bSupportFullFrameRec[MAX_VIDEO_CHANNEL];
	int m_RecFrameRatePos[MAX_VIDEO_CHANNEL];

}Video_Parame;

typedef enum {

		INPUT_OPEN_ASCII,	
		INPUT_OPEN_BINARY

}input_mode_t;

typedef enum {

		INPUT_SEEK_SET,
		INPUT_SEEK_CUR,
		INPUT_SEEK_END

} input_seek_t;

typedef enum {

		INPUT_CREATE_READ,
		INPUT_CREATE_WRITE,
		INPUT_CREATE_READ_WRITE

} input_creat_mode_t;
 #ifndef   _UNICODE   
#define   __stprintf         sprintf
#define   __tprintf          fprintf
#define   __vsnwprintf       _vsnprintf  
#define   __fopen            fopen  
#else   
#define   __stprintf       wsprintf  
#define   __tprintf        fwprintf 
#define   __vsnwprintf        _vsnwprintf
#define   __fopen           _wfopen
#endif

//----------------------------------------------------------------------