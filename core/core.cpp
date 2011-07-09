#include <iostream>
#include <cstdio>
#include <list>
#include <SDL/SDL.h>
#include <SDL/SDL_events.h>
#include <SDL/SDL_opengl.h>

#include "layer.h"
#include "object.h"
#include "core.h"
#include "basicRender.h"

using namespace std;

namespace Starlia
{

list<StarObjectLayer *> StarCore::objectLayers;
list<StarWidgetLayer *> StarCore::widgetLayers;
Star3dLayer *StarCore::layer3d = NULL;
unsigned int StarCore::last_recalc = 0;
Coordinate2d StarCore::scale;

void StarCore::draw()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);

	if (layer3d)
		layer3d->draw();

	for (list<StarObjectLayer *>::iterator it = objectLayers.begin(); it != objectLayers.end(); ++it)
	{
		if ((*it)->invalid)
		{
			(*it)->invalid = false;
			objectLayers.erase(it--);
			continue;
		}

		(*it)->draw();
	}

	for (list<StarWidgetLayer *>::iterator it = widgetLayers.begin(); it != widgetLayers.end(); ++it)
	{
		if ((*it)->invalid)
		{
			(*it)->invalid = false;
			widgetLayers.erase(it--);
			continue;
		}

		(*it)->draw();
	}
}

void StarCore::recalc()
{
	unsigned int time_now = SDL_GetTicks();

	for (unsigned int i = 0; i < time_now/10 - last_recalc/10; ++i)
	{
		if (layer3d)
			layer3d->recalc();

		for (list<StarObjectLayer *>::iterator it = objectLayers.begin(); it != objectLayers.end(); ++it)
		{
			if ((*it)->invalid)
			{
				(*it)->invalid = false;
				objectLayers.erase(it--);
				continue;
			}

			(*it)->recalc();
		}

		for (list<StarWidgetLayer *>::iterator it = widgetLayers.begin(); it != widgetLayers.end(); ++it)
		{
			if ((*it)->invalid)
			{
				(*it)->invalid = false;
				widgetLayers.erase(it--);
				continue;
			}

			(*it)->recalc();
		}
	}


	last_recalc = time_now;
}

inline void StarCore::display()
{
	StarCore::draw();
}

inline void StarCore::resize(int width, int height)
{
	scale.x = width;
	scale.y = height;
	glViewport(0, 0, width, height);
}

inline void StarCore::idle()
{
	StarCore::recalc();
}

inline void StarCore::click(int x, int y)
{
	Coordinate2d pos;
	pos.x = x / scale.x;
	pos.y = 1 - y / scale.y;

	for(list<StarWidgetLayer *>::reverse_iterator it = widgetLayers.rbegin();
			it != widgetLayers.rend() && !(*it)->click(pos); ++it)
		;
}

inline void StarCore::mouseOver(int x, int y)
{
	Coordinate2d pos;
	pos.x = x / scale.x;
	pos.y = 1 - y / scale.y;

	for(list<StarWidgetLayer *>::reverse_iterator it = widgetLayers.rbegin();
			it != widgetLayers.rend() && !(*it)->mouseOver(pos); ++it)
		;
}

void StarCore::loop()
{
	SDL_Event ev;
	bool looping = true;

	while(looping)
	{
		last_recalc = SDL_GetTicks();
		while(SDL_PollEvent(&ev))
		{
			switch(ev.type)
			{
				case SDL_QUIT:
					looping = false;
					break;
				case SDL_MOUSEMOTION:
					mouseOver(ev.motion.x, ev.motion.y);
					break;
				case SDL_MOUSEBUTTONDOWN:
					click(ev.button.x, ev.button.y);
					break;
				case SDL_VIDEORESIZE:
					resize(ev.resize.w, ev.resize.h);
					break;
				default:
					break;
			}
		}
		idle();
		display();
		SDL_Delay(10);
	}
}

void StarCore::init(string title, int width, int height)
{
	scale.x = width;
	scale.y = height;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetVideoMode(width, height, 32, SDL_OPENGL | SDL_RESIZABLE);
	SDL_WM_SetCaption(title.c_str(), NULL);
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

void StarCore::registerLayer(Star3dLayer *layer)
{
	layer3d = layer;
}

}
