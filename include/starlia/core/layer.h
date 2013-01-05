namespace Starlia
{
	class SLayer;
	template<typename T> class SListLayer;
}

#ifndef __LAYER_H__
#define __LAYER_H__

#include <iostream>
#include <functional>
#include <string>
#include <memory>
#include <list>
#include <map>

#include <SDL/SDL.h>
#include <glm/glm.hpp>

#include "camera.h"
#include "object.h"

namespace Starlia
{

using namespace std;
using namespace glm;

// Enumeration indicating which of [keypresses, mouse events, draw calls,
// update calls] are blocked from going to the next layer (e.g. in game
// menus probably want to block events)

enum BlockType
{
	Block_Mouse = 0x1,
	Block_Keyboard = 0x2,
	Block_Draw = 0x4,
	Block_Update = 0x8
};

// An SLayer denotes a set of objects. It also handles events and defines
// how its objects will be presented. For example, light sources should
// be defined on the Layer level, so that every object in the same layer
// shares light source information.

class SLayer
{
	private:
		bool invalid; // denotes whether layer should be deleted
		unsigned block;

		map<SDLKey, function<void (void)> > keypresses;
		map<SDLKey, function<void (void)> > keyreleases;

		mat4 world, view, projection, wvp;

	protected:
		unsigned program;

		virtual void draw();
		virtual void update() {};

		// event* functions are called by the StarCore class, on an event
		// (key, mouse, etc)
		bool eventKeyPress(SDLKey);
		bool eventKeyRelease(SDLKey);

		virtual bool eventClick(Coord2d position) { return false; };
		virtual bool eventMouseOver(Coord2d position) { return false; };

		void dispatchSignals(shared_ptr<SObject>);
		bool& getInvalidRef(shared_ptr<SObject>);
		void setLayer(shared_ptr<SObject>);

	public:
		SLayer();
		// destructor should be handled mostly by StarCore
		virtual ~SLayer() {};

		// marks the layer for deletion by StarCore 
		void invalidate();

		void addKeyPress(SDLKey, function<void (void)>);
		void addKeyPress(char, function<void (void)>);
		void addKeyRelease(SDLKey, function<void (void)>);
		void addKeyRelease(char, function<void (void)>);

		void setBlock(unsigned);

		void setWorld(const mat4&);
		void setView(const mat4&);
		void setProjection(const mat4&);
		const mat4& getWVP();

		int getAttrib(const string&);
		int getUniform(const string&);

		friend class StarCore;
};

// An SListLayer is an implementation of an SLayer, using a list. Its draw and
// update functions iterate on the list elements, calling the corresponding
// functions.

template <typename T>
class SListLayer : public SLayer
{
	private:
		list<shared_ptr<T>> elements;

	protected:
		// call draw and update on each object, iteratively
		virtual void draw() override;
		virtual void update() override;

	public:
		void add(T *);
		void add(shared_ptr<T>);
};

/*
// TODO
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
		SCamera * camera;
};
*/

#include "layer.inl"

}

#endif
