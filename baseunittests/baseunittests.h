
// baseunittests.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#include "Envrm.h"

// CBaseApp: 
// �йش����ʵ�֣������ baseunittests.cpp
//

class CBaseApp : public CWinApp
{
public:
	CBaseApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

private:
	CEnvrm m_env;
};

extern CBaseApp theApp;