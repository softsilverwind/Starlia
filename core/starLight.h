#ifndef __STARLIGHT_H__
#define __STARLIGHT_H__

#include <GL/gl.h>
#include "object.h"
#include "model.h"

namespace Starlia
{

// Far away, this ship has taken me far away...
class StarLight : public Star3dObject
{
	private:
		Color3f specular;
		Color3f diffuse;
		Color3f ambient;
		GLenum lightNum;

		void setLightNum(GLenum x) { lightNum = x; }
		GLenum getLightNum() { return lightNum; }

	protected:
		void prepLight();

	public:
		StarLight(Color3f specular, Color3f diffuse, Color3f ambient, Coordinate3d position, Coordinate3d halfsize, Coordinate3d angle, Star3dModel *model = NULL);

	friend class Star3dLayer;
};

}
#endif /* __STARLIGHT_H__ */
