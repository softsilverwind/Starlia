#include <cstdio>
#include <GL/gl.h>
#include <starlia/starlia.h>

using namespace Starlia;

int main(int argc, char** argv)
{
	StarCore::init("Starlia test bench");

	GLfloat light_model[] = {0, 0, 0};

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_model);

	Star3dLayer *layer = new Star3dLayer(new StarCamera(Coord3d(0, -5, 0), Coord3d(0, 0, 0)));

	layer->registerObject(new Star3dObject(Coord3d(0,0,0), Coord3d(1,1,1), Coord3d(0,0,0), new StarObjModel("fruit.obj", "fruit_Sphere.bmp")));
	layer->registerObject(new StarLight(Color3f(0.7,0.7,0.7), Color3f(0.8,0.8,0.8), Color3f(0.4,0.4,0.4), Coord3d(-20,-10,10), Coord3d(0,0,0), Coord3d(0,0,0)));
	
	StarCore::registerLayer(layer);
	StarCore::loop();

	return 0;
}