#pragma once

#include "SpringForceGenerator.h"
#include "core.hpp"

class RBParticle;

class AnchoredSpringForceGenerator : public SpringForceGenerator {
public:
	AnchoredSpringForceGenerator(double k, double resting, const Vector3& anchor_pos, Particle* other);
	AnchoredSpringForceGenerator(double k, double resting, const Vector3& anchor_pos, RBParticle* other);
	~AnchoredSpringForceGenerator();

	virtual void updateForce(Particle* particle, double t);
	virtual void updateForce(RBParticle* particle, double t);

protected:
	Particle* _other;
};

