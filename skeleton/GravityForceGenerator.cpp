#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(const Vector3& g)
{
	_gravity = g;
	isActive_ = true;
}

void GravityForceGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInverseMass()) < 1e-10)
		return;

	particle->addForce(_gravity * particle->getMass());
}
