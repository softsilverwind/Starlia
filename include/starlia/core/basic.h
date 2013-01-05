#ifndef __BASIC_H__
#define __BASIC_H__

#include "layer.h"
#include "structs.h"

#define POINTS 256
#define step (2 * M_PI / POINTS)

namespace Starlia
{

class SBasicLayer : public SListLayer<SObject>
{
	private:
		static bool initialized;
		static const char *v_shader;
		static const char *f_shader;
		static unsigned linked_program;

		static void initialize();

	public:
		SBasicLayer();
};


class SCircle : public SObject
{
	private:
		static bool initialized;
		static vector<Coord2d> vertices;

		static void initialize();

		Coord2d position;
		Coord2d radius;
		Color3f color;

	public:
		SCircle(Coord2d position, Coord2d radius, Color3f color);

		void draw();
};

}

#endif
