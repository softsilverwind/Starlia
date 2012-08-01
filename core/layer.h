#ifndef __LAYER_H__
#define __LAYER_H__

#include <SDL/SDL.h>
#include <functional>
#include <list>
#include <map>
#include <vector>
#include "object.h"
#include "starLight.h"
#include "camera.h"

using namespace std;

namespace Starlia
{

class StarLayer : public StarObject
{
	protected:
		list<StarObject *> objects;

		static void invalidate(StarObject *);
		bool blockFallThrough;

		bool eventKeyPress(SDLKey);
		bool eventKeyRelease(SDLKey);

		virtual bool eventClick(Coord2d position);
		virtual bool eventMouseOver(Coord2d position);

	private:
		map<SDLKey, function<void (void)> > keypresses;
		map<SDLKey, function<void (void)> > keyreleases;

		/* returns true if the mouse event is handled by the layer, false if it should fall through */

	public:
		bool invalid;

		StarLayer();
		virtual ~StarLayer();
		void demolishLayer();

		void draw();
		void recalc();

		void addKeyPress(SDLKey, function<void (void)>);
		void addKeyPress(char, function<void (void)>);
		void addKeyRelease(SDLKey, function<void (void)>);
		void addKeyRelease(char, function<void (void)>);

		void setBlockFallThrough(bool);

		friend class StarCore;
};

class StarWidgetLayer : public StarLayer
{
	protected:
		virtual void draw() override;
		virtual void recalc() override;

		virtual bool eventClick(Coord2d position) override;
		virtual bool eventMouseOver(Coord2d position) override;

	public:
		StarWidgetLayer();

		void add(StarWidget *object);
		void remove(StarWidget *object);
};

class StarObjectLayer : public StarLayer
{
	protected:
		// assets?
		virtual void draw() override;
		virtual void recalc() override;

	public:
		StarObjectLayer();
		~StarObjectLayer();

		void add(StarObject *object);
		void remove(StarObject *object);
};

}

#endif /* __LAYER__H__ */
