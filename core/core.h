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
		static list<StarObjectLayer *> objectLayers;
		static list<StarWidgetLayer *> widgetLayers;
		static unsigned int last_recalc;
		static Coordinate2d scale;


		static void draw();
		static void recalc();
		
		static void display();
		static void resize(int width, int height);
		static void idle(int _);
		static void click(int button, int state, int x, int y);
		static void mouseOver(int x, int y);

	public:
		static void init(string title, int width = 800, int height = 600);
		static void loop();

		static void registerLayerForeground(StarObjectLayer *layer);
		static void registerLayerBackground(StarObjectLayer *layer);
		static void unregisterLayer(StarObjectLayer *layer);

		static void registerLayerForeground(StarWidgetLayer *layer);
		static void registerLayerBackground(StarWidgetLayer *layer);
		static void unregisterLayer(StarWidgetLayer *layer);
};

}

#endif /* __STARCORE__H__ */
