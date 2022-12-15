#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
#include "ParticleDragGenerator.h"

class RBParticle;

class WindForceGenerator : public ParticleDragGenerator {

public:
	WindForceGenerator();
	WindForceGenerator(const float k1, const float k2, Vector3 windVelocity, Vector3 pos, int radius);
	virtual void updateForce(Particle* particle, double t) override;
	virtual void updateForce(RBParticle* particle, double t) override;
protected:
	Vector3 windVelocity_;
	Vector3 position_;
	int radius_;
};