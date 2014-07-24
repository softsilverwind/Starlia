#include <GL/glew.h>

#include <core/object.h>
#include <core/aux.h>
#include <core/particle.h>
#include <core/core.h>
#include <core/model.h>

#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>

#include "shaders/shaders.h"

using namespace std;

namespace Starlia
{

const string ParticleLayer::v_shader(shaders_particle_v);
const string ParticleLayer::f_shader(shaders_particle_f);

const Coord3f ParticleManager::square[] {
	Coord3f(-0.5f, -0.5f, 0.0f),
	Coord3f(0.5f, -0.5f, 0.0f),
	Coord3f(-0.5f,  0.5f, 0.0f),
	Coord3f(0.5f,  0.5f, 0.0f)
};


ParticleManager::ParticleManager(const string& filename, int maxSize, bool sortParticles, int srcBlend, int dstBlend)
	: tex(SModel::genTex(filename)), particles(maxSize), affectors(), emitters(), useIndex(0),
	  sortParticles(sortParticles), srcBlend(srcBlend), dstBlend(dstBlend)
{
	particles.shrink_to_fit();

	glGenBuffers(1, &square_buffer);
	glGenBuffers(1, &position_buffer);
	glGenBuffers(1, &tint_buffer);
	glGenBuffers(1, &radius_angle_buffer);

	glBindBuffer(GL_ARRAY_BUFFER, square_buffer);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Coord3f), square, GL_STATIC_DRAW);
}

ParticleManager::~ParticleManager()
{
	glDeleteBuffers(1, &square_buffer);
	glDeleteBuffers(1, &position_buffer);
	glDeleteBuffers(1, &tint_buffer);
	glDeleteBuffers(1, &radius_angle_buffer);

	glDeleteTextures(1, &tex);
}

int ParticleManager::firstUnused()
{
	for (int i = useIndex; i < (int) particles.size(); ++i)
		if (particles[i].life <= 0)
			return useIndex = i;

	for (int i = 0; i < useIndex; ++i)
		if (particles[i].life <= 0)
			return useIndex = i;

	return 0;
}

void ParticleManager::draw(SLayer *layer)
{
	vector<Coord3f> position_data;
	vector<Color4f> tint_data;
	vector<Coord2f> radius_angle_data;

	int attrib_sq = layer->getAttrib("square");
	int attrib_pos = layer->getAttrib("pos");
	int attrib_radang = layer->getAttrib("radang");
	int attrib_tint = layer->getAttrib("tint");
	int uniform_wvp = layer->getUniform("wvp");
	int uniform_tex = layer->getUniform("tex");

	auto firstDead = partition(particles, [](const Particle& p1){ return p1.life > 0; });

	if (sortParticles)
	{
		SStaticShaderLayer *layer2 = dynamic_cast<SStaticShaderLayer *>(layer);
		assert(layer2);
		shared_ptr<SCamera> cam = layer2->getCamera();
		sort(particles.begin(), firstDead, [&cam](const Particle& p1, const Particle& p2)
		{
			return cam->distanceFrom(p1.position) > cam->distanceFrom(p2.position);
		});
	}

	for (const auto& p : particles)
	{
		// TODO MultiArray sort should solve this copying...
		position_data.push_back(p.position);
		tint_data.push_back(p.tint);
		radius_angle_data.push_back(Coord2f(p.radius, p.angle));
	}
	int n = position_data.size();

	glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
	glBufferData(GL_ARRAY_BUFFER, position_data.size() * 3 * sizeof(float), NULL, GL_STREAM_DRAW); // init here due to buffer orphaning
	glBufferSubData(GL_ARRAY_BUFFER, 0, n * 3 * sizeof(float), &position_data.front());

	glBindBuffer(GL_ARRAY_BUFFER, tint_buffer);
	glBufferData(GL_ARRAY_BUFFER, position_data.size() * 4 * sizeof(float), NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, n * 4 * sizeof(float), &tint_data.front());

	glBindBuffer(GL_ARRAY_BUFFER, radius_angle_buffer);
	glBufferData(GL_ARRAY_BUFFER, position_data.size() * 2 * sizeof(float), NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, n * 2 * sizeof(float), &radius_angle_data.front());

	glEnable(GL_BLEND);
	glBlendFunc(srcBlend, dstBlend);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

	glUniform1i(uniform_tex, 0);

	glUniformMatrix4fv(uniform_wvp, 1, GL_FALSE, value_ptr(layer->getWVP()));

	glEnableVertexAttribArray(attrib_sq);
	glBindBuffer(GL_ARRAY_BUFFER, square_buffer);
	glVertexAttribPointer(attrib_sq, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(attrib_pos);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
	glVertexAttribPointer(attrib_pos, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(attrib_tint);
	glBindBuffer(GL_ARRAY_BUFFER, tint_buffer);
	glVertexAttribPointer(attrib_tint, 4, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(attrib_radang);
	glBindBuffer(GL_ARRAY_BUFFER, radius_angle_buffer);
	glVertexAttribPointer(attrib_radang, 2, GL_FLOAT, GL_FALSE, 0, NULL);


	glVertexAttribDivisor(attrib_sq, 0);
	glVertexAttribDivisor(attrib_pos, 1);
	glVertexAttribDivisor(attrib_tint, 1);
	glVertexAttribDivisor(attrib_radang, 1);

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, n);

	glDisableVertexAttribArray(attrib_sq);
	glDisableVertexAttribArray(attrib_pos);
	glDisableVertexAttribArray(attrib_tint);
	glDisableVertexAttribArray(attrib_radang);

	glBindTexture(GL_TEXTURE_2D, 0);
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
