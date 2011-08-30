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

		virtual ~StarObject();
};

class Star2dObject : public StarObject
{
	protected:
		Coordinate2d position;
		Coordinate2d velocity;
		Coordinate2d halfsize;
		double angle;
		double angvelocity;
		Star2dModel *model;

		virtual void draw();
		virtual bool recalc();

	public:
		Star2dObject(Coordinate2d position, Coordinate2d halfsize, double angle = 0, Star2dModel *model = NULL);
		~Star2dObject();
		void setVelocity(Coordinate2d);
		void setAngVelocity(double);
};

class StarWidget : public StarObject
{
	protected:
		Coordinate2d topLeft;
		Coordinate2d botRight;
		void (*onClick)(StarWidget *, Coordinate2d pos);
		void (*onMouseOver)(StarWidget *, Coordinate2d pos);

		virtual void draw();
		virtual bool recalc();

	public:
		StarWidget();
		StarWidget(Coordinate2d topLeft, Coordinate2d botRight, void (*onClick)(StarWidget *, Coordinate2d) = NULL, void (*onMouseOver)(StarWidget *, Coordinate2d) = NULL);
		const Coordinate2d& getTopLeft() { return topLeft; };
		const Coordinate2d& getBotRight() { return botRight; };
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
		Coordinate3d angvelocity;
		Star3dModel *model;

		virtual void draw();
		virtual bool recalc();

	public:
		Star3dObject(Coordinate3d position, Coordinate3d halfsize, Coordinate3d angle, Star3dModel *model = NULL);
		~Star3dObject();
		void setVelocity(Coordinate3d);
		void setAngVelocity(Coordinate3d);
		Coordinate3d getNormalX();
		Coordinate3d getNormalY();
		Coordinate3d getNormalZ();
};

}

#endif /* __STAROBJECT_H__ */
