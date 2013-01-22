#include <iostream>
#include <fstream>

#include <GL/glew.h>

#include <SDL/SDL_image.h>

#include <core/model.h>
#include <core/layer.h>

#include <glm/gtc/type_ptr.hpp>

using namespace std;

namespace Starlia
{

unsigned int SModel::genTex(string filename)
{
	SDL_Surface *img = IMG_Load(filename.c_str());
	unsigned int texture;
	int mode;

	if (!img)
		return 0;

	if (img->format->BytesPerPixel == 3)
	{
		mode = GL_RGB;
	}
	else if (img->format->BytesPerPixel == 4)
	{
		mode = GL_RGBA;
	}
	else
	{
		SDL_FreeSurface(img);
		return 0;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	gluBuild2DMipmaps(GL_TEXTURE_2D, mode, img->w, img->h, mode, GL_UNSIGNED_BYTE, img->pixels);

	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(img);

	return texture;
}

SObjModel::SObjModel(string filename, string texfile)
{
	vector<Coord3f> vertex;
	vector<Coord3f> normal;
	vector<Coord2f> texture;
	string type;

	ifstream fin(filename.c_str());
	while (fin >> type)
	{
		if (!type.compare("v"))
		{
			Coord3f v;
			fin >> v;
			vertex.push_back(v);
		}
		else if (!type.compare("vn"))
		{
			Coord3f v;
			fin >> v;
			normal.push_back(v);
		}
		else if (!type.compare("vt"))
		{
			Coord2f v;
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
		tex = genTex(texfile);
	else
		tex = 0;
}

void SObjModel::draw(SLayer *layer)
{
	int attrib_pos = layer->getAttrib("pos");
	int attrib_texcoord = layer->getAttrib("texcoord");
	int uniform_wvp = layer->getUniform("wvp");
	int uniform_tex = layer->getUniform("tex");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(uniform_tex, 0);

	glUniformMatrix4fv(uniform_wvp, 1, GL_FALSE, value_ptr(layer->getWVP()));

	glEnableVertexAttribArray(attrib_pos);
	glVertexAttribPointer(attrib_pos, 3, GL_FLOAT, GL_FALSE, 0, &vertices.front());
	glEnableVertexAttribArray(attrib_texcoord);
	glVertexAttribPointer(attrib_texcoord, 2, GL_FLOAT, GL_FALSE, 0, &textures.front());

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisableVertexAttribArray(attrib_pos);
	glDisableVertexAttribArray(attrib_texcoord);
}

SObjModel::~SObjModel()
{
	glDeleteTextures(1, &tex);
}

}
