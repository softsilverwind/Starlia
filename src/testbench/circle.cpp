#include <cstdio>
#include <starlia/starlia.h>

using namespace Starlia;

int main(int argc, char** argv)
{
	StarCore::init("Starlia test bench");

	SBasicLayer *layer = new SBasicLayer();

	layer->add(new SCircle(Coord2d(400,300), Coord2d(100,100), Color3f(1,0,1)));
	
	StarCore::addFront(layer);
	StarCore::loop();

	return 0;
}
