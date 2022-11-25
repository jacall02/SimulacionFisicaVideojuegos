#pragma once
#include "Particle.h"
#include "ParticleGenerator.h"
#include "ParticleForceRegistry.h"

#include <list>
#include <string>
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"

using namespace std;

class ParticleSystem
{
private:
	std::vector<Particle*> particles;
	ParticleForceRegistry* forceRegistry_;
	GravityForceGenerator* gravityForceGen_;
	WindForceGenerator* windForceGen_;
	WindForceGenerator* windForceGen2_;
	WhirlwindForceGenerator* whirlwindForceGen_;
	ExplosionForceGenerator* explosionForceGen_;

public:
	enum Generator { FUENTE, NUBE, PRUEBAS, SUELO };
	enum FGenerator { EXPLOSION, TORBELLINO };

	ParticleSystem();
	~ParticleSystem();
	void update(double t);

	ParticleGenerator* getParticleGenerator(Generator name);
	ForceGenerator* getForceGenerator(FGenerator name);

	void generateSpringDemo();

};
class FireworkSystem : ParticleSystem
{
private:
	vector<Firework*> _fireworks_pool;

	vector<Firework*> fireworks;

	
public:

	FireworkSystem();
	~FireworkSystem();
	void update(double t);
	void shootFirework(Vector3 pos, Vector3 vel, Vector3 acc, float time);

};