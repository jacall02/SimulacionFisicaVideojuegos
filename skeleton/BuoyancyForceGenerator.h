#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class BuoyancyForceGenerator : public ForceGenerator {
public:
	BuoyancyForceGenerator();

	virtual void updateForce(Particle* particle, double t);

protected:


};

