#include "StdAfx.h"
#include "robot object.h"



PUPPET::PUPPET(void)
{
	this->Reset();
}

PUPPET::~PUPPET(void)
{
}

void PUPPET::Copy( PUPPET fr)
{
	this->point.x	= fr.point.x;
	this->point.y	= fr.point.y;
	this->theta		= fr.theta;

	this->body_radius = fr.body_radius;
	this->head_radius = fr.head_radius;
	this->neck_length = fr.neck_length;

	this->w		= fr.w;
	this->v		= fr.v;
	
	this->body_color.R	= fr.body_color.R;
	this->body_color.G	= fr.body_color.G;
	this->body_color.B	= fr.body_color.B;

	this->head_color.R	= fr.head_color.R;
	this->head_color.G	= fr.head_color.G;
	this->head_color.B	= fr.head_color.B;
}

void PUPPET::Reset()
{
	point.x = 0;
	point.y = 0;
	theta = 0;

	v = 0;
	w = 0;

	body_radius = ROBOT_RADIUS;
	head_radius = HEAD_RADIUS;
	neck_length = NECK_LENGTH;

	body_color.R = rand() % 256;
	body_color.G = rand() % 256;
	body_color.B = rand() % 256;

	head_color.R = rand() % 256;
	head_color.G = rand() % 256;
	head_color.B = rand() % 256;

	ch.etc		= IDLE;
	ch.level	= IDLE;
	ch.main		= IDLE;
	ch.sub		= IDLE;
	ch.type		= IDLE;
}

