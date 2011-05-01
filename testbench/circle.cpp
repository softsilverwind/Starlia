#include <cstdio>
#include "starlia.h"

using namespace Starlia;

int main(int argc, char** argv)
{
	StarCore::init("Starlia test bench");

	StarLayer *layer = new StarLayer(Coordinate2d(800, 600));

	layer->registerObject(new Star2dObject(Coordinate2d(400,300), Coordinate2d(100,100), 0, new Circle(Color3d(0.5,0,0.75))));
	
	StarCore::registerLayerForeground(layer);
	StarCore::loop();

	return 0;
}
