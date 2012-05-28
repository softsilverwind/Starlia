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
	glScaled(radius.x, radius.y, 1);
	model->draw();
}

void Star2dObject::recalc()
{
	return;
}

Star2dObject::Star2dObject(Coord2d position, Coord2d radius, double angle, Star2dModel *model)
	: position(position), radius(radius), angle(angle), model(model)
{	
}

Star2dObject::~Star2dObject()
{
	if (model)
		delete model;
}

Star2dDynObject::Star2dDynObject(Coord2d position, Coord2d radius, double angle, Star2dModel *model)
	: Star2dObject(position, radius, angle, model), velocity(0,0), angvelocity(0)
{
}

void Star2dDynObject::draw()
{
	Star2dObject::draw();
}

void Star2dDynObject::recalc()
{
	position += velocity;
	angle += angvelocity;

	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;

	Star2dObject::recalc();
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
	glScaled(radius.x, radius.y, radius.z);
	model->draw();
}

void Star3dObject::recalc()
{
	return;
}

Star3dObject::Star3dObject(Coord3d position, Coord3d radius, Coord3d angle, Star3dModel *model)
	: position(position), radius(radius), angle(angle), model(model)
{	
}

Star3dObject::~Star3dObject()
{
	if (model)
		delete model;
}

Coord3d Star3dObject::getNormalX() const
{
	Coord3d c(cos(angle.x * M_PI / 180), cos(angle.y * M_PI / 180), cos(angle.z * M_PI / 180));
	Coord3d s(sin(angle.x * M_PI / 180), sin(angle.y * M_PI / 180), sin(angle.z * M_PI / 180));

	return Coord3d(c.y*c.z - s.x*s.y*s.z, c.y*s.z + c.z*s.x*s.y, -c.x*s.y);
}

Coord3d Star3dObject::getNormalY() const
{
	Coord3d c(cos(angle.x * M_PI / 180), cos(angle.y * M_PI / 180), cos(angle.z * M_PI / 180));
	Coord3d s(sin(angle.x * M_PI / 180), sin(angle.y * M_PI / 180), sin(angle.z * M_PI / 180));
	
	return Coord3d(-c.x*s.z, c.x*c.z, s.x);
}

Coord3d Star3dObject::getNormalZ() const
{
	Coord3d c(cos(angle.x * M_PI / 180), cos(angle.y * M_PI / 180), cos(angle.z * M_PI / 180));
	Coord3d s(sin(angle.x * M_PI / 180), sin(angle.y * M_PI / 180), sin(angle.z * M_PI / 180));

	return Coord3d(c.z*s.y + c.y*s.x*s.z, s.y*s.z - c.y*c.z*s.x, c.x*c.y);
}

Star3dDynObject::Star3dDynObject(Coord3d position, Coord3d radius, Coord3d angle, Star3dModel *model)
	: Star3dObject(position, radius, angle, model), velocity(0,0,0), angvelocity(0,0,0), thrust(0,0,0), actualVelocity(0,0,0)
{
}

void Star3dDynObject::draw()
{
	Star3dObject::draw();
}

void Star3dDynObject::recalc()
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

	Star3dObject::recalc();
}



}
