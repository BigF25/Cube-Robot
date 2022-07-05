#include "StdAfx.h"
#include "VideoStreamShow.h"
#include "JpegFile.h"
extern Video_Parame g_VideoSystemParamter;
CCriticalSection g_ChangeVideoIndeCritial;
extern TCHAR g_App_path[MAX_PATH];
int RawStreamDirectReadCallback(ULONG i,void *DataBuf,int FrameType,int width,int height,void *Context)
{

	CVideoStreamShow *dlg = (CVideoStreamShow *)Context;
	if(dlg)
	{
		dlg->RawStreamReadCallBack(i,DataBuf,FrameType,width,height);
	}
	return 0;
}
int StreamDirectReadCallback(ULONG i,void *DataBuf,DWORD Length,int FrameType,void *context)
{
	CVideoStreamShow *dlg = (CVideoStreamShow *)context;
	if(dlg)
	{
		dlg->StreamDirectRead(i,DataBuf,Length,FrameType);	
	}
	
	return 0;
}
void CVideoStreamShow::StreamDirectRead(ULONG i, void *DataBuf, DWORD Length, int FrameType)
{
	
	
	if(FrameType == PktIFrames && !m_bCanWriteFile[i] && m_pAviFile[i]&&m_bRecord[i])
	{
		m_bCanWriteFile[i] = 1;
	}
	if(m_bCanWriteFile[i])
	{
		if(m_bRecord[i])
		{
			
			if(FrameType ==PktIFrames || FrameType ==PktPFrames ||FrameType ==PktBBPFrames)
			{
				if(m_pAviFile[i])
				{
//				TRACE(_T("FrameType %d  Length %d\n"),FrameType,Length);
				m_pAviFile[i]->WriteVideo((BYTE*)DataBuf,Length,FrameType==PktIFrames?1:0,false);
				}
			
			   if(i ==0)
				lBitRateValue+=Length;
			
			}
			if(FrameType ==PktAudioFrames)
			{
				if(m_pAviFile[i] )
				{
				  DWORD dwResult=0;
				  m_pAviFile[i]->WriteAudio((BYTE*)DataBuf,Length,false,&dwResult);
				
				}
			}
		}
	}
	
	
	
}
CVideoStreamShow::CVideoStreamShow(void)
{
	m_TotalChannel = 0;
	m_TotalDSPs = 0;
	m_system_version = 0;
}


CVideoStreamShow::~CVideoStreamShow(void)
{
	VideoSystemExit();
}
void CVideoStreamShow::RawStreamReadCallBack(ULONG i,void *DataBuf,int FrameType,int width,int height)
{
	m_Video_FrameRate[i] ++;
}

int  CVideoStreamShow::VideoSystemInit()
{
	for(int i = 0;i<MAX_VIDEO_CHANNEL;i++)
	{
		m_hDSP[i] = (HANDLE) 0xffffffff;
		m_ShowIndex[i]= i;
		m_bCanWriteFile[i] = false;
		m_bRecord[i] = false;
		m_pAviFile[i] = NULL;
	}
	for(int i = 0;i<MAX_VIDEO_CHANNEL;i++)
	{
		m_Video_FrameRate[i] = 0;
	}
	ConfigSubChannelSplit(16,2);
	int ret = Video_Board_Init();
	return ret;
}

