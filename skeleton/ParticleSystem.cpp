#include "ParticleSystem.h"

UniformParticleGenerator* generador;

ParticleSystem::ParticleSystem()
{
    generador = new UniformParticleGenerator();
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::update(double t)
{

}

ParticleGenerator* ParticleSystem::getParticleGenerator(string name)
{
    return generador;
}

void ParticleSystem::generateFireworkSystem()
{

}
