// dvrssw.h : dvrssw DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CdvrsswApp
// �йش���ʵ�ֵ���Ϣ������� dvrssw.cpp
//

class CdvrsswApp : public CWinApp
{
public:
	CdvrsswApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
//--------------------------
void Set_Default_Config_Setting(void);
