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

// Enumeration indicating whether keypresses, mouse events, draw events
// are allowed to the next layer or not (e.g. in game menus probably want
// to block events)

enum FallthroughType
{
	Allow, Block
};

// An SLayer denotes a set of objects. It also handles events and defines
// how its objects will be presented. For example, light sources should
// be defined on the Layer level, so that every object in the same layer
// shares light source information.

class SLayer
{
	private:
		bool invalid; // denotes whether layer should be deleted
		FallthroughType blockMouse, blockKeyboard, blockDraw, blockUpdate;

		map<SDLKey, function<void (void)> > keypresses;
		map<SDLKey, function<void (void)> > keyreleases;

	protected:
		virtual void draw();
		virtual void update();

		// event* functions are called by the StarCore class, on an event
		// (key, mouse, etc)

		// search over a list of keypresses-function pairs, and call the
		// corresponding function.
		bool eventKeyPress(SDLKey);
		bool eventKeyRelease(SDLKey);

		// left to be defined by the subclasses
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

// An SListLayer is an implementation of an SLayer, using a list. Its draw and
// update functions iterate on the list elements, calling the corresponding
// functions.

template <typename T>
class SListLayer : public SLayer
{
	private:
		list<T *> elements;

	protected:
		// call draw and update on each object, iteratively
		virtual void draw() override;
		virtual void update() override;

	public:
		SListLayer();
		virtual ~SListLayer() override;

		void add(T *);
		void remove(T *);
};


class SWidgetLayer : public SListLayer<SWidget>
{
	protected:
		// mouse events should dispatch the call to the right widget
		virtual bool eventClick(Coord2d position) override;
		virtual bool eventMouseOver(Coord2d position) override;
};

class SObjectLayer : public SListLayer<SObject>
{
	protected:
		shared_ptr<SCamera> camera;
};

}

#endif
