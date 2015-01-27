 /**
 @file	robot society betaDlg.cpp
 @date	2015/01/27
 @author	joomin Kim ( goodmate2@naver.com )
 @version	1.0
 @brief	���� ���α׷�
 */

#include "Common\stdafx.h"
#include "afxwin.h"
#include "robot society beta.h"
#include "robot society betaDlg.h"

#include "Common\map_2d.h" // DXF ������ �ε��Ͽ� ������ ����


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CrobotsocietybetaDlg ��ȭ ����




CrobotsocietybetaDlg::CrobotsocietybetaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CrobotsocietybetaDlg::IDD, pParent)
	, point_lclk(0)
	, point_rclk(0)
	, m_nDrawCnt(0)
	, m_bIsRun(false)
	, m_nSpeed(6)
	, m_bStatusDlg(false)
	, m_sLogString(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CrobotsocietybetaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_SPEED, m_SliderSpeed);
	DDX_Control(pDX, IDC_LOG, m_log);
}

BEGIN_MESSAGE_MAP(CrobotsocietybetaDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	
	ON_BN_CLICKED(IDB_START_STOP, &CrobotsocietybetaDlg::OnBnClickedStartStop)
	ON_BN_CLICKED(IDB_RESET, &CrobotsocietybetaDlg::OnBnClickedReset)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SPEED, &CrobotsocietybetaDlg::OnNMCustomdrawSliderSpeed)
	ON_BN_CLICKED(IDB_OPEN_STATUS, &CrobotsocietybetaDlg::OnBnClickedOpenStatus)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_MAP, &CrobotsocietybetaDlg::OnBnClickedButtonLoadMap)
END_MESSAGE_MAP()


// CrobotsocietybetaDlg �޽��� ó����

BOOL CrobotsocietybetaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	showLog("�ʱ�ȭ \r\n");

	//m_sLogString += "�ʱ�ȭ";
	//m_log.SetWindowText(m_sLogString);
	//m_log.LineScroll(m_log.GetLineCount());




	robot_status_dlg = new ROBOT_STATUS;
	robot_status_dlg->status_hander = &robot_hander;

	RECT stage1_rect;
	CStatic *pictureBox = (CStatic *)GetDlgItem(IDC_STATIC_STAGE1);
	pictureBox->GetClientRect(&stage1_rect);
	showLog("�κ��߰� \r\n");

	//load_dxf (g_ini.map_file, &_map_2d);
	//load_dxf ("D:\RobotSimulator\test\robot_society\robot society beta\map\modelhouse.dxf", &_map_2d);
	//PictureBox1.Image = System.Drawing.Image.FromFile("C:\test.jpg")
	//pctBox->Image = Image::FromFile(L"E:\\Programs\\Person.bmp");




	stage1_offset_x = stage1_offset_y = 12;		//MFC Dialog ��輱
	//stage1_offset_x = stage1_offset_y = 0;	//MFC Dialog ��輱

	stage1_w		= stage1_rect.right;
	stage1_h		= stage1_rect.bottom;

	stage1_top		= stage1_rect.top + stage1_offset_y;
	stage1_btm		= stage1_rect.bottom + stage1_offset_y;
	stage1_right	= stage1_rect.right + stage1_offset_x;;
	stage1_left		= stage1_rect.left + stage1_offset_x;
	

