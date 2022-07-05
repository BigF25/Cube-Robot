////////////////////////////////////////////////////////////////////////////////
//DvrsCap.h
//////////////////////////////////////////////////////////////////////////////

#ifndef _DVRS_CAP_SDK_H_
#define _DVRS_CAP_SDK_H_

#include "datatype.h"

//预览窗口排列方式定义(主要是为overlay方式用)
typedef struct _PREVIEWRC
{
	int   sizeUnit;				//本窗口的大小倍数（以标准单位计）
	int   xUnit, yUnit;			//左上坐标位置（以标准单位计）
} stPreviewRC,*pstPreviewRC; 
typedef struct _PREVIEWMODE
{
	int nPreviewCount;			//窗口总数
	int hUnit, vUnit;			//x,y方向上的标准单位数目
	int nWidth, nHeight;		//标准预览的宽和高(overlay)
	int maxWidth, maxHeight;	//最大预览的宽和高(offscreen)
	stPreviewRC* nPreviewPos;	//预览排列的大小及位置信息数组指针(至少包含窗口总数个)
} stPreviewMode,*pstPreviewMode;

#ifndef  DVRS_CAP_EXPORT
#define DVRS_API __declspec(dllexport)
#endif DVRS_CAP_EXPORT



#define ERR_NONE							0
#define ERR_CHANNEL							0xc0000001

