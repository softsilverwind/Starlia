#include <iostream>
#include <memory>
#include <list>

#include <GL/glew.h>
#include <SDL/SDL.h>
#include <SDL/SDL_events.h>

#include <core/layer.h>
#include <core/object.h>
#include <core/core.h>
#include <core/timer.h>

using namespace std;

namespace Starlia
{

list<shared_ptr<SLayer>> StarCore::layers;
unsigned int StarCore::last_update = 0;
Coord2d StarCore::scale;

inline void StarCore::draw()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto it = layers.begin(); it != layers.end(); ++it)
	{
		if ((*it)->invalid)
		{
			(*it)->invalid = false;
			layers.erase(it--);
		}
	}

	auto fit = layers.begin();
	while (fit != layers.end() && !((*fit)->block & Block_Draw))
		++fit;

	if (fit != layers.end())
		++fit;

	for (auto rit = reverse_iterator<list<shared_ptr<SLayer>>::iterator>(fit);
			rit != layers.rend(); ++rit)
		(*rit)->draw();
}

inline void StarCore::update()
{
	unsigned int time_now = SDL_GetTicks();

	for (unsigned int i = 0; i < time_now/10 - last_update/10; ++i)
	{
		for (auto it = layers.begin(); it != layers.end(); ++it)
		{
			if ((*it)->block & Block_Update)
				break;

			if ((*it)->invalid)
			{
				(*it)->invalid = false;
				layers.erase(it--);
				continue;
			}

			(*it)->update();
		}
	}

	last_update = time_now;
}

inline void StarCore::resize(int width, int height)
{
	scale.x = width;
	scale.y = height;
	glViewport(0, 0, width, height);
}

inline void StarCore::eventClick(int x, int y)
{
	Coord2d pos;
	pos.x = x / scale.x;
	pos.y = 1 - y / scale.y;

	for(auto it = layers.begin();
			it != layers.end() && !(*it)->eventClick(pos); ++it)
		;
}

inline void StarCore::eventKeyPress(SDL_keysym c)
{
	for(auto it = layers.begin();
			it != layers.end() && !(*it)->eventKeyPress(c.sym); ++it)
		;
}

inline void StarCore::eventKeyRelease(SDL_keysym c)
{
	for(auto it = layers.begin();
			it != layers.end() && !(*it)->eventKeyRelease(c.sym); ++it)
		;
}

inline void StarCore::eventMouseOver(int x, int y)
{
	Coord2d pos;
	pos.x = x / scale.x;
	pos.y = 1 - y / scale.y;

	for(auto it = layers.rbegin();
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
					eventMouseOver(ev.motion.x, ev.motion.y);
					break;
				case SDL_MOUSEBUTTONDOWN:
					eventClick(ev.button.x, ev.button.y);
					break;
				case SDL_KEYDOWN:
					eventKeyPress(ev.key.keysym);
					break;
				case SDL_KEYUP:
					eventKeyRelease(ev.key.keysym);
					break;
				default:
					break;
			}
		}
		StarCore::update();
		StarCore::draw();
		SDL_GL_SwapBuffers();
		STimer::loopTimers(last_update);
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

	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK)
	{
		cerr << "Error: " << glewGetErrorString(glew_status) << endl;
		throw 42;
	}
}

void StarCore::addFront(SLayer *layer)
{
	layers.push_front(shared_ptr<SLayer>(layer));
}

void StarCore::addFront(shared_ptr<SLayer> layer)
{
	layers.push_front(layer);
}


void StarCore::addBack(SLayer *layer)
{
	layers.push_back(shared_ptr<SLayer>(layer));
}

void StarCore::addBack(shared_ptr<SLayer> layer)
{
	layers.push_back(layer);
}

}
