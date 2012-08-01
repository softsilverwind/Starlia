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
		static bool canHasEmit;
		map<string, function<void (void)> > connections;
		bool invalid;

	protected:
		virtual void draw();
		virtual void recalc();

	public:
		StarObject();
		virtual ~StarObject();

		void connect(string, function<void (void)>);
		static void emit(string);

	friend class StarLayer;
};

class Star2dObject : public StarObject
{
	protected:
		Coord2d position;
		Coord2d radius;
		double angle;
		Star2dModel *model;

		virtual void draw() override;
		virtual void recalc() override;

	public:
		Star2dObject(Coord2d position, Coord2d radius, double angle = 0, Star2dModel *model = NULL);
		~Star2dObject();

		void setPosition(const Coord2d&);
		const Coord2d& getPosition() const;
		void setAngle(const double&);
		double getAngle() const;
		void setRadius(const Coord2d&);
		const Coord2d& getRadius() const;
};

class Star2dDynObject : public Star2dObject
{
	protected:
		Coord2d velocity;
		double angvelocity;

		virtual void draw();
		virtual void recalc();

	public:
		Star2dDynObject(Coord2d position, Coord2d radius, double angle = 0, Star2dModel *model = NULL);

		void setVelocity(const Coord2d&);
		const Coord2d& getVelocity() const;
		void setAngVelocity(const double&);
		double getAngVelocity() const;
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
		const Coord2d& getTopLeft() const;
		const Coord2d& getBotRight() const;
		bool eventClick(Coord2d pos);
		bool eventMouseOver(Coord2d pos);
};


class Star3dObject : public StarObject
{
	protected:
		Coord3d position;
		Coord3d radius;
		Coord3d angle;
		Star3dModel *model;

		virtual void draw();
		virtual void recalc();

	public:
		Star3dObject(Coord3d position, Coord3d radius, Coord3d angle, Star3dModel *model = NULL);
		~Star3dObject();

		Coord3d getNormalX() const;
		Coord3d getNormalY() const;
		Coord3d getNormalZ() const;

		void setPosition(const Coord3d&);
		const Coord3d& getPosition() const;
		void setAngle(const Coord3d&);
		const Coord3d& getAngle() const;
		void setRadius(const Coord3d&);
		const Coord3d& getRadius() const;
};

class Star3dDynObject : public Star3dObject
{
	protected:
		Coord3d velocity;
		Coord3d angvelocity;
		Coord3d thrust;
		Coord3d actualVelocity;

		virtual void draw();
		virtual void recalc();

	public:
		Star3dDynObject(Coord3d position, Coord3d radius, Coord3d angle, Star3dModel *model = NULL);

		void setVelocity(const Coord3d&);
		const Coord3d& getVelocity() const;
		void setAngVelocity(const Coord3d&);
		const Coord3d& getAngVelocity() const;
		void setThrust(const Coord3d&);
		const Coord3d& getThrust() const;
};

#include "object.inl"

}

#endif /* __STAROBJECT_H__ */