int  CVideoStreamShow::VideoSystemExit()
{
	int i;
	if(	m_TotalChannel<=0) return 0;
	if(m_TotalDSPs <=0) return 0;
	for( i = 0;i<m_TotalChannel;i++)
	{
		if(m_hDSP[i]!= (HANDLE) 0xffffffff)
		{
			StopVideoCapture(m_hDSP[i]);
			
		}
	}
	for( i = 0;i<m_TotalChannel;i++)
	{
		if(m_hDSP[i]!= (HANDLE) 0xffffffff)
		{
			StopDsp(m_hDSP[i]);		
		}
	}
	Sleep(1);
	for( i = 0;i<m_TotalChannel;i++)
	{
		if(m_hDSP[i]!= (HANDLE) 0xffffffff)
		{
			ChannelClose(m_hDSP[i]);	
		}
	}

	DeInitDSPs();	
	for( i = 0;i<m_TotalChannel;i++)
	{
		m_hDSP[i] = (HANDLE) 0xffffffff;
	}
	for( i = 0;i<MAX_VIDEO_CHANNEL;i++)
	{
		if(m_pAviFile[i])
		{
		  delete m_pAviFile[i];
		  m_pAviFile[i] = NULL;
		}
	}
	m_TotalChannel = 0;
	m_TotalDSPs = 0;
	return 0;
}
int  CVideoStreamShow::Video_Board_Init()
{
	// TODO: Add your control notification handler code here
	int i;
	//DebugString("Video_Board_Init[1]\n");
	m_TotalDSPs = InitDSPs();
	if(m_TotalDSPs ==0) 
	{
		DebugString("Video_Board_InitInitDSPs == g_TotalDSPs =0 [1]\n");
		return -3;
	}
	else if(m_TotalDSPs == -2)
	{
		return -2;
	}
	ConfigSubChannelSplit(16,2);
	m_TotalChannel = GetTotalChannels();
	if(m_TotalChannel ==0) 
	{
		DebugString("Video_Board_ GetTotalChannels  == g_TotalChannel =0 [1]\n");
		return -3;
	}
	if (m_TotalChannel>MAX_VIDEO_CHANNEL)
		m_TotalChannel=MAX_VIDEO_CHANNEL;
	
	for( i = 0;i<m_TotalChannel;i++)
	{
		m_hDSP[i] = ChannelOpen(i);
	}
	//---------------------------------
	m_Current =0;
	//---------------------------------
	for( i = 0;i<m_TotalChannel;i++)
	{
		if(m_hDSP[i]!= (HANDLE) 0xffffffff)
		{	
			RECT  rect;
			rect.bottom =0;
			rect.left = 0;
			rect.top = 0;
			rect.right =0;
			StartVideoPreview(m_hDSP[i],NULL,&rect,false,0,0);
			
		}
		
	}
	m_system_version = GetHardWare_Version(m_hDSP[0]);
	Video_Board_SetParameter();
	Video_Board_preview();
	RegisterRAWStreamDirectCallback(RawStreamDirectReadCallback,this);
	RegisterStreamDirectReadCallback(StreamDirectReadCallback,this);
	return 0;
}

void CVideoStreamShow::Video_Board_SetParameter()
{
	// TODO: Add your control notification handler code here
	//StopAllDSPs();
	for(int i = 0;i<m_TotalChannel;i++)
	{
		SetParameter(i);
	}
}

void CVideoStreamShow::SetParameter(int nChannel)
{
	BOOL m_Save_Capture;
	if(m_hDSP[nChannel]!= (HANDLE) 0xffffffff)
	{
	
		Set_DeInterlace_Enable(m_hDSP[nChannel],g_VideoSystemParamter.m_VideoDeinterlaceEn[nChannel]);
		Set_FullSizeRecoder_Enable(m_hDSP[nChannel],g_VideoSystemParamter.m_Video_Full_Size[nChannel]);
		
		switch(m_system_version)
		{
		case 5:
			case 6:
			case 7:
			case 8:
		    case 9:
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 42:
			case 15:
			case 17:
			case 20:
			case 22:
			case 23:
			case 24:
			case 26:
			case 28:
			case 29:
			case 30:
			case 31:
			case 34:
			case 35:
			case 40:
			case 41:
		default:
		{

		g_VideoSystemParamter.m_Slider_BR[nChannel]=20;
		g_VideoSystemParamter.m_Slider_CO[nChannel]=145;
		g_VideoSystemParamter.m_Slider_SA[nChannel]=118;
		g_VideoSystemParamter.m_Slider_HU[nChannel]=0x80;
		g_VideoSystemParamter.m_Slider_SH[nChannel]=4;
		break;
		}
		case 36:
		case 37:
		case 38:
		case 27:
		case 50:
		case 51:
		case 53:
		case 55:
		case 54:
		case 72:
		case 73:
		case 70:
		{
		//-------------support AHD 
		g_VideoSystemParamter.m_Slider_BR[nChannel]=0x08;
		g_VideoSystemParamter.m_Slider_CO[nChannel]=0x88;
		g_VideoSystemParamter.m_Slider_SA[nChannel]=0x5F;
		g_VideoSystemParamter.m_Slider_HU[nChannel]=0x00;
		
		break;

			}
	}
		int Size = g_VideoSystemParamter.m_Video_Format_size[nChannel];
		int standard = g_VideoSystemParamter.m_Video_Stand_mode[nChannel];
		if(standard == 0)
		{
			SetVideoStandard(m_hDSP[nChannel],StandardPAL);
			
		}
		else
		{
			SetVideoStandard(m_hDSP[nChannel],StandardNTSC);
			
		}
	switch(m_system_version)
	{
	case 36:
	case 37:
	case 38:
	case 27:
	case 50:
	case 51:
	case 54:
	case 72:
	case 73:
	case 70:
	{
		SetEncoderPictureFormat(m_hDSP[nChannel],(PictureFormat_t)Size);
		break;
	}
	case 53:
	case 55:
	{
		switch(Size)
		{
		case 0:
		default:
			SetEncoderPictureFormat(m_hDSP[nChannel],ENC_CIF_FORMAT);
			break;
		case 1:
			SetEncoderPictureFormat(m_hDSP[nChannel],ENC_2CIF_FORMAT);	
			break;
		}
		break;
	}
	default:
	{
		switch(Size)
		{
		case 0:
		default:
			SetEncoderPictureFormat(m_hDSP[nChannel],ENC_CIF_FORMAT);
			break;
		case 1:
			SetEncoderPictureFormat(m_hDSP[nChannel],ENC_2CIF_FORMAT);	
			break;
		}
		break;
	}
	}

		int nPos = g_VideoSystemParamter.m_FrameRatePos[nChannel];
		if(nChannel ==0)
		{
		   //nPos = 12;
		}		
			
			int nBr = g_VideoSystemParamter.m_Slider_BR[nChannel];	
			int nCo = g_VideoSystemParamter.m_Slider_CO[nChannel];	
			int nSa = g_VideoSystemParamter.m_Slider_SA[nChannel];	
			int nHu = g_VideoSystemParamter.m_Slider_HU[nChannel] ;				
			SetVideoPara(m_hDSP[nChannel],nBr,nCo,nSa,nHu);
			int nSH = g_VideoSystemParamter.m_Slider_SH[nChannel];	
			SetVideoSharp(m_hDSP[nChannel],nSH);
			//TRACE("StartVideoCapture\n");
			//---------------------------------------------------
			SetRecoderFrameRate(m_hDSP[nChannel],g_VideoSystemParamter.m_RecFrameRatePos[nChannel]);
			Set_Video_Quality_Level(m_hDSP[nChannel],g_VideoSystemParamter.m_VideoQualityLev[nChannel]);

			//----------------------------------------------------
			SetVideoFrameRate(m_hDSP[nChannel],g_VideoSystemParamter.m_FrameRatePos[nChannel]);	
			StartVideoCapture(m_hDSP[nChannel]);
			//CString m_chName;
			//m_chName.Format("测试版%02d",nChannel+1);
			//SetOSD(nChannel,m_chName.GetBuffer());
	
}
}

