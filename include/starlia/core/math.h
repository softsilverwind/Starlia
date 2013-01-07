#ifndef __MATH_H__
#define __MATH_H__

#include <cmath>

#include "structs.h"

#ifndef M_PI
	#define M_PI 3.14159 
#endif

namespace Starlia
{

int randomsgn();
int randomi(int min, int max);
double randomd();

double randomdUp(double mul, double div);
double randomdDown(double mul, double div);

Coord2i randomCoord2i(int min, int max);

Coord3i randomCoord3i(int min, int max);

double angleOf(Coord2f start, Coord2i end);

double length(Coord2f start, Coord2i end);

double dmod(double first, int second);

Coord2f polarToXY(double radius, double angle);
Coord2f polarToXY(Polar2f pol);

}

#endif
