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

double angleOf(Coord2f start, Coord2f end);

double length(Coord2f start, Coord2f end);

double dmod(double first, int second);
double clamp(double operand, double dlimit, double ulimit);

Coord2f polarToXY(double radius, double angle);
Coord2f polarToXY(Polar2f pol);

template<typename T> int8_t sign(T arg);

#include "math.inl"

}

#endif
