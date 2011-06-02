#include <GL/glu.h>
#include <iostream>
#include <list>
#include "layer.h"
	
using namespace std;

namespace Starlia
{

StarLayer::StarLayer(Coordinate2d size)
	: size(size), invalid(false)
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

StarObjectLayer::StarObjectLayer(Coordinate2d size) : StarLayer(size)
{
}

void StarObjectLayer::registerObject(StarObject *object, void (*onEnd)(), bool remove, bool destroy)
{
	if (destroy)
		remove = true;

	objectList.push_back(EntryType(object, onEnd, remove, destroy));
}

void StarObjectLayer::unregisterObject(StarObject *object)
{
	for (list<EntryType>::iterator it = objectList.begin(); it != objectList.end(); ++it)
		if (it->object == object)
		{
			it->invalid = true;
			return;
		}

	cerr << "Unregistering invalid object: " << object->tag << endl;
}

StarWidgetLayer::StarWidgetLayer(Coordinate2d size, bool blockFallThrough) : StarLayer(size), blockFallThrough(blockFallThrough)
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

}
