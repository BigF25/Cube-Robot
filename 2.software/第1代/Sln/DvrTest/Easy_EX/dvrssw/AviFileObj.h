// AviFileObj.h: interface for the CAviFileObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AVIFILEOBJ_H__9E06513C_B1E9_44CA_B1D5_FD84A01030DE__INCLUDED_)
#define AFX_AVIFILEOBJ_H__9E06513C_B1E9_44CA_B1D5_FD84A01030DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <wtypes.h>
#include <Vfw.h>

class CAviFileObj  
{
public:
	CAviFileObj();
	virtual ~CAviFileObj();

public:
	virtual HRESULT Create(TCHAR* szFile, UINT uiMode, DWORD* pdwError = NULL);
	virtual HRESULT Close(DWORD* pdwError = NULL);

	virtual HRESULT SetVideoFormat(FOURCC fccVideo, DWORD dwWidth, DWORD dwHeight, DWORD dwRate, DWORD dwScale, DWORD* pdwError = NULL);
	virtual HRESULT GetVideoFormat(FOURCC& fccVideo, DWORD& dwWidth, DWORD& dwHeight, DWORD& dwRate, DWORD& dwScale, DWORD* pdwError = NULL);

	virtual HRESULT SetAudioFormat(DWORD dwFormat, DWORD* pdwError = NULL);
	virtual HRESULT GetAudioFormat(DWORD& dwFormat, DWORD* pdwError = NULL);

	virtual HRESULT WriteVideo(BYTE* pbData, LONG lSize, BOOL bIsKeyFrame, BOOL bPaused = FALSE, DWORD* pdwError = NULL);

	virtual HRESULT WriteAudio(BYTE* pbData, LONG lSize, BOOL bPaused = FALSE, DWORD* pdwError = NULL);
public :
		COleDateTime m_StartDate;
	    CString      m_AviFileName;
		int          m_currChannel;
		TCHAR		m_szFile[MAX_PATH]; // AVI�ļ�ȫ·��
protected:
	PAVIFILE	m_pAviFile;
	
//	UINT		m_uiMode; // �����ļ���ģʽ
	
	PAVISTREAM	m_psVideoStream;
	AVISTREAMINFO	m_siVideo;
	BITMAPINFOHEADER	m_bihVideo;
	LONG		m_lVideoStart;
	LONG		m_lVideoSamples;

	DWORD		m_dwAudioFormat;
	PAVISTREAM	m_psAudioStream;
	AVISTREAMINFO	m_siAudio;
	LPVOID			m_lpAudioFormat;
	LONG		m_lAudioStart;
	LONG		m_lAudioSamples;
	LONG        m_TotalStreamSize;
	BOOL        m_bCreateFile;
	//---------------------------
	FILE *m_pStreamFile;

protected:
	CRITICAL_SECTION	m_csObject;
};

#endif // !defined(AFX_AVIFILEOBJ_H__9E06513C_B1E9_44CA_B1D5_FD84A01030DE__INCLUDED_)
