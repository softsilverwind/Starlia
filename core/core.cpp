#include <iostream>
#include <cstdio>
#include <list>
#include <SDL/SDL.h>
#include <SDL/SDL_events.h>
#include <SDL/SDL_opengl.h>

#include "layer.h"
#include "object.h"
#include "core.h"
#include "timer.h"
#include "sound.h"

using namespace std;

namespace Starlia
{

list<StarLayer *> StarCore::layers;
unsigned int StarCore::last_recalc = 0;
Coord2d StarCore::scale;

void StarCore::draw()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (list<StarLayer *>::iterator it = layers.begin(); it != layers.end(); ++it)
	{
		if ((*it)->invalid)
		{
			(*it)->invalid = false;
			layers.erase(it--);
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
		for (list<StarLayer *>::iterator it = layers.begin(); it != layers.end(); ++it)
		{
			if ((*it)->invalid)
			{
				(*it)->invalid = false;
				layers.erase(it--);
				continue;
			}

			(*it)->recalc();
		}
	}

	last_recalc = time_now;
}

inline void StarCore::resize(int width, int height)
{
	scale.x = width;
	scale.y = height;
	glViewport(0, 0, width, height);
}

inline void StarCore::click(int x, int y)
{
	Coord2d pos;
	pos.x = x / scale.x;
	pos.y = 1 - y / scale.y;

	for(list<StarLayer *>::reverse_iterator it = layers.rbegin();
			it != layers.rend() && !(*it)->eventClick(pos); ++it)
		;
}

inline void StarCore::keypress(SDL_keysym c)
{
	for(list<StarLayer *>::reverse_iterator it = layers.rbegin();
			it != layers.rend() && !(*it)->eventKeyPress(c.sym); ++it)
		;
}

inline void StarCore::keyrelease(SDL_keysym c)
{
	for(list<StarLayer *>::reverse_iterator it = layers.rbegin();
			it != layers.rend() && !(*it)->eventKeyRelease(c.sym); ++it)
		;
}

inline void StarCore::mouseOver(int x, int y)
{
	Coord2d pos;
	pos.x = x / scale.x;
	pos.y = 1 - y / scale.y;

	for(list<StarLayer *>::reverse_iterator it = layers.rbegin();
			it != layers.rend() && !(*it)->eventMouseOver(pos); ++it)
		;
}

void StarCore::loop()
{
	SDL_Event ev;
	bool looping = true;

	while(looping)
	{
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
				case SDL_KEYDOWN:
					keypress(ev.key.keysym);
					break;
				case SDL_KEYUP:
					keyrelease(ev.key.keysym);
					break;
				default:
					break;
			}
		}
		StarCore::recalc();
		StarCore::draw();
		SDL_GL_SwapBuffers();
		StarTimer::loopTimers(last_recalc);
		SDL_Delay(10);
	}
}

void StarCore::init(string title, int width, int height)
{
	scale.x = width;
	scale.y = height;

	SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO);
	SDL_WM_SetCaption(title.c_str(), NULL);

	SDL_SetVideoMode(width, height, 32, SDL_OPENGL);

	StarSound::initialize();
}

void StarCore::addFront(StarLayer *layer)
{
	layers.push_back(layer);
}

void StarCore::addBack(StarLayer *layer)
{
	layers.push_front(layer);
}

void StarCore::remove(StarLayer *layer)
{
	for (list<StarLayer *>::iterator it = layers.begin(); it != layers.end(); ++it)
		if (*it == layer)
		{
			(*it)->invalid = true;
			return;
		}
}

}
