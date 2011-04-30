#include <iostream>
#include <cstdio>
#include <list>
#include <GL/glut.h>

#include "object.h"
#include "core.h"
#include "basicRender.h"

using namespace std;

namespace Starlia
{

StarLayer::StarLayer(Coordinate2d size)
	: size(size), invalid(false)
{
}

void StarLayer::registerObject(StarObject *object, void (*onEnd)(), bool remove, bool destroy)
{
	if (destroy)
		remove = true;

	objectList.push_back(EntryType(object, onEnd, remove, destroy));
}

void StarLayer::unregisterObject(StarObject *object)
{
	for (list<EntryType>::iterator it = objectList.begin(); it != objectList.end(); ++it)
		if (it->object == object)
		{
			it->invalid = true;
			return;
		}

	cerr << "Unregistering invalid object: " << object->tag << endl;
}

void StarLayer::registerWidget(StarWidget *widget, void (*onEnd)(), bool remove, bool destroy)
{
	clickList.push_back(widget);
	registerObject(widget, onEnd, remove, destroy);
}

void StarLayer::unregisterWidget(StarWidget *widget)
{
	for (list<StarWidget *>::iterator it = clickList.begin(); it != clickList.end(); ++it)
		if (*it == widget)
		{
			clickList.erase(it);
			break;
		}

	unregisterObject(widget);
}

bool StarLayer::click(Coordinate2d position)
{
	position *= size;

	for (list<StarWidget *>::iterator it = clickList.begin(); it != clickList.end(); ++it)
	{
		Coordinate2d tl, br;

		tl = (*it)->getTopLeft();
		br = (*it)->getBotRight();

		if (position.x >= tl.x && position.x <= br.x && position.y <= tl.y && position.y >= br.y)
		{
			(*it)->click();
			return true;
		}
	}
	return false;
}

void StarLayer::draw()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, size.x, 0, size.y);
	glMatrixMode(GL_MODELVIEW);

	for (list<EntryType>::iterator it = objectList.begin(); it != objectList.end(); ++it)
	{
		if (it->invalid)
		{
			if (it->destroy)
				delete it->object;

			objectList.erase(it--);
			continue;
		}
	
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		it->object->draw();
		glPopAttrib();
		glPopMatrix();
	}
}

bool StarLayer::recalc()
{
	for (list<EntryType>::iterator it = objectList.begin(); it != objectList.end(); ++it)
	{
		if (it->invalid)
		{
			if (it->destroy)
				delete it->object;

			objectList.erase(it--);
			continue;
		}

		if (!(it->object->recalc()))
		{
			if (it->onEnd)
				it->onEnd();

			if (it->destroy)
				delete it->object;
			
			if (it->remove)
				objectList.erase(it--);
		}
	}
	return true;
}

list<StarLayer *> StarCore::layers;
unsigned int StarCore::last_recalc = 0;
Coordinate2d StarCore::scale;

void StarCore::draw()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);


	for (list<StarLayer *>::iterator it = layers.begin(); it != layers.end(); ++it)
	{
		if ((*it)->invalid)
		{
			layers.erase(it--);
			continue;
		}

		(*it)->draw();
	}
}

void StarCore::recalc()
{
	unsigned int time_now = glutGet(GLUT_ELAPSED_TIME);

	for (unsigned int i = 0; i < time_now/10 - last_recalc/10; ++i)
		for (list<StarLayer *>::iterator it = layers.begin(); it != layers.end(); ++it)
		{
			if ((*it)->invalid)
			{
				layers.erase(it--);
				continue;
			}

			(*it)->recalc();
		}

	last_recalc = time_now;
}

void StarCore::display()
{
	StarCore::draw();
	glutSwapBuffers();
}

void StarCore::resize(int width, int height)
{
	scale.x = width;
	scale.y = height;
	glViewport(0, 0, width, height);
}

void StarCore::idle(int _)
{
	StarCore::recalc();
	glutTimerFunc(10, idle, 42);
	glutPostRedisplay();
}

void StarCore::click(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		Coordinate2d pos;
		pos.x = x / scale.x;
		pos.y = 1 - y / scale.y;

		layers.back()->click(pos);
	}
}

void StarCore::loop()
{
	last_recalc = glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();
}

void StarCore::init(string title, int width, int height)
{
	char *argv[1];
	int argc = 1;
	argv[0] = (char *) "Starlia";

	scale.x = width;
	scale.y = height;

	glutInit(&argc, argv);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);

	glutCreateWindow(title.c_str());

	glutDisplayFunc(StarCore::display);
	glutReshapeFunc(StarCore::resize);
	glutMouseFunc(StarCore::click);

	glutTimerFunc(10, StarCore::idle, 42);
}

void StarCore::registerLayerForeground(StarLayer *layer)
{
	layers.push_back(layer);
}

void StarCore::registerLayerBackground(StarLayer *layer)
{
	layers.push_front(layer);
}

void StarCore::unregisterLayer(StarLayer *layer)
{
	for (list<StarLayer *>::iterator it = layers.begin(); it != layers.end(); ++it)
		if (*it == layer)
		{
			(*it)->invalid = true;
			return;
		}

	cerr << "Unregistering invalid layer: " << layer->tag << endl;
}

}
