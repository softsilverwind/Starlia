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

class StarLayer
{
	private:
		bool invalid;
		bool blockFallThrough;

		map<SDLKey, function<void (void)> > keypresses;
		map<SDLKey, function<void (void)> > keyreleases;

		bool eventKeyPress(SDLKey);
		bool eventKeyRelease(SDLKey);

		virtual bool eventClick(Coord2d position);
		virtual bool eventMouseOver(Coord2d position);

		virtual void draw();
		virtual void update();

	public:
		StarLayer();
		virtual ~StarLayer();
		void demolishLayer();

		void invalidate();

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
		list<StarWidget *> widgets;

		virtual void draw() override;
		virtual void update() override;

		virtual bool eventClick(Coord2d position) override;
		virtual bool eventMouseOver(Coord2d position) override;

	public:
		StarWidgetLayer();
		virtual ~StarWidgetLayer() override;

		void add(StarWidget *object);
		void remove(StarWidget *object);
};

class StarObjectLayer : public StarLayer
{
	protected:
		list<StarObject *> objects;

		virtual void draw() override;
		virtual void update() override;

	public:
		StarObjectLayer();
		virtual ~StarObjectLayer() override;

		void add(StarObject *object);
		void remove(StarObject *object);
};

}

#endif /* __LAYER__H__ */
