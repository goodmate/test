#pragma once
#include <vector>

using namespace std;

enum eEntityType {
	ET_NONE = 0,
	ET_LINE,
	ET_POINT,
	ET_CIRCLE,
	ET_RECT,
};

struct DXF_ENTITY_ITEM {
	eEntityType type;
	double x0, y0, z0;
	double x1, y1, z1;
};

extern int load_dxf(const char *file_name, vector<DXF_ENTITY_ITEM> *items);
