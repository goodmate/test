#pragma once

#include "robot object.h"
#include "afxwin.h"

// ROBOT_STATUS 대화 상자입니다.

class CrobotsocietybetaDlg;

class ROBOT_STATUS : public CDialog
{
	DECLARE_DYNAMIC(ROBOT_STATUS)

public:
	ROBOT_STATUS(CWnd* pParent = NULL);   // 표준 생성자입니다.

	virtual ~ROBOT_STATUS();

	ROBOT_OBJECTS *status_hander;



	void AddStatus(int num, CString str2add);
	void InitStatus(int num, CString str2show);
	void AddStatus(int num, char* char2add);
	void InitStatus(int num, char* char2show);



	void Update();







// 대화 상자 데이터입니다.
	enum { IDD = IDD_STATUS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
