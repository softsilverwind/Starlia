#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "object.h"

namespace Starlia
{

class StarCamera : public Star3dObject
{
	protected:
		void draw();

	public:
		StarCamera(Coord3d position, Coord3d angle);

	friend class Star3dLayer;
};

}

#endif /* __CAMERA_H__ */
