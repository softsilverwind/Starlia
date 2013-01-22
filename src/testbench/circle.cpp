#include <cstdio>
#include <starlia/starlia.h>

using namespace Starlia;

int main()
{
	StarCore::init("Starlia test bench");

	SBasicColorLayer *layer = new SBasicColorLayer();
	layer->add(new S2dObject(Coord2f(0.3, 0.3), Coord2f(0.6,0.8), 0, new SCircle(Color3f(0.6,0,0.8))));
	layer->add(new S2dObject(Coord2f(-0.3, -0.3), Coord2f(0.6,0.8), 0, new SCircle(Color3f(0,0.6,0))));

	StarCore::addFront(layer);
	StarCore::loop();

	return 0;
}
