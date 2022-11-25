#pragma once

#include "SpringForceGenerator.h"
#include "core.hpp"

class AnchoredSpringForceGenerator : public SpringForceGenerator {
public:
	AnchoredSpringForceGenerator(double k, double resting, const Vector3& anchor_pos);
	~AnchoredSpringForceGenerator();

	virtual void updateForce(Particle* particle, double t);

protected:
	Particle* _other;
};

