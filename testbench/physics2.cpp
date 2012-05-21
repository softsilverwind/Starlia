#include <iostream>
#include <GL/gl.h>
#include <cstdio>
#include "starlia.h"

using namespace Starlia;

Star2dObjectLayer *layer;

class Ball : public StarObject
{
	private:
		static int id_pool;
		int id;
		Coord2d center;
		double radius;
		Color3f color;
		Coord2d velocity;

	public:
		Ball(Coord2d center, double radius, Color3f color, Coord2d velocity);
		void recalc();
		void draw();
		bool collides(Coord2d cnt2, double rad2);
		list<Ball *>::iterator itpos;
};

int Ball::id_pool = 0;

list<Ball *> balls;

Ball::Ball(Coord2d center, double radius, Color3f color, Coord2d velocity)
	: center(center), radius(radius), color(color), velocity(velocity)
{
	id = id_pool++;
}

bool Ball::collides(Coord2d cnt2, double rad2)
{
	return (fabs((center - cnt2).x) + fabs((center - cnt2).y) < radius + rad2);
}

void Ball::recalc()
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

	for (list<Ball *>::iterator it = balls.begin(); it != balls.end(); ++it)
	{
		if (id == (*it)->id)
			continue;

		if ((*it)->collides(center, radius))
		{
			double newvely = ((fabs(velocity.y) + fabs((*it)->velocity.y)) / 2) * 0.8;
			double newvelx = ((fabs(velocity.x) + fabs((*it)->velocity.x)) / 2) * 0.8;

			if (center.y > (*it)->center.y)
			{
				velocity.y = newvely;
				(*it)->velocity.y = -newvely;
			}
			else
			{
				velocity.y = -newvely;
				(*it)->velocity.y = newvely;
			}

			if (center.x > (*it)->center.x)
			{
				velocity.x = newvelx;
				(*it)->velocity.x = -newvelx;
			}
			else
			{
				velocity.x = -newvelx;
				(*it)->velocity.x = newvelx;
			}
		}
	}

	if (!(fabs(velocity.y) > 0.002 || center.y - radius > 10 || fabs(velocity.x) > 0.2))
	{
		balls.erase(itpos);
		
		EMIT(_delete);
	}
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
	balls.push_front(new Ball(Coord2d(randomi(200,600), randomi(300,500)), randomi(5,15), Color3f(randomd(), randomd(), randomd()), Coord2d(randomsgn() * randomd() * 10, randomsgn() * randomd() * 10)));
	balls.front()->itpos = balls.begin();
	layer->registerObject(balls.front());
	StarTimer::registerTimer(1000, createBall);
}

int main(int argc, char** argv)
{
	StarCore::init("Starlia test bench");
	layer = new Star2dObjectLayer(Coord2d(800, 600));
	StarCore::registerLayerForeground(layer);
	StarTimer::registerTimer(500, createBall);
	StarCore::loop();

	return 0;
}
