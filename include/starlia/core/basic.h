#ifndef __BASIC_H__
#define __BASIC_H__

#include "layer.h"
#include "structs.h"

#define POINTS 256
#define step (2 * M_PI / POINTS)

namespace Starlia
{

class SBasicColorLayer : public SListLayer<SObject>
{
	private:
		static bool initialized;
		static const char *v_shader;
		static const char *f_shader;
		static unsigned linked_program;

		static void initialize();

		shared_ptr<SCamera> camera;

	protected:
		virtual void draw() override;

	public:
		SBasicColorLayer(shared_ptr<SCamera> camera);
		SBasicColorLayer(SCamera *camera = new SOrthoCamera(Coord2f(-1, -1), Coord2f(1, 1)));
};

class SBasicObjectLayer : public SListLayer<SObject>
{
	private:
		static bool initialized;
		static const char *v_shader;
		static const char *f_shader;
		static unsigned linked_program;

		static void initialize();

		shared_ptr<SCamera> camera;

	protected:
		virtual void draw() override;

	public:
		SBasicObjectLayer(shared_ptr<SCamera> camera);
		SBasicObjectLayer(SCamera *camera = new SOrthoCamera(Coord2f(-1, -1), Coord2f(1, 1)));
};


class SCircle : public SModel
{
	private:
		static bool initialized;
		static vector<Coord2f> vertices;

		static void initialize();

		Color3f color;

	public:
		SCircle(Color3f color);

		virtual void draw(SLayer *) override;
};

}

#endif
