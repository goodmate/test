//////////////////////////////////////////////////////
// Common files for Robot applications
// 
// Copyright (c) 2002-2008. All Rights Reserved.
// Division of Applied Robot Technology KITECH
// Web: http://www.orobot.net
// Written by KwangWoong Yang<page365@gmail.com>
//
// Multimedia timer�� ����ϱ� ���� �Լ��� ����

#pragma once 
#pragma comment (lib,"winmm.lib")

typedef unsigned long DWORD;
typedef unsigned int  UINT;


class CMultimediaTimer {
private:
	UINT _timerRes;
	DWORD _timerId;

public:
	CMultimediaTimer ();
	~CMultimediaTimer ();

	virtual void OnTimer (UINT timerId, UINT msg) { }

	void Start (UINT executionPeriod);
	void Stop ();
	bool IsRunning () { return _timerId != -1; }

	static DWORD GetTime ();
	static void Sleep (DWORD ms);

public:
	UINT _period;	// ms
};