void CVideoStreamShow::SetOSD(int nChannel,char  *ch_name)
{
	//if(g_NetService.isOSD_Disp ==FALSE) return;
	SetOsd(m_hDSP[nChannel],true);
	char szChannelName[64];
	memset(szChannelName,0x0,64);
	sprintf(szChannelName,"%s",ch_name);
	USHORT		Buf1[100];
	memset(Buf1,0x0,100);
	USHORT		Buf2[100]={10,20,_OSD_YEAR4,'-',_OSD_MONTH2,'-',_OSD_DAY,' ',\
	_OSD_HOUR24,':',_OSD_MINUTE,':',_OSD_SECOND,' ','\0'};

	Buf2[0] = 200;
	Buf2[1] = 270;
	int Length;
	int offset;
	char szTemp;
	char szTemp1;
	int result;
			Length = 0;
			offset= 0;
			szTemp= NULL;
			szTemp1= NULL;
			Buf1[0]=10;
			Buf1[1]=10;
			Length  = strlen(szChannelName);
			
			WCHAR wszOsdSting[256];          // Unicode user name
			//memset((char*)wszOsdSting,0x0,sizeof(WCHAR)*256);
			int nCount = MultiByteToWideChar( CP_ACP, 0, szChannelName,
				Length, wszOsdSting,   
				sizeof(wszOsdSting)/sizeof(wszOsdSting[0]) );
			
			 offset=2;
			for (int temp=0; temp<nCount;)
			{
				Buf1[offset]=wszOsdSting[temp];
				offset++;
				temp++;
			}
			Buf1[offset]='\0';
		if(nChannel ==0)
		{
			SetStreamType(m_hDSP[nChannel],STREAM_TYPE_AVSYNC);
		}			
		result=SetOsdDisplayMode(m_hDSP[nChannel],255,FALSE,0x1000,Buf1,Buf2);
		
		SetOsd(m_hDSP[nChannel],TRUE);

}
void CVideoStreamShow::SetDefaultParameter(int index)
{
	
		g_VideoSystemParamter.m_Video_Format_size[index]=3;  //---- 0--1/4 
 		g_VideoSystemParamter.m_Video_Stand_mode[index]=0;
		g_VideoSystemParamter.m_FrameRatePos[index]=25;
		
		g_VideoSystemParamter.m_Slider_BR[index]=00;
		g_VideoSystemParamter.m_Slider_CO[index]=150;
		g_VideoSystemParamter.m_Slider_SA[index]=147;
		g_VideoSystemParamter.m_Slider_HU[index]=128;

		// if  support AHD 
		g_VideoSystemParamter.m_Slider_BR[index]=0x08;
		g_VideoSystemParamter.m_Slider_CO[index]=0x88;
		g_VideoSystemParamter.m_Slider_SA[index]=0x5F;
		g_VideoSystemParamter.m_Slider_HU[index]=0x00;



		g_VideoSystemParamter.m_Slider_SH[index]=4;
		
		g_VideoSystemParamter.m_VideoQualityLev[index] =0;

}

