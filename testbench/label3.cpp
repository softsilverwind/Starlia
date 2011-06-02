#include <starlia.h>

using namespace Starlia;

int main()
{
	StarWidgetLayer *layer = new StarWidgetLayer(Coordinate2d(100, 100));
	layer->registerObject(new StarLabel("1234567890?:,.\'", Coordinate2d(20, 30), Coordinate2d(80, 10), 4, Color3d(1,1,0), StarLabel::CENTER));

	StarCore::init("Starlia test bench");

	StarCore::registerLayerForeground(layer);
	StarCore::loop();

	return 0;
}
