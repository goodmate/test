// robot_status.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "robot society beta.h"
#include "robot_status.h"
#include "robot society betaDlg.h"



// ROBOT_STATUS ��ȭ �����Դϴ�.

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


// ROBOT_STATUS �޽��� ó�����Դϴ�.
void ROBOT_STATUS::Update()
{//status�� update�Ѵ�. Ÿ�̸ӿ��� ��� ȣ��
	SetDlgItemInt(IDC_EDIT_ROBOT_NUM, status_hander->robot_count);
	
}

void ROBOT_STATUS::OnBnClickedCheckShowStatus()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� �������ϰ�  ����ũ�� OR �����Ͽ� ������
	// ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ���ؾ߸�
	// �ش� �˸� �޽����� �����ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//
	


}

BOOL ROBOT_STATUS::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_sStatusString1.Format("");
	m_sStatusString2.Format("");


	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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