void CVideoStreamShow::Video_Board_preview()
{
	// TODO: Add your control notification handler code here
	
	int i;

	for( i = 0;i<m_TotalChannel;i++)
	{
		StartDsp(m_hDSP[i]);
		Set_Main_Enable(m_hDSP[i],0);
	}
	for( i = 0;i<m_TotalChannel;i++)
	{
		StartDMA(m_hDSP[i]);
	}
}
void CVideoStreamShow::SetStartVideoPreview(int index,HWND hwnd,RECT *rect)
{
	int i;
	//for( i = 0;i<m_TotalChannel;i++)
	//{
	//	StartVideoPreview(m_hDSP[i],NULL,rect,false,0,0);
	//}
	StartVideoPreview(m_hDSP[index],hwnd,rect,false,0,0);
}
void CVideoStreamShow::StopSaveAllCapture()
{
int i;
	TCHAR szFileName[256];
	for( i = 0;i<m_TotalChannel;i++)
	{
		if(m_hDSP[i]!= (HANDLE) 0xffffffff)
		{
			//StopVideoCapture(m_hDSP[i]);
			StopSaveFile(i);
		}
	}
}
void CVideoStreamShow::StopSaveFile(int nChannel)
{
	if(m_hDSP[nChannel]== (HANDLE) 0xffffffff)
	{
		return;
	}
	if(nChannel>=0 && nChannel<MAX_VIDEO_CHANNEL)
	{
		m_bRecord[nChannel] = false;
		DWORD dwResult =0;
		m_bCanWriteFile[nChannel] = false;
		if(m_pAviFile[nChannel])
		{
			m_pAviFile[nChannel]->Close(&dwResult);
			delete m_pAviFile[nChannel];
			m_pAviFile[nChannel] = NULL;
		}
	}
}
void CVideoStreamShow::StartSaveAllCapture()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: Add your control notification handler code here
	COleDateTime time = COleDateTime::GetCurrentTime();
//	ReStartAllDSPs();
	int i;
	TCHAR szFileName[256];
	for( i = 0;i<m_TotalChannel;i++)
	{
	    m_bCanWriteFile[i] = false;
		StartVideoCapture(m_hDSP[i]);
		sprintf(szFileName,_T("d:\\Record\\%02d%04d%02d%02d%02d%02d%02d.avi"),i+1,time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
		
		CRect rect;
		PictureFormat_t pictureformat;
		VideoStandard_t  m_videostandard;
		pictureformat = ENC_CIF_FORMAT;
		if(g_VideoSystemParamter.m_Video_Stand_mode[0] == 0)
		{
			m_videostandard = StandardPAL;
			
		}
		else
		{
			m_videostandard = StandardNTSC;
			
		}
		int Size = g_VideoSystemParamter.m_Video_Format_size[i];;
			switch(m_system_version)
		{
		case 36:
		case 37:
		case 38:
		case 27:
		case 50:
		case 52:
		case 53:
		case 55:
		case 51:
		case 54:
		{
		switch(Size)
		{
			case 0:
				pictureformat = ENC_CIF_FORMAT;
				break;
			case 1:
				pictureformat = ENC_CIF_FORMAT;
				break;
			case 2:
				pictureformat = ENC_2CIF_FORMAT;
				break;
			case 3:
				pictureformat = ENC_2CIF_FORMAT;
				break;
			default:
				return;
				break;
				
		}
	
	switch(pictureformat)
		{
			case ENC_CIF_FORMAT:
			{
				if(g_VideoSystemParamter.m_Video_Full_Size[i] ==0)
						rect  = CRect(0,0,640,360);
				else
						rect  = CRect(0,0,1280,720);
				break;
			}
			case ENC_2CIF_FORMAT:
			{
				rect  = CRect(0,0,1280,720);
				break;
			}
			default:
				return;
				break;
		}
	break;
}
case 60:
case 70:
case 71:
case 72:
case 73:
{
	switch(Size)
	{
			case 0:
				pictureformat = ENC_CIF_FORMAT;
				rect  = CRect(0,0,640,360);
				break;
			case 1:
				pictureformat = ENC_QCIF_FORMAT;
				rect  = CRect(0,0,1280,720);
				break;
			case 2:
				pictureformat = ENC_2CIF_FORMAT;
				rect  = CRect(0,0,960,540);
				break;
			case 3:
				pictureformat = ENC_4CIF_FORMAT;
				rect  = CRect(0,0,1920,1080);
				break;
			default:
				pictureformat = ENC_CIF_FORMAT;
				rect  = CRect(0,0,640,360);
				break;
				
	}
	break;
}
default:
{
		
	switch(Size)
	{
			case 0:
				pictureformat = ENC_CIF_FORMAT;
				break;
			case 1:
				pictureformat = ENC_2CIF_FORMAT;
				break;
			default:
				return;
				break;
				
		}
	switch(pictureformat)
		{
			case ENC_CIF_FORMAT:
			{
				switch(m_videostandard)
				{
					case  StandardNone:
							if(g_VideoSystemParamter.m_Video_Full_Size[i] ==0)
								rect  = CRect(0,0,720,576);
							else
								rect  = CRect(0,0,960,576);
							break;
					case StandardNTSC:
							if(g_VideoSystemParamter.m_Video_Full_Size[i] ==0)
								rect  = CRect(0,0,720,480);
							else
								rect  = CRect(0,0,960,480);
							break;
					case StandardPAL:
							if(g_VideoSystemParamter.m_Video_Full_Size[i] ==0)
								rect  = CRect(0,0,720,576);
							else
								rect  = CRect(0,0,960,576);
					break;
					default:
					return ;
					break;
				}
				break;
			}
			case ENC_2CIF_FORMAT:
			{
				switch(m_videostandard)
				{
					case  StandardNone:
							if(g_VideoSystemParamter.m_Video_Full_Size[i] ==0)
							rect  = CRect(0,0,720,576);
							else
							rect  = CRect(0,0,960,576);
							break;
					case StandardNTSC:
							if(g_VideoSystemParamter.m_Video_Full_Size[i] ==0)
							rect  = CRect(0,0,720,480);
							else
							rect  = CRect(0,0,960,480);
					break;
					case StandardPAL:
						if(g_VideoSystemParamter.m_Video_Full_Size[i] ==0)
						rect  = CRect(0,0,720,576);
						else
						rect  = CRect(0,0,960,576);
					break;
					default:
					return ;
					break;
				}
				break;
			}
			default:
				return;
				break;
		}
break;
}
}		
		int RecFrameRate =  g_VideoSystemParamter.m_RecFrameRatePos[i];
		StartSaveFile(time,i,szFileName,RecFrameRate,rect.Width(),rect.Height());
	}	
}

