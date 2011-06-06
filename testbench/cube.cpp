#include <GL/glut.h>
#include <starlia.h>

using namespace Starlia;

class Cube : public StarObject
{
	public:
		virtual void draw();
};

void Cube::draw()
{
	glColor3d(0,0,1);
	glRotated(45,0,0,1);
	glRotated(30,1,0,0);

	glutWireCube(1);

}

int main()
{
	StarCore::init("Starlia test bench");

	Star3dLayer *layer = new Star3dLayer();

	layer->registerObject(new Cube());
	
	StarCore::registerLayer(layer);
	StarCore::loop();

	return 0;
}
