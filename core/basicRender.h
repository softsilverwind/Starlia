#ifndef __BASICRENDER_H__
#define __BASICRENDER_H__

#include <vector>
#include "structs.h"
#include "core.h"

#define POINTS 256
#define step (2 * M_PI / POINTS)

namespace Starlia
{

class Circle : public Star2dModel
{
	private:
		static bool initialized;
		static Coordinate2d vertex[POINTS];
		Color3d color;

	public:
		static void prepare();
		static void draw(Color3d color);
		
		void draw();
		Circle(Color3d color);
};


class Line
{
	public:
		static void draw(Coordinate2d start, Coordinate2d end, Color3d color, unsigned int thickness = 1);
};

class VectorLetter
{
	private:

		static bool initialized;
		static vector<Coordinate2d> character[128];


	public:

		static void writeCharacter(unsigned char);
		static void prepare();
};

}

#endif /* __BR_ENGINE_H__ */
