#include <cstdlib>
#include <ctime>

#include "math.h"

namespace Starlia
{

static bool isInit = false;

static void initialize()
{
	srand((unsigned int) time(NULL));
	for (int i = 0; i < 5; ++i)
		rand();

	isInit = true;
}


double randomd()
{
	return ((double) rand()) / RAND_MAX;
}

int randomsgn()
{
	return (rand() % 2 == 0) ? 1 : -1;
}

int randomi(int min, int max)
{
	if (!isInit)
		initialize();

	const int range = max - min + 1;

	return rand() % range + min;
}

double randomdUp(double mul, double div)
{
	if (!isInit)
		initialize();
	
	return 1 - (mul * randomd() / div);
}

double randomdDown(double mul, double div)
{
	if (!isInit)
		initialize();
	
	return (mul * randomd() / div);
}

Coord3d randomCoord3d(int min, int max)
{
	if (!isInit)
		initialize();

	const int range = max - min + 1;

	return Coord3d(rand() % range + min, rand() % range + min, rand() % range + min);
}

double angleOf(Coord2d start, Coord2d end)
{
        if (end.x == start.x)
                if (end.y > start.y)
                        return M_PI / 2;
                else
                        return -M_PI / 2;
        else if (end.x >= start.x)
                return atan((end.y - start.y) / (end.x - start.x));
        else
                return atan((end.y - start.y) / (end.x - start.x)) + M_PI;
}

double length(Coord2d start, Coord2d end)
{
	return sqrt((end.x - start.x) * (end.x - start.x) + (end.y - start.y) * (end.y - start.y));
}

Coord2d polarToXY(double radius, double angle)
{
	return Coord2d(radius*cos(angle), radius*sin(angle));
}

}
