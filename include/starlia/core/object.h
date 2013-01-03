namespace Starlia
{
	class SObject;
	class S2dObject;
	class S2dDynObject;
	class SWidget;
	class S3dObject;
	class S3dDynObject;
}

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <functional>
#include <memory>
#include <string>
#include <map>

#include "structs.h"
#include "model.h"

// work around cyclical dependency
#ifndef __LAYER_H__
	#define __LAYER_H__
	#include "layer.h"
	#undef __LAYER_H__
#else
	#include "layer.h"
#endif


namespace Starlia
{

using namespace std;

class SObject
{
	private:
		vector<string> emittedSignals;
		map<string, function<void (void)> > connections;
		bool invalid;

		void dispatchSignals();

	protected:
		void emit(string);

		SLayer *layer;

	public:
		SObject();
		virtual ~SObject() {};

		virtual void draw() {};
		virtual void update() {};

		void connect(string, function<void (void)>);

		friend class SLayer;
};

class S2dObject : public SObject
{
	protected:
		Coord2f position;
		Coord2f radius;
		float angle;
		SModel *model;

	public:
		S2dObject(Coord2f position, Coord2f radius, float angle = 0, SModel *model = NULL);

		virtual void draw() override;

		void setPosition(const Coord2f&);
		const Coord2f& getPosition() const;
		void setAngle(float);
		float getAngle() const;
		void setRadius(const Coord2f&);
		const Coord2f& getRadius() const;
};

class S2dDynObject : public S2dObject
{
	protected:
		Coord2f velocity;
		float angvelocity;

	public:
		S2dDynObject(Coord2f position, Coord2f radius, float angle = 0, SModel *model = NULL);

		virtual void update() override;

		void setVelocity(const Coord2f&);
		const Coord2f& getVelocity() const;
		void setAngVelocity(float);
		float getAngVelocity() const;
};


class SWidget : public SObject
{
	protected:
		Coord2f topLeft;
		Coord2f botRight;
		function<void (Coord2f)> onClick;
		function<void (Coord2f)> onMouseOver;

	public:
		SWidget();
		SWidget(Coord2f topLeft, Coord2f botRight);

		const Coord2f& getTopLeft() const;
		const Coord2f& getBotRight() const;
		bool eventClick(Coord2f pos);
		bool eventMouseOver(Coord2f pos);
};


class S3dObject : public SObject
{
	protected:
		Coord3f position;
		Coord3f radius;
		Coord3f angle;
		SModel *model;

	public:
		S3dObject(Coord3f position, Coord3f radius, Coord3f angle, SModel *model = NULL);

		virtual void draw() override;

		Coord3f getNormalX() const;
		Coord3f getNormalY() const;
		Coord3f getNormalZ() const;

		void setPosition(const Coord3f&);
		const Coord3f& getPosition() const;
		void setAngle(const Coord3f&);
		const Coord3f& getAngle() const;
		void setRadius(const Coord3f&);
		const Coord3f& getRadius() const;
};

class S3dDynObject : public S3dObject
{
	protected:
		Coord3f velocity;
		Coord3f angvelocity;
		Coord3f thrust;
		Coord3f actualVelocity;

	public:
		S3dDynObject(Coord3f position, Coord3f radius, Coord3f angle, SModel *model = NULL);

		virtual void update() override;

		void setVelocity(const Coord3f&);
		const Coord3f& getVelocity() const;
		void setAngVelocity(const Coord3f&);
		const Coord3f& getAngVelocity() const;
		void setThrust(const Coord3f&);
		const Coord3f& getThrust() const;
};

#include "object.inl"

}

#endif
