#pragma once
#include "AviFileObj.h"
typedef struct _BMP_CFIO_
{
	FILE *fp;
	int output_width;
	int output_height;
	int density_unit;
	int X_density;
	int Y_density;
}bmp_info;
class CVideoStreamShow
{
public:
	void RawStreamReadCallBack(ULONG i,void *DataBuf,int FrameType,int width,int height);
	int VideoSystemInit();
	int  Video_Board_Init();
	void Video_Board_SetParameter();
	void SetParameter(int nChannel);
	void SetDefaultParameter(int index);
	void Video_Board_preview();
	void SetOSD(int nChannel,char  *ch_name);
	int  VideoSystemExit();
	void SetStartVideoPreview(int index,HWND hwnd,RECT *rect);
	void StartSaveAllCapture();
	void StopSaveAllCapture();
	void StopSaveFile(int nChannel);
	void StartSaveOneCapture(int index,char *dirstr);
	void StartSaveFile(COleDateTime StartDate,int nChannel, TCHAR *pFileName, DWORD nFrameRate, int nWidth, int nHeight);
	void StreamDirectRead(ULONG i, void *DataBuf, DWORD Length, int FrameType);
	int CaptureImage(int index,char *path);
	void StartAudioPreview(int index);
	void StopAudioPreview(int index) ;
	int  ConvertYUVToJpgFile(char *pszFile, BYTE *pSource);
	void SetChangeVideoSize(int hChannel,int sizeindex);
	void SetColorParameter(int hChannel, int br,int co,int sa,int hu);
	void write_bmp_header (bmp_info *cinfo,  char * pDataBuffer);
	int m_delayTimer;
	//-----------------------
	HANDLE m_hDSP[MAX_VIDEO_CHANNEL];
	int m_TotalDSPs;
	int m_TotalChannel;
	int m_Current;
	int m_OemVersion;
	int m_system_version;
	int m_ShowIndex[MAX_VIDEO_CHANNEL];
	BOOL m_bCanWriteFile[MAX_VIDEO_CHANNEL];
	BOOL m_bRecord[MAX_VIDEO_CHANNEL];
	CAviFileObj *m_pAviFile[MAX_VIDEO_CHANNEL];
	unsigned long lBitRateValue;
	int     m_Video_FrameRate[MAX_VIDEO_CHANNEL];
	CVideoStreamShow(void);
	~CVideoStreamShow(void);
};

