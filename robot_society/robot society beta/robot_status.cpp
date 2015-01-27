// robot_status.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "robot society beta.h"
#include "robot_status.h"
#include "robot society betaDlg.h"



// ROBOT_STATUS 대화 상자입니다.

IMPLEMENT_DYNAMIC(ROBOT_STATUS, CDialog)

ROBOT_STATUS::ROBOT_STATUS(CWnd* pParent /*=NULL*/)
	: CDialog(ROBOT_STATUS::IDD, pParent)
{
	
}

ROBOT_STATUS::~ROBOT_STATUS()
{
}

void ROBOT_STATUS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_SHOW_STATUS, m_bShowStatus);
	DDX_Control(pDX, IDC_EDIT1, m_eStatus1);
	DDX_Control(pDX, IDC_EDIT2, m_eStatus2);
}


BEGIN_MESSAGE_MAP(ROBOT_STATUS, CDialog)
	ON_BN_CLICKED(IDC_CHECK_SHOW_STATUS, &ROBOT_STATUS::OnBnClickedCheckShowStatus)
	ON_EN_CHANGE(IDC_EDIT1, &ROBOT_STATUS::OnEnChangeEdit1)
END_MESSAGE_MAP()


// ROBOT_STATUS 메시지 처리기입니다.
void ROBOT_STATUS::Update()
{//status를 update한다. 타이머에서 계속 호출
	SetDlgItemInt(IDC_EDIT_ROBOT_NUM, status_hander->robot_count);
	
}

void ROBOT_STATUS::OnBnClickedCheckShowStatus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_bShowStatus.GetCheck())
	{
		TRACE("Show status \r\n");
	}
	else
	{
		
		TRACE("Set Robot \r\n");
	}
}

void ROBOT_STATUS::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정하고  마스크에 OR 연산하여 설정된
	// ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출해야만
	// 해당 알림 메시지를 보냅니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//
	


}

BOOL ROBOT_STATUS::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_sStatusString1.Format("");
	m_sStatusString2.Format("");


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
void ROBOT_STATUS::AddStatus(int num, char* char2add)
{
	CString str;
	str.Format("%s",char2add);
	AddStatus(num, str);
}


void ROBOT_STATUS::InitStatus(int num, char* char2show)
{
	CString str;
	str.Format("%s",char2show);
	InitStatus(num, str);
}

void ROBOT_STATUS::AddStatus(int num, CString str2add)
{
	switch(num)
	{
	case 1:
		m_sStatusString1 += str2add;
		//str2add.Format("\r\n");m_sStatusString1 += str2add;

		m_eStatus1.SetWindowText(m_sStatusString1);
		m_eStatus1.LineScroll(m_eStatus1.GetLineCount());
		break;
	case 2:
		m_sStatusString2 += str2add;
		//str2add.Format("\r\n");m_sStatusString1 += str2add;

		m_eStatus2.SetWindowText(m_sStatusString2);
		m_eStatus2.LineScroll(m_eStatus2.GetLineCount());
		break;
	}	
}


void ROBOT_STATUS::InitStatus(int num, CString str2show)
{
	switch(num)
	{
	case 1:
		m_sStatusString1.Format("");
		m_sStatusString1 = str2show;

		m_eStatus1.SetWindowText(m_sStatusString1);
		m_eStatus1.LineScroll(m_eStatus1.GetLineCount());
		break;
	case 2:
		m_sStatusString2.Format("");
		m_sStatusString2 = str2show;

		m_eStatus2.SetWindowText(m_sStatusString2);
		m_eStatus2.LineScroll(m_eStatus2.GetLineCount());
		break;
	}	
	
}