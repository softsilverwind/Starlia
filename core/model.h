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
		vector<Coordinate3d> vertices;
		vector<Coordinate3d> normals;
		vector<Coordinate2d> textures;

	public:
		virtual void draw();

		StarObjModel(string filename);
};

}

#endif /* __STARMODEL_H__ */
