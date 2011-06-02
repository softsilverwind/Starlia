#include <GL/glut.h>
#include <string>
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

void Star2dObject::draw()
{
	if (!model)
		return;

	glPushMatrix();
	glTranslated(position.x, position.y, 0);
	glRotated(angle,0,0,1);
	glScaled(halfsize.x, halfsize.y, 1);
	model->draw();
	glPopMatrix();
}

bool Star2dObject::recalc()
{
	position += velocity;
	return true;
}

Star2dObject::Star2dObject(Coordinate2d position, Coordinate2d halfsize, double angle, Star2dModel *model)
	: position(position), velocity(0,0), halfsize(halfsize), angle(angle), model(model)
{	
}

Star2dObject::~Star2dObject()
{
	if (model)
		delete model;
}

StarWidget::StarWidget(Coordinate2d topLeft, Coordinate2d botRight, void (*onClick)(Coordinate2d), void (*onMouseOver)(Coordinate2d))
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
		onClick(pos);
		return true;
	}
	else
		return false;
}

bool StarWidget::mouseOver(Coordinate2d pos)
{
	if (onMouseOver)
	{
		onMouseOver(pos);
		return true;
	}
	else
		return false;
}

}
