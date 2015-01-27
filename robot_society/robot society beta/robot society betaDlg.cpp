 /**
 @file	robot society betaDlg.cpp
 @date	2015/01/27
 @author	joomin Kim ( goodmate2@naver.com )
 @version	1.0
 @brief	메인 프로그램
 */

#include "Common\stdafx.h"
#include "afxwin.h"
#include "robot society beta.h"
#include "robot society betaDlg.h"

#include "Common\map_2d.h" // DXF 파일을 로딩하여 맵으로 저장


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CrobotsocietybetaDlg 대화 상자




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


// CrobotsocietybetaDlg 메시지 처리기

BOOL CrobotsocietybetaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	showLog("초기화 \r\n");

	//m_sLogString += "초기화";
	//m_log.SetWindowText(m_sLogString);
	//m_log.LineScroll(m_log.GetLineCount());




	robot_status_dlg = new ROBOT_STATUS;
	robot_status_dlg->status_hander = &robot_hander;

	RECT stage1_rect;
	CStatic *pictureBox = (CStatic *)GetDlgItem(IDC_STATIC_STAGE1);
	pictureBox->GetClientRect(&stage1_rect);
	showLog("로봇추가 \r\n");

	//load_dxf (g_ini.map_file, &_map_2d);
	//load_dxf ("D:\RobotSimulator\test\robot_society\robot society beta\map\modelhouse.dxf", &_map_2d);
	//PictureBox1.Image = System.Drawing.Image.FromFile("C:\test.jpg")
	//pctBox->Image = Image::FromFile(L"E:\\Programs\\Person.bmp");




	stage1_offset_x = stage1_offset_y = 12;		//MFC Dialog 경계선
	//stage1_offset_x = stage1_offset_y = 0;	//MFC Dialog 경계선

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
	


	stage1_view_offset_x = stage1_view_offset_y = 0;			//STAGE1에서 보여지는 offset
	stage1_view_center_x = stage1_view_center_Y = 0;
	stage1_view_zoom = 1.0;


	m_SliderSpeed.SetRange(1, 9);
	m_SliderSpeed.SetPos(m_nSpeed);
	
	
	SetTimer(1, 10, NULL);		//10ms 주기
	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CrobotsocietybetaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);		// 그리기를 위한 디바이스 컨텍스트
		CRect rect;				// 클라이언트 영역의 크기
		CDC memDC;				// CDC for STAGE
		CBitmap imgBit;
		GetClientRect(&rect);	// 클라이언트 영역의 크기를 얻음	
		memDC.CreateCompatibleDC(&dc);
		imgBit.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		memDC.SelectObject(&imgBit); 

		CBrush brush_black(COLOR_D_BLACK);
		CBrush brush_lgreen(COLOR_L_GREEN);
		CBrush brush_lred(COLOR_L_RED);
		CBrush brush_lblue(COLOR_L_BLUE);
		CBrush brush_lpurple(COLOR_L_PURPLE);		
		CBrush brush_white(COLOR_WHITE);		

		
		//stage1 그리기
		//memDC.SelectObject(brush_black);
		memDC.SelectObject(brush_white);
		memDC.Rectangle(stage1_left, stage1_top, stage1_right, stage1_btm);

	
		//로봇들 그리기 
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

		//더블 버퍼링
		dc.BitBlt(stage1_left, stage1_top, stage1_w, stage1_h, &memDC, 0, 0, SRCCOPY);			
		
		//메모리 반환
		memDC.DeleteDC();
		imgBit.DeleteObject();

		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_pMousePt.x = point.x - 12 ;
	m_pMousePt.y = point.y - 12 ;
	CDialog::OnMouseMove(nFlags, point);
}

BOOL CrobotsocietybetaDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	TRACE("R btn down\r\n");
	point_rclk = CPoint(point.x-12, point.y-12);

	for(int i=0; i<robot_hander.robot_count; i++)
	{
		//TRACE("(%.1f, %.1f) - (%.1f, %.1f) : ", (double)(_iP(m_pMousePt).x), (double)(_iP(m_pMousePt).y), (double)(robot_hander.robots[i].point.x), (double)(robot_hander.robots[i].point.y));
		//TRACE("거리:,%.1f   반지름: %.1f  \r\n",Get_Length(_iP(m_pMousePt), robot_hander.robots[i].point), robot_hander.robots[i].body_radius);

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
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	bool r = FALSE;
	if(m_pMousePt.x>=stage1_left && m_pMousePt.x<=stage1_right && m_pMousePt.y>=stage1_top && m_pMousePt.y<=stage1_btm)
	{
		if(pMsg->message==WM_KEYDOWN)
		{
			TRACE("키가 눌렸다: %d \r\n", pMsg->wParam);
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

			case 101:	//원상태로 
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	static int timer_count = 0;

	if(++timer_count >= m_nSpeed && m_bIsRun)
	{
		timer_count = 0;

		robot_hander.Localization();	//위치를 갱신한다. 
		robot_hander.Update();			//정보를 갱신한다. 
		
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(!m_bIsRun)
	{
		m_bIsRun = TRUE;
		//SetTimer(1, 10, NULL);		//10ms 주기
	}
	else
	{
		m_bIsRun = FALSE;
		//KillTimer(1);
	}
}

void CrobotsocietybetaDlg::OnBnClickedReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	static int prePos = 0;
	int nNewPos = m_SliderSpeed.GetPos();

	if(prePos != nNewPos)
	{
		prePos = nNewPos;
		m_nSpeed = m_SliderSpeed.GetRangeMax() - nNewPos + 1;
		m_SliderSpeed.SetPos(nNewPos);
		TRACE("슬라이더: %d\r\n", m_nSpeed);

		HWND hWnd = ::GetFocus();
		HWND NextWnd;

		NextWnd = ::GetNextDlgTabItem(m_hWnd, hWnd, TRUE);
		::SetFocus(NextWnd);
	}

	*pResult = 0;
}

void CrobotsocietybetaDlg::OnBnClickedOpenStatus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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

 @param a 정수형 변수
 @param b 정수형 변수

 @return 더해진 값을 리턴

 @exception 

 @remark 이 함수는 정수형 덧셈을 해주는 함수
 */
void CrobotsocietybetaDlg::OnBnClickedButtonLoadMap()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		CFileDialog fdlg(TRUE, "dxf", "*.dxf", OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, 
		"Map Files (*.dxf)|*.dxf|All Files (*.*)|*.*||", this);

	if (IDOK == fdlg.DoModal ()) {
		CString fileName = fdlg.GetPathName ();

		//strncpy (g_ini.map_file, (LPCSTR)fileName, MAX_PATH);

		_map_2d.clear();
		load_dxf ((LPCSTR)fileName, &_map_2d);

		// load_dxf() 함수로 읽어들인 맵 정보는 mm로 저장되어있다. 
		// 이 데이터를 m로 단위 변경한다.
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

 @param a 정수형 변수
 @param b 정수형 변수

 @return 더해진 값을 리턴

 @exception 

 @remark 이 함수는 정수형 덧셈을 해주는 함수
 */

void CrobotsocietybetaDlg::showLog(CString strLog)
{
	m_sLogString += strLog;
	m_log.SetWindowText(m_sLogString);
	m_log.LineScroll(m_log.GetLineCount());
}
