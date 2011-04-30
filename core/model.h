#ifndef __STARMODEL_H__
#define __STARMODEL_H__

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
		void draw();
};

class Star3dModel : public StarModel
{
	public:
		void draw();
};

}

#endif /* __STARMODEL_H__ */
