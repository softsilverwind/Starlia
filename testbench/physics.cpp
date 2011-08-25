#include <iostream>
#include <GL/gl.h>
#include <cstdio>
#include "starlia.h"

using namespace Starlia;
using namespace std;

Star2dObjectLayer *layer;

class Ball : public StarObject
{
	private:
		Coordinate2d center;
		double radius;
		Color3f color;
		Coordinate2d velocity;

	public:
		Ball(Coordinate2d center, double radius, Color3f color, Coordinate2d velocity);
		bool recalc();
		void draw();
};

Ball::Ball(Coordinate2d center, double radius, Color3f color, Coordinate2d velocity)
	: center(center), radius(radius), color(color), velocity(velocity)
{
}

bool Ball::recalc()
{
	center += velocity;
	velocity.y -= 0.1;
	if (center.x - radius < 0)
		velocity.x = fabs(velocity.x * 0.8);
		
	if (center.x + radius > 800)
		velocity.x = -fabs(velocity.x * 0.8);

	if (center.y - radius < 0)
		velocity.y = fabs(velocity.y * 0.8);

	if (center.y + radius > 600)
		velocity.y = -fabs(velocity.y * 0.8);

	return fabs(velocity.y) > 0.002 || center.y - radius > 10 || fabs(velocity.x) > 0.2;
}

void Ball::draw()
{
	glPushMatrix();
	glTranslated(center.x, center.y, 0);
	glScaled(radius, radius, 0);
	Circle::draw(color);
	glPopMatrix();
}

void createBall()
{
	layer->registerObject(new Ball(Coordinate2d(randomi(200,600), randomi(300,500)), randomi(5,15), Color3f(randomd(), randomd(), randomd()), Coordinate2d(randomsgn() * randomd() * 10, randomsgn() * randomd() * 10)));
	StarTimer::registerTimer(500, createBall);
}

int main(int argc, char** argv)
{
	StarCore::init("Starlia test bench");
	layer = new Star2dObjectLayer(Coordinate2d(800, 600));
	StarCore::registerLayerForeground(layer);
	StarTimer::registerTimer(500, createBall);
	StarCore::loop();

	return 0;
}
