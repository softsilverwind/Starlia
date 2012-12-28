#include <cstdio>
#include <starlia/starlia.h>

using namespace Starlia;

int main(int argc, char** argv)
{
	StarCore::init("Starlia test bench");

	Star2dObjectLayer *layer = new Star2dObjectLayer(Coord2d(800, 600));

	layer->registerObject(new Star2dObject(Coord2d(400,300), Coord2d(100,100), 0, new Circle(Color3f(0.5,0,0.75))));
	
	StarCore::registerLayerForeground(layer);
	StarCore::loop();

	return 0;
}
