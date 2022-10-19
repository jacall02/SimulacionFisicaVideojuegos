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

	random_device rd;
	mt19937 gen(rd());

	uniform_real_distribution<> posX(-1, 1);
	uniform_real_distribution<> posY(-1, 1);
	uniform_real_distribution<> posZ(-1, 1);
	
	uniform_real_distribution<> velX(1, 10);
	uniform_real_distribution<> velY(1, 10);
	uniform_real_distribution<> velZ(1, 10);

	Vector3 pos, vel;
	
	for (int i = 0; i < _num_particles; i++)
	{
		pos.x = posX(gen);
		pos.y = posY(gen);
		pos.z = posZ(gen);
		vel.x = velX(gen);
		vel.y = velY(gen);
		vel.z = velZ(gen);

		Particle* particula = new Particle(pos, vel, {0, 1, 0}, 0.99f);
		lista.push_back(particula);
	}


    return lista;
}
