#include <GL/gl.h>
#include <starlia.h>

using namespace Starlia;

Star2dObjectLayer *layer;

class Particle : public Star2dObject
{
	private:
		int life;

	public:
		Particle(Coord2d position, Coord2d velocity, int life);
			
		void recalc();
		void draw();

		int getLife();

		void yield();
};

Particle::Particle(Coord2d position, Coord2d velocity, int life)
	: Star2dObject(position, Coord2d(2,2), 0, new Circle(Color3f(0.75,0.25,0))), life(life)
{
	setVelocity(velocity);
}

void Particle::yield()
{
	cout << position << endl;
}

void Particle::recalc()
{
	Star2dObject::recalc();
	--life;
}

void Particle::draw()
{
	glPushMatrix();
	Star2dObject::draw();
	glPopMatrix();
}

int Particle::getLife()
{
	return life;
}

class P_Engine : public StarObject
{
	private:
		Coord2d position;
		Particle *particles[200];

		Particle *genParticle();

	public:
		P_Engine();
		~P_Engine();

		void draw();
		void recalc();
};

Particle *P_Engine::genParticle()
{
	int mag = randomi(100, 300);
	Coord2d delta = polarToXY(mag, randomd() * 2 * M_PI);
	Coord2d pos = delta + position;
	Coord2d vel = delta * (-1) / mag;

	return new Particle(pos, vel, mag);
}

P_Engine::P_Engine()
	: position(Coord2d(400, 300))
{
	for (int i = 0; i < 200; ++i)
	{
		particles[i] = genParticle();
	}
}

P_Engine::~P_Engine()
{
	for (int i = 0; i < 200; ++i)
		delete particles[i];
}

void P_Engine::draw()
{
	for (int i = 0; i < 200; ++i)
	{
		particles[i]->draw();
	}
}

void P_Engine::recalc()
{
	for (int i = 0; i < 200; ++i)
	{
		particles[i]->recalc();
		if (particles[i]->getLife() <= 0)
		{
			delete particles[i];
			particles[i] = genParticle();
		}
	}
}

int main(int argc, char** argv)
{
	StarCore::init("Starlia test bench");
	layer = new Star2dObjectLayer(Coord2d(800, 600));
	StarCore::registerLayerForeground(layer);
	layer->registerObject(new P_Engine());
	StarCore::loop();

	return 0;
}
