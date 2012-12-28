#ifndef __CORE_H__
#define __CORE_H__

#include <string>
#include <list>

#include <starlia/core/object.h>
#include <starlia/core/layer.h>

using namespace std;

namespace Starlia
{

class StarCore
{
	private:
		static list<SLayer *> layers;

		static unsigned int last_update;
		static Coord2d scale;

		static void draw();
		static void update();
		
		static void resize(int width, int height);
		static void click(int x, int y);
		static void mouseOver(int x, int y);
		static void keypress(SDL_keysym);
		static void keyrelease(SDL_keysym);

	public:
		static const Coord2d& getScale() { return scale; };
		static void init(string title, int width = 800, int height = 600);
		static void loop();

		static void addFront(SLayer *);
		static void addBack(SLayer *);
		static void remove(SLayer *);
};

}

#endif
