#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class SpringForceGenerator : public ForceGenerator {
public:
	SpringForceGenerator();

	virtual void updateForce(Particle* particle, double t);

protected:
	float _k;
	float _rest_length;
	Particle* _other;
	//_force = p1->getPos
	//_l = _force.normalice()
	//_force *= (-l-_rest_length)*_k
};

