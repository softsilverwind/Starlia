#ifndef __STAROBJECT_H__
#define __STAROBJECT_H__

#include <functional>
#include <string>
#include <map>
#include "model.h"
#include "structs.h"

using namespace std;

#define CONNECT($1, $2) StarObject::connect(string(#$1), $2)
#define EMIT($1) StarObject::emit(string(#$1))

namespace Starlia
{

class StarObject
{
	private:
		static vector<string> emittedSignals;
		map<string, function<void (void)> > connections;
		bool invalid;

	public:
		StarObject();
		virtual ~StarObject();

		virtual void draw();
		virtual void recalc();

		void connect(string, function<void (void)>);
		static void emit(string);

	friend class StarLayer;
};

class Star2dObject : public StarObject
{
	protected:
		Coord2d position;
		Coord2d velocity;
		Coord2d halfsize;
		double angle;
		double angvelocity;
		Star2dModel *model;

		virtual void draw();
		virtual void recalc();

	public:
		Star2dObject(Coord2d position, Coord2d halfsize, double angle = 0, Star2dModel *model = NULL);
		~Star2dObject();
		void setVelocity(Coord2d);
		void setAngVelocity(double);
};

class StarWidget : public StarObject
{
	protected:
		Coord2d topLeft;
		Coord2d botRight;
		function<void (Coord2d)> onClick;
		function<void (Coord2d)> onMouseOver;

		virtual void draw();
		virtual void recalc();

	public:
		StarWidget();
		StarWidget(Coord2d topLeft, Coord2d botRight, function<void (Coord2d)> onClick = NULL, function<void (Coord2d)> onMouseOver = NULL);
		const Coord2d& getTopLeft() { return topLeft; };
		const Coord2d& getBotRight() { return botRight; };
		bool click(Coord2d pos);
		bool mouseOver(Coord2d pos);
};

class Star3dObject : public StarObject
{
	protected:
		Coord3d position;
		Coord3d halfsize;
		Coord3d angle;
		Coord3d velocity;
		Coord3d angvelocity;
		Coord3d thrust;
		Coord3d actualVelocity;
		Star3dModel *model;

		virtual void draw();
		virtual void recalc();

	public:
		Star3dObject(Coord3d position, Coord3d halfsize, Coord3d angle, Star3dModel *model = NULL);
		~Star3dObject();

		void setVelocity(Coord3d);
		void setAngVelocity(Coord3d);
		void setThrust(Coord3d);

		Coord3d getNormalX();
		Coord3d getNormalY();
		Coord3d getNormalZ();
};

}

#endif /* __STAROBJECT_H__ */
