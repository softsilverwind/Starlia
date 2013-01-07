#include <memory>
#include <cstdio>
#include <starlia/starlia.h>

using namespace Starlia;
using namespace std;

shared_ptr<SBasicLayer> layer;

class Satellite : public S2dObject
{
	private:
		Coord2f center;
		Polar2f offset;
		double rad_velocity;
		int life;

	public:
		Satellite(Coord2f center, Polar2f offset, double radius, Color3f color, double rad_vel, int life);
		virtual void update() override;
};

Satellite::Satellite(Coord2f center, Polar2f offset, double radius, Color3f color, double rad_velocity, int life)
	: S2dObject(Coord2f(0,0), Coord2f(radius, radius), 0, new SCircle(color)), center(center), offset(offset), rad_velocity(rad_velocity), life(life)
{
	position = center + polarToXY(offset);
}

void Satellite::update()
{
	offset.a += rad_velocity;
	position = center + polarToXY(offset);

	if (--life <= 0)
		invalid = true;
}

void createSatellite()
{
	layer->add(new Satellite(Coord2f(400,300), Polar2f(randomi(100,200), randomd() * 2 * M_PI), 5, Color3f(randomd(), randomd(), randomd()), randomd() / 100, randomi(500, 1000)));
	STimer::registerTimer(10, createSatellite);
}

int main(int argc, char** argv)
{
	StarCore::init("Starlia test bench");
	layer = make_shared<SBasicLayer>(Coord2f(0,0), Coord2f(800, 600));
	StarCore::addFront(layer);
	STimer::registerTimer(10, createSatellite);
	StarCore::loop();

	return 0;
}
