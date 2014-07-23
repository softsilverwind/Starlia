#include <core/particle.h>
#include <core/core.h>

namespace Starlia
{

const string ParticleLayer::v_shader(
		"#version 120\n"
		"attribute vec3 pos;\n"
		"attribute vec2 texcoord;\n"
		"\n"
		"varying vec2 f_texcoord;\n"
		"\n"
		"uniform mat4 wvp;\n"
		"\n"
		"void main(void)\n"
		"{\n"
		"\tgl_Position = wvp * vec4(pos, 1.0);\n"
		"\tf_texcoord = texcoord;\n"
		"}\n");

const string ParticleLayer::f_shader(
		"#version 120\n"
		"varying vec2 f_texcoord;\n"
		"uniform sampler2D tex;\n"
		"\n"
		"void main(void)\n"
		"{\n"
		"\tvec2 flipped_texcoord = vec2(f_texcoord.x, f_texcoord.y);"
		"\tgl_FragColor = texture2D(tex, flipped_texcoord);\n"
		"}\n");


ParticleManager::ParticleManager(unsigned int tex, int maxSize)
	: tex(tex), particles(maxSize)
{
	particles.shrink_to_fit();
}

void ParticleManager::draw(SLayer *)
{
	// TODO draw particles
}

void ParticleManager::update()
{
	for (auto it = particles.begin(); it != particles.end(); ++it)
	{
		it->life -= StarCore::getMSPF();
		if (it->life <= 0)
			particles.erase(it--);
	}

	for (auto& e : emitters)
		e.update();

	for (auto& a : affectors)
		a.update();
}

vector<Particle>::iterator ParticleManager::begin()
{
	return particles.begin();
}

vector<Particle>::iterator ParticleManager::end()
{
	return particles.end();
}

void ParticleManager::add(const Particle& par)
{
	particles.push_back(par);
}

void ParticleManager::add(const ParticleAffector& aff)
{
	affectors.push_back(aff);
	affectors.back().manager = this;
}

void ParticleManager::add(const ParticleEmitter& em)
{
	emitters.push_back(em);
	emitters.back().manager = this;
}

void ConstantEmitter::update()
{
	fraction += (float) numPerSecond / StarCore::getFPS();

	float i = 0;
	fraction = modff(fraction, &i);

	emit(i);
}

void FireAffector::update()
{
	for (Particle& p : getManager())
	{
		p.position.z += velocity;
		p.angle += angvel;
	}
}

}
