#include <starlia.h>

using namespace Starlia;

int main()
{
	StarLayer *layer = new StarLayer(Coordinate2d(100, 100));
	layer->registerObject(new StarLabel("The quick brown fox jumps over the lazy dog", Coordinate2d(20, 90), Coordinate2d(80, 70), 4, Color3d(1,1,0), -1, StarLabel::STATIC, StarLabel::RIGHT));
	layer->registerObject(new StarLabel("The quick brown fox jumps over the lazy dog", Coordinate2d(20, 60), Coordinate2d(80, 40), 4, Color3d(1,1,0), -1, StarLabel::STATIC, StarLabel::LEFT));
	layer->registerObject(new StarLabel("The quick brown fox jumps over the lazy dog", Coordinate2d(20, 30), Coordinate2d(80, 10), 4, Color3d(1,1,0), -1, StarLabel::STATIC, StarLabel::CENTER));

	StarCore::init("Starlia test bench");

	StarCore::registerLayerForeground(layer);
	StarCore::loop();

	return 0;
}
