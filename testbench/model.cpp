#include <cstdio>
#include "starlia.h"

using namespace Starlia;

int main(int argc, char** argv)
{
	StarCore::init("Starlia test bench");

	Star3dLayer *layer = new Star3dLayer();

	layer->registerObject(new Star3dObject(Coordinate3d(0,0,0), Coordinate3d(1,1,1), new StarObjModel("head.obj")));
	
	StarCore::registerLayer(layer);
	StarCore::loop();

	return 0;
}
