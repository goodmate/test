// robot society betaDlg.h : ��� ����
//

#pragma once
#include "atltypes.h"
#include "parameters.h"
#include "robot object.h"
#include <math.h>
#include "afxcmn.h"
#include "robot_status.h"
#include "afxwin.h"


// CrobotsocietybetaDlg ��ȭ ����
class CrobotsocietybetaDlg : public CDialog
{
// �����Դϴ�.
public:
	CrobotsocietybetaDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ROBOTSOCIETYBETA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	// ��Ŭ�� �� ����Ʈ
	CPoint point_lclk;
	// �� Ŭ�� �� ����Ʈ
	CPoint point_rclk;

	// �κ� ��ä
	ROBOT_OBJECTS robot_hander;

	// Status Dialog ���� ����
	ROBOT_STATUS *robot_status_dlg;
	bool m_bStatusDlg;

	// �׸��� ���� �Լ� 
	void DrawCircle(CDC* pDC, CPoint point, int radius);
	void DrawCircle(CDC* pDC, CBrush* brush, CPoint point, int radius);
	void DrawCircle(CDC* pDC, CPoint point, double radius);
	void DrawCircle(CDC* pDC, CBrush* brush, CPoint point, double radius);
	CPoint PointThetaShift(CPoint point, double distance, double theta);

	// STAGE1
	int stage1_offset_x, stage1_offset_y;					//STAGE1���� �ʱ� ȭ���� offset
	int stage1_top,stage1_btm,stage1_right,stage1_left;
	int stage1_w, stage1_h;
	int stage1_view_offset_x, stage1_view_offset_y;			//STAGE1���� �������� offset
	int stage1_view_center_x, stage1_view_center_Y;
	double stage1_view_zoom;

	// ���� ���콺 ��ġ 
	CPoint m_pMousePt;

	// �ùķ��̼��� ���������� ����
	bool m_bIsRun;
	
	// �׽�Ʈ ���� ���� ȭ������ �Ѹ� ����
	int m_nDrawCnt;
	CPoint m_pDraw[100];


	// �ùķ��̼� �ӵ� ���� Slider control
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