// 	TRACE("top: %d", stage1_top);
// 	TRACE("btm: %d", stage1_btm);
// 	TRACE("right: %d", stage1_right);
// 	TRACE("left: %d", stage1_left);
// 	TRACE("Width: %d", stage1_w);
// 	TRACE("Height: %d", stage1_h);
// 	TRACE("end");
	


	stage1_view_offset_x = stage1_view_offset_y = 0;			//STAGE1���� �������� offset
	stage1_view_center_x = stage1_view_center_Y = 0;
	stage1_view_zoom = 1.0;


	m_SliderSpeed.SetRange(1, 9);
	m_SliderSpeed.SetPos(m_nSpeed);
	
	
	SetTimer(1, 10, NULL);		//10ms �ֱ�
	

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CrobotsocietybetaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CrobotsocietybetaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);		// �׸��⸦ ���� ����̽� ���ؽ�Ʈ
		CRect rect;				// Ŭ���̾�Ʈ ������ ũ��
		CDC memDC;				// CDC for STAGE
		CBitmap imgBit;
		GetClientRect(&rect);	// Ŭ���̾�Ʈ ������ ũ�⸦ ����	
		memDC.CreateCompatibleDC(&dc);
		imgBit.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		memDC.SelectObject(&imgBit); 

		CBrush brush_black(COLOR_D_BLACK);
		CBrush brush_lgreen(COLOR_L_GREEN);
		CBrush brush_lred(COLOR_L_RED);
		CBrush brush_lblue(COLOR_L_BLUE);
		CBrush brush_lpurple(COLOR_L_PURPLE);		
		CBrush brush_white(COLOR_WHITE);		

		
		//stage1 �׸���
		//memDC.SelectObject(brush_black);
		memDC.SelectObject(brush_white);
		memDC.Rectangle(stage1_left, stage1_top, stage1_right, stage1_btm);

	
		//�κ��� �׸��� 
		for(int i=0; i<robot_hander.robot_count; i++)
		{
			CBrush brush_body(RGB(robot_hander.robots[i].body_color.R, robot_hander.robots[i].body_color.G, robot_hander.robots[i].body_color.B));
			CBrush brush_head(RGB(robot_hander.robots[i].head_color.R, robot_hander.robots[i].head_color.G, robot_hander.robots[i].head_color.B));
			DrawCircle(&memDC, &brush_body, robot_hander.robots[i].point, robot_hander.robots[i].body_radius);
			//DrawCircle(&memDC, &brush_head, PointThetaShift(robot_hander.robots[i].point, robot_hander.robots[i].body_radius+ robot_hander.robots[i].neck_length, robot_hander.robots[i].theta), robot_hander.robots[i].head_radius);


		}
		
		for(int i=0; i<m_nDrawCnt; i++)
		{
			DrawCircle(&memDC, &brush_lred, m_pDraw[i], 10);
		}

		//���� ���۸�
		dc.BitBlt(stage1_left, stage1_top, stage1_w, stage1_h, &memDC, 0, 0, SRCCOPY);			
		
		//�޸� ��ȯ
		memDC.DeleteDC();
		imgBit.DeleteObject();

		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CrobotsocietybetaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//
void CrobotsocietybetaDlg::DrawCircle(CDC* pDC, CPoint point, int radius)
{
	pDC->Ellipse( _X((int)(point.x) - radius)
		, _Y((int)(point.y) - radius)
		, _X((int)(point.x) + radius)
		, _Y((int)(point.y) + radius) );
}

void CrobotsocietybetaDlg::DrawCircle(CDC* pDC, CBrush* brush, CPoint point, int radius)
{
	pDC->SelectObject(brush);
	DrawCircle(pDC, point, radius);
}

void CrobotsocietybetaDlg::DrawCircle(CDC* pDC, CPoint point, double d_radius)
{
	int radius = (int)d_radius;
	pDC->Ellipse( _X((int)(point.x) - radius)
		, _Y((int)(point.y) - radius)
		, _X((int)(point.x) + radius)
		, _Y((int)(point.y) + radius) );
}

void CrobotsocietybetaDlg::DrawCircle(CDC* pDC, CBrush* brush, CPoint point, double d_radius)
{
	int radius = (int)d_radius;
	pDC->SelectObject(brush);
	DrawCircle(pDC, point, radius);
}

CPoint CrobotsocietybetaDlg::PointThetaShift(CPoint point, double distance, double theta)
{
	CPoint point_return;
	
	point_return.x = point.x + (LONG)(distance*cos(theta));
	point_return.y = point.y + (LONG)(distance*sin(theta));

	return point_return;
}
//
int CrobotsocietybetaDlg::_X(double x)
{
	return (int)(x*stage1_view_zoom + stage1_view_offset_x + stage1_w/2);
}

int CrobotsocietybetaDlg::_Y(double y)
{
	return (int)(stage1_h/2 - y*stage1_view_zoom + stage1_view_offset_y);
}

int CrobotsocietybetaDlg::_X(int x)
{
	double d = (double)x;
	return _X(d);
}

int CrobotsocietybetaDlg::_Y(int y)
{
	double d = (double)y;
	return _Y(d);
}

CPoint CrobotsocietybetaDlg::_P(CPoint p)
{
	CPoint r;
	r.x = _X(p.x);
	r.y = _Y(p.y);
	return r;
}

int CrobotsocietybetaDlg::_iX(double x)
{
	//return (int)(x*stage1_view_zoom + stage1_view_offset_x + stage1_w/2);
	return (int)((x-stage1_w/2-stage1_view_offset_x)/stage1_view_zoom);
}

int CrobotsocietybetaDlg::_iY(double y)
{
	//return (int)(stage1_h/2 - y*stage1_view_zoom + stage1_view_offset_y);
	return (int)(( stage1_h/2 - y + stage1_view_offset_y )/stage1_view_zoom );
}

int CrobotsocietybetaDlg::_iX(int x)
{
	double d = (double)x;
	return _iX(d);
}

int CrobotsocietybetaDlg::_iY(int y)
{
	double d = (double)y;
	return _iY(d);
}

