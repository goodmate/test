#include "basic_function.h"


double Get_Length(double x1, double y1, double x2, double y2)
{
	return sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
}

double Get_Length(CPoint p1, CPoint p2)
{
	return Get_Length(p1.x, p1.y, p2.x, p2.y);
}

bool isPercent(int p)
{//p % 확률로 true를 return한다.
	int n = rand() % 101;	//0~100까지

	if(p >= n)	return TRUE;
	else		return FALSE;
}

int isRandom(int fr, int to)
{//fr~to사이의 값을 랜덤하게. 
	int diff = to - fr + 1;
	int r_zero2diff = rand() % diff;
	int r = fr + r_zero2diff;
	if(r >= to)	return to;
	if(r <= fr)	return fr;	
	return r;	
}

double _Deg(double t)
{
	double r = t;
	while(1)
	{
		if(t>360)
			t -= 360;
		else if(t<0)
			t += 360;
		else
			break;
	}
	return r;
}
