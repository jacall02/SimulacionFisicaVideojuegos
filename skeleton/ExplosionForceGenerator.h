#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class ExplosionForceGenerator : public ForceGenerator {

public:
	ExplosionForceGenerator();
	ExplosionForceGenerator(Vector3 pos_, double K, double radius, double constante);
	virtual void updateForce(Particle* particle, double t) override;
protected:
	Vector3 position_;
	int K_;
	float radius_;
	double constante_;
	int vel_expansion = 343;
};