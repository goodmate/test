#pragma once

#define ROBOT_RADIUS	15		//�κ��� ������
#define HEAD_RADIUS		9		//�κ� �Ӹ��� ������
#define NECK_LENGTH		-6		//�κ��� �� ����

#define MAX_ROBOT_COUNT	1000		//��ü �κ��� ��

#define MAX_STAGE_LENGTH		2000	//���ƴٴ� ������ �ִ� ����
#define MAX_STAGE_HALF_LENGTH	(MAX_STAGE_LENGTH/2)

#define V_MAX		(double)30
#define W_MAX		(double)0.04

// type
#define IDLE		0
// level

// main

// sub

// etc





#include "parameters.h"
#include "basic_function.h"


typedef struct tRGB_DATA
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
}RGB_DATA;

typedef struct CHARACTOR
{
	unsigned char type;
	unsigned char level;
	unsigned char main;
	unsigned char sub;
	unsigned char etc;
}CHARACTOR;

class PUPPET 
{
public:
	PUPPET(void);
	~PUPPET(void);

	void Copy(PUPPET fr);
	void Reset();
	bool isMeet(PUPPET *p);
	bool isMeet(CPoint p);
	
	void SetV(double v_in);
	void SetW(double w_in);

public:
	CPoint point;
	double theta;
	double v,w;

	double body_radius;
	double head_radius;
	double neck_length;

	RGB_DATA head_color;
	RGB_DATA body_color;
	

	CHARACTOR ch;
	
};

class ROBOT_OBJECTS
{
public:
	ROBOT_OBJECTS(void);
	~ROBOT_OBJECTS(void);


	void Localization();
	void Update();
	

	void Pop(int num);

	void Add(double x, double y);
	void Add(CPoint p);
	void Add();
	
	

	CString Data(int i);

private:
	void Localization(PUPPET *p);

public:
	PUPPET robots[MAX_ROBOT_COUNT];
	int robot_count;

};
