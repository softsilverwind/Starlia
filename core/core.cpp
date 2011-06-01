#include <iostream>
#include <cstdio>
#include <list>
#include <GL/glut.h>

#include "layer.h"
#include "object.h"
#include "core.h"
#include "basicRender.h"

using namespace std;

namespace Starlia
{

list<StarObjectLayer *> StarCore::objectLayers;
list<StarWidgetLayer *> StarCore::widgetLayers;
unsigned int StarCore::last_recalc = 0;
Coordinate2d StarCore::scale;

void StarCore::draw()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);


	for (list<StarObjectLayer *>::iterator it = objectLayers.begin(); it != objectLayers.end(); ++it)
	{
		if ((*it)->invalid)
		{
			objectLayers.erase(it--);
			continue;
		}

		(*it)->draw();
	}

	for (list<StarWidgetLayer *>::iterator it = widgetLayers.begin(); it != widgetLayers.end(); ++it)
	{
		if ((*it)->invalid)
		{
			widgetLayers.erase(it--);
			continue;
		}

		(*it)->draw();
	}
}

void StarCore::recalc()
{
	unsigned int time_now = glutGet(GLUT_ELAPSED_TIME);

	for (unsigned int i = 0; i < time_now/10 - last_recalc/10; ++i)
	{
		for (list<StarObjectLayer *>::iterator it = objectLayers.begin(); it != objectLayers.end(); ++it)
		{
			if ((*it)->invalid)
			{
				objectLayers.erase(it--);
				continue;
			}

			(*it)->recalc();
		}

		for (list<StarWidgetLayer *>::iterator it = widgetLayers.begin(); it != widgetLayers.end(); ++it)
		{
			if ((*it)->invalid)
			{
				widgetLayers.erase(it--);
				continue;
			}

			(*it)->recalc();
		}
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

		widgetLayers.back()->click(pos);
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

void StarCore::registerLayerForeground(StarObjectLayer *layer)
{
	objectLayers.push_back(layer);
}

void StarCore::registerLayerBackground(StarObjectLayer *layer)
{
	objectLayers.push_front(layer);
}

void StarCore::unregisterLayer(StarObjectLayer *layer)
{
	for (list<StarObjectLayer *>::iterator it = objectLayers.begin(); it != objectLayers.end(); ++it)
		if (*it == layer)
		{
			(*it)->invalid = true;
			return;
		}

	cerr << "Unregistering invalid layer: " << layer->tag << endl;
}

void StarCore::registerLayerForeground(StarWidgetLayer *layer)
{
	widgetLayers.push_back(layer);
}

void StarCore::registerLayerBackground(StarWidgetLayer *layer)
{
	widgetLayers.push_front(layer);
}

void StarCore::unregisterLayer(StarWidgetLayer *layer)
{
	for (list<StarWidgetLayer *>::iterator it = widgetLayers.begin(); it != widgetLayers.end(); ++it)
		if (*it == layer)
		{
			(*it)->invalid = true;
			return;
		}

	cerr << "Unregistering invalid layer: " << layer->tag << endl;
}

}
