#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class SpringForceGenerator : public ForceGenerator {
public:
	SpringForceGenerator(double k, double resting_length, Particle* other);
	SpringForceGenerator(double k, double resting_length, RBParticle* other);

	virtual void updateForce(Particle* particle, double t);
	virtual void updateForce(RBParticle* particle, double t);

protected:
	float _k;
	float _rest_length;
	Particle* _other;
	RBParticle* _other_RB;
};

