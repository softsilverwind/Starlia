#include <GL/gl.h>
#include <starlia.h>

using namespace Starlia;

Star2dObjectLayer *layer;

class Particle : public Star2dObject
{
	private:
		int life;

	public:
		Particle(Coordinate2d position, Coordinate2d velocity, int life);
			
		bool recalc();
		void draw();

		void yield();
};

Particle::Particle(Coordinate2d position, Coordinate2d velocity, int life)
	: Star2dObject(position, Coordinate2d(2,2), 0, new Circle(Color3f(0.75,0.25,0))), life(life)
{
	setVelocity(velocity);
}

void Particle::yield()
{
	cout << position << endl;
}

bool Particle::recalc()
{
	Star2dObject::recalc();
	return --life > 0;
}

void Particle::draw()
{
	glPushMatrix();
	Star2dObject::draw();
	glPopMatrix();
}

class P_Engine : public StarObject
{
	private:
		Coordinate2d position;
		Particle *particles[200];

		Particle *genParticle();

	public:
		P_Engine();
		~P_Engine();

		void draw();
		bool recalc();
};

Particle *P_Engine::genParticle()
{
	int mag = randomi(100, 300);
	Coordinate2d delta = polarToXY(mag, randomd() * 2 * M_PI);
	Coordinate2d pos = delta + position;
	Coordinate2d vel = delta * (-1) / mag;

	return new Particle(pos, vel, mag);
}

P_Engine::P_Engine()
	: position(Coordinate2d(400, 300))
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
		cout << i << ": ";
		particles[i]->yield();
	}
}

bool P_Engine::recalc()
{
	for (int i = 0; i < 200; ++i)
		if (!particles[i]->recalc())
		{
			delete particles[i];
			particles[i] = genParticle();
		}
			
	return true;
}

int main(int argc, char** argv)
{
	StarCore::init("Starlia test bench");
	layer = new Star2dObjectLayer(Coordinate2d(800, 600));
	StarCore::registerLayerForeground(layer);
	layer->registerObject(new P_Engine());
	StarCore::loop();

	return 0;
}
