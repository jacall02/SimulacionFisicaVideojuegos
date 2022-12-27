#pragma once
#include "Particle.h"
#include "ParticleGenerator.h"
#include "ParticleForceRegistry.h"

#include "RBParticle.h"
#include "RigidBodyGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"


using namespace std;
using namespace physx;

class RBSystem
{
private:
	std::vector<RBParticle*> solidosRigidos_;
	RigidForceRegistry* forceRegistry_;
	WhirlwindForceGenerator* whirlwindForceGen_;
	WindForceGenerator* windForceGen_;

	ExplosionForceGenerator* explosion;
	WhirlwindForceGenerator* torbellino;
	WindForceGenerator* viento;
	PxScene* scene_;
	PxPhysics* gPhysics_;

public:
	enum Generator { FUENTE };
	enum FGenerator { EXPLOSION, TORBELLINO, VIENTO };

	RBSystem(PxScene *scene, PxPhysics *gPhysics);
	~RBSystem() {};
	void update(double t);
	UniformRigidGenerator* getParticleGenerator(Generator name);
	ForceGenerator* getForceGenerator(FGenerator name);

	// PROYECTO FINAL
	void clearScene();

	void generateSueloArena();
	void generateSueloPiedra();
	void generateSueloNieve();
	void generateSueloBaldosas();

	void generateBloquePiedra(float x, float z);
	void generateBloqueHielo(float x, float z);

	void generateArbol(float x, float z);
	void generateEstructura(float x, float z);
	void generateGelatina(float x, float z);

	void generateJaulaS();
	void generateJaulaM();
	void generateJaulaL();

	void generateExplosion();
};