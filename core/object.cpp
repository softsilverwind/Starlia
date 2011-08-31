#include <iostream>
#include <GL/gl.h>
#include <string>
#include "starMath.h"
#include "object.h"
#include "structs.h"

using namespace std;

namespace Starlia
{

void StarObject::draw()
{
	return;
}

bool StarObject::recalc()
{
	return true;
}

StarObject::~StarObject()
{
}

void Star2dObject::draw()
{
	if (!model)
		return;

	glTranslated(position.x, position.y, 0);
	glRotated(angle,0,0,1);
	glScaled(halfsize.x, halfsize.y, 1);
	model->draw();
}

bool Star2dObject::recalc()
{
	position += velocity;
	angle += angvelocity;

	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;

	return true;
}

Star2dObject::Star2dObject(Coordinate2d position, Coordinate2d halfsize, double angle, Star2dModel *model)
	: position(position), velocity(0,0), halfsize(halfsize), angle(angle), angvelocity(0), model(model)
{	
}

Star2dObject::~Star2dObject()
{
	if (model)
		delete model;
}

void Star2dObject::setVelocity(Coordinate2d vel)
{
	velocity = vel;
}

void Star2dObject::setAngVelocity(double angvel)
{
	angvelocity = angvel;
}

StarWidget::StarWidget(Coordinate2d topLeft, Coordinate2d botRight, void (*onClick)(StarWidget *, Coordinate2d), void (*onMouseOver)(StarWidget *, Coordinate2d))
	: topLeft(topLeft), botRight(botRight), onClick(onClick), onMouseOver(onMouseOver)
{
}

void StarWidget::draw()
{
	return;
}

bool StarWidget::recalc()
{
	return true;
}

bool StarWidget::click(Coordinate2d pos)
{
	if (onClick)
	{
		onClick(this, pos);
		return true;
	}
	else
		return false;
}

bool StarWidget::mouseOver(Coordinate2d pos)
{
	if (onMouseOver)
	{
		onMouseOver(this, pos);
		return true;
	}
	else
		return false;
}

void Star3dObject::draw()
{
	if (!model)
		return;

	glTranslated(position.x, position.y, position.z);

#ifdef __DEBUG__

	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);

	glColor3f(1,0,0);
	Coordinate3d lol = this->getNormalX() * -10;
	glVertex3d(lol.x, lol.y, lol.z);
	lol = this->getNormalX() * 10;
	glVertex3d(lol.x, lol.y, lol.z);

	glColor3f(0,1,0);
	lol = this->getNormalY() * -10;
	glVertex3d(lol.x, lol.y, lol.z);
	lol = this->getNormalY() * 10;
	glVertex3d(lol.x, lol.y, lol.z);

	glColor3f(0,0,1);
	lol = this->getNormalZ() * -10;
	glVertex3d(lol.x, lol.y, lol.z);
	lol = this->getNormalZ() * 10;
	glVertex3d(lol.x, lol.y, lol.z);

	glEnd();
	glEnable(GL_LIGHTING);

#endif

	glRotated(angle.z,0,0,1);
	glRotated(angle.x,1,0,0);
	glRotated(angle.y,0,1,0);
	glScaled(halfsize.x, halfsize.y, halfsize.z);
	model->draw();



}

bool Star3dObject::recalc()
{
	position += velocity;
	angle += angvelocity;

	if (angle.x < -90)
		angle.x = -90;
	else if (angle.x > 90)
		angle.x = 90;

	if (angle.y < 0)
		angle.y += 360;
	else if (angle.y >= 360)
		angle.y -= 360;

	if (angle.z < 0)
		angle.z += 360;
	else if (angle.z >= 360)
		angle.z -= 360;

	return true;
}

Star3dObject::Star3dObject(Coordinate3d position, Coordinate3d halfsize, Coordinate3d angle, Star3dModel *model)
	: position(position), velocity(0,0,0), halfsize(halfsize), angle(angle), angvelocity(0,0,0), model(model)
{	
}

Star3dObject::~Star3dObject()
{
	if (model)
		delete model;
}

void Star3dObject::setVelocity(Coordinate3d vel)
{
	velocity = vel;
}

void Star3dObject::setAngVelocity(Coordinate3d angvel)
{
	angvelocity = angvel;
}

Coordinate3d Star3dObject::getNormalX()
{
	Coordinate3d c(cos(angle.x * M_PI / 180), cos(angle.y * M_PI / 180), cos(angle.z * M_PI / 180));
	Coordinate3d s(sin(angle.x * M_PI / 180), sin(angle.y * M_PI / 180), sin(angle.z * M_PI / 180));

	return Coordinate3d(c.y*c.z - s.x*s.y*s.z, c.y*s.z + c.z*s.x*s.y, -c.x*s.y);
}

Coordinate3d Star3dObject::getNormalY()
{
	Coordinate3d c(cos(angle.x * M_PI / 180), cos(angle.y * M_PI / 180), cos(angle.z * M_PI / 180));
	Coordinate3d s(sin(angle.x * M_PI / 180), sin(angle.y * M_PI / 180), sin(angle.z * M_PI / 180));
	
	return Coordinate3d(-c.x*s.z, c.x*c.z, s.x);
}

Coordinate3d Star3dObject::getNormalZ()
{
	Coordinate3d c(cos(angle.x * M_PI / 180), cos(angle.y * M_PI / 180), cos(angle.z * M_PI / 180));
	Coordinate3d s(sin(angle.x * M_PI / 180), sin(angle.y * M_PI / 180), sin(angle.z * M_PI / 180));

	return Coordinate3d(c.z*s.y + c.y*s.x*s.z, s.y*s.z - c.y*c.z*s.x, c.x*c.y);
}

}
