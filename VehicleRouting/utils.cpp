#include"utils.h"
#include<math.h>


float dist(int x1, int y1, int x2, int y2)
{
	int xdiff, ydiff;
	xdiff = x1 - x2;
	ydiff = y1 - y2;
	return sqrtf(xdiff * xdiff + ydiff * ydiff);
}

float angle(int x, int y)
{
	if (x > 0) {
		if (y > 0) 
			return atan2f(y, x) * 180 / PI;
		else 
			return 360 - atan2f(-y, x) * 180 / PI;
	}
	else {
		if (y > 0) 
			return 180 - atan2f(y, -x) * 180 / PI;
		else
			return 180 + atan2f(-y, -x) * 180 / PI;
	}
}
