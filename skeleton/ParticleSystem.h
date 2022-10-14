#pragma once
#include "Particle.h"
#include "ParticleGenerator.h"

#include <list>
#include <string>

using namespace std;

class ParticleSystem
{
private:
	list<Particle*> _particles;
	list<ParticleGenerator*> _particle_generators;
	vector<Firework*> _fireworks_pool;
	ParticleGenerator* _firework_gen;

public:
	ParticleSystem();
	~ParticleSystem();
	void update(double t);
	ParticleGenerator* getParticleGenerator(string name);
	void generateFireworkSystem();
};

