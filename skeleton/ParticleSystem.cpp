#include "ParticleSystem.h"

UniformParticleGenerator* fuente;
GaussianParticleGenerator* nube;

ParticleSystem::ParticleSystem()
{
	fuente = new UniformParticleGenerator({ 0, 0, 0 }, { 0, 0, 0 },
		{ 0, 80, 0 }, { 10, 20, 10 }, { 0, -10, 0 }, 2, Particle::WATER, 95);

	nube = new GaussianParticleGenerator({ 0, 0, 0 }, { 100, 100, 100 },
		{ 0, 0, 0 }, { 2, 2, 2 }, { 0, 0, 0 }, 10, Particle::MIST, 80);
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::update(double t)
{
	for (int i = 0; i < particles.size(); i++) {
		particles[i]->integrate(t);
		if (particles[i]->getLife() < 0) {
			auto p = particles[i];
			delete p;
			particles.erase(particles.begin() + i);
			i--;
		}
	}


	/*auto fuenteGenerator = getParticleGenerator(ParticleSystem::FUENTE);
	for (auto particula : fuenteGenerator->generateParticles())
		particles.push_back(particula);

	auto nubeGenerator = getParticleGenerator(ParticleSystem::NUBE);
	for (auto particula : nubeGenerator->generateParticles())
		particles.push_back(particula);*/
}

ParticleGenerator* ParticleSystem::getParticleGenerator(Generator name)
{
	switch (name)
	{
	case ParticleSystem::FUENTE:
		return fuente;
		break;
	case ParticleSystem::NUBE:
		return nube;
		break;
	default:
		break;
	}
}

FireworkSystem::FireworkSystem()
{
	_firework_gen = new UniformFireworkGenerator({ 0, 0, 0 }, { 0, 0, 0 },
		{ 0, 0, 0 }, { 0, 0, 0 }, { 0, 10, 0 }, 1, Particle::WATER, 100);
}

void FireworkSystem::update(double t) {
	for (int i = 0; i < particles.size(); i++) {
		particles[i]->integrate(t);
		if (particles[i]->getLife() < 0) {
			auto p = particles[i];
			onParticleDeath();
			delete p;
			particles.erase(particles.begin() + i);
			i--;
		}
	}
}

void FireworkSystem::shootFirework()
{
	for (auto firework : _firework_gen->generateFireworks())
		particles.push_back(firework);
}

void FireworkSystem::onParticleDeath()
{
	for (Firework* particula : particles)
		particula->explode();
}