#include "WindForceGenerator.h"
#include <iostream>

WindForceGenerator::WindForceGenerator()
{
}

WindForceGenerator::WindForceGenerator(const float k1, const float k2, Vector3 windVelocity)
{
	setDrag(k1, k2);
	windVelocity_ = windVelocity;
}

void WindForceGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInverseMass()) < 1e-10)
		return;

	Vector3 v = windVelocity_ - particle->getVelocity();
	float velocity_module = v.normalize();
	Vector3 dragF;
	velocity_module = _k1 * velocity_module + _k2 * velocity_module * velocity_module;
	dragF = -v * velocity_module;

	particle->addForce(dragF);
}