CPoint CrobotsocietybetaDlg::_iP(CPoint p)
{
	CPoint r;
	r.x = _iX(p.x);
	r.y = _iY(p.y);
	return r;
}




//

//
void CrobotsocietybetaDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_pMousePt.x = point.x - 12 ;
	m_pMousePt.y = point.y - 12 ;
	CDialog::OnMouseMove(nFlags, point);
}

BOOL CrobotsocietybetaDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	bool b = FALSE;

	if(m_pMousePt.x>=stage1_left && m_pMousePt.x<=stage1_right && m_pMousePt.y>=stage1_top && m_pMousePt.y<=stage1_btm)
	{
		if(zDelta>0)
		{
			stage1_view_zoom += 0.06;
			b = TRUE;
		}
		else
		{
			stage1_view_zoom -= 0.06;
			if(stage1_view_zoom<0.1)	stage1_view_zoom = 0.1;
			b = TRUE;
		}
	}
	if(b)
	{
		Invalidate();
		return TRUE;
	}
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void CrobotsocietybetaDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	TRACE("L btn down\r\n");
	point_lclk = CPoint(point.x-12, point.y-12);


	if(robot_status_dlg->m_bShowStatus.GetCheck())
	{
		for(int i=0; i<robot_hander.robot_count; i++)
		{
			//if(Get_Length(_iP(point_lclk), robot_hander.robots[i].point) < robot_hander.robots[i].body_radius)
			if(robot_hander.robots[i].isMeet(_iP(point_lclk)))
			{
				robot_status_dlg->AddStatus(1, robot_hander.Data(i));
				TRACE("test1 \r\n");
			}
		}
	}
	else
	{
		robot_hander.Add(_iP(point_lclk));
	}
	


	Invalidate();

	CDialog::OnLButtonDown(nFlags, point);
}

void CrobotsocietybetaDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	TRACE("R btn down\r\n");
	point_rclk = CPoint(point.x-12, point.y-12);

	for(int i=0; i<robot_hander.robot_count; i++)
	{
		//TRACE("(%.1f, %.1f) - (%.1f, %.1f) : ", (double)(_iP(m_pMousePt).x), (double)(_iP(m_pMousePt).y), (double)(robot_hander.robots[i].point.x), (double)(robot_hander.robots[i].point.y));
		//TRACE("�Ÿ�:,%.1f   ������: %.1f  \r\n",Get_Length(_iP(m_pMousePt), robot_hander.robots[i].point), robot_hander.robots[i].body_radius);

		//if(Get_Length(_iP(point_rclk), robot_hander.robots[i].point) < robot_hander.robots[i].body_radius)
		if(robot_hander.robots[i].isMeet(_iP(point_rclk)))
		{
			robot_hander.Pop(i);
			TRACE("POP: %d \r\n", i);
		}

	}

	Invalidate();

	CDialog::OnRButtonDown(nFlags, point);
}
BOOL CrobotsocietybetaDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	bool r = FALSE;
	if(m_pMousePt.x>=stage1_left && m_pMousePt.x<=stage1_right && m_pMousePt.y>=stage1_top && m_pMousePt.y<=stage1_btm)
	{
		if(pMsg->message==WM_KEYDOWN)
		{
			TRACE("Ű�� ���ȴ�: %d \r\n", pMsg->wParam);
			switch(pMsg->wParam)
			{
			case 104:
			case VK_UP:
				stage1_view_offset_y -= 25;
				r = TRUE;
				break;
			case 98:
			case VK_DOWN: 
				stage1_view_offset_y += 25;
				r = TRUE;
				break;
			case 102:
			case VK_RIGHT:
				stage1_view_offset_x += 25;
				r = TRUE;
				break;
			case 100:
			case VK_LEFT: 
				stage1_view_offset_x -= 25;
				r = TRUE;
				break;

			case 97:	//down left
				stage1_view_offset_x -= 20;
				stage1_view_offset_y += 20;
				r = TRUE;
				break;
			case 99:	//down right
				stage1_view_offset_x += 20;
				stage1_view_offset_y += 20;
				r = TRUE;
				break;
			case 103:	//up left
				stage1_view_offset_x -= 20;
				stage1_view_offset_y -= 20;
				r = TRUE;
				break;
			case 105:	//up right
				stage1_view_offset_x += 20;
				stage1_view_offset_y -= 20;
				r = TRUE;
				break;

			case 107:	//zoom up
				stage1_view_zoom += 0.06;
				r = TRUE;
				break;
			case 109:	//zoom down
				stage1_view_zoom -= 0.06;
				if(stage1_view_zoom<0.1)	stage1_view_zoom = 0.1;
				r = TRUE;
				break;

			case 101:	//�����·� 
				stage1_view_offset_x = 0;
				stage1_view_offset_y = 0;
				r = TRUE;
				break;
			}
			if(r)
			{
				Invalidate(FALSE);
				return TRUE;
			}	
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CrobotsocietybetaDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	static int timer_count = 0;

	if(++timer_count >= m_nSpeed && m_bIsRun)
	{
		timer_count = 0;

		robot_hander.Localization();	//��ġ�� �����Ѵ�. 
		robot_hander.Update();			//������ �����Ѵ�. 
		
		Invalidate(FALSE);
	}

	if(m_bStatusDlg)
	{
		robot_status_dlg->Update();
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CrobotsocietybetaDlg::OnBnClickedStartStop()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(!m_bIsRun)
	{
		m_bIsRun = TRUE;
		//SetTimer(1, 10, NULL);		//10ms �ֱ�
	}
	else
	{
		m_bIsRun = FALSE;
		//KillTimer(1);
	}
}

void CrobotsocietybetaDlg::OnBnClickedReset()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int curr_robot_count = robot_hander.robot_count;
	int max_robot_count = curr_robot_count + 100;

	if(max_robot_count>MAX_ROBOT_COUNT)	max_robot_count = MAX_ROBOT_COUNT;
	//robot_hander.robot_count = max_robot_count;

	for(int i=curr_robot_count; i<max_robot_count; i++)
	{
		robot_hander.Add();
	}
	
	Invalidate();
}



void CrobotsocietybetaDlg::OnNMCustomdrawSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	static int prePos = 0;
	int nNewPos = m_SliderSpeed.GetPos();

	if(prePos != nNewPos)
	{
		prePos = nNewPos;
		m_nSpeed = m_SliderSpeed.GetRangeMax() - nNewPos + 1;
		m_SliderSpeed.SetPos(nNewPos);
		TRACE("�����̴�: %d\r\n", m_nSpeed);

		HWND hWnd = ::GetFocus();
		HWND NextWnd;

		NextWnd = ::GetNextDlgTabItem(m_hWnd, hWnd, TRUE);
		::SetFocus(NextWnd);
	}

	*pResult = 0;
}

