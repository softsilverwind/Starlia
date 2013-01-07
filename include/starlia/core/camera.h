#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "object.h"

namespace Starlia
{

class SCamera : public S3dDynObject
{
	protected:
		void draw();

	public:
		SCamera(Coord3f position, Coord3f angle);

	friend class SObjectLayer;
};

}

#endif
