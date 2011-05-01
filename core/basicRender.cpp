#include <GL/glut.h>
#include "basicRender.h"
#include "starMath.h"
#include "structs.h"

namespace Starlia
{

bool Circle::initialized = false;
Coordinate2d Circle::vertex[POINTS];

void Circle::prepare()
{
	if (initialized)
		return;

	initialized = true;
	for (int i = 0; i < POINTS / 8; i++)
	{
		vertex[i].x = cos(i * step);
		vertex[i].y = sin(i * step);

		vertex[POINTS/4 - i - 1].x = vertex[i].y;
		vertex[POINTS/4 - i - 1].y = vertex[i].x;

		/* Define POINTS in second quadrant */
		vertex[POINTS/4 + i].x = -vertex[i].y;
		vertex[POINTS/4 + i].y =  vertex[i].x;

		vertex[POINTS/2 - i - 1].x = -vertex[i].x;
		vertex[POINTS/2 - i - 1].y =  vertex[i].y;

		/* Define POINTS in third quadrant */
		vertex[POINTS/2 + i].x = -vertex[i].x;
		vertex[POINTS/2 + i].y = -vertex[i].y;

		vertex[(POINTS*3)/4 - i - 1].x = -vertex[i].y;
		vertex[(POINTS*3)/4 - i - 1].y = -vertex[i].x;

		/* Define POINTS in fourth quadrant */
		vertex[(POINTS*3)/4 + i].x =  vertex[i].y;
		vertex[(POINTS*3)/4 + i].y = -vertex[i].x;

		vertex[POINTS - i - 1].x =  vertex[i].x;
		vertex[POINTS - i - 1].y = -vertex[i].y;
	}

}

void Circle::draw(Color3d color)
{
	if (!initialized)
		prepare();

	glPushAttrib(GL_CURRENT_BIT);
	glColor3d(color.r, color.g, color.b);

	glBegin(GL_POLYGON);

	for (int i = 0; i < POINTS; i++)
	{
		glVertex2f(vertex[i].x, vertex[i].y);
	}

	glEnd();

	glPopAttrib();
}

void Circle::draw()
{
	draw(color);
}

Circle::Circle(Color3d color)
	: color(color)
{
}

void Line::draw(Coordinate2d start, Coordinate2d end, Color3d color, unsigned int thickness)
{
	glColor3d(color.r, color.g, color.b);
	glLineWidth(thickness);

	glBegin(GL_LINES);
	glVertex2d(start.x, start.y);
	glVertex2d(end.x, end.y);
	glEnd();
}

bool VectorLetter::initialized = false;
vector<Coordinate2d> VectorLetter::character[128];

void VectorLetter::prepare()
{
	initialized = true;

	character['A'].push_back(Coordinate2d(  -1,  -1));
	character['A'].push_back(Coordinate2d(   0,   1));
	character['A'].push_back(Coordinate2d(   1,  -1));
	character['A'].push_back(Coordinate2d( 0.5,   0));
	character['A'].push_back(Coordinate2d(-0.5,   0));

	character['B'].push_back(Coordinate2d(  -1,  -1));
	character['B'].push_back(Coordinate2d(  -1,   1));
	character['B'].push_back(Coordinate2d(   1, 0.5));
	character['B'].push_back(Coordinate2d(  -1,   0));
	character['B'].push_back(Coordinate2d(   1,-0.5));
	character['B'].push_back(Coordinate2d(  -1,  -1));

	character['C'].push_back(Coordinate2d(   1,   1));
	character['C'].push_back(Coordinate2d(  -1,   1));
	character['C'].push_back(Coordinate2d(  -1,  -1));
	character['C'].push_back(Coordinate2d(   1,  -1));

	character['D'].push_back(Coordinate2d(  -1,  -1));
	character['D'].push_back(Coordinate2d(  -1,   1));
	character['D'].push_back(Coordinate2d(   1,   0));
	character['D'].push_back(Coordinate2d(  -1,  -1));

	character['E'].push_back(Coordinate2d(   1,   1));
	character['E'].push_back(Coordinate2d(  -1,   1));
	character['E'].push_back(Coordinate2d(  -1,   0));
	character['E'].push_back(Coordinate2d(   1,   0));
	character['E'].push_back(Coordinate2d(  -1,   0));
	character['E'].push_back(Coordinate2d(  -1,  -1));
	character['E'].push_back(Coordinate2d(   1,  -1));

	character['F'].push_back(Coordinate2d(   1,   1));
	character['F'].push_back(Coordinate2d(  -1,   1));
	character['F'].push_back(Coordinate2d(  -1,   0));
	character['F'].push_back(Coordinate2d(   1,   0));
	character['F'].push_back(Coordinate2d(  -1,   0));
	character['F'].push_back(Coordinate2d(  -1,  -1));

	character['G'].push_back(Coordinate2d(   0,   1));
	character['G'].push_back(Coordinate2d(  -1,   0));
	character['G'].push_back(Coordinate2d(   0,  -1));
	character['G'].push_back(Coordinate2d(   1,   0));
	character['G'].push_back(Coordinate2d(   0,   0));

	character['H'].push_back(Coordinate2d(  -1,  -1));
	character['H'].push_back(Coordinate2d(  -1,   1));
	character['H'].push_back(Coordinate2d(  -1,   0));
	character['H'].push_back(Coordinate2d(   1,   0));
	character['H'].push_back(Coordinate2d(   1,  -1));
	character['H'].push_back(Coordinate2d(   1,   1));

	character['I'].push_back(Coordinate2d(  -1,  -1));
	character['I'].push_back(Coordinate2d(   1,  -1));
	character['I'].push_back(Coordinate2d(   0,  -1));
	character['I'].push_back(Coordinate2d(   0,   1));
	character['I'].push_back(Coordinate2d(  -1,   1));
	character['I'].push_back(Coordinate2d(   1,   1));

	character['J'].push_back(Coordinate2d(   1,   1));
	character['J'].push_back(Coordinate2d(   1,  -1));
	character['J'].push_back(Coordinate2d(  -1,  -1));
	character['J'].push_back(Coordinate2d(  -1,   0));

	character['K'].push_back(Coordinate2d(  -1,  -1));
	character['K'].push_back(Coordinate2d(  -1,   1));
	character['K'].push_back(Coordinate2d(  -1,   0));
	character['K'].push_back(Coordinate2d(   1,   1));
	character['K'].push_back(Coordinate2d(  -1,   0));
	character['K'].push_back(Coordinate2d(   1,  -1));

	character['L'].push_back(Coordinate2d(  -1,   1));
	character['L'].push_back(Coordinate2d(  -1,  -1));
	character['L'].push_back(Coordinate2d(   1,  -1));

	character['M'].push_back(Coordinate2d(  -1,  -1));
	character['M'].push_back(Coordinate2d(  -1,   1));
	character['M'].push_back(Coordinate2d(   0,   0));
	character['M'].push_back(Coordinate2d(   1,   1));
	character['M'].push_back(Coordinate2d(   1,  -1));

	character['N'].push_back(Coordinate2d(  -1,  -1));
	character['N'].push_back(Coordinate2d(  -1,   1));
	character['N'].push_back(Coordinate2d(   1,  -1));
	character['N'].push_back(Coordinate2d(   1,   1));

	character['O'].push_back(Coordinate2d(   0,  -1));
	character['O'].push_back(Coordinate2d(  -1,   0));
	character['O'].push_back(Coordinate2d(   0,   1));
	character['O'].push_back(Coordinate2d(   1,   0));
	character['O'].push_back(Coordinate2d(   0,  -1));

	character['P'].push_back(Coordinate2d(  -1,  -1));
	character['P'].push_back(Coordinate2d(  -1,   1));
	character['P'].push_back(Coordinate2d(   1, 0.5));
	character['P'].push_back(Coordinate2d(  -1,   0));

	character['Q'].push_back(Coordinate2d(   0,  -1));
	character['Q'].push_back(Coordinate2d(  -1,   0));
	character['Q'].push_back(Coordinate2d(   0,   1));
	character['Q'].push_back(Coordinate2d(   1,   0));
	character['Q'].push_back(Coordinate2d(   0,  -1));
	character['Q'].push_back(Coordinate2d( 0.5,-0.5));
	character['Q'].push_back(Coordinate2d(   0,   0));
	character['Q'].push_back(Coordinate2d(   1,  -1));

	character['R'].push_back(Coordinate2d(  -1,  -1));
	character['R'].push_back(Coordinate2d(  -1,   1));
	character['R'].push_back(Coordinate2d(   1, 0.5));
	character['R'].push_back(Coordinate2d(  -1,   0));
	character['R'].push_back(Coordinate2d(   1,  -1));

	character['S'].push_back(Coordinate2d(   1,   1));
	character['S'].push_back(Coordinate2d(  -1,   1));
	character['S'].push_back(Coordinate2d(  -1,   0));
	character['S'].push_back(Coordinate2d(   1,   0));
	character['S'].push_back(Coordinate2d(   1,  -1));
	character['S'].push_back(Coordinate2d(  -1,  -1));

	character['T'].push_back(Coordinate2d(  -1,   1));
	character['T'].push_back(Coordinate2d(   1,   1));
	character['T'].push_back(Coordinate2d(   0,   1));
	character['T'].push_back(Coordinate2d(   0,  -1));

	character['U'].push_back(Coordinate2d(  -1,   1));
	character['U'].push_back(Coordinate2d(  -1,  -1));
	character['U'].push_back(Coordinate2d(   1,  -1));
	character['U'].push_back(Coordinate2d(   1,   1));

	character['V'].push_back(Coordinate2d(  -1,   1));
	character['V'].push_back(Coordinate2d(   0,  -1));
	character['V'].push_back(Coordinate2d(   1,   1));

	character['W'].push_back(Coordinate2d(  -1,   1));
	character['W'].push_back(Coordinate2d(-0.5,  -1));
	character['W'].push_back(Coordinate2d(   0,   1));
	character['W'].push_back(Coordinate2d( 0.5,  -1));
	character['W'].push_back(Coordinate2d(   1,   1));

	character['X'].push_back(Coordinate2d(  -1,  -1));
	character['X'].push_back(Coordinate2d(   1,   1));
	character['X'].push_back(Coordinate2d(   0,   0));
	character['X'].push_back(Coordinate2d(  -1,   1));
	character['X'].push_back(Coordinate2d(   1,  -1));

	character['Y'].push_back(Coordinate2d(  -1,   1));
	character['Y'].push_back(Coordinate2d(   0,   0));
	character['Y'].push_back(Coordinate2d(  -1,  -1));
	character['Y'].push_back(Coordinate2d(   1,   1));

	character['Z'].push_back(Coordinate2d(  -1,   1));
	character['Z'].push_back(Coordinate2d(   1,   1));
	character['Z'].push_back(Coordinate2d(  -1,  -1));
	character['Z'].push_back(Coordinate2d(   1,  -1));

	character[':'].push_back(Coordinate2d(-0.1, 0.5));
	character[':'].push_back(Coordinate2d( 0.1, 0.5));
	character[':'].push_back(Coordinate2d( 0.1, 0.7));
	character[':'].push_back(Coordinate2d(-0.1, 0.7));
	character[':'].push_back(Coordinate2d(-0.1, 0.5));
	character[':'].push_back(Coordinate2d(  42,  42));
	character[':'].push_back(Coordinate2d(-0.1,-0.5));
	character[':'].push_back(Coordinate2d( 0.1,-0.5));
	character[':'].push_back(Coordinate2d( 0.1,-0.7));
	character[':'].push_back(Coordinate2d(-0.1,-0.7));
	character[':'].push_back(Coordinate2d(-0.1,-0.5));

	character['.'].push_back(Coordinate2d(-0.1,-0.8));
	character['.'].push_back(Coordinate2d( 0.1,-0.8));
	character['.'].push_back(Coordinate2d( 0.1,  -1));
	character['.'].push_back(Coordinate2d(-0.1,  -1));
	character['.'].push_back(Coordinate2d(-0.1,-0.8));

	character[','].push_back(Coordinate2d(-0.2,-0.6));
	character[','].push_back(Coordinate2d( 0.2,-0.8));
	character[','].push_back(Coordinate2d(-0.2,  -1));

	character['?'].push_back(Coordinate2d(-0.2,-0.8));
	character['?'].push_back(Coordinate2d( 0.2,-0.8));
	character['?'].push_back(Coordinate2d( 0.2,-1.0));
	character['?'].push_back(Coordinate2d(-0.2,-1.0));
	character['?'].push_back(Coordinate2d(-0.2,-0.8));
	character['?'].push_back(Coordinate2d(  42,  42));
	character['?'].push_back(Coordinate2d(   0,-0.5));
	character['?'].push_back(Coordinate2d(   0, 0.5));
	character['?'].push_back(Coordinate2d( 0.5, 0.5));
	character['?'].push_back(Coordinate2d( 0.5,   1));
	character['?'].push_back(Coordinate2d(-0.5,   1));
	character['?'].push_back(Coordinate2d(-0.5, 0.5));

	character['\''].push_back(Coordinate2d(-0.2, 0.6));
	character['\''].push_back(Coordinate2d( 0.2, 0.8));
	character['\''].push_back(Coordinate2d(-0.2,   1));

	initialized = true;
}

void VectorLetter::writeCharacter(unsigned char c)
{
	if (!initialized)
		prepare();

	glBegin(GL_LINE_STRIP);
	{
		for (vector<Coordinate2d>::iterator it = character[c].begin();
				it != character[c].end(); ++it)
		{
			if (it->x > 20)
			{
				glEnd();
				glBegin(GL_LINE_STRIP);
			}
			else
				glVertex2d(it->x, it->y);
		}
	}
	glEnd();
}

}
