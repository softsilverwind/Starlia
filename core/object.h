#ifndef __STAROBJECT_H__
#define __STAROBJECT_H__

#include <string>
#include "model.h"
#include "structs.h"

using namespace std;

namespace Starlia
{

class StarObject
{
	public:
		string tag;

		virtual void draw();
		virtual bool recalc();
};

class Star2dObject : public StarObject
{
	protected:
		Coordinate2d position;
		Coordinate2d velocity;
		Coordinate2d halfsize;
		double angle;
		Star2dModel *model;


	protected:
		virtual void draw();
		virtual bool recalc();

	public:
		Star2dObject(Coordinate2d position, Coordinate2d halfsize, double angle = 0, Star2dModel *model = NULL);
		~Star2dObject();
};

class StarWidget : public StarObject
{
	protected:
		Coordinate2d topLeft;
		Coordinate2d botRight;
		void (*onClick)(Coordinate2d pos);
		void (*onMouseOver)(Coordinate2d pos);

		virtual void draw();
		virtual bool recalc();

	public:
		StarWidget();
		const Coordinate2d& getTopLeft() { return topLeft; };
		const Coordinate2d& getBotRight() { return botRight; };
		StarWidget(Coordinate2d topLeft, Coordinate2d botRight, void (*onClick)(Coordinate2d) = NULL, void (*onMouseOver)(Coordinate2d) = NULL);
		bool click(Coordinate2d pos);
		bool mouseOver(Coordinate2d pos);
};

class Star3dObject : public StarObject
{
	protected:
		Coordinate3d position;
		Coordinate3d velocity;
		Coordinate3d halfsize;
		Coordinate3d angle;
		Star3dModel *model;

		virtual void draw();
		virtual bool recalc();
};

}

#endif /* __STAROBJECT_H__ */
