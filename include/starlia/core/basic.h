#ifndef __BASIC_H__
#define __BASIC_H__

#include <starlia/core/layer.h>
#include <starlia/core/structs.h>

#define POINTS 256
#define step (2 * M_PI / POINTS)

namespace Starlia
{

// for type safety reasons
class SBasicObject : public SObject
{
};

class SBasicLayer : public SListLayer<SBasicObject>
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


class SCircle : public SBasicObject
{
	private:
		static bool initialized;
		static vector<Coord2d> vertices;

		static void initialize();

		Coord2d position;
		Coord2d scale;
		Color3f color;

	public:
		void draw();
		SCircle(Coord2d position, Coord2d scale, Color3f color);
};

}

#endif
