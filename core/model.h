#ifndef __STARMODEL_H__
#define __STARMODEL_H__

#include <iostream>
#include <vector>
#include "structs.h"

using namespace std;

namespace Starlia
{

class StarModel
{
	public:
		virtual void draw();
};

class Star2dModel : public StarModel
{
	public:
		virtual void draw();
};

class Star3dModel : public StarModel
{
	public:
		virtual void draw();
};

class StarObjModel : public Star3dModel
{
	private:
		typedef struct
		{
			Coordinate3d a, b, c;
		}
		Triangle;

		vector<Triangle> triangles;

	public:
		virtual void draw();

		StarObjModel(string filename);
};

}

#endif /* __STARMODEL_H__ */
