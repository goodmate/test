// robot society beta.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CrobotsocietybetaApp:
// �� Ŭ������ ������ ���ؼ��� robot society beta.cpp�� �����Ͻʽÿ�.
//

class CrobotsocietybetaApp : public CWinApp
{
public:
	CrobotsocietybetaApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CrobotsocietybetaApp theApp;