void CrobotsocietybetaDlg::OnBnClickedOpenStatus()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_bStatusDlg )
	{
		m_bStatusDlg = FALSE;
		robot_status_dlg->DestroyWindow();
		//delete(robot_status_dlg);
	}
	else
	{
		m_bStatusDlg = TRUE;
		//delete(robot_status_dlg);
		//robot_status_dlg = new ROBOT_STATUS;
		//robot_status_dlg->status_hander = &robot_hander;
		robot_status_dlg->Create(IDD_STATUS_DIALOG, this);
		robot_status_dlg->ShowWindow(SW_SHOW);
	}


	UpdateData(TRUE);
}


 /**
 @fn void CrobotsocietybetaDlg::OnBnClickedButtonLoadMap()

 @brief addtion funtion
 @date 2012/07/02

 @author joomin kim (  )

 @param a ������ ����
 @param b ������ ����

 @return ������ ���� ����

 @exception 

 @remark �� �Լ��� ������ ������ ���ִ� �Լ�
 */
void CrobotsocietybetaDlg::OnBnClickedButtonLoadMap()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		CFileDialog fdlg(TRUE, "dxf", "*.dxf", OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, 
		"Map Files (*.dxf)|*.dxf|All Files (*.*)|*.*||", this);

	if (IDOK == fdlg.DoModal ()) {
		CString fileName = fdlg.GetPathName ();

		//strncpy (g_ini.map_file, (LPCSTR)fileName, MAX_PATH);

		_map_2d.clear();
		load_dxf ((LPCSTR)fileName, &_map_2d);

		// load_dxf() �Լ��� �о���� �� ������ mm�� ����Ǿ��ִ�. 
		// �� �����͸� m�� ���� �����Ѵ�.
		for (unsigned int i=0; i<_map_2d.size(); ++i) {
			_map_2d[i].x0 *= 0.001;
			_map_2d[i].y0 *= 0.001;
			_map_2d[i].z0 *= 0.001;
			_map_2d[i].x1 *= 0.001;
			_map_2d[i].y1 *= 0.001;
			_map_2d[i].z1 *= 0.001; 
		}
	}

}

 /**
 @fn void CrobotsocietybetaDlg::showLog(CString strLog)

 @brief addtion funtion
 @date 2012/07/02

 @author joomin kim (  )

 @param a ������ ����
 @param b ������ ����

 @return ������ ���� ����

 @exception 

 @remark �� �Լ��� ������ ������ ���ִ� �Լ�
 */

void CrobotsocietybetaDlg::showLog(CString strLog)
{
	m_sLogString += strLog;
	m_log.SetWindowText(m_sLogString);
	m_log.LineScroll(m_log.GetLineCount());
}
