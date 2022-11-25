#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class SpringForceGenerator : public ForceGenerator {
public:
	SpringForceGenerator(double k, double resting_length, Particle* other);

	virtual void updateForce(Particle* particle, double t);

protected:
	float _k;
	float _rest_length;
	Particle* _other;
};

