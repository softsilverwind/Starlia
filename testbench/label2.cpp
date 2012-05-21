#include <cstdio>
#include <starlia.h>

using namespace Starlia;
using namespace std;

void foo1(Coord2d pos)
{
	printf("first label clicked on (%f,%f) :)\n", pos.x, pos.y);
}

void foo2(Coord2d pos)
{
	printf("second label clicked on (%f,%f) :)\n", pos.x, pos.y);
}

void foo3(Coord2d pos)
{
	printf("third label clicked on (%f,%f) :)\n", pos.x, pos.y);
}

int main()
{
	StarWidgetLayer *layer = new StarWidgetLayer(Coord2d(100, 100));
	layer->registerObject(new StarLabel("The quick brown fox jumps over the lazy dog", Coord2d(20, 90), Coord2d(80, 70), 4, Color3f(1,1,0), StarLabel::RIGHT, foo1));
	layer->registerObject(new StarLabel("The quick brown fox jumps over the lazy dog", Coord2d(20, 60), Coord2d(80, 40), 4, Color3f(1,1,0), StarLabel::LEFT, foo2));
	layer->registerObject(new StarLabel("The quick brown fox jumps over the lazy dog", Coord2d(20, 30), Coord2d(80, 10), 4, Color3f(1,1,0), StarLabel::CENTER, foo3));

	StarCore::init("Starlia test bench");

	StarCore::registerLayerForeground(layer);
	StarCore::loop();

	return 0;
}
