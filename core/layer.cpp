#include <SDL/SDL.h>
#include <GL/glu.h>
#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include "core.h"
#include "layer.h"
#include "starLight.h"
#include "camera.h"
	
using namespace std;

namespace Starlia
{

void StarLayer::invalidate(StarObject * so)
{
	so->invalid = true;
}

StarLayer::StarLayer()
	: blockFallThrough(false), invalid(false)
{
}

StarLayer::~StarLayer()
{
	demolishLayer();
}

void StarLayer::demolishLayer()
{
	for (auto it : objectList)
		delete it;

	objectList.clear();
}

void StarLayer::draw()
{
	for (auto it : objectList)
	{
		glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		it->draw();
		glPopAttrib();
		glPopMatrix();
	}
}

void StarLayer::recalc()
{
	for (auto it = objectList.begin(); it != objectList.end(); ++it)
	{
		bool del = false, rem = false;
		StarObject::canHasEmit = true;
		(*it)->recalc();
		StarObject::canHasEmit = false;

		for(string& str : StarObject::emittedSignals)
		{
			if (!str.compare("_delete"))
			{
				del = true;
				rem = true;
			}
			else if (!str.compare("_remove"))
			{
				rem = true;
			}
			else
			{
				auto fun = (*it)->connections[str];
				if (fun)
				{
					fun();
				}
			}
		}

		StarObject::emittedSignals.clear();

		if (del)
		{
			delete *it;
		}
		else if ((*it)->invalid)
		{
			objectList.erase(it--);
			continue;
		}

		if (rem)
		{
			objectList.erase(it--);
		}
	}
}

bool StarLayer::keypress(SDLKey c)
{
	map<SDLKey, function<void (void)> >::iterator it = keypresses.find(c);

	if (it != keypresses.end())
	{
		(it->second)();
		return true;
	}

	return blockFallThrough;
}

bool StarLayer::keyrelease(SDLKey c)
{
	map<SDLKey, function<void (void)> >::iterator it = keyreleases.find(c);

	if (it != keyreleases.end())
	{
		(it->second)();
		return true;
	}

	return blockFallThrough;
}

void StarLayer::registerKeyPress(SDLKey c, function<void (void)> fun)
{
	keypresses[c] = fun;
}

void StarLayer::registerKeyPress(char c, function<void (void)> fun)
{
	keypresses[(SDLKey) c] = fun;
}

void StarLayer::registerKeyRelease(SDLKey c, function<void (void)> fun)
{
	keyreleases[c] = fun;
}

void StarLayer::registerKeyRelease(char c, function<void (void)> fun)
{
	keyreleases[(SDLKey) c] = fun;
}

void StarLayer::setBlockFallThrough(bool block)
{
	blockFallThrough = block;
}

Star2dLayer::Star2dLayer(Coord2d size) : size(size)
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

Star2dObjectLayer::Star2dObjectLayer(Coord2d size) : Star2dLayer(size)
{
}

void Star2dObjectLayer::registerObject(StarObject *object)
{
	objectList.push_back(object);
}

void Star2dObjectLayer::unregisterObject(StarObject *object)
{
	for (auto it : objectList)
		if (it == object)
		{
			invalidate(it);
			return;
		}
}

StarWidgetLayer::StarWidgetLayer(Coord2d size) : Star2dLayer(size)
{
}

void StarWidgetLayer::registerObject(StarWidget *object)
{
	objectList.push_back(object);
}

void StarWidgetLayer::unregisterObject(StarWidget *object)
{
	for (auto it : objectList)
		if (it == object)
		{
			invalidate(it);
			return;
		}
}

bool StarWidgetLayer::click(Coord2d position)
{
	position *= size;

	for (auto it : objectList)
	{
		StarWidget *it2 = (StarWidget *) it;
		Coord2d tl, br;

		tl = it2->getTopLeft();
		br = it2->getBotRight();

		if (position.x >= tl.x && position.x <= br.x && position.y <= tl.y && position.y >= br.y)
		{
			Coord2d pos((position - tl) / (br - tl));
			return it2->click(pos) || blockFallThrough;
		}
	}
	return blockFallThrough;
}

bool StarWidgetLayer::mouseOver(Coord2d position)
{
	position *= size;

	for (auto it : objectList)
	{
		StarWidget *it2 = (StarWidget *) it;
		Coord2d tl, br;

		tl = it2->getTopLeft();
		br = it2->getBotRight();

		if (position.x >= tl.x && position.x <= br.x && position.y <= tl.y && position.y >= br.y)
		{
			Coord2d pos((position - tl) / (br - tl));
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

void Star3dLayer::recalc()
{
	camera->recalc();
	return StarLayer::recalc();
}

void Star3dLayer::registerObject(StarObject *object)
{
	objectList.push_back(object);
}

void Star3dLayer::unregisterObject(StarObject *object)
{
	for (auto it : objectList)
		if (it == object)
		{
			invalidate(it);
			return;
		}
}

void Star3dLayer::registerObject(StarLight *light)
{
	light->setLightNum(lightNums.back());
	lightNums.pop_back();
	lights.push_back(light);
	registerObject((Star3dObject *) light);
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
