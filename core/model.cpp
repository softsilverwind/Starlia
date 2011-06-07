#include <GL/gl.h>
#include <fstream>
#include "model.h"

using namespace std;

namespace Starlia
{

void StarModel::draw()
{
}

void Star2dModel::draw()
{
}

void Star3dModel::draw()
{
}

StarObjModel::StarObjModel(string filename)
{
	vector<Coordinate3d> vertices;
	string type;
	Coordinate3d vertex;
	Triangle tri;

	ifstream fin(filename.c_str());
	while (fin >> type)
	{
		if (!type.compare("v"))
		{
			fin >> vertex;
			vertices.push_back(vertex);
		}
		else if (!type.compare("f"))
		{
			int i;
			string rest;
			fin >> i >> rest;

			tri.a = vertices[i-1];

			fin >> i >> rest;

			tri.b = vertices[i-1];

			fin >> i >> rest;

			tri.c = vertices[i-1];

			triangles.push_back(tri);
		}
	}
}

void StarObjModel::draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_DOUBLE, 0, &(triangles.front()));
	glDrawArrays(GL_TRIANGLES, 0, triangles.size() * 3);
	glDisableClientState(GL_VERTEX_ARRAY);
}

}
