#ifndef __M_ENGINE__
#define __M_ENGINE__

#include <cmath>
#include "structs.h"

#ifndef M_PI
	/* 
	 * cmath in linux defines pi, but this is not a
	 * standard, so Visual Studio does not.
	 */
	#define M_PI 3.14159 
#endif

namespace Starlia
{

double randomd();
int randomsgn();
int randomi(int min, int max);
double randomdUp(double mul, double div);
double randomdDown(double mul, double div);
Coord3d randomCoord3d(int min, int max);

double angleOf(Coord2d start, Coord2d end);
double length(Coord2d start, Coord2d end);
Coord2d polarToXY(double radius, double angle);

}

#endif /* __M_ENGINE__ */
