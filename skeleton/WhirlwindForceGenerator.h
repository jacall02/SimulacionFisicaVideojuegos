#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
#include "WindForceGenerator.h"

class WhirlwindForceGenerator : public WindForceGenerator {

public:
	WhirlwindForceGenerator();
	WhirlwindForceGenerator(const float k1, const float k2);
	virtual void updateForce(Particle* particle, double t);
protected:
	float _k1; //Coef for velocity
	float _k2; //Coef for square velocity
};