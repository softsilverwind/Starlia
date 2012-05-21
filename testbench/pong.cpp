#include <GL/gl.h>
#include <SDL/SDL.h>
#include <cstdio>
#include "starlia.h"

using namespace Starlia;

Star2dObjectLayer *layer;

class Racket : public StarObject
{
	private:
		Coord2d position;
		double halfheight;
		double halfwidth;
		Coord2d velocity;
		Color3f color;

	public:
		Racket(Coord2d position, double halfheight, double halfwidth, Color3f color);

		void recalc();
		void draw();

		double getTop() { return position.y + halfheight; }
		double getBottom() { return position.y - halfheight; }
		double getLeft() { return position.x - halfwidth; }
		double getRight() { return position.x + halfwidth; }
		double getPos() { return position.x; }
		void  goRight() { velocity.x = 5; }
		void  goLeft() { velocity.x = -5; }
		void  stopRight() { if (velocity.x > 0) velocity.x = 0; }
		void  stopLeft() { if (velocity.x < 0) velocity.x = 0; }
};

Racket::Racket(Coord2d position, double halfheight, double halfwidth, Color3f color)
	: position(position), halfheight(halfheight), halfwidth(halfwidth), velocity(Coord2d(0,0)), color(color)
{
}

void Racket::recalc()
{
	position += velocity;
	if (position.x - halfwidth < 0 || position.x + halfwidth > 800)
		position -= velocity;
}

void Racket::draw()
{
	glColor3f(color.r, color.g, color.b);
	glRectd(position.x - halfwidth, position.y - halfheight, position.x + halfwidth, position.y + halfheight);
}

Racket *player[2];

class Ball : public StarObject
{
	private:
		Coord2d position;
		double radius;
		Coord2d velocity;
		Color3f color;

		void changeDirection(double x, bool up);

	public:
		Ball(Coord2d position, double radius, Coord2d velocity, Color3f color);
		void recalc();
		void draw();
};

Ball::Ball(Coord2d position, double radius, Coord2d velocity, Color3f color)
	: position(position), radius(radius), velocity(velocity), color(color)
{
}

void Ball::recalc()
{
	position += velocity;
	if (position.y - radius < player[0]->getTop() && position.y + radius > player[0]->getBottom())
		if (position.x - radius < player[0]->getRight() &&
				position.x + radius > player[0]->getLeft())
			changeDirection(player[0]->getPos(), true);


	if (position.y + radius > player[1]->getBottom() && position.y - radius < player[1]->getTop())
		if (position.x - radius < player[1]->getRight() &&
				position.x + radius > player[1]->getLeft())
			changeDirection(player[1]->getPos(), false);


	if (position.x + radius > 800 || position.x - radius < 0)
		velocity.x = -velocity.x;

	if (position.y > 600 || position.y < 0)
	{
		EMIT(_delete);
		EMIT(restart);
	}
}

void Ball::draw()
{
	glPushMatrix();
	glTranslated(position.x, position.y, 0);
	glScaled(radius, radius, 0);
	Circle::draw(color);
	glPopMatrix();
}

void Ball::changeDirection(double x, bool up)
{
	if (up)
		velocity.y = fabs(velocity.y);
	else
		velocity.y = -fabs(velocity.y);

	velocity.x = (position.x - x) / 10;
}

void start();

void restart()
{
	StarTimer::registerTimer(2000, start);
}

void start()
{
	Ball *ball = new Ball(Coord2d(400,300), 10, Coord2d(0.0, 3), Color3f(0,0,1));
	ball->CONNECT(restart, restart);
	layer->registerObject(ball);
}

int main(int argc, char** argv)
{
	StarCore::init("Starlia Pong - keys are \"A,D\" and \"J,L\"");
	layer = new Star2dObjectLayer(Coord2d(800, 600));

	player[0] = new Racket(Coord2d(400,50), 10, 50, Color3f(1,0,0));
	player[1] = new Racket(Coord2d(400,550), 10, 50, Color3f(0,1,0));
	StarCore::registerLayerForeground(layer);

	layer->registerObject(player[0]);
	layer->registerObject(player[1]);
	layer->registerKeyPress('a', [](){ player[0]->goLeft(); });
	layer->registerKeyPress('d', [](){ player[0]->goRight(); });
	layer->registerKeyPress('j', [](){ player[1]->goLeft(); });
	layer->registerKeyPress('l', [](){ player[1]->goRight(); });
	layer->registerKeyRelease('a', [](){ player[0]->stopLeft(); });
	layer->registerKeyRelease('d', [](){ player[0]->stopRight(); });
	layer->registerKeyRelease('j', [](){ player[1]->stopLeft(); });
	layer->registerKeyRelease('l', [](){ player[1]->stopRight(); });
	restart();
	StarCore::loop();

	return 0;
}
