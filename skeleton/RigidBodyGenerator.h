#pragma once
#include "core.hpp"

#include <list>
#include <string>
#include <random>

using namespace std;
using namespace physx;

class RigidBodyGenerator
{

protected:
	Vector3 pos_, offPos_, vel_, offVel_, acc_;
	double _generation_probability;
	int _num_particles;
	bool active_;
	float size_;
	int life_;
	double inverse_mass_;
	Vector4 color_;
	PxPhysics* gPhysics_;

public:
	RigidBodyGenerator();
	~RigidBodyGenerator();
	virtual list<PxRigidDynamic*> generateParticles() = 0;

	void setActive(bool a) { active_ = a; };
	bool getActive() { return active_; };

	void setPos(Vector3 pos) { pos_ = pos; };
	PxRigidDynamic* GenerateSolid(Vector3 pos, Vector3 vel, Vector3 acc, int life, float inverse_mass, Vector3 size, Vector4 color);
};

class UniformRigidGenerator : public RigidBodyGenerator
{
	UniformRigidGenerator(Vector3 pos, Vector3 offPos, Vector3 vel, Vector3 offVel, Vector3 acc, int num, int life, float inverse_mass, float size, Vector4 color, double propability, PxPhysics* gPhysics);
	list<PxRigidDynamic*> uniformGenerator(Vector3 pos, Vector3 offPos, Vector3 vel, Vector3 offVel, Vector3 acc, int num, int life, float inverse_mass, Vector3 size, Vector4 color, double propability);
};