void CVideoStreamShow::StartSaveOneCapture(int index,char *dirstr)
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: Add your control notification handler code here
	COleDateTime time = COleDateTime::GetCurrentTime();
//	ReStartAllDSPs();
	int i;
	TCHAR szFileName[256];
	i = index;
	    m_bCanWriteFile[i] = false;
		StartVideoCapture(m_hDSP[i]);
		sprintf(szFileName,_T("%s\\%02d%04d%02d%02d%02d%02d%02d.avi"),dirstr,i+1,time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
		
		CRect rect;
		PictureFormat_t pictureformat;
		VideoStandard_t  m_videostandard;
		pictureformat = ENC_CIF_FORMAT;
		if(g_VideoSystemParamter.m_Video_Stand_mode[0] == 0)
		{
			m_videostandard = StandardPAL;
			
		}
		else
		{
			m_videostandard = StandardNTSC;
			
		}
		int Size = g_VideoSystemParamter.m_Video_Format_size[i];;
			switch(m_system_version)
		{
		case 36:
		case 37:
		case 38:
		case 27:
		case 50:
		case 52:
		case 53:
		case 55:
		case 51:
		case 54:
		{
		switch(Size)
		{
			case 0:
				pictureformat = ENC_CIF_FORMAT;
				break;
			case 1:
				pictureformat = ENC_CIF_FORMAT;
				break;
			case 2:
				pictureformat = ENC_2CIF_FORMAT;
				break;
			case 3:
				pictureformat = ENC_2CIF_FORMAT;
				break;
			default:
				return;
				break;
				
		}
	
	switch(pictureformat)
		{
			case ENC_CIF_FORMAT:
			{
				if(g_VideoSystemParamter.m_Video_Full_Size[i] ==0)
						rect  = CRect(0,0,640,360);
				else
						rect  = CRect(0,0,1280,720);
				break;
			}
			case ENC_2CIF_FORMAT:
			{
				rect  = CRect(0,0,1280,720);
				break;
			}
			default:
				return;
				break;
		}
	break;
}
case 60:
case 70:
case 71:
case 72:
case 73:
{
	switch(Size)
	{
			case 0:
				pictureformat = ENC_CIF_FORMAT;
				rect  = CRect(0,0,640,360);
				break;
			case 1:
				pictureformat = ENC_QCIF_FORMAT;
				rect  = CRect(0,0,1280,720);
				break;
			case 2:
				pictureformat = ENC_2CIF_FORMAT;
				rect  = CRect(0,0,960,540);
				break;
			case 3:
				pictureformat = ENC_4CIF_FORMAT;
				rect  = CRect(0,0,1920,1080);
				break;
			default:
				pictureformat = ENC_CIF_FORMAT;
				rect  = CRect(0,0,640,360);
				break;
				
	}
	break;
}
default:
{
		
	switch(Size)
	{
			case 0:
				pictureformat = ENC_CIF_FORMAT;
				break;
			case 1:
				pictureformat = ENC_2CIF_FORMAT;
				break;
			default:
				return;
				break;
				
		}
	switch(pictureformat)
		{
			case ENC_CIF_FORMAT:
			{
				switch(m_videostandard)
				{
					case  StandardNone:
							if(g_VideoSystemParamter.m_Video_Full_Size[i] ==0)
								rect  = CRect(0,0,720,576);
							else
								rect  = CRect(0,0,960,576);
							break;
					case StandardNTSC:
							if(g_VideoSystemParamter.m_Video_Full_Size[i] ==0)
								rect  = CRect(0,0,720,480);
							else
								rect  = CRect(0,0,960,480);
							break;
					case StandardPAL:
							if(g_VideoSystemParamter.m_Video_Full_Size[i] ==0)
								rect  = CRect(0,0,720,576);
							else
								rect  = CRect(0,0,960,576);
					break;
					default:
					return ;
					break;
				}
				break;
			}
			case ENC_2CIF_FORMAT:
			{
				switch(m_videostandard)
				{
					case  StandardNone:
							if(g_VideoSystemParamter.m_Video_Full_Size[i] ==0)
							rect  = CRect(0,0,720,576);
							else
							rect  = CRect(0,0,960,576);
							break;
					case StandardNTSC:
							if(g_VideoSystemParamter.m_Video_Full_Size[i] ==0)
							rect  = CRect(0,0,720,480);
							else
							rect  = CRect(0,0,960,480);
					break;
					case StandardPAL:
						if(g_VideoSystemParamter.m_Video_Full_Size[i] ==0)
						rect  = CRect(0,0,720,576);
						else
						rect  = CRect(0,0,960,576);
					break;
					default:
					return ;
					break;
				}
				break;
			}
			default:
				return;
				break;
		}
break;
}
}		
		int RecFrameRate =  g_VideoSystemParamter.m_RecFrameRatePos[i];
		StartSaveFile(time,i,szFileName,RecFrameRate,rect.Width(),rect.Height());	
}

