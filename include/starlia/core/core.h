#ifndef __CORE_H__
#define __CORE_H__

#include <string>
#include <list>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "layer.h"
#include "object.h"

namespace Starlia
{

using namespace std;

class StarCore
{
	private:
		static list<SLayer *> layers;

		static unsigned int last_update;
		static Coord2d scale;

		static void draw();
		static void update();
		
		static void resize(int width, int height);
		static void eventClick(int x, int y);
		static void eventMouseOver(int x, int y);
		static void eventKeyPress(SDL_keysym);
		static void eventKeyRelease(SDL_keysym);

	public:
		static const Coord2d& getScale() { return scale; };
		static void init(string title, int width = 800, int height = 600);
		static void loop();

		static void addFront(SLayer *);
		static void addBack(SLayer *);
};

}

#endif
