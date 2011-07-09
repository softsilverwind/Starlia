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
		static Star3dLayer *layer3d;
		static unsigned int last_recalc;
		static Coordinate2d scale;


		static void draw();
		static void recalc();
		
		static void display();
		static void resize(int width, int height);
		static void idle();
		static void click(int x, int y);
		static void mouseOver(int x, int y);

	public:
		static const Coordinate2d& getScale() { return scale; };
		static void init(string title, int width = 800, int height = 600);
		static void loop();

		static void registerLayerForeground(StarObjectLayer *layer);
		static void registerLayerBackground(StarObjectLayer *layer);
		static void unregisterLayer(StarObjectLayer *layer);

		static void registerLayerForeground(StarWidgetLayer *layer);
		static void registerLayerBackground(StarWidgetLayer *layer);
		static void unregisterLayer(StarWidgetLayer *layer);

		static void registerLayer(Star3dLayer *layer = NULL);
};

}

#endif /* __STARCORE__H__ */
