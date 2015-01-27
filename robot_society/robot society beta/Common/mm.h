#pragma once
#include <math.h>

#ifndef M_PI
#define M_PI		3.14159265358979323846	// pi 
#endif

#define _RAD2DEG	(180./M_PI)
#define _DEG2RAD	(M_PI/180.)

inline double DeltaRad (double ang1, double ang2)
{
	double da = ang1 - ang2;
	if (-M_PI < da && da < M_PI) return da;
	else {
		da = fmod (da, 2*M_PI);
		if (M_PI <= da) return da - 2*M_PI;
		else if (da <= -M_PI) return da + 2*M_PI;
		else return da;
	}
	return da;
}

inline int INTEGER (const double a)
{
	// return (long)floor (a + 0.5);
	return (0 < a)? (int)(a + 0.5) : (int)(a - 0.5);
}

inline double Distance (double x1, double y1, double x2, double y2)
{
	double dx = x2 - x1;
	double dy = y2 - y1;

	return sqrt (dx*dx + dy*dy);
}

template<typename T>
inline T bound(T x, T l, T u)
{
	if (x <= l) return l;
	if (x >= u) return u;
	return x;
}
