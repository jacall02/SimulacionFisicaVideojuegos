#pragma once

#include "SpringForceGenerator.h"
#include "core.hpp"

class AnchoredSpringForceGenerator : public SpringForceGenerator {
public:
	AnchoredSpringForceGenerator();

	virtual void updateForce(Particle* particle, double t);

protected:
	//Particle* _other; es fija
};