bool PUPPET::isMeet(PUPPET *p)
{
	if( Get_Length(this->point, p->point) < (this->body_radius + p->body_radius))
	{//두 점 사이의 거리가 반지름의 합보다 짧으면 만난 것이다. 
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

bool PUPPET::isMeet(CPoint p)
{
	if( Get_Length(this->point, p) < this->body_radius )
	{//두 점 사이의 거리가 반지름의 합보다 짧으면 만난 것이다. 
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


void PUPPET::SetV(double v_in)
{
	v = v_in;
	if(v >= V_MAX)	v = V_MAX;
	if(v <= -V_MAX)	v = -V_MAX;

	
}

void PUPPET::SetW(double w_in)
{
	w = w_in;
	if(w >= W_MAX)	w = W_MAX;
	if(w <= -W_MAX)	w = -W_MAX;

}










ROBOT_OBJECTS:: ROBOT_OBJECTS(void)
{
	for(int i=0;i<MAX_ROBOT_COUNT;i++)
	{
		robots[i].point.x = (LONG)0.0;
		robots[i].point.y = (LONG)0.0;
		robots[i].theta = 0.0;
	}
	robot_count = 0;
}

ROBOT_OBJECTS:: ~ROBOT_OBJECTS(void)
{

}


void ROBOT_OBJECTS::Update()
{
	for(int i=0; i<robot_count; i++)
	{

		if( abs( robots[i].point.x ) > MAX_STAGE_HALF_LENGTH || abs( robots[i].point.y ) > MAX_STAGE_HALF_LENGTH )
		{//영역을 벗어나려고 하면 위치를 강제로. 
			double dis2go = 10.0;
			robots[i].theta = _Deg(180 + robots[i].theta);
			robots[i].point.x += (LONG)(dis2go * cos(robots[i].theta));	
			robots[i].point.y += (LONG)(dis2go * sin(robots[i].theta));	
		}
		else
		{//영역 안에 있을 때 랜덤한 움직임

			robots[i].SetV(7);
			robots[i].SetW(robots[i].w += ((double)isRandom(-10,10))/1000);
		}

		for(int j=0; j<robot_count; j++)
		{//충돌 조건 
			if(j==i)	continue;
			if(robots[i].isMeet(&robots[j]))
			{//로봇과 로봇이 만났을 경우에 

				//현재는 큰놈이 작은놈을 먹도록 되어있다. -> 먹고나서 커진다. 
				if(robots[i].body_radius >= robots[j].body_radius)
				{
					robots[i].body_radius += robots[j].body_radius/3;
					robots[i].head_radius += robots[j].head_radius/3;
					robots[i].neck_length += robots[j].neck_length/3;
					Pop(j);
				}
				else
				{
					robots[j].body_radius += robots[i].body_radius/3;
					robots[j].head_radius += robots[i].head_radius/3;
					robots[j].neck_length += robots[i].neck_length/3;
					Pop(i);
				}
				continue;
			}
		}

	}
}


void ROBOT_OBJECTS::Localization()
{
	for(int i=0; i<robot_count; i++)
	{
		Localization(&robots[i]);
	}
}

void ROBOT_OBJECTS::Localization(PUPPET *p)
{
	double x_inc, y_inc, theta_inc;
	x_inc = p->v * cos(p->theta);
	y_inc = p->v * sin(p->theta);
	theta_inc = p->w;

	p->point.x += (LONG)x_inc;
	p->point.y += (LONG)y_inc;
	p->theta += theta_inc;

}


CString ROBOT_OBJECTS::Data(int i)
{
	CString out,str2add;
	out.Format("");

	str2add.Format("\r\n\r\n==== %d 번째 로봇 ====\r\n",i);
	out += str2add;

	str2add.Format(" X = %.1f\r\n Y = %.1f\r\n Theta = %.1f\r\n",(double)(robots[i].point.x), (double)(robots[i].point.y), robots[i].theta);
	out += str2add;

	str2add.Format(" v = %.3f cm/s\r\n w = %.3f deg/s\r\n", robots[i].v, robots[i].w);
	out += str2add;

	str2add.Format(" Body Rad = %.1f\r\n Head Rad = %.1f\r\n Neck Length = %.1f\r\n",robots[i].body_radius, robots[i].head_radius, robots[i].neck_length);
	out += str2add;

	str2add.Format(" Body Color: (%d, %d, %d) \r\n",robots[i].body_color.R,robots[i].body_color.G,robots[i].body_color.B);
	out += str2add;
	str2add.Format(" Head Color: (%d, %d, %d) \r\n",robots[i].head_color.R,robots[i].head_color.G,robots[i].head_color.B);
	out += str2add;
	


// 	ch.etc		= IDLE;
// 	ch.level	= IDLE;
// 	ch.main		= IDLE;
// 	ch.sub		= IDLE;
// 	ch.type		= IDLE;


	return out;

}

void ROBOT_OBJECTS::Pop(int num)
{
	if(num < robot_count)
	{
//		for(int i=0; i<num; i++)
//			robots[i].Copy(robots[i+1]);

		for(int i=num; i<robot_count-1; i++)
			robots[i].Copy(robots[i+1]);

		robot_count--;
	}
}
void ROBOT_OBJECTS::Add(double x, double y)
{
	if(robot_count < MAX_ROBOT_COUNT)
	{
		robots[robot_count].Reset();
		robots[robot_count].point.x = (LONG)x;
		robots[robot_count].point.y = (LONG)y;
		robots[robot_count].theta = (double)((rand() / 360)*D2R);
		robot_count++;
	}
}

void ROBOT_OBJECTS::Add(CPoint p)
{
	if(robot_count < MAX_ROBOT_COUNT)
	{
		robots[robot_count].Reset();
		robots[robot_count].point.x = (LONG)p.x;
		robots[robot_count].point.y = (LONG)p.y;
		robots[robot_count].theta = (double)((rand() / 360)*D2R);
		robot_count++;
	}
}

void ROBOT_OBJECTS::Add()
{
	if(robot_count < MAX_ROBOT_COUNT)
	{
		robots[robot_count].Reset();
		robots[robot_count].point.x = (LONG)(rand() % MAX_STAGE_LENGTH - MAX_STAGE_HALF_LENGTH);
		robots[robot_count].point.y = (LONG)(rand() % MAX_STAGE_LENGTH - MAX_STAGE_HALF_LENGTH);
		robots[robot_count].theta = (double)((rand() / 360)*D2R);
		robot_count++;
	}
}
