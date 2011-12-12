#include <SDL/SDL.h>
#include <GL/glu.h>
#include <iostream>
#include <vector>
#include <list>
#include "core.h"
#include "layer.h"
#include "starLight.h"
#include "camera.h"
	
using namespace std;

namespace Starlia
{

StarLayer::StarLayer()
	: blockFallThrough(false), invalid(false)
{
}

StarLayer::~StarLayer()
{
	clearLayer();
}

void StarLayer::clearLayer()
{
	for (list<EntryType>::iterator it = objectList.begin(); it != objectList.end(); ++it)
	{
		if (it->destroy)
			delete it->object;

		objectList.erase(it--);
	}
}

void StarLayer::draw()
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

		glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
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

bool StarLayer::keypress(SDLKey c)
{
	map<SDLKey, void (*)()>::iterator it = keypresses.find(c);

	if (it != keypresses.end())
	{
		(*(it->second))();
		return true;
	}

	return blockFallThrough;
}

bool StarLayer::keyrelease(SDLKey c)
{
	map<SDLKey, void (*)()>::iterator it = keyreleases.find(c);

	if (it != keyreleases.end())
	{
		(*(it->second))();
		return true;
	}

	return blockFallThrough;
}

void StarLayer::registerKeyPress(SDLKey c, void (*fun)())
{
	keypresses[c] = fun;
}

void StarLayer::registerKeyPress(char c, void (*fun)())
{
	keypresses[(SDLKey) c] = fun;
}

void StarLayer::registerKeyRelease(SDLKey c, void (*fun)())
{
	keyreleases[c] = fun;
}

void StarLayer::registerKeyRelease(char c, void (*fun)())
{
	keyreleases[(SDLKey) c] = fun;
}

void StarLayer::setBlockFallThrough(bool block)
{
	blockFallThrough = block;
}

Star2dLayer::Star2dLayer(Coordinate2d size) : size(size)
{
}

void Star2dLayer::draw()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, size.x, 0, size.y);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	StarLayer::draw();
}

Star2dObjectLayer::Star2dObjectLayer(Coordinate2d size) : Star2dLayer(size)
{
}

void Star2dObjectLayer::registerObject(StarObject *object, void (*onEnd)(), bool remove, bool destroy)
{
	if (destroy)
		remove = true;

	objectList.push_back(EntryType(object, onEnd, remove, destroy));
}

void Star2dObjectLayer::unregisterObject(StarObject *object)
{
	for (list<EntryType>::iterator it = objectList.begin(); it != objectList.end(); ++it)
		if (it->object == object)
		{
			it->invalid = true;
			return;
		}

	cerr << "Unregistering invalid object: " << object->tag << endl;
}

StarWidgetLayer::StarWidgetLayer(Coordinate2d size) : Star2dLayer(size)
{
}

void StarWidgetLayer::registerObject(StarWidget *object, void (*onEnd)(), bool remove, bool destroy)
{
	if (destroy)
		remove = true;

	objectList.push_back(EntryType(object, onEnd, remove, destroy));
}

void StarWidgetLayer::unregisterObject(StarWidget *object)
{
	for (list<EntryType>::iterator it = objectList.begin(); it != objectList.end(); ++it)
		if (it->object == object)
		{
			it->invalid = true;
			return;
		}

	cerr << "Unregistering invalid object: " << object->tag << endl;
}

bool StarWidgetLayer::click(Coordinate2d position)
{
	position *= size;

	for (list<EntryType>::iterator it = objectList.begin(); it != objectList.end(); ++it)
	{
		StarWidget *it2 = (StarWidget *) it->object;
		Coordinate2d tl, br;

		tl = it2->getTopLeft();
		br = it2->getBotRight();

		if (position.x >= tl.x && position.x <= br.x && position.y <= tl.y && position.y >= br.y)
		{
			Coordinate2d pos((position - tl) / (br - tl));
			return it2->click(pos) || blockFallThrough;
		}
	}
	return blockFallThrough;
}

bool StarWidgetLayer::mouseOver(Coordinate2d position)
{
	position *= size;

	for (list<EntryType>::iterator it = objectList.begin(); it != objectList.end(); ++it)
	{
		StarWidget *it2 = (StarWidget *) it->object;
		Coordinate2d tl, br;

		tl = it2->getTopLeft();
		br = it2->getBotRight();

		if (position.x >= tl.x && position.x <= br.x && position.y <= tl.y && position.y >= br.y)
		{
			Coordinate2d pos((position - tl) / (br - tl));
			return it2->mouseOver(pos) || blockFallThrough;
		}
	}
	return blockFallThrough;
}

Star3dLayer::Star3dLayer(StarCamera *camera)
	: camera(camera)
{
	lightNums.push_back(GL_LIGHT7);
	lightNums.push_back(GL_LIGHT6);
	lightNums.push_back(GL_LIGHT5);
	lightNums.push_back(GL_LIGHT4);
	lightNums.push_back(GL_LIGHT3);
	lightNums.push_back(GL_LIGHT2);
	lightNums.push_back(GL_LIGHT1);
	lightNums.push_back(GL_LIGHT0);
}

Star3dLayer::~Star3dLayer()
{
	if (camera)
		delete camera;
}

void Star3dLayer::draw()
{
	glEnable(GL_NORMALIZE);
        glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_LIGHT6);
	glEnable(GL_LIGHT7);

	for (vector<GLenum>::iterator it = lightNums.begin(); it != lightNums.end(); ++it)
		glDisable(*it);

	for (list<StarLight *>::iterator it = lights.begin(); it != lights.end(); ++it)
		(*it)->prepLight();

	camera->draw();

	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);

	StarLayer::draw();

	glDisable(GL_DEPTH_TEST);

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);
	glDisable(GL_LIGHT5);
	glDisable(GL_LIGHT6);
	glDisable(GL_LIGHT7);

	glDisable(GL_LIGHTING);
	glDisable(GL_NORMALIZE);
}

bool Star3dLayer::recalc()
{
	camera->recalc();
	return StarLayer::recalc();
}

void Star3dLayer::registerObject(StarObject *object, void (*onEnd)(), bool remove, bool destroy)
{
	if (destroy)
		remove = true;

	objectList.push_back(EntryType(object, onEnd, remove, destroy));
}

void Star3dLayer::unregisterObject(StarObject *object)
{
	for (list<EntryType>::iterator it = objectList.begin(); it != objectList.end(); ++it)
		if (it->object == object)
		{
			it->invalid = true;
			return;
		}

	cerr << "Unregistering invalid object: " << object->tag << endl;
}


void Star3dLayer::registerObject(StarLight *light, void (*onEnd)(), bool remove, bool destroy)
{
	light->setLightNum(lightNums.back());
	lightNums.pop_back();
	lights.push_back(light);
	registerObject((Star3dObject *) light, onEnd, remove, destroy);
}

void Star3dLayer::unregisterObject(StarLight *light)
{
	for (list<StarLight *>::iterator it = lights.begin(); it != lights.end(); ++it)
		if (*it == light)
			lights.erase(it);

	lightNums.push_back(light->getLightNum());
	unregisterObject((Star3dObject *) light);
}

void Star3dLayer::registerObject(StarCamera *cam, bool deletePrev)
{
	if (deletePrev)
		delete camera;
	camera = cam;
}

}
