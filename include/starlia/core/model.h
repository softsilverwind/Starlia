#ifndef __MODEL_H__
#define __MODEL_H__

#include <istream>
#include <vector>

#include "layer.h"
#include "structs.h"

namespace Starlia
{

using namespace std;

class SModel
{
	public:
		virtual void draw(SLayer *) {};

		virtual ~SModel() {};
};

class STexModel : public SModel
{
	unsigned int tex;

	STexModel(string filename);
	~STexModel();	
};

class SObjModel : public SModel
{
	private:
		vector<Coord3f> vertices;
		vector<Coord3f> normals;
		vector<Coord2f> textures;

		unsigned int tex;

	public:
		virtual void draw(SLayer *) override;

		SObjModel(istream source);
		SObjModel(string filename);
		~SObjModel();
};

}

#endif
