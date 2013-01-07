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


class SCircle : public SModel
{
	private:
		static bool initialized;
		static vector<Coord2d> vertices;

		static void initialize();

		Color3f color;

	public:
		SCircle(Color3f color);

		virtual void draw(SLayer *) override;
};

}

#endif
