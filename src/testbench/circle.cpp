#include <cstdio>
#include <starlia/starlia.h>

using namespace Starlia;

int main(int argc, char** argv)
{
	StarCore::init("Starlia version " STARLIA_VERSION_STRING " test bench");

	SBasicLayer *layer = new SBasicLayer();
	layer->add(new S2dObject(Coord2f(0.3, 0.3), Coord2f(0.6,0.8), 0, new SCircle(Color3f(0.6,0,0.8))));
	layer->add(new S2dObject(Coord2f(-0.3, -0.3), Coord2f(0.6,0.8), 0, new SCircle(Color3f(0,0.6,0))));

	StarCore::addFront(layer);
	StarCore::loop();

	return 0;
}
