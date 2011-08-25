#include <GL/gl.h>
#include <SDL/SDL.h>
#include <cstdio>
#include "starlia.h"

using namespace Starlia;

Star2dObjectLayer *layer;

class Racket : public StarObject
{
	private:
		Coordinate2d position;
		double halfheight;
		double halfwidth;
		Coordinate2d velocity;
		Color3f color;

	public:
		Racket(Coordinate2d position, double halfheight, double halfwidth, Color3f color);

		bool recalc();
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

Racket::Racket(Coordinate2d position, double halfheight, double halfwidth, Color3f color)
	: position(position), halfheight(halfheight), halfwidth(halfwidth), velocity(Coordinate2d(0,0)), color(color)
{
}

bool Racket::recalc()
{
	position += velocity;
	if (position.x - halfwidth < 0 || position.x + halfwidth > 800)
		position -= velocity;
	return true;
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
		Coordinate2d position;
		double radius;
		Coordinate2d velocity;
		Color3f color;

		void changeDirection(double x, bool up);

	public:
		Ball(Coordinate2d position, double radius, Coordinate2d velocity, Color3f color);
		bool recalc();
		void draw();
};

Ball::Ball(Coordinate2d position, double radius, Coordinate2d velocity, Color3f color)
	: position(position), radius(radius), velocity(velocity), color(color)
{
}

bool Ball::recalc()
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
		return false;
	else
		return true;
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

void keyboard(int key)
{
	switch (key)
	{
		case 'a':
			player[0]->goLeft();
			break;
		case 'd':
			player[0]->goRight();
			break;
		case 'j':
			player[1]->goLeft();
			break;
		case 'l':
			player[1]->goRight();
			break;
		default:
			break;
	}
}

void keyboardup(int key)
{
	switch (key)
	{
		case 'a':
			player[0]->stopLeft();
			break;
		case 'd':
			player[0]->stopRight();
			break;
		case 'j':
			player[1]->stopLeft();
			break;
		case 'l':
			player[1]->stopRight();
			break;
		default:
			break;
	}
}

void start();

void restart()
{
	StarTimer::registerTimer(2000, start);
}

void start()
{
	layer->registerObject(new Ball(Coordinate2d(400,300), 10, Coordinate2d(0.0, 3), Color3f(0,0,1)), restart);
}

int main(int argc, char** argv)
{
	StarCore::init("Starlia Pong - keys are \"A,D\" and \"J,L\"");
	layer = new Star2dObjectLayer(Coordinate2d(800, 600));

	player[0] = new Racket(Coordinate2d(400,50), 10, 50, Color3f(1,0,0));
	player[1] = new Racket(Coordinate2d(400,550), 10, 50, Color3f(0,1,0));
	StarCore::registerLayerForeground(layer);

	layer->registerObject(player[0]);
	layer->registerObject(player[1]);
	layer->registerKeyPress('a', keyboard, 'a');
	layer->registerKeyPress('d', keyboard, 'd');
	layer->registerKeyPress('j', keyboard, 'j');
	layer->registerKeyPress('l', keyboard, 'l');
	layer->registerKeyRelease('a', keyboardup, 'a');
	layer->registerKeyRelease('d', keyboardup, 'd');
	layer->registerKeyRelease('j', keyboardup, 'j');
	layer->registerKeyRelease('l', keyboardup, 'l');
	restart();
	StarCore::loop();

	return 0;
}
