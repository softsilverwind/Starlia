#ifndef __MODEL_H__
#define __MODEL_H__

#include <istream>
#include <vector>

#include <starlia/core/structs.h>

namespace Starlia
{

using namespace std;

class SModel
{
	public:
		virtual void draw();

		virtual ~SModel();
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
		vector<Coord3d> vertices;
		vector<Coord3d> normals;
		vector<Coord2d> textures;

		unsigned int tex;

	public:
		virtual void draw();

		SObjModel(istream source);
		SObjModel(string filename);
		~SObjModel();
};

}

#endif
