#include <iostream>
#include <GL/gl.h>
#include <string>
#include <vector>
#include "starMath.h"
#include "object.h"
#include "structs.h"

using namespace std;

namespace Starlia
{

vector<string> StarObject::emittedSignals;
bool StarObject::canHasEmit = false;

StarObject::StarObject()
	: invalid(false)
{
}

void StarObject::draw()
{
	return;
}

void StarObject::recalc()
{
}

StarObject::~StarObject()
{
}

void StarObject::connect(string str, function<void (void)> fun)
{
	connections[str] = fun;
}

void StarObject::emit(string str)
{
	if (!canHasEmit)
	{
		cerr << "Discarding emitting of \"" << str << "\" outside of recalc function!!!" << endl;
		return;
	}

	emittedSignals.push_back(str);
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

void Star2dObject::recalc()
{
	position += velocity;
	angle += angvelocity;

	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;
}

Star2dObject::Star2dObject(Coord2d position, Coord2d halfsize, double angle, Star2dModel *model)
	: position(position), velocity(0,0), halfsize(halfsize), angle(angle), angvelocity(0), model(model)
{	
}

Star2dObject::~Star2dObject()
{
	if (model)
		delete model;
}

void Star2dObject::setVelocity(Coord2d vel)
{
	velocity = vel;
}

void Star2dObject::setAngVelocity(double angvel)
{
	angvelocity = angvel;
}

StarWidget::StarWidget(Coord2d topLeft, Coord2d botRight, function<void (Coord2d)> onClick, function<void (Coord2d)> onMouseOver)
	: topLeft(topLeft), botRight(botRight), onClick(onClick), onMouseOver(onMouseOver)
{
}

void StarWidget::draw()
{
	return;
}

void StarWidget::recalc()
{
}

bool StarWidget::click(Coord2d pos)
{
	if (onClick)
	{
		onClick(pos);
		return true;
	}
	else
		return false;
}

bool StarWidget::mouseOver(Coord2d pos)
{
	if (onMouseOver)
	{
		onMouseOver(pos);
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
	Coord3d lol = this->getNormalX() * -10;
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

void Star3dObject::recalc()
{
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

	actualVelocity = velocity + getNormalX() * thrust.x
		+ getNormalY() * thrust.y + getNormalZ() * thrust.z;

	position += actualVelocity;
}

Star3dObject::Star3dObject(Coord3d position, Coord3d halfsize, Coord3d angle, Star3dModel *model)
	: position(position), halfsize(halfsize), angle(angle), velocity(0,0,0), angvelocity(0,0,0), thrust(0,0,0), actualVelocity(0,0,0), model(model)
{	
}

Star3dObject::~Star3dObject()
{
	if (model)
		delete model;
}

void Star3dObject::setVelocity(Coord3d vel)
{
	velocity = vel;
}

void Star3dObject::setAngVelocity(Coord3d angvel)
{
	angvelocity = angvel;
}

void Star3dObject::setThrust(Coord3d thr)
{
	thrust = thr;
}

Coord3d Star3dObject::getNormalX()
{
	Coord3d c(cos(angle.x * M_PI / 180), cos(angle.y * M_PI / 180), cos(angle.z * M_PI / 180));
	Coord3d s(sin(angle.x * M_PI / 180), sin(angle.y * M_PI / 180), sin(angle.z * M_PI / 180));

	return Coord3d(c.y*c.z - s.x*s.y*s.z, c.y*s.z + c.z*s.x*s.y, -c.x*s.y);
}

Coord3d Star3dObject::getNormalY()
{
	Coord3d c(cos(angle.x * M_PI / 180), cos(angle.y * M_PI / 180), cos(angle.z * M_PI / 180));
	Coord3d s(sin(angle.x * M_PI / 180), sin(angle.y * M_PI / 180), sin(angle.z * M_PI / 180));
	
	return Coord3d(-c.x*s.z, c.x*c.z, s.x);
}

Coord3d Star3dObject::getNormalZ()
{
	Coord3d c(cos(angle.x * M_PI / 180), cos(angle.y * M_PI / 180), cos(angle.z * M_PI / 180));
	Coord3d s(sin(angle.x * M_PI / 180), sin(angle.y * M_PI / 180), sin(angle.z * M_PI / 180));

	return Coord3d(c.z*s.y + c.y*s.x*s.z, s.y*s.z - c.y*c.z*s.x, c.x*c.y);
}

}
