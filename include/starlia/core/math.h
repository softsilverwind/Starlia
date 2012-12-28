#ifndef __MATH_H__
#define __MATH_H__

#include <cmath>

#include <starlia/core/structs.h>

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

Coord2d randomCoord2d(int min, int max);

Coord3d randomCoord3d(int min, int max);

double angleOf(Coord2d start, Coord2d end);

double length(Coord2d start, Coord2d end);

Coord2d polarToXYd(double radius, double angle);

}

#endif
