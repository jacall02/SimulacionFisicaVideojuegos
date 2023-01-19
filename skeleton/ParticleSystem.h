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
protected:
	std::vector<Particle*> particles;
	ParticleForceRegistry* forceRegistry_;
	GravityForceGenerator* gravityForceGen_;
	WindForceGenerator* windForceGen_;
	WindForceGenerator* windForceGen2_;
	WhirlwindForceGenerator* whirlwindForceGen_;
	ExplosionForceGenerator* explosionForceGen_;

	ExplosionForceGenerator* explosion;
	WhirlwindForceGenerator* torbellino;
	WindForceGenerator* viento;
public:
	enum Generator { FUENTE, NUBE, PRUEBAS, SUELO };
	enum FGenerator { EXPLOSION, TORBELLINO, VIENTO };

	ParticleSystem();
	~ParticleSystem();
	void update(double t);

	ParticleGenerator* getParticleGenerator(Generator name);
	ForceGenerator* getForceGenerator(FGenerator name);

	void generateSpringDemo();

	// PROYECTO FINAL
	void clearScene();
	
	void generateSueloArena();
	void generateSueloPiedra();
	void generateSueloNieve();

	void generateBloqueArena(float x, float z);

	void generateArbol(float x, float z);
	void generateEstructura(float x, float z);
};
class FireworkSystem : public ParticleSystem
{
private:
	vector<Firework*> _fireworks_pool;

	vector<Firework*> fireworks;

	
public:

	FireworkSystem();
	~FireworkSystem();
	void update(double t);
	void shootFirework(Vector3 pos, Vector3 vel, Vector3 acc, float time);


	// PROYECTO FINAL
	void clearScene();

	void generateHumo(float x, float z);
	void generateFuego(float x, float z);
};