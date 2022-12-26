#pragma once
#include "core.hpp"

#include <list>
#include <string>
#include <random>

using namespace std;
using namespace physx;

class RBParticle;

class RigidBodyGenerator
{

protected:
	Vector3 pos_, offPos_, vel_, offVel_, acc_;
	double _generation_probability;
	int _num_particles;
	bool active_;
	Vector3 size_;
	int life_;
	double inverse_mass_;
	Vector4 color_;
	PxPhysics* gPhysics_;
	PxScene* scene_;
	bool cuadrado_;

public:
	RigidBodyGenerator();
	~RigidBodyGenerator();

	void setActive(bool a) { active_ = a; };
	bool getActive() { return active_; };

	void setPos(Vector3 pos) { pos_ = pos; };
	RBParticle* GenerateSolid(Vector3 pos, Vector3 vel, Vector3 acc, int life, float inverse_mass, Vector3 size, Vector4 color);
	RBParticle* GenerateSolidSphere(Vector3 pos, Vector3 vel, Vector3 acc, int life, float inverse_mass, Vector3 size, Vector4 color);
};

class UniformRigidGenerator : public RigidBodyGenerator
{
public:
	UniformRigidGenerator(Vector3 pos, Vector3 offPos, Vector3 vel, Vector3 offVel, Vector3 acc, int num, int life, float inverse_mass, Vector3 size, Vector4 color, double propability, PxPhysics* gPhysics, PxScene* scene, bool cuadrado = false);
	list<RBParticle*> uniformGenerator();
};