void CVideoStreamShow::StartSaveFile(COleDateTime StartDate,int nChannel, TCHAR *pFileName, DWORD nFrameRate, int nWidth, int nHeight)
{
	DWORD dwResult =0;
	if(nChannel>=0 && nChannel<MAX_VIDEO_CHANNEL)
	{
		if(m_hDSP[nChannel]!= (HANDLE) 0xffffffff)
		{
			if(m_pAviFile[nChannel])
			{
				m_pAviFile[nChannel]->Close(&dwResult);
				delete m_pAviFile[nChannel];
				m_pAviFile[nChannel] = NULL;
			}
			m_pAviFile[nChannel] = new CAviFileObj();
			if(m_pAviFile[nChannel])
			{
				
				int out_width;
				out_width = nWidth;
				m_pAviFile[nChannel]->SetVideoFormat(streamtypeVIDEO,out_width,nHeight,nFrameRate,1,&dwResult);
				//--------------------------------------
				m_pAviFile[nChannel]->SetAudioFormat(0,&dwResult);
				HRESULT hr = E_FAIL;
				hr = m_pAviFile[nChannel]->Create(pFileName,OF_SHARE_COMPAT|OF_CREATE| OF_WRITE);
				if(FAILED(hr))
				{
					DebugString("Create File fail [%d]%s \n",nChannel,pFileName);
				}
				else
				{
					m_bRecord[nChannel] = true;
					m_bCanWriteFile[nChannel] = false;
				}
			}
		}
	}
}
int  CVideoStreamShow::CaptureImage(int index,char *path)
{
	 char szFile[256];
	//CTime time = CTime::GetCurrentTime();
	int ret =-1;
	if(m_hDSP[index]!= (HANDLE) 0xffffffff)
	{
		ULONG size=1920*1080*3;
		BYTE *TempBuffer=new BYTE[size];
		int result;
		if(TempBuffer)
		{
		  result = GetOriginalImage(m_hDSP[index],TempBuffer,&size);
		  if(result == 0)
		  {
			  //sprintf(szFile,"c:\\%02d%02d%02d%02d%02d.jpg",index+1,time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
			  ConvertYUVToJpgFile(path,TempBuffer);
			  ret = 0;
		  }
		  else
		  {
		    AfxMessageBox(_T("fail"));
		  }
         
		  delete [] TempBuffer;
		  TempBuffer = NULL;
		}
	}
	return ret;
}
void CVideoStreamShow::StartAudioPreview(int index)
{
	if(m_hDSP[index]!= (HANDLE) 0xffffffff)
	{
		SetAudioPreview(m_hDSP[index],true);
	}
}

