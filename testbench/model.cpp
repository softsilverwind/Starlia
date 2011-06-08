#include <cstdio>
#include <GL/gl.h>
#include "starlia.h"

using namespace Starlia;

int main(int argc, char** argv)
{
	StarCore::init("Starlia test bench");

	GLfloat light_specular[] = {0.7,0.7,0.7};
	GLfloat light_diffuse[] = {0.8,0.8,0.8};
	GLfloat light_ambient[] = {0.4,0.4,0.4};
	GLfloat light_position[] = {-5, 2, 2, 1.0};
	GLfloat light_model[] = {0, 0, 0};

	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0,GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0,GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0,GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_model);

	Star3dLayer *layer = new Star3dLayer();

	layer->registerObject(new Star3dObject(Coordinate3d(0,0,0), Coordinate3d(1,1,1), new StarObjModel("head.obj")));
	
	StarCore::registerLayer(layer);
	StarCore::loop();

	return 0;
}
