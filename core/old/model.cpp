#include <GL/gl.h>
#include <fstream>
#include <cstdio>
#include "model.h"
#include "texture.h"

using namespace std;

namespace Starlia
{

void StarModel::draw()
{
}

StarModel::~StarModel()
{
}

void Star2dModel::draw()
{
}

void Star3dModel::draw()
{
}

StarObjModel::StarObjModel(string filename, string texfile)
{
	vector<Coord3d> vertex;
	vector<Coord3d> normal;
	vector<Coord2d> texture;
	string type;

	ifstream fin(filename.c_str());
	while (fin >> type)
	{
		if (!type.compare("v"))
		{
			Coord3d v;
			fin >> v;
			vertex.push_back(v);
		}
		else if (!type.compare("vn"))
		{
			Coord3d v;
			fin >> v;
			normal.push_back(v);
		}
		else if (!type.compare("vt"))
		{
			Coord2d v;
			fin >> v;
			texture.push_back(v);
		}
		else if (!type.compare("f"))
		{
			for (int i = 0; i < 3; ++i)
			{
				int v, t, n;
				(fin >> v).ignore(1, '/');
				(fin >> t).ignore(1, '/');
				fin >> n;

				vertices.push_back(vertex[v-1]);
				textures.push_back(texture[t-1]);
				normals.push_back(normal[n-1]);
			}
		}
	}
	if (!texfile.empty())
		tex = genBMPTex(texfile);
	else
		tex = 0;
}

void StarObjModel::draw()
{
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, tex);

	glVertexPointer(3, GL_DOUBLE, 0, &(vertices.front()));
	glNormalPointer(GL_DOUBLE, 0, &(normals.front()));
	glTexCoordPointer(2, GL_DOUBLE, 0, &(textures.front()));

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

#ifdef __STAROBJ_PRINT_NORMALS__

	glBegin(GL_LINES);

	for (int i = 0; i < (int) vertices.size(); ++i)
	{
		glColor3f(1,0,0);
		glVertex3d(vertices[i].x, vertices[i].y, vertices[i].z);
		glColor3f(0,1,0);
		glVertex3d(vertices[i].x + normals[i].x, vertices[i].y + normals[i].y, vertices[i].z + normals[i].z);
	}
	glEnd();

#endif /* __STAROBJ_PRINT_NORMALS__ */
	
}

StarObjModel::~StarObjModel()
{
	glDeleteTextures(1, &tex);
}

}
