#include <GL/glut.h>
#include <cstdio>
#include "starlia.h"

using namespace Starlia;

StarLayer *layer;

class Satellite : public StarObject
{
	private:
		Coordinate2d center;
		Coordinate2dpolar position;
		double radius;
		Color3d color;
		double rad_velocity;
		int life;

	public:
		Satellite(Coordinate2d center, Coordinate2dpolar position, double radius, Color3d color, double rad_vel, int life);
		bool recalc();
		void draw();
};

Satellite::Satellite(Coordinate2d center, Coordinate2dpolar position, double radius, Color3d color, double rad_velocity, int life)
	: center(center), position(position), radius(radius), color(color), rad_velocity(rad_velocity), life(life)
{
}

bool Satellite::recalc()
{
	position.a += rad_velocity;
	--life;
	return life > 0;
}

void Satellite::draw()
{
	glPushMatrix();
	Coordinate2d pos = center + polarToXY(position);
	glTranslated(pos.x, pos.y, 0);
	glScaled(radius, radius, 0);
	Circle::draw(color);
	glPopMatrix();
}

void createSatellite(int _)
{
	layer->registerObject(new Satellite(Coordinate2d(400,300), Coordinate2dpolar(randomi(100,200), randomd() * 2 * M_PI), 5, Color3d(randomd(), randomd(), randomd()), randomd() / 100, randomi(500, 1000)), NULL, true, true);
	glutTimerFunc(10, createSatellite, 42);
}

int main(int argc, char** argv)
{
	StarCore::init("Starlia test bench");
	layer = new StarLayer(Coordinate2d(800, 600));
	StarCore::registerLayerForeground(layer);
	glutTimerFunc(10, createSatellite, 42);
	StarCore::loop();

	return 0;
}
