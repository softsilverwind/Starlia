#include <memory>
#include <cstdio>
#include <starlia/starlia.h>

using namespace Starlia;
using namespace std;

class MyLayer : public SBasicColorLayer
{
	protected:
		virtual bool eventClick(Coord2f) override;

	public:
		MyLayer(SCamera *camera);
};

bool MyLayer::eventClick(Coord2f pos)
{
	cout << pos << endl;
	cout << static_pointer_cast<SOrthoCamera>(camera)->unproject(pos) << endl;
	return true;
}

MyLayer::MyLayer(SCamera *camera)
	: SBasicColorLayer(camera)
{
}

shared_ptr<MyLayer> layer;

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

int main()
{
	StarCore::init("Starlia test bench");
	SOrthoCamera *cam = new SOrthoCamera(Coord2f(400,300), Coord2f(400, 300));
	layer = make_shared<MyLayer>(cam);

	layer->addKeyPress('w', [cam]{ cam->move(Coord2f(0, -42)); });
	layer->addKeyPress('a', [cam]{ cam->move(Coord2f(-42, 0)); });
	layer->addKeyPress('s', [cam]{ cam->move(Coord2f(0, 42)); });
	layer->addKeyPress('d', [cam]{ cam->move(Coord2f(42, 0)); });
	layer->addKeyPress('q', [cam]{ cam->zoom(2); });
	layer->addKeyPress('e', [cam]{ cam->zoom(0.5); });

	StarCore::addFront(layer);
	STimer::registerTimer(10, createSatellite);
	StarCore::loop();

	return 0;
}
