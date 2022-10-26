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

	std::vector<Particle*> particles;

public:
	enum Generator { FUENTE, NUBE };

	ParticleSystem();
	~ParticleSystem();
	void update(double t);
	ParticleGenerator* getParticleGenerator(Generator name);

};
class FireworkSystem : ParticleSystem
{
private:
	list<Firework*> _particles;
	list<ParticleGenerator*> _particle_generators;
	vector<Firework*> _fireworks_pool;
	ParticleGenerator* _firework_gen;

	std::vector<Firework*> particles;

public:

	FireworkSystem();
	~FireworkSystem();
	void update(double t);
	void shootFirework();
	void onParticleDeath();

};