void CVideoStreamShow::StopAudioPreview(int index) 
{
	// TODO: Add your control notification handler code here
	if(m_hDSP[index]!= (HANDLE) 0xffffffff)
	{
		SetAudioPreview(m_hDSP[index],false);
	}	
}
void CVideoStreamShow::write_bmp_header (bmp_info *cinfo,  char * pDataBuffer)
/* Write a Windows-style BMP file header, including colormap if needed */
{
  char * bmpfileheader ;
  char * bmpinfoheader;


#define PUT_2B(array,offset,value)  \
	(array[offset] = (char) ((value) & 0xFF), \
	 array[offset+1] = (char) (((value) >> 8) & 0xFF))
#define PUT_4B(array,offset,value)  \
	(array[offset] = (char) ((value) & 0xFF), \
	 array[offset+1] = (char) (((value) >> 8) & 0xFF), \
	 array[offset+2] = (char) (((value) >> 16) & 0xFF), \
	 array[offset+3] = (char) (((value) >> 24) & 0xFF))
  int  headersize, bfSize;
  int bits_per_pixel, cmap_entries;
  //-----------ponit 
    bmpfileheader =pDataBuffer;
	bmpinfoheader = pDataBuffer+14;  	
  /* Compute colormap size and total file size */
  
      bits_per_pixel = 24;
      cmap_entries = 0;
  /* File size */
  headersize = 14 + 40 + cmap_entries * 4; /* Header and colormap */
  bfSize = headersize + (int) cinfo->output_width  * (int) cinfo->output_height	;
  
  /* Set unused fields of header to 0 */
  memset(bmpfileheader,0, sizeof(bmpfileheader));
  memset(bmpinfoheader,0, sizeof(bmpinfoheader));

  /* Fill the file header */
  bmpfileheader[0] = 0x42;	/* first 2 bytes are ASCII 'B', 'M' */
  bmpfileheader[1] = 0x4D;
  PUT_4B(bmpfileheader, 2, bfSize); /* bfSize */
  /* we leave bfReserved1 & bfReserved2 = 0 */
  PUT_4B(bmpfileheader, 10, headersize); /* bfOffBits */

  /* Fill the info header (Microsoft calls this a BITMAPINFOHEADER) */
  PUT_2B(bmpinfoheader, 0, 40);	/* biSize */
  PUT_4B(bmpinfoheader, 4, cinfo->output_width); /* biWidth */
  PUT_4B(bmpinfoheader, 8, cinfo->output_height); /* biHeight */
  PUT_2B(bmpinfoheader, 12, 1);	/* biPlanes - must be 1 */
  PUT_2B(bmpinfoheader, 14, bits_per_pixel); /* biBitCount */
  /* we leave biCompression = 0, for none */
  /* we leave biSizeImage = 0; this is correct for uncompressed data */
  if (cinfo->density_unit == 2) { /* if have density in dots/cm, then */
    PUT_4B(bmpinfoheader, 24, (int) (cinfo->X_density*100)); /* XPels/M */
    PUT_4B(bmpinfoheader, 28, (int) (cinfo->Y_density*100)); /* XPels/M */
  }
  PUT_2B(bmpinfoheader, 32, cmap_entries); /* biClrUsed */
  
}
int CVideoStreamShow::ConvertYUVToJpgFile(char *pszFile, BYTE *pSource)
{
	BOOL bSize = 0;
	if(pSource!= NULL )
	{
		
		int nWidth,nHeight;
		nWidth=*(short *)pSource;
		nHeight=*(short *)(pSource+2);
		
		BYTE *buf = new BYTE [3*(nWidth*nHeight)];
		int nSize = 3*nWidth*nHeight;
		BYTE *source = pSource+4;
		BYTE *dest1 = buf+nSize-nWidth*3;
		BYTE *dest2;
		BYTE *source2;
		int ndestpatch = nWidth*3;
		int nsourcepatch = nWidth*12/8;
		BYTE *linstart = source;
		if(buf)
		{
			int i,j;
			double R, G, B, y1,u1,v1,y2,u2,v2;
			for (i=0; i<nHeight; i++)
			{
				
				for (j=0; j<nWidth/2; j++)
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
					R = max (0, min (255, R));
					G = max (0, min (255, G));
					B = max (0, min (255, B));	

					dest1[0] = (BYTE)B;
					dest1[1] = (BYTE)G;
					dest1[2] = (BYTE)R;
					dest1+=3;
					R =(double)(y2 + 1.375 * v1);
					G =(double)(y2 - 0.34375 * u1 - 0.703125 * v1);
					B =(double)(y2 + 1.734375 * u1);
					R = max (0, min (255, R));
					G = max (0, min (255, G));
					B = max (0, min (255, B));

					dest1[0] = (BYTE)B;
					dest1[1] = (BYTE)G;
					dest1[2] = (BYTE)R;
					dest1+=3;
					source += 4;
				}
				dest1 -= 2*nWidth*3;

			}	
#if 0
            CJpegFile *pJpgFile  = new CJpegFile();
			if(pJpgFile)
			{
				pJpgFile->VertFlipBuf(buf,nWidth*3,nHeight);
				pJpgFile->BGRFromRGB(buf, nWidth, nHeight);
				bSize = pJpgFile->RGBToJpegFile(pszFile,buf,nWidth,nHeight,TRUE,75);
				
				delete pJpgFile;
				pJpgFile = NULL;
			}
#else


	FILE *bmp_out;
	unsigned char *p_outbmpbuffer;
    p_outbmpbuffer = (unsigned char *) malloc( 3* nWidth * nHeight+54);
	memset(p_outbmpbuffer,0,3* nWidth * nHeight+54);
	bmp_info m_cfio;
	bmp_out= fopen(pszFile, "w+b");
	m_cfio.fp =bmp_out;
	m_cfio.density_unit =0;
	m_cfio.output_height=nHeight;
	m_cfio.output_width = nWidth;
	m_cfio.X_density =0;
	m_cfio.Y_density =0;
	memcpy(p_outbmpbuffer+54,buf,3* nWidth * nHeight);
	write_bmp_header(&m_cfio,(char *)p_outbmpbuffer);
	fwrite(p_outbmpbuffer,3*nWidth*nHeight+54,1,bmp_out);
	free(p_outbmpbuffer);
	fclose(bmp_out);
#endif
			delete [] buf;
			buf = NULL;
	  }	
	}
	
	return bSize;
}

