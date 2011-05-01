#ifndef __STARCORE_H__
#define __STARCORE_H__

#include <string>
#include <list>
#include "object.h"

using namespace std;

namespace Starlia
{

class StarLayer : public StarObject
{
	private:
		typedef struct EntryType_tag
		{
			StarObject *object;
			bool invalid;
			void (*onEnd)();
			bool remove;
			bool destroy;
			EntryType_tag (StarObject *object, void (*onEnd)(), bool remove, bool destroy)
				: object(object), invalid(false), onEnd(onEnd), remove(remove), destroy(destroy) {};
		}
		EntryType;

		Coordinate2d size;
		list<EntryType> objectList;
		list<StarWidget *> clickList; // TODO HASH THE F*CK OUT OF IT! :D

	public:
		bool invalid;

		StarLayer(Coordinate2d size);

		void registerObject(StarObject *object, void (*onEnd)() = NULL, bool remove = true, bool destroy = true);
		void unregisterObject(StarObject *object);
		void registerWidget(StarWidget *widget, void (*onEnd)() = NULL, bool remove = true, bool destroy = true);
		void unregisterWidget(StarWidget *widget);

		/* returns true if the click is handled by the layer, false if it should fall through */
		bool click(Coordinate2d position);

		void draw();
		bool recalc();
};

class StarCore
{
	private:
		static list<StarLayer *> layers;
		static unsigned int last_recalc;
		static Coordinate2d scale;


		static void draw();
		static void recalc();
		
		static void display();
		static void resize(int width, int height);
		static void idle(int _);
		static void click(int button, int state, int x, int y);

	public:
		static void init(string title, int width = 800, int height = 600);
		static void loop();

		static void registerLayerForeground(StarLayer *layer);
		static void registerLayerBackground(StarLayer *layer);
		static void unregisterLayer(StarLayer *layer);
};

}

#endif /* __STARCORE__H__ */
