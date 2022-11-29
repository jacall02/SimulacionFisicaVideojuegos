#include "BungeeForceGenerator.h"

BungeeForceGenerator::BungeeForceGenerator(double k, double resting, Particle* other)
	: SpringForceGenerator(k, resting, other) {
}

void BungeeForceGenerator::updateForce(Particle* particle, double t)
{
	Vector3 f = particle->getPosition().p;
	f -= _other->getPosition().p;

	float length = f.normalize();
	length = (length - _rest_length);
	if (length <= 0.0f) return;

	f *= -(length * _k);
	particle->addForce(f);
}