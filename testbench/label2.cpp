#include <cstdio>
#include <starlia.h>

using namespace Starlia;
using namespace std;

void foo1()
{
	puts("first label clicked :)");
}

void foo2()
{
	puts("second label clicked :)");
}

void foo3()
{
	puts("third label clicked :)");
}

int main()
{
	StarWidgetLayer *layer = new StarWidgetLayer(Coordinate2d(100, 100));
	layer->registerObject(new StarLabel("The quick brown fox jumps over the lazy dog", Coordinate2d(20, 90), Coordinate2d(80, 70), 4, Color3d(1,1,0), StarLabel::RIGHT, foo1));
	layer->registerObject(new StarLabel("The quick brown fox jumps over the lazy dog", Coordinate2d(20, 60), Coordinate2d(80, 40), 4, Color3d(1,1,0), StarLabel::LEFT, foo2));
	layer->registerObject(new StarLabel("The quick brown fox jumps over the lazy dog", Coordinate2d(20, 30), Coordinate2d(80, 10), 4, Color3d(1,1,0), StarLabel::CENTER, foo3));

	StarCore::init("Starlia test bench");

	StarCore::registerLayerForeground(layer);
	StarCore::loop();

	return 0;
}
