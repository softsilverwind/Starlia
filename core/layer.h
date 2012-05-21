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
		list<StarObject *> objectList;

		static void invalidate(StarObject *);
		bool blockFallThrough;

	private:
		map<SDLKey, function<void (void)> > keypresses;
		map<SDLKey, function<void (void)> > keyreleases;

	public:
		bool invalid;

		StarLayer();
		virtual ~StarLayer();
		void demolishLayer();

		void draw();
		void recalc();

		bool keypress(SDLKey);
		bool keyrelease(SDLKey);
		void registerKeyPress(SDLKey, function<void (void)>);
		void registerKeyPress(char, function<void (void)>);
		void registerKeyRelease(SDLKey, function<void (void)>);
		void registerKeyRelease(char, function<void (void)>);

		void setBlockFallThrough(bool);
};

class Star2dLayer : public StarLayer
{
	protected:
		Coord2d size;

	public:
		void draw();
		Star2dLayer(Coord2d size);
};

class Star2dObjectLayer : public Star2dLayer
{
	public:
		Star2dObjectLayer(Coord2d size);

		void registerObject(StarObject *object);
		void unregisterObject(StarObject *object);
};

class StarWidgetLayer : public Star2dLayer
{
	public:
		StarWidgetLayer(Coord2d size);

		void registerObject(StarWidget *object);
		void unregisterObject(StarWidget *object);

		/* returns true if the click is handled by the layer, false if it should fall through */
		bool click(Coord2d position);
		bool mouseOver(Coord2d position);
};

class Star3dLayer : public StarLayer
{
	private:
		list<StarLight *> lights;
		vector<GLenum> lightNums;
		StarCamera *camera;

	public:
		Star3dLayer(StarCamera *camera);
		~Star3dLayer();

		void draw();
		void recalc();

		void registerObject(StarObject *object);
		void unregisterObject(StarObject *object);

		void registerObject(StarLight *light);
		void unregisterObject(StarLight *light);

		void registerObject(StarCamera *camera, bool deletePrev = true);
};

}

#endif /* __LAYER__H__ */
