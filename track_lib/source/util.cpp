#include "../include/as_alg_private.h"
AsRect  asRect(int x, int y, int width, int height)
{
	AsRect r;

	r.x = x;
	r.y = y;
	r.width = width;
	r.height = height;

	return r;
}
static  AsPoint  asPoint(int x, int y)
{
	AsPoint p;

	p.x = x;
	p.y = y;

	return p;
}