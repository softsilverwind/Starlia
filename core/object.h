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
		Coord2d radius;
		double angle;
		Star2dModel *model;

		virtual void draw();
		virtual void recalc();

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

inline void Star2dObject::setPosition(const Coord2d& pos) { position = pos; }
inline const Coord2d& Star2dObject::getPosition() const { return position; }
inline void Star2dObject::setAngle(const double& ang) { angle = ang; }
inline double Star2dObject::getAngle() const { return angle; }
inline void Star2dObject::setRadius(const Coord2d& rad) { radius = rad; }
inline const Coord2d& Star2dObject::getRadius() const { return radius; }

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

inline void Star2dDynObject::setVelocity(const Coord2d& vel) { velocity = vel; }
inline const Coord2d& Star2dDynObject::getVelocity() const { return velocity; }
inline void Star2dDynObject::setAngVelocity(const double& angvel) { angvelocity = angvel; }
inline double Star2dDynObject::getAngVelocity() const { return angvelocity; }

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
		bool click(Coord2d pos);
		bool mouseOver(Coord2d pos);
};

inline const Coord2d& StarWidget::getTopLeft() const { return topLeft; }
inline const Coord2d& StarWidget::getBotRight() const { return botRight; }

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

inline void Star3dObject::setPosition(const Coord3d& pos) { position = pos; }
inline const Coord3d& Star3dObject::getPosition() const { return position; }
inline void Star3dObject::setAngle(const Coord3d& ang) { angle = ang; }
inline const Coord3d& Star3dObject::getAngle() const { return angle; }
inline void Star3dObject::setRadius(const Coord3d& rad) { radius = rad; }
inline const Coord3d& Star3dObject::getRadius() const { return radius; }

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

inline void Star3dDynObject::setVelocity(const Coord3d& vel) { velocity = vel; }
inline const Coord3d& Star3dDynObject::getVelocity() const { return velocity; }
inline void Star3dDynObject::setAngVelocity(const Coord3d& angvel) { angvelocity = angvel; }
inline const Coord3d& Star3dDynObject::getAngVelocity() const { return angvelocity; }
inline void Star3dDynObject::setThrust(const Coord3d& thr) { thrust = thr; }
inline const Coord3d& Star3dDynObject::getThrust() const { return thrust; }

}

#endif /* __STAROBJECT_H__ */
