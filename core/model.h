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

		virtual ~StarModel();
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
		vector<Coord3d> vertices;
		vector<Coord3d> normals;
		vector<Coord2d> textures;

		unsigned int tex;

	public:
		virtual void draw();

		StarObjModel(string filename, string texfile);
		~StarObjModel();
};

}

#endif /* __STARMODEL_H__ */
