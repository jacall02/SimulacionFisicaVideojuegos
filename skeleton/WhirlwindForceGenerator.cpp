#include "WhirlwindForceGenerator.h"
#include <iostream>

WhirlwindForceGenerator::WhirlwindForceGenerator()
{
}

WhirlwindForceGenerator::WhirlwindForceGenerator(const float k1, const float k2, float k, float dragToCenterCoef, Vector3 origen)
{
	windVelocity_ = Vector3(0, 0, 0);
	setDrag(k1, k2);
	k_ = k;
	dragToCenterCoef_ = dragToCenterCoef;
	origen_ = origen;
}

void WhirlwindForceGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInverseMass()) < 1e-10)
		return;

	auto x = -(particle->getPosition().p.z - origen_.z);
	auto y = 50 - (particle->getPosition().p.y - origen_.y);
	auto z = -(particle->getPosition().p.x - origen_.x);

	windVelocity_ = k_ * Vector3(x, y, z);

	Vector3 v = windVelocity_ - particle->getVelocity();
	float velocity_module = v.normalize();
	
	Vector3 dragF;
	velocity_module = _k1 * velocity_module + _k2 * velocity_module * velocity_module;
	dragF = -v * velocity_module;

	particle->addForce(dragF);
}
