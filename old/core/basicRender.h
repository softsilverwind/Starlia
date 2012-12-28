#ifndef __BASICRENDER_H__
#define __BASICRENDER_H__

#include <vector>
#include "structs.h"
#include "core.h"

#define POINTS 256
#define step (2 * M_PI / POINTS)

namespace Starlia
{

class Circle
{
	private:
		static bool initialized;
		static Coord2d vertex[POINTS];
		static void prepare();

	public:
		static void draw(Color3f color);

	private:
		Circle() = delete;
};

class Line
{
	public:
		static void draw(Coord2d start, Coord2d end, Color3f color, unsigned int thickness = 1);
};

class VectorLetter
{
	private:
		static bool initialized;
		static vector<Coord2d> character[128];
		static void prepare();

	public:
		static void writeCharacter(unsigned char);

	private:
		VectorLetter() = delete;
};

}

#endif /* __BASICRENDER_H__ */
