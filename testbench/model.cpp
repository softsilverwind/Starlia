#include <cstdio>
#include <GL/gl.h>
#include "starlia.h"

using namespace Starlia;

int main(int argc, char** argv)
{
	StarCore::init("Starlia test bench");

	GLfloat light_model[] = {0, 0, 0};

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_model);

	Star3dLayer *layer = new Star3dLayer(Coordinate3d(0,0,-5), Coordinate3d(0,0,0), Coordinate3d(0,1,0));

	layer->registerObject(new Star3dObject(Coordinate3d(0,0,0), Coordinate3d(1,1,1), Coordinate3d(90,0,0), new StarObjModel("fruit.obj", "fruit_Sphere.bmp")));
	layer->registerObject(new StarLight(Color3f(0.7,0.7,0.7), Color3f(0.8,0.8,0.8), Color3f(0.4,0.4,0.4), Coordinate3d(5,-2,-2), Coordinate3d(0,0,0), Coordinate3d(0,0,0)));
	
	StarCore::registerLayer(layer);
	StarCore::loop();

	return 0;
}
