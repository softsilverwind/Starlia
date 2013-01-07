#include <cstdlib>
#include <ctime>
#include <cmath>

#include <core/math.h>

namespace Starlia
{

using namespace std;

static bool initialized = false;

static void initialize()
{
	srand((unsigned int) time(NULL));
	for (int i = 0; i < 5; ++i)
		rand();

	initialized = true;
}


int randomsgn()
{
	return (rand() % 2 == 0) ? 1 : -1;
}

int randomi(int min, int max)
{
	if (!initialized)
		initialize();

	const int range = max - min + 1;

	return rand() % range + min;
}

double randomd()
{
	return ((double) rand()) / RAND_MAX;
}


double randomdUp(double mul, double div)
{
	if (!initialized)
		initialize();
	
	return 1 - (mul * randomd() / div);
}

double randomdDown(double mul, double div)
{
	if (!initialized)
		initialize();
	
	return (mul * randomd() / div);
}

Coord2i randomCoord2i(int min, int max)
{
	if (!initialized)
		initialize();

	const int range = max - min + 1;

	return Coord2i(rand() % range + min, rand() % range + min);
}

Coord3i randomCoord3i(int min, int max)
{
	if (!initialized)
		initialize();

	const int range = max - min + 1;

	return Coord3i(rand() % range + min, rand() % range + min, rand() % range + min);
}

double angleOf(Coord2f start, Coord2f end)
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

double length(Coord2f start, Coord2f end)
{
	return sqrt((end.x - start.x) * (end.x - start.x) + (end.y - start.y) * (end.y - start.y));
}

double dmod(double first, int second)
{
	double ipart;
	double dpart = modf(first, &ipart);

	return (int) first % (int)second + dpart;
}

Coord2f polarToXY(double radius, double angle)
{
	return Coord2f(radius*cos(angle), radius*sin(angle));
}

Coord2f polarToXY(Polar2f pol)
{
	return polarToXY(pol.r, pol.a);
}

}
