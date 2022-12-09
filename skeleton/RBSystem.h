#pragma once
#include "Particle.h"
#include "ParticleGenerator.h"
#include "ParticleForceRegistry.h"

#include "WindForceGenerator.h"
#include "ExplosionForceGenerator.h"

using namespace std;
using namespace physx;
class RBSystem
{
private:
	std::vector<PxRigidDynamic*> solidosRigidos_;
	PxScene* scene_;
	PxPhysics* gPhysics_;

public:
	RBSystem(PxScene *scene, PxPhysics *gPhysics);
	~RBSystem();
	void update(double t);

	PxRigidDynamic* GenerateSolid(Vector3 pos, Vector3 vel, Vector3 acc, int life, float inverse_mass, float size, Vector4 color);

	list<PxRigidDynamic*> uniformGenerator(Vector3 pos, Vector3 offPos, Vector3 vel, Vector3 offVel, Vector3 acc, int num, int life, float inverse_mass, float size, Vector4 color, double propability);
};