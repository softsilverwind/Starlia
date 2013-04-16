#include <memory>
#include <cstdio>
#include <starlia/starlia.h>

using namespace Starlia;
using namespace std;

shared_ptr<SBasicColorLayer> layer1;
shared_ptr<SBasicColorLayer> layer2;

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
	if (randomi(0,1))
		layer1->add(new Satellite(Coord2f(400,300), Polar2f(randomi(100,200), randomd() * 2 * M_PI), 5, Color3f(1,0,0), randomd() / 100, randomi(500, 1000)));
	else
		layer2->add(new Satellite(Coord2f(200,150), Polar2f(randomi(50,100), randomd() * 2 * M_PI), 5, Color3f(0,0,1), randomd() / 100, randomi(500, 1000)));
	STimer::registerTimer(10, createSatellite);
}

int main()
{
	StarCore::init("Starlia test bench");
	layer1 = make_shared<SBasicColorLayer>(new SOrthoCamera(Coord2f(400,300), Coord2f(400, 300)));
	layer2 = make_shared<SBasicColorLayer>(new SOrthoCamera(Coord2f(200,150), Coord2f(200, 150)));
	StarCore::addFront(layer1);
	StarCore::addFront(layer2);
	STimer::registerTimer(10, createSatellite);
	StarCore::loop();

	return 0;
}
