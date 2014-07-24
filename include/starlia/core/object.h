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

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "structs.h"
#include "model.h"

namespace Starlia
{

class SLayer;

using namespace std;
using namespace glm;

class SObject
{
	private:
		vector<string> emittedSignals;
		map<string, function<void (void)> > connections;

		void dispatchSignals();

	protected:
		void emit(string);
		bool invalid;

	public:
		SObject();
		virtual ~SObject() {};

		virtual void draw(SLayer *) {};
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
		shared_ptr<SModel> model;

	public:
		S2dObject(Coord2f position, Coord2f radius, float angle = 0, SModel *model = NULL);
		S2dObject(Coord2f position, Coord2f radius, float angle, shared_ptr<SModel> model);

		virtual void draw(SLayer *) override;

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
		S2dDynObject(Coord2f position, Coord2f radius, float angle, shared_ptr<SModel> model);

		virtual void update() override;

		void setVelocity(const Coord2f&);
		const Coord2f& getVelocity() const;
		void setAngVelocity(float);
		float getAngVelocity() const;
};


class SWidget : public SObject
{
	protected:
		Coord2f center;
		Coord2f halfsize;
		function<void (Coord2f)> onClick;
		function<void (Coord2f)> onMouseOver;

	public:
		SWidget();
		SWidget(Coord2f center, Coord2f halfsize);

		const Coord2f& getCenter() const;
		const Coord2f& getHalfSize() const;
		bool eventClick(Coord2f pos);
		bool eventMouseOver(Coord2f pos);
};


class S3dObject : public SObject
{
	protected:
		Coord3f position;
		Coord3f radius;
		Coord3f angle;
		shared_ptr<SModel> model;

	public:
		S3dObject(Coord3f position, Coord3f radius, Coord3f angle, SModel *model = NULL);
		S3dObject(Coord3f position, Coord3f radius, Coord3f angle, shared_ptr<SModel> model);

		virtual void draw(SLayer *) override;

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
		S3dDynObject(Coord3f position, Coord3f radius, Coord3f angle, shared_ptr<SModel> model);

		virtual void update() override;

		void setVelocity(const Coord3f&);
		const Coord3f& getVelocity() const;
		void setAngVelocity(const Coord3f&);
		const Coord3f& getAngVelocity() const;
		void setThrust(const Coord3f&);
		const Coord3f& getThrust() const;
};

class SCamera
{
	public:
		virtual mat4 getProjection() { return mat4(1.0f); };
		virtual mat4 getView() { return mat4(1.0f); };

		virtual float distanceFrom(Coord3f) { return 0; }
};

class SOrthoCamera : public SCamera
{
	private:
		Coord2f center, halfsize;

	public:
		SOrthoCamera(Coord2f center, Coord2f halfsize);

		void zoom(float);
		void move(Coord2f);
		Coord2f unproject(Coord2f);

		virtual mat4 getProjection() override;
		virtual mat4 getView() override;

		virtual float distanceFrom(Coord3f point) override;
};

class SPerspCamera : public SCamera, public S3dDynObject
{
	private:
		float fov, near, far;

	public:
		SPerspCamera(Coord3f position, Coord3f angle, float fov = M_PI / 4, float near = 1, float far = 100);

		virtual mat4 getProjection() override;
		virtual mat4 getView() override;

		virtual float distanceFrom(Coord3f point) override;
};

#include "object.inl"

}

#endif
