// malib.h : malib DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
using namespace std;
#include "cv.h"
#include "highgui.h"
#include "CvvImage.h"
// CmalibApp
// �йش���ʵ�ֵ���Ϣ������� malib.cpp
//

class CmalibApp : public CWinApp
{
public:
	CmalibApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
