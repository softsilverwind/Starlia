#ifndef __STARCORE_H__
#define __STARCORE_H__

#include <string>
#include <list>
#include "object.h"
#include "layer.h"

using namespace std;

namespace Starlia
{

class StarCore
{
	private:
		static list<StarLayer *> layers;

		static unsigned int last_recalc;
		static Coord2d scale;

		static void draw();
		static void recalc();
		
		static void resize(int width, int height);
		static void click(int x, int y);
		static void mouseOver(int x, int y);
		static void keypress(SDL_keysym);
		static void keyrelease(SDL_keysym);

	public:
		static const Coord2d& getScale() { return scale; };
		static void init(string title, int width = 800, int height = 600);
		static void loop();

		static void addFront(StarLayer *layer);
		static void addBack(StarLayer *layer);
		static void remove(StarLayer *layer);
};

}

#endif /* __STARCORE__H__ */
