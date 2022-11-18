#pragma once

#include "SpringForceGenerator.h"
#include "core.hpp"

class BungeeForceGenerator : public SpringForceGenerator {
public:
	BungeeForceGenerator();

	virtual void updateForce(Particle* particle, double t);

protected:


};

