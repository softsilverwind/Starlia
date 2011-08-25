#include <GL/gl.h>
#include <cstdio>
#include <cstdlib>
#include "starlia.h"

using namespace Starlia;

Star3dLayer *layer;

class Satellite : public Star3dObject
{
	private:
		Coordinate2d center;
		Coordinate2dpolar posp;
		double radius;
		Color3f color;
		double rad_velocity;
		int life;

	public:
		Satellite(Coordinate2d center, Coordinate2dpolar posp, double radius, Color3f color, double rad_vel, int life);
		bool recalc();
		void draw();
};

Satellite::Satellite(Coordinate2d center, Coordinate2dpolar posp, double radius, Color3f color, double rad_velocity, int life)
	: Star3dObject(Coordinate3d(0,0,0), Coordinate3d(5,5,5), Coordinate3d(0,0,0), new StarObjModel("fruit.obj", "fruit_Sphere.bmp")), center(center), posp(posp), radius(radius), color(color), rad_velocity(rad_velocity), life(life)
{
}

bool Satellite::recalc()
{
	posp.a += rad_velocity;
	Coordinate2d pos = center + polarToXY(posp);
	position.x = pos.x;
	position.y = pos.y;

	--life;
	return life > 0;
}

void Satellite::draw()
{
	Star3dObject::draw();
}

void createSatellite()
{
	layer->registerObject(new Satellite(Coordinate2d(400,300), Coordinate2dpolar(randomi(100,200), randomd() * 2 * M_PI), 5, Color3f(randomd(), randomd(), randomd()), randomd() / 100, randomi(500, 5000)));
	StarTimer::registerTimer(10, createSatellite);
}

int main(int argc, char** argv)
{
	StarCore::init("Starlia test bench");

	GLfloat light_model[] = {0, 0, 0};

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_model);

	layer = new Star3dLayer(Coordinate3d(400, 0, -50), Coordinate3d(400,300,0), Coordinate3d(0,1,0));
	layer->registerObject(new StarLight(Color3f(0.7,0.7,0.7), Color3f(0.8,0.8,0.8), Color3f(0.4,0.4,0.4), Coordinate3d(400,300,-1000), Coordinate3d(0,0,0), Coordinate3d(0,0,0)));
	StarCore::registerLayer(layer);
	StarTimer::registerTimer(10, createSatellite);
	StarCore::loop();

	return 0;
}
