#include <GL/gl.h>
#include "starlia.h"

using namespace Starlia;

Star3dObject *myObj;

void keyboard(int key)
{
	Coordinate3d angvel(0,0,0);
	Coordinate3d vel(0,0,0);
	switch (key)
	{
		case 'w':
			angvel.x = 1;
			break;
		case 'a':
			angvel.z = 1;
			break;
		case 's':
			angvel.x = -1;
			break;
		case 'd':
			angvel.z = -1;
			break;
		case 'q':
			angvel.y = -1;
			break;
		case 'e':
			angvel.y = 1;
			break;
		default:
			return;
	}
	myObj->setAngVelocity(angvel);
}

void keyboardup(int key)
{
	myObj->setAngVelocity(Coordinate3d(0,0,0));
}

int main(int argc, char** argv)
{
	StarCore::init("Starlia test bench");

	GLfloat light_model[] = {0, 0, 0};

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_model);

	Star3dLayer *layer = new Star3dLayer(new StarCamera(Coordinate3d(0, -5, 1), Coordinate3d(0, 0, 0)));

	layer->registerObject(myObj = new Star3dObject(Coordinate3d(0,0,0), Coordinate3d(1,1,1), Coordinate3d(0,0,0), new StarObjModel("fruit.obj", "fruit_Sphere.bmp")));
	layer->registerObject(new StarLight(Color3f(0.7,0.7,0.7), Color3f(0.8,0.8,0.8), Color3f(0.4,0.4,0.4), Coordinate3d(5,-2,-2), Coordinate3d(0,0,0), Coordinate3d(0,0,0)));
	
	layer->registerKeyPress('w', keyboard, 'w');
	layer->registerKeyPress('a', keyboard, 'a');
	layer->registerKeyPress('s', keyboard, 's');
	layer->registerKeyPress('d', keyboard, 'd');
	layer->registerKeyPress('q', keyboard, 'q');
	layer->registerKeyPress('e', keyboard, 'e');
	layer->registerKeyRelease('w', keyboardup, 'w');
	layer->registerKeyRelease('a', keyboardup, 'a');
	layer->registerKeyRelease('s', keyboardup, 's');
	layer->registerKeyRelease('d', keyboardup, 'd');
	layer->registerKeyRelease('q', keyboardup, 'q');
	layer->registerKeyRelease('e', keyboardup, 'e');

	StarCore::registerLayer(layer);
	StarCore::loop();

	return 0;
}
