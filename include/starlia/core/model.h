#ifndef __MODEL_H__
#define __MODEL_H__

#include <assimp/scene.h>

#include <istream>
#include <vector>

#include "structs.h"

namespace Starlia
{

class SLayer;

using namespace std;

class SModel
{
	public:
		static unsigned int genTex(const string& filename, unsigned int texhint = 0);

		virtual void draw(SLayer *) {};

		virtual ~SModel() {};
};

/* TODO for simple 2d games
class STexModel : public SModel
{
	unsigned int tex;

	public:
		STexModel(string filename);
		~STexModel();	
};
*/

// A simple one-mesh, no-material obj loader, mostly for debugging purposes.
// A more generic loader should come soon...
class SObjModel : public SModel
{
	private:
		vector<Coord3f> vertices;
		vector<Coord3f> normals;
		vector<Coord2f> textures;

		unsigned int tex;

	public:
		virtual void draw(SLayer *) override;

		SObjModel(const string& filename, const string& texname = "");
		~SObjModel();
};

class SAssimpModel : public SModel
{
	private:
		vector<Coord3f> vertices;
		vector<Coord3f> normals;
		vector<Coord2f> textures;

		unsigned int tex;

		void initialize(const struct aiScene *scene, struct aiNode *node);

	public:
		SAssimpModel(const string& filename);

		virtual void draw(SLayer *) override;
};

}

#endif
