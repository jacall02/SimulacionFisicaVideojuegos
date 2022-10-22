#include "ParticleSystem.h"

UniformParticleGenerator* fuente;
GaussianParticleGenerator* nube;

UniformParticleGenerator* fuegosArtificiales;

ParticleSystem::ParticleSystem()
{
    fuente = new UniformParticleGenerator();
    nube = new GaussianParticleGenerator();
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
	case ParticleSystem::FUEGOS_ARTIFICIALES:
		return fuegosArtificiales;
		break;
	default:
		break;
	}
}

void ParticleSystem::generateFireworkSystem()
{
	fuegosArtificiales = new UniformParticleGenerator();
}

void ParticleSystem::shootFirework()
{
	auto fireworkGenerator = getParticleGenerator(ParticleSystem::FUEGOS_ARTIFICIALES);
	for (auto particula : fireworkGenerator->generateParticles())
		particles.push_back(particula); 
}

void ParticleSystem::onParticleDeath()
{
	for (Firework* particula : fuegosArtificiales)
		particula->explode();
}

