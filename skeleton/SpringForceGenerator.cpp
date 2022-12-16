#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Particle* other)
{
	_k = k;
	_rest_length = resting_length;
	_other = other;
}

void SpringForceGenerator::updateForce(Particle* particle, double t)
{
	Vector3 force = _other->getPosition().p - particle->getPosition().p;

	const float length = force.normalize();
	const float delta_x = length - _rest_length;

	force *= delta_x * _k;

	particle->addForce(force);
}

void SpringForceGenerator::updateForce(RBParticle* particle, double t)
{
	Vector3 force = _other->getPosition().p - particle->getPosition().p;

	const float length = force.normalize();
	const float delta_x = length - _rest_length;

	force *= delta_x * _k;

	particle->addForce(force);
}
