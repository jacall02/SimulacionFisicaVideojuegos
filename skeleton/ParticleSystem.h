#pragma once
#include "Particle.h"
#include "ParticleGenerator.h"

#include <list>
#include <string>

using namespace std;

class ParticleSystem
{
private:
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
	list<ParticleGenerator*> _particle_generators;
	vector<Firework*> _fireworks_pool;

	vector<Firework*> fireworks;

public:

	FireworkSystem();
	~FireworkSystem();
	void update(double t);
	void shootFirework(Vector3 pos, Vector3 vel, Vector3 acc, float time);
	void onParticleDeath();

};