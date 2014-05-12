#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <core/core.h>
#include <core/layer.h>
#include <core/math.h>
#include <core/object.h>
#include <core/structs.h>

using namespace std;

namespace Starlia
{

void SObject::dispatchSignals()
{
	for (string& str : emittedSignals)
		connections[str]();

	emittedSignals.clear();
}

void SObject::connect(string str, function<void (void)> fun)
{
	connections[str] = fun;
}

void SObject::emit(string str)
{
	emittedSignals.push_back(str);
}

SObject::SObject()
	: invalid(false)
{
}



void S2dObject::draw()
{
	if (!model)
		return;

	layer->setWorld(
			scale(
				rotate(
					translate(mat4(1.0f), vec3(position.x, position.y, 0))
				, angle, vec3(0, 0, 1))
			, vec3(radius.x, radius.y, 1)));

	model->draw(layer);
}


S2dObject::S2dObject(Coord2f position, Coord2f radius, float angle, SModel *model)
	: position(position), radius(radius), angle(angle), model(shared_ptr<SModel>(model))
{	
}

S2dObject::S2dObject(Coord2f position, Coord2f radius, float angle, shared_ptr<SModel> model)
	: position(position), radius(radius), angle(angle), model(model)
{	
}

void S2dDynObject::update()
{
	position += velocity;
	angle += angvelocity;

	angle = dmod(angle, M_PI * 2);
}


S2dDynObject::S2dDynObject(Coord2f position, Coord2f radius, float angle, SModel *model)
	: S2dObject(position, radius, angle, shared_ptr<SModel>(model)), velocity(0,0), angvelocity(0)
{
}

S2dDynObject::S2dDynObject(Coord2f position, Coord2f radius, float angle, shared_ptr<SModel> model)
	: S2dObject(position, radius, angle, model), velocity(0,0), angvelocity(0)
{
}


SWidget::SWidget(Coord2f center, Coord2f halfsize)
	: center(center), halfsize(halfsize)
{
}

bool SWidget::eventClick(Coord2f)
{
	return false;
}

bool SWidget::eventMouseOver(Coord2f)
{
	return false;
}

void S3dObject::draw()
{
	if (!model)
		return;

	layer->setWorld(
			scale(
				rotate(
					rotate(
						rotate(
							translate(mat4(1.0f), vec3(position.x, position.y, position.z))
							, angle.z, vec3(0, 0, 1))
						, angle.x, vec3(1, 0, 0))
				, angle.y, vec3(0, 1, 0))
			, vec3(radius.x, radius.y, radius.z)));

	model->draw(layer);
}

S3dObject::S3dObject(Coord3f position, Coord3f radius, Coord3f angle, SModel *model)
	: position(position), radius(radius), angle(angle), model(shared_ptr<SModel>(model))
{	
}

S3dObject::S3dObject(Coord3f position, Coord3f radius, Coord3f angle, shared_ptr<SModel> model)
	: position(position), radius(radius), angle(angle), model(model)
{	
}

Coord3f S3dObject::getNormalX() const
{
	Coord3f c(cos(angle.x), cos(angle.y), cos(angle.z));
	Coord3f s(sin(angle.x), sin(angle.y), sin(angle.z));

	return Coord3f(c.y*c.z - s.x*s.y*s.z, c.y*s.z + c.z*s.x*s.y, -c.x*s.y);
}

Coord3f S3dObject::getNormalY() const
{
	Coord3f c(cos(angle.x), cos(angle.y), cos(angle.z));
	Coord3f s(sin(angle.x), sin(angle.y), sin(angle.z));
	
	return Coord3f(-c.x*s.z, c.x*c.z, s.x);
}

Coord3f S3dObject::getNormalZ() const
{
	Coord3f c(cos(angle.x), cos(angle.y), cos(angle.z));
	Coord3f s(sin(angle.x), sin(angle.y), sin(angle.z));

	return Coord3f(c.z*s.y + c.y*s.x*s.z, s.y*s.z - c.y*c.z*s.x, c.x*c.y);
}


S3dDynObject::S3dDynObject(Coord3f position, Coord3f radius, Coord3f angle, SModel *model)
	: S3dObject(position, radius, angle, shared_ptr<SModel>(model)), velocity(0,0,0), angvelocity(0,0,0), thrust(0,0,0), actualVelocity(0,0,0)
{
}

S3dDynObject::S3dDynObject(Coord3f position, Coord3f radius, Coord3f angle, shared_ptr<SModel> model)
	: S3dObject(position, radius, angle, model), velocity(0,0,0), angvelocity(0,0,0), thrust(0,0,0), actualVelocity(0,0,0)
{
}

void S3dDynObject::update()
{
	angle += angvelocity;

	angle.x = clamp(angle.x, -M_PI / 2, M_PI / 2);
	angle.y = dmod(angle.y, M_PI * 2);
	angle.z = dmod(angle.z, M_PI * 2);

	actualVelocity = velocity + getNormalX() * thrust.x
		+ getNormalY() * thrust.y + getNormalZ() * thrust.z;

	position += actualVelocity;
}


SPerspCamera::SPerspCamera(Coord3f position, Coord3f angle, float fov, float near, float far)
	: S3dDynObject(position, Coord3f(0,0,0), angle), fov(fov), near(near), far(far)
{
}

mat4 SPerspCamera::getProjection()
{
	const Coord2f& scale = StarCore::getScale();
	return perspective(fov, scale.x / scale.y, near, far);
}

mat4 SPerspCamera::getView()
{
	return translate(
				rotate(
					rotate(
						rotate(
							rotate(mat4(1.0f), (float) -M_PI / 2, vec3(1, 0, 0))
						, -angle.y, vec3(0, 1, 0))
					, -angle.x, vec3(1, 0, 0))
				, -angle.z, vec3(0, 0, 1))
			, vec3(-position.x, -position.y, -position.z));
}

SOrthoCamera::SOrthoCamera(Coord2f center, Coord2f halfsize)
	: center(center), halfsize(halfsize)
{
}

void SOrthoCamera::zoom(float times)
{
	halfsize *= times;
}

void SOrthoCamera::move(Coord2f delta)
{
	center += delta;
}

Coord2f SOrthoCamera::unproject(Coord2f pos)
{
	pos *= 2;
	pos -= Coord2f(1,1);

	pos.x *= halfsize.x;
	pos.y *= halfsize.y;

	pos += center;

	return pos;	
}

mat4 SOrthoCamera::getProjection()
{
	Coord2f topleft(center - halfsize);
	Coord2f botright(center + halfsize);
	return ortho(topleft.x, botright.x, botright.y, topleft.y);
}

mat4 SOrthoCamera::getView()
{
	return mat4(1.0f);
}

}
