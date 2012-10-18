#include <GL/gl.h>
#include <cstdio>
#include <starlia/starlia.h>

using namespace Starlia;

Star2dObjectLayer *layer;

class Satellite : public StarObject
{
	private:
		Coord2d center;
		Polar2d position;
		double radius;
		Color3f color;
		double rad_velocity;
		int life;

	public:
		Satellite(Coord2d center, Polar2d position, double radius, Color3f color, double rad_vel, int life);
		void recalc();
		void draw();
};

Satellite::Satellite(Coord2d center, Polar2d position, double radius, Color3f color, double rad_velocity, int life)
	: center(center), position(position), radius(radius), color(color), rad_velocity(rad_velocity), life(life)
{
}

void Satellite::recalc()
{
	position.a += rad_velocity;
	if (--life <= 0)
		EMIT(_delete);
}

void Satellite::draw()
{
	glPushMatrix();
	Coord2d pos = center + polarToXY(position);
	glTranslated(pos.x, pos.y, 0);
	glScaled(radius, radius, 0);
	Circle::draw(color);
	glPopMatrix();
}

void createSatellite()
{
	layer->registerObject(new Satellite(Coord2d(400,300), Polar2d(randomi(100,200), randomd() * 2 * M_PI), 5, Color3f(randomd(), randomd(), randomd()), randomd() / 100, randomi(500, 1000)));
	StarTimer::registerTimer(10, createSatellite);
}

int main(int argc, char** argv)
{
	StarCore::init("Starlia test bench");
	layer = new Star2dObjectLayer(Coord2d(800, 600));
	StarCore::registerLayerForeground(layer);
	StarTimer::registerTimer(10, createSatellite);
	StarCore::loop();

	return 0;
}