# ifdef __cplusplus
extern "C"
{
# endif 



typedef void (*DRAWFUN_CALLBACK)(long nPort,HDC hDc,LONG nUser,DWORD dwReserved);
typedef void (*LOGRECORD_CALLBACK)(char *str, void *context);
typedef int (*STREAM_READ_CALLBACK)(ULONG channelNumber,void *DataBuf,int FrameType,int width,int height,void *context);
typedef int (*VIDEO_STATUS_CALLBACK)(ULONG channelNumber,BOOL bStatus, void *context);
typedef int (*STREAM_DIRECT_READ_CALLBACK)(ULONG channelNumber,void *DataBuf,DWORD Length,int FrameType,void *context);
typedef int (*RAWSTREAM_DIRECT_READ_CALLBACK)(ULONG channelNumber,void *DataBuf,int FrameType,int width,int height,void *context);
DVRS_API  int __stdcall Test(HANDLE hChannel);

DVRS_API  int __stdcall InitDSPs();
DVRS_API  int __stdcall DeInitDSPs();
DVRS_API  HANDLE __stdcall ChannelOpen(int nChannel);
DVRS_API  int __stdcall ChannelClose(HANDLE hChannel);
DVRS_API  int __stdcall GetTotalChannels();
DVRS_API  int __stdcall GetTotalDSPs();
DVRS_API  int __stdcall StopAllDSPs();
DVRS_API  int __stdcall ReStartAllDSPs();
DVRS_API  int __stdcall StartDsp(HANDLE hChannel);
DVRS_API  int __stdcall StopDsp(HANDLE hChannel);

//////////////////////////////////////////////
// preview 
////////////////////////////////////////////////////////
DVRS_API  int __stdcall SetPreviewOverlayMode(BOOL bTrue);
DVRS_API  int __stdcall StartVideoPreview(HANDLE hChannel,HWND WndHandle, RECT *rect, BOOL bOverlay, int VideoFormat, int FrameRate);
DVRS_API  int __stdcall StopVideoPreview(HANDLE hChannel);
DVRS_API  int __stdcall SetOverlayColorKey(COLORREF DestColorKey);



DVRS_API  int __stdcall SetVideoPara(HANDLE hChannel, int Brightness, int Contrast, int Saturation, int Hue);
DVRS_API  int __stdcall GetVideoPara(HANDLE hChannel, VideoStandard_t *VideoStandard, int *Brightness, int *Contrast, int *Saturation, int *Hue);
DVRS_API  int __stdcall GetVideoSignal(HANDLE  hChannel);
DVRS_API  int __stdcall SetEncoderPictureFormat(HANDLE hChannel, PictureFormat_t PictureFormat);
DVRS_API  int __stdcall SetVideoStandard(HANDLE hChannel, VideoStandard_t VideoStandard);
DVRS_API  int __stdcall StartVideoCapture(HANDLE hChannel);
DVRS_API  int __stdcall StopVideoCapture(HANDLE hChannel);
DVRS_API  int __stdcall ConfigSubChannelSplit( int nMaxSubCh, int nMode=0 );
DVRS_API  int __stdcall SetStreamType(HANDLE hChannel, USHORT Type);
DVRS_API  int __stdcall GetStreamType(HANDLE hChannel, USHORT *StreamType);


DVRS_API  int __stdcall GetBoardInfo(HANDLE hChannel, ULONG *BoardType, UCHAR *SerialNo);

DVRS_API  int __stdcall RegisterLogRecordCallback(LOGRECORD_CALLBACK LogRecordFunc, void *Context);
DVRS_API  int __stdcall ReadStreamData(HANDLE hChannel, void *DataBuf, DWORD *Length, int *FrameType);
DVRS_API  int __stdcall RegisterMessageNotifyHandle(HWND hWnd, UINT MessageId);
DVRS_API  int __stdcall RegisterStreamReadCallback(STREAM_READ_CALLBACK StreamReadCallback, void *Context);
DVRS_API  int __stdcall RegisterStreamDirectReadCallback(STREAM_DIRECT_READ_CALLBACK StreamDirectReadCallback, void* Context);
DVRS_API  int __stdcall RegisterSubStreamDirectReadCallback(STREAM_DIRECT_READ_CALLBACK StreamDirectReadCallback, void* Context);
DVRS_API  int __stdcall RegisterSubQCIFStreamDirectReadCallback(STREAM_DIRECT_READ_CALLBACK StreamDirectReadCallback, void* Context);
DVRS_API  int __stdcall CaptureIFrame(HANDLE hChannel);
DVRS_API  int __stdcall SetEncoderPictureFormat(HANDLE hChannel, PictureFormat_t PictureFormat);
//----RAW  DATA ---- 
DVRS_API  int __stdcall RegisterRAWStreamDirectCallback(RAWSTREAM_DIRECT_READ_CALLBACK RawStreamDirectReadCallback, void* Context);
///////////////////////////
//  capture 
//////////////////
DVRS_API  int __stdcall GetOriginalImage(HANDLE hChannel, UCHAR *ImageBuf, ULONG *Size);
DVRS_API  int __stdcall LoadYUVFromBmpFile(TCHAR *FileName, unsigned char *yuv, int BufLen, int *Width, int *Height);
DVRS_API  int __stdcall SaveYUVToBmpFile(TCHAR *FileName, unsigned char *yuv, int Width, int Height);


////////////////////////////////
//Osd
/////////////////////////////////////
DVRS_API  int __stdcall SetOsd(HANDLE hChannel, BOOL Enable);
DVRS_API  int __stdcall SetOsdDisplayMode(HANDLE hChannel, int Brightness, BOOL Translucent, int TwinkleInterval, USHORT *Format1, USHORT *Format2);
DVRS_API  int __stdcall SetLogoDisplayMode(HANDLE hChannel, COLORREF ColorKey, BOOL Translucent, int TwinkleInterval);
DVRS_API  int __stdcall SetLogo(HANDLE hChannel, int x, int y, int w, int h, unsigned char *yuv);
DVRS_API  int __stdcall StopLogo(HANDLE hChannel);
///////////////////////////////////////
//
//////////////////////////////////


///////////////////////////////////////////////////////////////////////
//motion
/////////////////////////////////////////////////////////////////////
DVRS_API  int __stdcall StartMotionDetection(HANDLE hChannel);
DVRS_API  int __stdcall AdjustMotionDetectPrecision( HANDLE hChannel, 
										   int iGrade, int iFastMotionDetectFps, 
										   int iSlowMotionDetectFps);
DVRS_API  int __stdcall SetupMotionDetection(HANDLE hChannel, RECT *RectList, int iAreas);
DVRS_API  int __stdcall MotionAnalyzer(HANDLE hChannel, char *MotionData, int iThreshold, int *iResult);
DVRS_API  int __stdcall StopMotionDetection(HANDLE hChannel);



DVRS_API  int __stdcall SetVideoFrameRate(HANDLE hChannel, int nFrameRate);

//////////////////////////////
//Audio
//////////////////////////////
DVRS_API  int __stdcall SetAudioPreview(HANDLE hChannel, BOOL bEnable);
DVRS_API int __stdcall  UpdateVideoPreview();


DVRS_API int __stdcall SetDefaultDisplayPicture(HANDLE hChannel, TCHAR *pFileName);
DVRS_API int __stdcall SetupMask(HANDLE hChannel, RECT *rectList, int iAreas);
DVRS_API int __stdcall StopMask(HANDLE hChannel);

DVRS_API int __stdcall SetBitrateControlMode(HANDLE hChannel, BitrateControlType_t brc);
DVRS_API int __stdcall SetIBPMode(HANDLE hChannel, int KeyFrameIntervals, int BFrames, int PFrames, int FrameRate);
DVRS_API int __stdcall SetupBitrateControl(HANDLE hChannel, ULONG MaxBps);
DVRS_API int __stdcall SetDefaultQuant(HANDLE hChannel, int IQuantVal, int PQuantVal, int BQuantVal);
DVRS_API int __stdcall SetVideoSharp(HANDLE hChannel, int nLevel);//8 Level: 0~7
DVRS_API int __stdcall SetAudioVolume(HANDLE hChannel,int nVolume);  //range: 0(min)~100(max)
DVRS_API int __stdcall AdjustForLargeChannles();
DVRS_API int __stdcall SetPreviewOsdMode(BOOL bOsdMode);
DVRS_API int __stdcall GetBoardInfoEx(HANDLE hChannel, ULONG *BoardType, UCHAR *buffer );
DVRS_API int __stdcall GetSystemBoardInfo(SYSTEM_BOARD_INFO* pBoardInfo);
DVRS_API int __stdcall SetDefaultDisplayLanguage(HANDLE hChannel, int nLanguage);
DVRS_API int __stdcall LowLevelVideoPreview(int offset=1);
DVRS_API int __stdcall UpdateVideoPreviewEx(int nCount,int index=0);
DVRS_API int __stdcall GetVideoPreviewModeInfo(int nCount,stPreviewMode* pModeInfo);
DVRS_API int __stdcall AddVideoPreviewModeInfo(stPreviewMode* pModeInfo);
DVRS_API int __stdcall SetVideoPreviewIndex(HANDLE hChannel,int nIndex);
DVRS_API int __stdcall RegisterDrawFun(DWORD nport, DRAWFUN_CALLBACK drawfun,LONG nUser);
DVRS_API int __stdcall ConfigVideoEncode( int nMode, int nIntensity );
DVRS_API int __stdcall ConfigAutoAdjust( int nEnable, int nMinCpu, int nMaxCpu );
DVRS_API int __stdcall ConfigDvrLevel( int nLevel );
DVRS_API int __stdcall ForceVideoFormat( int nForce );

DVRS_API int __stdcall GetCurrentVideoFormat(HANDLE hChannel,
												 PictureFormat_t* pPictureFormat,
												 VideoStandard_t* pVideoStandard=NULL,
												 int* pWidth=NULL, int* pHight=NULL );
DVRS_API int __stdcall CryptoDogCheck(HANDLE hChannel,BYTE* buffer);
DVRS_API int __stdcall CryptoDogConfig(HANDLE hChannel,DWORD dwReadPassword,DWORD dwWritePassword,BYTE* Ci,BYTE* Sk,BYTE* Gc);
DVRS_API int __stdcall CryptoDogAccess(HANDLE hChannel,BOOL bWrite,int nAddress,int nNumber,BYTE* buffer);
DVRS_API int __stdcall CryptoDogCheckEx(HANDLE hChannel, BYTE* buffer, DWORD dwID, BYTE* Data, DWORD* pdwLength );
DVRS_API int __stdcall SetImageStream(HANDLE hChannel,BOOL bStart,UINT fps,UINT width,UINT height,unsigned char**imageBuffer,bool bVideoIn=false);
DVRS_API int __stdcall StartVideoOutput(int iBoardNo,int chIndex);
DVRS_API int __stdcall GpioInit(int iBoardNo,DWORD dwData);
DVRS_API int __stdcall GpioSetData(int iBoardNo,DWORD dwData);
DVRS_API int __stdcall GpioGetData(int iBoardNo,DWORD* pdwData);


DVRS_API int __stdcall SetVideoChangeProperty(HANDLE hChannel);
DVRS_API int __stdcall ReadReg(HANDLE hChannel,PDRV_RW pRW);
DVRS_API int __stdcall WriteReg(HANDLE hChannel,DRV_RW rw);
DVRS_API int __stdcall RegisterDrawFun(DWORD nport, DRAWFUN_CALLBACK DrawFun,LONG nUser);

DVRS_API  int __stdcall GetBoardData(HANDLE hChannel, BYTE* buffer,int nSize);
DVRS_API  int __stdcall GetBoardDataEx(HANDLE hChannel, BYTE* buffer,int nSize);
DVRS_API  int __stdcall SetOsdColor(HANDLE hChannel, 	COLORREF timecolor,COLORREF titlecolor);
DVRS_API  int __stdcall SetPreview(HANDLE hChannel, 	BOOL bPreview);
DVRS_API  int __stdcall GBI2CWrite(HANDLE hChannel, 	DWORD addr,DWORD value);

DVRS_API  int __stdcall StopDMA(HANDLE hChannel);
DVRS_API  int __stdcall StartDMA(HANDLE hChannel);
DVRS_API  int __stdcall ReStartDsp(HANDLE hChannel);

DVRS_API  int __stdcall WriteZone(HANDLE hChannel,unsigned char wr_zone,unsigned char wr_addr,unsigned char wr_number,unsigned char *pData);
DVRS_API  void* __stdcall ReadZone(HANDLE hChannel,unsigned char rd_zone, DWORD rd_addr, unsigned char rd_number);
DVRS_API  int  __stdcall GetSysDeviceID(HANDLE hChannel);
DVRS_API  int __stdcall ReInit_Video_Derive(HANDLE hChannel);
DVRS_API  int __stdcall GetInit_Video_Status(HANDLE hChannel);
DVRS_API  int __stdcall SetInit_Video_Status(HANDLE hChannel,int status);
DVRS_API  int __stdcall Change_Video_OVSW(HANDLE hChannel,int status);
DVRS_API  int __stdcall Get_DSP_TotalChnnel(HANDLE hChannel);
DVRS_API  BOOL __stdcall ReOpen_USB_Device(HANDLE hChannel);

DVRS_API  int __stdcall RegisterVideoStatusCallback(VIDEO_STATUS_CALLBACK VideoStatusCallback, void *Context);
DVRS_API  int __stdcall Set_Main_Enable(HANDLE hChannel,int status);
DVRS_API  int __stdcall Set_Sub_Enable(HANDLE hChannel,int status);
DVRS_API  int __stdcall Set_Sub_QCIF_Enable(HANDLE hChannel,int status);
DVRS_API int __stdcall SetRecoderFrameRate(HANDLE hChannel, int nFrameRate);
DVRS_API  int __stdcall Set_Sys_PowerDown(HANDLE hChannel,BOOL bEn);
DVRS_API  int __stdcall SetDisplayCard_Mode(int mode);
DVRS_API  int __stdcall Set_DeInterlace_Enable(HANDLE hChannel,int status);
DVRS_API  int __stdcall Set_Video_Quality_Level(HANDLE hChannel,int lv);
DVRS_API int __stdcall SetOem_Version(HANDLE hChannel,int oemcode);
DVRS_API  int __stdcall Set_FullSizeRecoder_Enable(HANDLE hChannel,int status);
DVRS_API  int __stdcall SetVideoRecQA(HANDLE hChannel,int QA);
DVRS_API  int __stdcall SYS_EE_UA_SIZE(HANDLE hChannel);
DVRS_API int __stdcall SYS_EE_UA_READ(HANDLE hChannel,BYTE *data,int len);
DVRS_API int __stdcall SYS_EE_UA_WRITE(HANDLE hChannel,BYTE *data,int len);
DVRS_API int __stdcall GetHardWare_Version(HANDLE hChannel);
# ifdef __cplusplus
}
# endif
#endif