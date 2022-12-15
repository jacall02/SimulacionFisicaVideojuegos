#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
#include "WindForceGenerator.h"

class RBParticle;

class WhirlwindForceGenerator : public WindForceGenerator {

public:
	WhirlwindForceGenerator();
	WhirlwindForceGenerator(const float k1, const float k2, float k, float dragToCenterCoef, Vector3 origen, int radius);
	virtual void updateForce(Particle* particle, double t) override;
	virtual void updateForce(RBParticle* particle, double t) override;
protected:
	Vector3 origen_;
	float dragToCenterCoef_;
	float k_;
};