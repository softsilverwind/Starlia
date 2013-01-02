#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <starlia/core/object.h>

namespace Starlia
{

class SCamera : public S3dDynObject
{
	protected:
		void draw();

	public:
		SCamera(Coord3d position, Coord3d angle);

	friend class SObjectLayer;
};

}

#endif
