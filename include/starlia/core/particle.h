#include <GL/gl.h>

#include "layer.h"
#include "structs.h"
#include "basic.h"

#define DEFAULT_MAX_PARTICLE_COUNT 5000

namespace Starlia
{

struct Particle
{
	Coord3f position;
	Color4f tint;

	float radius;
	float angle;

	int initlife, life;
};

class ParticleLayer : public SStaticShaderLayer
{
	private:
		static const string v_shader;
		static const string f_shader;

	public:
		ParticleLayer(shared_ptr<SCamera> camera)
			: SStaticShaderLayer(camera, v_shader, f_shader)
		{}
		ParticleLayer(SCamera *camera = new SOrthoCamera(Coord2f(0, 0), Coord2f(1, 1)))
			: SStaticShaderLayer(shared_ptr<SCamera>(camera), v_shader, f_shader)
		{}
};

class ParticleEmitter;
class ParticleAffector;

class ParticleManager : public SObject
{
	private:
		static const Coord3f square[];

		unsigned int tex;

		vector<Particle> particles;
		vector<ParticleAffector> affectors;
		vector<ParticleEmitter> emitters;

		unsigned int square_buffer;
		unsigned int position_buffer;
		unsigned int tint_buffer;
		unsigned int radius_angle_buffer;

		int useIndex;
		int firstUnused();

		bool sortParticles;
		int srcBlend, dstBlend;

	public:
		ParticleManager(const string& filename, int maxSize = DEFAULT_MAX_PARTICLE_COUNT,
				bool sortParticles = true, int srcBlend = GL_SRC_ALPHA,
				int dstBlend = GL_ONE_MINUS_SRC_ALPHA);

		virtual ~ParticleManager() override;

		virtual void draw(SLayer *) override;
		virtual void update() override;

		void add(const Particle& par);
		void add(const ParticleAffector& aff);
		void add(const ParticleEmitter& em);

		vector<Particle>::iterator begin();
		vector<Particle>::iterator end();
};

class ParticleEmitter : public SObject
{
	private:
		ParticleManager *manager;
		Particle minPrototype;
		Particle maxPrototype;

	protected:
		ParticleManager& getManager() { return *manager; }

	public:
		ParticleEmitter(const Particle& minPrototype, const Particle& maxPrototype)
			: minPrototype(minPrototype), maxPrototype(maxPrototype) {}

		virtual void emit(int number);

	friend class ParticleManager;
};

class ConstantEmitter : public ParticleEmitter
{
	private:
		int numPerSecond;
		float fraction;

		ConstantEmitter(const Particle& minPrototype, const Particle& maxPrototype, int numPerSecond, float fraction)
			: ParticleEmitter(minPrototype, maxPrototype), numPerSecond(numPerSecond), fraction(fraction)
		{}

		virtual void update() override;
};

class ParticleAffector : public SObject
{
	private:
		ParticleManager *manager;

	protected:
		ParticleManager& getManager() { return *manager; }

	public:
		ParticleAffector() {}
	
	friend class ParticleManager;
};

class FireAffector : public ParticleAffector
{
	private:
		float velocity;
		float angvel;

	public:
		FireAffector(float velocity, float angvel)
			: velocity(velocity), angvel(angvel)
		{}

		virtual void update() override;
};

}
