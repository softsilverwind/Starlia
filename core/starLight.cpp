#include "structs.h"
#include "starLight.h"

namespace Starlia
{
	
StarLight::StarLight(Color3f specular, Color3f diffuse, Color3f ambient, Coordinate3d pos, Coordinate3d halfsize, Coordinate3d angle, Star3dModel *model)
	: Star3dObject(pos, halfsize, angle, model), specular(specular), diffuse(diffuse), ambient(ambient)
{
}


void StarLight::prepLight()
{
	glEnable(lightNum);

	float pos[4] = { position.x, position.y, position.z, 1 };

	glLightfv(lightNum, GL_SPECULAR, (float *) &specular);
	glLightfv(lightNum, GL_DIFFUSE, (float *) &diffuse);
	glLightfv(lightNum, GL_AMBIENT, (float *) &ambient);
	glLightfv(lightNum, GL_POSITION, pos);
}

}
