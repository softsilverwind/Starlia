#include <GL/gl.h>
#include "starlia.h"

using namespace Starlia;

class CoordDisp: public StarObject
{
	void draw()
	{
		glBegin(GL_LINES);

		for (int i = 0; i < 800; i += 50)
		{
			glColor3f(0.001 * i, 0, 0);
			glVertex2d(i, 0);
			glVertex2d(i, 600);
		}

		for (int i = 0; i < 600; i += 50)
		{
			glColor3f(0, 0.001 * i, 0);
			glVertex2d(0, i);
			glVertex2d(800, i);
		}

		glEnd();
	}
};

int main(int argc, char** argv)
{
	StarCore::init("Starlia test bench");

	Star2dObjectLayer *layer = new Star2dObjectLayer(Coordinate2d(800, 600));

	layer->registerObject(new CoordDisp());
	
	StarCore::registerLayerForeground(layer);
	StarCore::loop();

	return 0;
}
