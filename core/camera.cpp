#include <GL/glu.h>
#include "core.h"
#include "camera.h"

namespace Starlia
{

void StarCamera::draw()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, StarCore::getScale().x / StarCore::getScale().y, 1, 10000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotated(-90,1,0,0);
	glRotated(-angle.y,0,1,0);
	glRotated(-angle.x,1,0,0);
	glRotated(-angle.z,0,0,1);
	glTranslated(-position.x, -position.y, -position.z);
}

StarCamera::StarCamera(Coord3d position, Coord3d angle)
	: Star3dObject(position, Coord3d(), angle)
{
}

}
