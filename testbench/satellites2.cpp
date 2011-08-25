#include <GL/gl.h>
#include <cstdio>
#include "starlia.h"

using namespace Starlia;

Star2dObjectLayer *layer1;
Star2dObjectLayer *layer2;

class Satellite : public StarObject
{
	private:
		Coordinate2d center;
		Coordinate2dpolar position;
		double radius;
		Color3f color;
		double rad_velocity;
		int life;

	public:
		Satellite(Coordinate2d center, Coordinate2dpolar position, double radius, Color3f color, double rad_vel, int life);
		bool recalc();
		void draw();
};

Satellite::Satellite(Coordinate2d center, Coordinate2dpolar position, double radius, Color3f color, double rad_velocity, int life)
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

void createSatellite()
{
	if (randomi(0,1))
		layer1->registerObject(new Satellite(Coordinate2d(400,300), Coordinate2dpolar(randomi(100,200), randomd() * 2 * M_PI), 8, Color3f(1,0,0), randomd() / 100, randomi(500, 1000)), NULL);
	else
		layer2->registerObject(new Satellite(Coordinate2d(200,150), Coordinate2dpolar(randomi(50,100), randomd() * 2 * M_PI), 4, Color3f(0,0,1), randomd() / 100, randomi(500, 1000)), NULL);
	StarTimer::registerTimer(10, createSatellite);
}

int main(int argc, char** argv)
{
	StarCore::init("Starlia test bench");
	layer1 = new Star2dObjectLayer(Coordinate2d(800, 600));
	layer2 = new Star2dObjectLayer(Coordinate2d(400, 300));
	StarCore::registerLayerForeground(layer1);
	StarCore::registerLayerForeground(layer2);
	StarTimer::registerTimer(10, createSatellite);
	StarCore::loop();

	return 0;
}
