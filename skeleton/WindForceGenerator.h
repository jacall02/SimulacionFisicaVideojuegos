#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
#include "ParticleDragGenerator.h"

class WindForceGenerator : public ParticleDragGenerator {

public:
	WindForceGenerator();
	WindForceGenerator(const float k1, const float k2);
	virtual void updateForce(Particle* particle, double t);
protected:

	float windSpeed;
};