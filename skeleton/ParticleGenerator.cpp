#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator()
{
	_num_particles = 100;
}

ParticleGenerator::~ParticleGenerator()
{
}

void ParticleGenerator::setParticle(Particle* model)
{
}

GaussianParticleGenerator::GaussianParticleGenerator()
{
}

list<Particle*> GaussianParticleGenerator::generateParticles()
{
    return list<Particle*>();
}

UniformParticleGenerator::UniformParticleGenerator()
{
}

list<Particle*> UniformParticleGenerator::generateParticles()
{
	list<Particle*> lista;

	for (int i = 0; i < _num_particles; i++)
	{
		Particle* particula = new Particle({ 0, 0, 0}, {0, 1, 1}, {0, 1, 0}, 0.99f);
		lista.push_back(particula);
	}


    return lista;
}