void CVideoStreamShow::SetChangeVideoSize(int hChannel,int sizeindex)
{
	//-----------------------------
	int m_Format_size;
	int Video_Size_Index = sizeindex;
	switch(m_system_version)
	{
	case 72:
	case 73:
		{
		g_VideoSystemParamter.m_VideoDeinterlaceEn[hChannel]  =0;
		g_VideoSystemParamter.m_VideoRecQA[hChannel] = 12;
		g_VideoSystemParamter.m_Video_Full_Size[hChannel] = 0;
		g_VideoSystemParamter.m_Video_Format_size[hChannel] =Video_Size_Index;
		switch(Video_Size_Index)
		{
		case 0:
		default:
		g_VideoSystemParamter.m_Video_Format_size[hChannel] =0;
		break;
		case 1:
		g_VideoSystemParamter.m_Video_Format_size[hChannel] =1;
		break;
		case 2:
		g_VideoSystemParamter.m_Video_Format_size[hChannel] =2;
		break;
		case 3:
		g_VideoSystemParamter.m_Video_Format_size[hChannel] =3;
		break;
		}
		break;
	}
	case 36:
	case 37:
	{
	
		g_VideoSystemParamter.m_Video_Full_Size[hChannel] = 0;
		if(Video_Size_Index == 1) Video_Size_Index = 3;
		g_VideoSystemParamter.m_Video_Format_size[hChannel] =Video_Size_Index;		
		switch(Video_Size_Index)
		{
		case 0:
		g_VideoSystemParamter.m_VideoDeinterlaceEn[hChannel]  = 0;
		g_VideoSystemParamter.m_VideoRecQA[hChannel] = 12;
		break;
		case 3:
		g_VideoSystemParamter.m_VideoDeinterlaceEn[hChannel]  =1;
		g_VideoSystemParamter.m_VideoRecQA[hChannel] =  12;
		break;
		default:
		g_VideoSystemParamter.m_VideoDeinterlaceEn[hChannel]  = 0;
		break;
		}
		if(Video_Size_Index == 3) Video_Size_Index = 1;
	break;
	
		
	}
	case 38:
	case 27:
	case 50:
	case 51:
	default:
		{
	switch(Video_Size_Index)
	{
	case 0:
		g_VideoSystemParamter.m_Video_Format_size[hChannel] =0;
		g_VideoSystemParamter.m_Video_Full_Size[hChannel] = 0;
		break;
	case 1:
		g_VideoSystemParamter.m_Video_Format_size[hChannel] =0;
		g_VideoSystemParamter.m_Video_Full_Size[hChannel] = 1;
		break;
	case 2:
		g_VideoSystemParamter.m_Video_Format_size[hChannel] =1;
		g_VideoSystemParamter.m_Video_Full_Size[hChannel] = 0;
		break;
	case 3:
		g_VideoSystemParamter.m_Video_Format_size[hChannel] =1;
		g_VideoSystemParamter.m_Video_Full_Size[hChannel] = 1;
		break;
	default:
		g_VideoSystemParamter.m_Video_Format_size[hChannel] =0;
		
		break;
	}
	break;
		}
	}
	SetParameter(hChannel);

	//--------------------------------
}

void CVideoStreamShow::SetColorParameter(int hChannel,int br,int co,int sa,int hu)
{
			int nBr = br;	
			int nCo = co;	
			int nSa = sa;	
			int nHu = hu ;				
			SetVideoPara(m_hDSP[hChannel],nBr,nCo,nSa,nHu);

}