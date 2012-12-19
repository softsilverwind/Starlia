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
	for (auto it : objects)
		delete it;

	objects.clear();
}

void StarLayer::invalidate()
{
	invalid = true;
}

void StarLayer::draw()
{
	for (auto it : objects)
	{
		glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		it->draw();
		glPopAttrib();
		glPopMatrix();
	}
}

void StarLayer::update()
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		bool del = false, rem = false;
		StarObject::canHasEmit = true;
		(*it)->update();
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
			objects.erase(it--);
			continue;
		}

		if (rem)
		{
			objects.erase(it--);
		}
	}
}

bool StarLayer::eventKeyPress(SDLKey c)
{
	map<SDLKey, function<void (void)> >::iterator it = keypresses.find(c);

	if (it != keypresses.end())
	{
		(it->second)();
		return true;
	}

	return blockFallThrough;
}

bool StarLayer::eventKeyRelease(SDLKey c)
{
	map<SDLKey, function<void (void)> >::iterator it = keyreleases.find(c);

	if (it != keyreleases.end())
	{
		(it->second)();
		return true;
	}

	return blockFallThrough;
}

void StarLayer::addKeyPress(SDLKey c, function<void (void)> fun)
{
	keypresses[c] = fun;
}

void StarLayer::addKeyPress(char c, function<void (void)> fun)
{
	keypresses[(SDLKey) c] = fun;
}

void StarLayer::addKeyRelease(SDLKey c, function<void (void)> fun)
{
	keyreleases[c] = fun;
}

void StarLayer::addKeyRelease(char c, function<void (void)> fun)
{
	keyreleases[(SDLKey) c] = fun;
}

void StarLayer::setBlockFallThrough(bool block)
{
	blockFallThrough = block;
}

StarWidgetLayer::StarWidgetLayer()
{
}

void StarWidgetLayer::add(StarWidget *object)
{
	objects.push_back(object);
}

void StarWidgetLayer::remove(StarWidget *object)
{
	for (auto it : objects)
		if (it == object)
		{
			invalidate(it);
			return;
		}
}

bool StarWidgetLayer::eventClick(Coord2d position)
{
	for (auto it : objects)
	{
		StarWidget *sw = static_cast<StarWidget *>(it); // and may god be with me...
		Coord2d tl, br;

		tl = sw->getTopLeft();
		br = sw->getBotRight();

		if (position.x >= tl.x && position.x <= br.x && position.y <= tl.y && position.y >= br.y)
		{
			Coord2d pos((position - tl) / (br - tl));
			return sw->eventClick(pos) || blockFallThrough;
		}
	}
	return blockFallThrough;
}

bool StarWidgetLayer::eventMouseOver(Coord2d position)
{
	for (auto it : objects)
	{
		StarWidget *sw = static_cast<StarWidget *>(it); // and may god forgive me...
		Coord2d tl, br;

		tl = sw->getTopLeft();
		br = sw->getBotRight();

		if (position.x >= tl.x && position.x <= br.x && position.y <= tl.y && position.y >= br.y)
		{
			Coord2d pos((position - tl) / (br - tl));
			return sw->eventMouseOver(pos) || blockFallThrough;
		}
	}
	return blockFallThrough;
}

StarObjectLayer::StarObjectLayer()
{
}

StarObjectLayer::~StarObjectLayer()
{
}

void StarObjectLayer::draw()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);

	StarLayer::draw();

	glDisable(GL_DEPTH_TEST);
}

void StarObjectLayer::update()
{
	return StarLayer::update();
}

void StarObjectLayer::add(StarObject *object)
{
	objects.push_back(object);
}

void StarObjectLayer::remove(StarObject *object)
{
	for (auto it : objects)
		if (it == object)
		{
			invalidate(it);
			return;
		}
}

}
