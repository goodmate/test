// robot society betaDlg.h : 헤더 파일
//

#pragma once
#include "atltypes.h"
#include "parameters.h"
#include "robot object.h"
#include <math.h>
#include "afxcmn.h"
#include "robot_status.h"
#include "afxwin.h"


// CrobotsocietybetaDlg 대화 상자
class CrobotsocietybetaDlg : public CDialog
{
// 생성입니다.
public:
	CrobotsocietybetaDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ROBOTSOCIETYBETA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	// 좌클릭 시 포인트
	CPoint point_lclk;
	// 우 클릭 시 포인트
	CPoint point_rclk;

	// 로봇 객채
	ROBOT_OBJECTS robot_hander;

	// Status Dialog 관련 변수
	ROBOT_STATUS *robot_status_dlg;
	bool m_bStatusDlg;

	// 그리기 관련 함수 
	void DrawCircle(CDC* pDC, CPoint point, int radius);
	void DrawCircle(CDC* pDC, CBrush* brush, CPoint point, int radius);
	void DrawCircle(CDC* pDC, CPoint point, double radius);
	void DrawCircle(CDC* pDC, CBrush* brush, CPoint point, double radius);
	CPoint PointThetaShift(CPoint point, double distance, double theta);

	// STAGE1
	int stage1_offset_x, stage1_offset_y;					//STAGE1에서 초기 화면의 offset
	int stage1_top,stage1_btm,stage1_right,stage1_left;
	int stage1_w, stage1_h;
	int stage1_view_offset_x, stage1_view_offset_y;			//STAGE1에서 보여지는 offset
	int stage1_view_center_x, stage1_view_center_Y;
	double stage1_view_zoom;

	// 현재 마우스 위치 
	CPoint m_pMousePt;

	// 시뮬레이션이 실행중인지 여부
	bool m_bIsRun;
	
	// 테스트 등을 위한 화면위에 뿌릴 점들
	int m_nDrawCnt;
	CPoint m_pDraw[100];


	// 시뮬레이션 속도 관련 Slider control
	CSliderCtrl m_SliderSpeed;
	int m_nSpeed;

public:
	CPoint _P(CPoint p);
	int _X(double x);
	int _Y(double y);
	int _X(int x);
	int _Y(int y);
	CPoint _iP(CPoint p);
	int _iX(double x);
	int _iY(double y);
	int _iX(int x);
	int _iY(int y);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedStartStop();
	afx_msg void OnBnClickedReset();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNMCustomdrawSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOpenStatus();
	afx_msg void OnBnClickedButtonLoadMap();

	CEdit m_log;
	CString m_sLogString;
	void showLog(CString strLog);
};

