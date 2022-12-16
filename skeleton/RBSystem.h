#pragma once
#include "Particle.h"
#include "ParticleGenerator.h"
#include "ParticleForceRegistry.h"

#include "RBParticle.h"
#include "RigidBodyGenerator.h"
#include "WhirlwindForceGenerator.h"


using namespace std;
using namespace physx;

class RBSystem
{
private:
	std::vector<RBParticle*> solidosRigidos_;
	RigidForceRegistry* forceRegistry_;
	WhirlwindForceGenerator* whirlwindForceGen_;
	WindForceGenerator* windForceGen_;
	PxScene* scene_;
	PxPhysics* gPhysics_;

public:
	enum Generator { FUENTE };

	RBSystem(PxScene *scene, PxPhysics *gPhysics);
	~RBSystem() {};
	void update(double t);
	UniformRigidGenerator* getParticleGenerator(Generator name);
};