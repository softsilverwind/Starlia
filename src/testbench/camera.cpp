#include <starlia/starlia.h>

using namespace Starlia;

shared_ptr<SPerspCamera> camera;

void keyboard(int key)
{
	Coord3d angvel(0,0,0);
	Coord3d vel(0,0,0);
	switch (key)
	{
		case 'w':
			angvel.x = 0.01;
			break;
		case 'a':
			angvel.z = 0.01;
			break;
		case 's':
			angvel.x = -0.01;
			break;
		case 'd':
			angvel.z = -0.01;
			break;
		case 'q':
			angvel.y = -0.01;
			break;
		case 'e':
			angvel.y = 0.01;
			break;
		case 'z':
			vel.y = 0.1;
			break;
		case 'c':
			vel.y = -0.1;
			break;
		default:
			return;
	}
	camera->setAngVelocity(angvel);
	camera->setVelocity(vel);
}

void keyboardup(int)
{
	camera->setAngVelocity(Coord3d(0,0,0));
	camera->setVelocity(Coord3d(0,0,0));

	cerr << camera->getPosition() << camera->getAngle() << endl;
}

int main()
{
	StarCore::init("Starlia test bench");

	SBasicColorLayer *layer = new SBasicColorLayer(camera = make_shared<SPerspCamera>(Coord3f(0, 0, 5), Coord3f(0, 0, 0)));
	layer->add(new S2dObject(Coord2f(0.3, 0.3), Coord2f(0.6,0.6), 0, new SCircle(Color3f(0.6,0,0.8))));
	layer->add(new S2dObject(Coord2f(-0.3, -0.3), Coord2f(0.6,0.6), 0, new SCircle(Color3f(0,0.6,0))));
	layer->add(new S3dObject(Coord3f(0, 5, 5), Coord3f(1.4,1.4,1.4), Coord3f(90,0,0), new SCircle(Color3f(0.8,0.6,0))));

	for (char c : { 'w', 'a', 's', 'd', 'q', 'e', 'c', 'z' })
	{
		layer->addKeyPress(c, [c](){ cerr << "press: " << c << endl; keyboard(c); });
		layer->addKeyRelease(c, [c](){ cerr << "release: " << c << endl; keyboardup(c); });
	}

	StarCore::addFront(layer);
	StarCore::loop();

	return 0;
}
