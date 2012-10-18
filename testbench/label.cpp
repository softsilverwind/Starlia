#include <starlia/starlia.h>

using namespace Starlia;

int main()
{
	StarWidgetLayer *layer = new StarWidgetLayer(Coord2d(100, 100));
	layer->registerObject(new StarLabel("The quick brown fox jumps over the lazy dog", Coord2d(20, 90), Coord2d(80, 70), 4, Color3f(1,1,0), StarLabel::RIGHT));
	layer->registerObject(new StarLabel("The quick brown fox jumps over the lazy dog", Coord2d(20, 60), Coord2d(80, 40), 4, Color3f(1,1,0), StarLabel::LEFT));
	layer->registerObject(new StarLabel("The quick brown fox jumps over the lazy dog", Coord2d(20, 30), Coord2d(80, 10), 4, Color3f(1,1,0), StarLabel::CENTER));

	StarCore::init("Starlia test bench");

	StarCore::registerLayerForeground(layer);
	StarCore::loop();

	return 0;
}
