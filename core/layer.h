#ifndef __LAYER_H__
#define __LAYER_H__

#include <list>
#include "object.h"

using namespace std;

namespace Starlia
{

class StarLayer : public StarObject
{
	protected:
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

		list<EntryType> objectList;

	public:
		bool invalid;

		StarLayer();
		virtual ~StarLayer();
		void clearLayer();

		void draw();
		bool recalc();
};

class Star2dLayer : public StarLayer
{
	protected:
		Coordinate2d size;

	public:
		void draw();
		Star2dLayer(Coordinate2d size);
};

class StarObjectLayer : public Star2dLayer
{
	public:
		StarObjectLayer(Coordinate2d size);

		void registerObject(StarObject *object, void (*onEnd)() = NULL, bool remove = true, bool destroy = true);
		void unregisterObject(StarObject *object);
};

class StarWidgetLayer : public Star2dLayer
{
	private:
		bool blockFallThrough;

	public:
		StarWidgetLayer(Coordinate2d size, bool blockFallThrough = false);

		void registerObject(StarWidget *object, void (*onEnd)() = NULL, bool remove = true, bool destroy = true);
		void unregisterObject(StarWidget *object);

		/* returns true if the click is handled by the layer, false if it should fall through */
		bool click(Coordinate2d position);
		bool mouseOver(Coordinate2d position);
};

class Star3dLayer : public StarLayer
{
	private:
		Coordinate3d campos;
		Coordinate3d lookpos;
		Coordinate3d n;

	public:
		Star3dLayer(Coordinate3d campos, Coordinate3d lookpos, Coordinate3d n);

		void draw();

		void registerObject(StarObject *object, void (*onEnd)() = NULL, bool remove = true, bool destroy = true);
		void unregisterObject(StarObject *object);
};

}

#endif /* __LAYER__H__ */
