#ifndef __LAYER_H__
#define __LAYER_H__

#include <functional>
#include <memory>
#include <list>
#include <map>

#include <SDL/SDL.h>

#include <starlia/core/object.h>
#include <starlia/core/camera.h>

using namespace std;

namespace Starlia
{

// enum indicating whether keypresses, mouse events, draw
// events are allowed to the next layer or not (e.g. in game
// menus probably want to block events)
enum FallthroughType
{
	Allow, Block
};

// SLayer is a set of objects. It also handles events and defines
// how its objects will be presented. For example, light sources
// should be defined on the Layer level, so that every object in
// the same layer shares light source information.
class SLayer
{
	private:
		bool invalid; // whether layer should be deleted
		FallthroughType blockMouse, blockKeyboard, blockDraw, blockUpdate;

		map<SDLKey, function<void (void)> > keypresses;
		map<SDLKey, function<void (void)> > keyreleases;

	protected:
		virtual void draw();
		virtual void update();

		// event* functions are called by the StarCore class, on an event (key, mouse, etc)
		virtual bool eventKeyPress(SDLKey);
		virtual bool eventKeyRelease(SDLKey);

		virtual bool eventClick(Coord2d position);
		virtual bool eventMouseOver(Coord2d position);

	public:
		SLayer();
		virtual ~SLayer(); // destructor should be handled mostly by StarCore

		void invalidate(); // marks the layer for deletion by StarCore 

		// add actions on key events
		void addKeyPress(SDLKey, function<void (void)>);
		void addKeyPress(char, function<void (void)>);
		void addKeyRelease(SDLKey, function<void (void)>);
		void addKeyRelease(char, function<void (void)>);

		void setBlockMouse(FallthroughType);
		void setBlockKeyboard(FallthroughType);
		void setBlockDraw(FallthroughType);
		void setBlockUpdate(FallthroughType);

		friend class StarCore;
};

class SWidgetLayer : public SLayer
{
	protected:
		list<SWidget *> widgets;

		virtual void draw() override;
		virtual void update() override;

		// mouse events should dispatch the call to the right widget
		virtual bool eventClick(Coord2d position) override;
		virtual bool eventMouseOver(Coord2d position) override;

	public:
		SWidgetLayer();
		virtual ~SWidgetLayer() override;

		void add(SWidget *widget);
		void remove(SWidget *widget);
};

class SObjectLayer : public SLayer
{
	protected:
		list<SObject *> objects;
		shared_ptr<SCamera> *camera;

		virtual void draw() override;
		virtual void update() override;

	public:
		SObjectLayer();
		virtual ~SObjectLayer() override;

		void add(SObject *object);
		void remove(SObject *object);
};

}

#endif
