#include <iostream>
#include <fstream>

#include <GL/glew.h>

#include <SDL/SDL_image.h>

#include <core/model.h>
#include <core/layer.h>

#include <glm/gtc/type_ptr.hpp>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

namespace Starlia
{

unsigned int SModel::genTex(const string& filename)
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

SObjModel::SObjModel(const string& filename, const string& texfile)
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
			v.y = 1 - v.y;
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


void SAssimpModel::initialize(const struct aiScene *scene, struct aiNode *node)
{
	for (int i = 0; i < (int) node->mNumMeshes; ++i)
	{
		const struct aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		for (int j = 0; j < (int) mesh->mNumFaces; ++j)
		{
			const struct aiFace* face = &mesh->mFaces[j];

			if (face->mNumIndices != 3)
				continue;

			for(int k = 0; k < (int) face->mNumIndices; k++)
			{
				int index = face->mIndices[k];
				if(mesh->mNormals != NULL)
					normals.push_back(Coord3f(mesh->mNormals[index].x, mesh->mNormals[index].y, mesh->mNormals[index].z));
				vertices.push_back(Coord3f(mesh->mVertices[index].x, mesh->mVertices[index].y, mesh->mVertices[index].z));

				textures.push_back(Coord2f(mesh->mTextureCoords[0][index].x, 1 - mesh->mTextureCoords[0][index].y));
			}
		}
	}

	for (int i = 0; i < (int) node->mNumChildren; ++i)
		initialize(scene, node->mChildren[i]);
}

SAssimpModel::SAssimpModel(const string& filename)
{
	const aiScene *scene = aiImportFile(filename.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene->mNumMaterials > 0)
	{
		aiString pth;
		scene->mMaterials[1]->GetTexture(aiTextureType_DIFFUSE, 0, &pth);

		string path = filename.substr(0, filename.rfind("/")) + "/" + string(pth.C_Str());
		tex = genTex(path);
	}
	else
	{
		tex = 0;
	}


	initialize(scene, scene->mRootNode);

	aiReleaseImport(scene);
}

void SAssimpModel::draw(SLayer *layer)
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

}
