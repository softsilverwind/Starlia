#include <GL/glu.h>
#include <iostream>
#include <list>
#include "core.h"
#include "layer.h"
	
using namespace std;

namespace Starlia
{

StarLayer::StarLayer()
	: invalid(false)
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

StarObjectLayer::StarObjectLayer(Coordinate2d size) : Star2dLayer(size)
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

StarWidgetLayer::StarWidgetLayer(Coordinate2d size, bool blockFallThrough) : Star2dLayer(size), blockFallThrough(blockFallThrough)
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

Star3dLayer::Star3dLayer(Coordinate3d campos, Coordinate3d lookpos, Coordinate3d n)
	: campos(campos), lookpos(lookpos), n(n)
{
}

void Star3dLayer::draw()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, StarCore::getScale().x / StarCore::getScale().y, 1, 10000);
	gluLookAt(campos.x, campos.y, campos.z, lookpos.x, lookpos.y, lookpos.z, n.x, n.y, n.z);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	StarLayer::draw();

	glDisable(GL_DEPTH_TEST);
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

}
