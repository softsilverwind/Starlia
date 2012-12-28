#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <functional>
#include <string>
#include <map>

#include <starlia/core/model.h>
#include <starlia/core/structs.h>

using namespace std;

namespace Starlia
{

class SObject
{
	private:
		vector<string> emittedSignals;
		map<string, function<void (void)> > connections;
		bool invalid;

	protected:
		virtual void draw();
		virtual void update();

		void emit(string);

	public:
		SObject();
		virtual ~SObject();

		void connect(string, function<void (void)>);

		void invalidate();

	friend class SLayer;
};

class S2dObject : public SObject
{
	protected:
		Coord2d position;
		Coord2d radius;
		double angle;
		SModel *model;

		virtual void draw() override;
		virtual void update() override;

	public:
		S2dObject(Coord2d position, Coord2d radius, double angle = 0, SModel *model = NULL);
		~S2dObject();

		void setPosition(const Coord2d&);
		const Coord2d& getPosition() const;
		void setAngle(const double&);
		double getAngle() const;
		void setRadius(const Coord2d&);
		const Coord2d& getRadius() const;
};

class S2dDynObject : public S2dObject
{
	protected:
		Coord2d velocity;
		double angvelocity;

		virtual void draw();
		virtual void update();

	public:
		S2dDynObject(Coord2d position, Coord2d radius, double angle = 0, SModel *model = NULL);

		void setVelocity(const Coord2d&);
		const Coord2d& getVelocity() const;
		void setAngVelocity(const double&);
		double getAngVelocity() const;
};


class SWidget : public SObject
{
	protected:
		Coord2d topLeft;
		Coord2d botRight;
		function<void (Coord2d)> onClick;
		function<void (Coord2d)> onMouseOver;

		virtual void draw();
		virtual void update();

	public:
		SWidget();
		SWidget(Coord2d topLeft, Coord2d botRight, function<void (Coord2d)> onClick = NULL, function<void (Coord2d)> onMouseOver = NULL);
		const Coord2d& getTopLeft() const;
		const Coord2d& getBotRight() const;
		bool eventClick(Coord2d pos);
		bool eventMouseOver(Coord2d pos);
};


class S3dObject : public SObject
{
	protected:
		Coord3d position;
		Coord3d radius;
		Coord3d angle;
		SModel *model;

		virtual void draw();
		virtual void update();

	public:
		S3dObject(Coord3d position, Coord3d radius, Coord3d angle, SModel *model = NULL);
		~S3dObject();

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

class S3dDynObject : public S3dObject
{
	protected:
		Coord3d velocity;
		Coord3d angvelocity;
		Coord3d thrust;
		Coord3d actualVelocity;

		virtual void draw();
		virtual void update();

	public:
		S3dDynObject(Coord3d position, Coord3d radius, Coord3d angle, SModel *model = NULL);

		void setVelocity(const Coord3d&);
		const Coord3d& getVelocity() const;
		void setAngVelocity(const Coord3d&);
		const Coord3d& getAngVelocity() const;
		void setThrust(const Coord3d&);
		const Coord3d& getThrust() const;
};

#include <starlia/core/object.inl>

}

#endif
