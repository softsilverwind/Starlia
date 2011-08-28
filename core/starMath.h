#ifndef __M_ENGINE__
#define __M_ENGINE__

#include <cmath>
#include "structs.h"

#ifndef M_PI
        /* 
	 * cmath in linux defines Mathematical PI, but this is not a
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
Coordinate3d randomCoord3d(int min, int max);

double angleOf(Coordinate2d start, Coordinate2d end);
double length(Coordinate2d start, Coordinate2d end);
Coordinate2d polarToXY(double radius, double angle);
Coordinate2d polarToXY(Coordinate2dpolar coord);

}

#endif /* __M_ENGINE__ */
