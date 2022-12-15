#pragma once
#include "Particle.h"
#include "ParticleGenerator.h"
#include "ParticleForceRegistry.h"

#include "GravityForceGenerator.h"


using namespace std;
using namespace physx;

class RBParticle;

class RBSystem
{
private:
	std::vector<RBParticle*> solidosRigidos_;
	RigidForceRegistry* forceRegistry_;
	GravityForceGenerator* gravityForceGen_;
	PxScene* scene_;
	PxPhysics* gPhysics_;

public:
	RBSystem(PxScene *scene, PxPhysics *gPhysics);
	~RBSystem();
	void update(double t);
};