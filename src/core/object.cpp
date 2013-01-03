#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
	: position(position), radius(radius), angle(angle), model(model)
{	
}


void S2dDynObject::update()
{
	position += velocity;
	angle += angvelocity;

	angle = dmod(angle, 360);
}


S2dDynObject::S2dDynObject(Coord2f position, Coord2f radius, float angle, SModel *model)
	: S2dObject(position, radius, angle, model), velocity(0,0), angvelocity(0)
{
}


SWidget::SWidget(Coord2f topLeft, Coord2f botRight)
	: topLeft(topLeft), botRight(botRight)
{
}

bool SWidget::eventClick(Coord2f pos)
{
	return false;
}

bool SWidget::eventMouseOver(Coord2f pos)
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
					translate(mat4(1.0f), vec3(position.x, position.y, 0))
				, angle.z, vec3(0, 0, 1))
				, angle.x, vec3(1, 0, 0))
				, angle.y, vec3(0, 1, 0))
			, vec3(radius.x, radius.y, radius.z)));

	model->draw(layer);
}

S3dObject::S3dObject(Coord3f position, Coord3f radius, Coord3f angle, SModel *model)
	: position(position), radius(radius), angle(angle), model(model)
{	
}

Coord3f S3dObject::getNormalX() const
{
	Coord3f c(cos(angle.x * M_PI / 180), cos(angle.y * M_PI / 180), cos(angle.z * M_PI / 180));
	Coord3f s(sin(angle.x * M_PI / 180), sin(angle.y * M_PI / 180), sin(angle.z * M_PI / 180));

	return Coord3f(c.y*c.z - s.x*s.y*s.z, c.y*s.z + c.z*s.x*s.y, -c.x*s.y);
}

Coord3f S3dObject::getNormalY() const
{
	Coord3f c(cos(angle.x * M_PI / 180), cos(angle.y * M_PI / 180), cos(angle.z * M_PI / 180));
	Coord3f s(sin(angle.x * M_PI / 180), sin(angle.y * M_PI / 180), sin(angle.z * M_PI / 180));
	
	return Coord3f(-c.x*s.z, c.x*c.z, s.x);
}

Coord3f S3dObject::getNormalZ() const
{
	Coord3f c(cos(angle.x * M_PI / 180), cos(angle.y * M_PI / 180), cos(angle.z * M_PI / 180));
	Coord3f s(sin(angle.x * M_PI / 180), sin(angle.y * M_PI / 180), sin(angle.z * M_PI / 180));

	return Coord3f(c.z*s.y + c.y*s.x*s.z, s.y*s.z - c.y*c.z*s.x, c.x*c.y);
}

S3dDynObject::S3dDynObject(Coord3f position, Coord3f radius, Coord3f angle, SModel *model)
	: S3dObject(position, radius, angle, model), velocity(0,0,0), angvelocity(0,0,0), thrust(0,0,0), actualVelocity(0,0,0)
{
}

void S3dDynObject::update()
{
	angle += angvelocity;

	angle.x = dmod(angle.x + 90, 180) - 90;
	angle.y = dmod(angle.y, 360);
	angle.z = dmod(angle.z, 360);

	actualVelocity = velocity + getNormalX() * thrust.x
		+ getNormalY() * thrust.y + getNormalZ() * thrust.z;

	position += actualVelocity;
}


}
