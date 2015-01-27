#pragma once

#include "robot object.h"
#include "afxwin.h"

// ROBOT_STATUS ��ȭ �����Դϴ�.

class CrobotsocietybetaDlg;

class ROBOT_STATUS : public CDialog
{
	DECLARE_DYNAMIC(ROBOT_STATUS)

public:
	ROBOT_STATUS(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.

	virtual ~ROBOT_STATUS();

	ROBOT_OBJECTS *status_hander;



	void AddStatus(int num, CString str2add);
	void InitStatus(int num, CString str2show);
	void AddStatus(int num, char* char2add);
	void InitStatus(int num, char* char2show);



	void Update();







// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_STATUS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CButton m_bShowStatus;
	afx_msg void OnBnClickedCheckShowStatus();
	CEdit m_eStatus1;
	CEdit m_eStatus2;

	CString m_sStatusString1;
	CString m_sStatusString2;

	afx_msg void OnEnChangeEdit1();
	virtual BOOL OnInitDialog();
};
