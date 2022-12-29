#include "AnchoredSpringForceGenerator.h"

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(double k, double resting, const Vector3& anchor_pos, Particle* other) : 
	SpringForceGenerator(k, resting, other) {

}
AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(double k, double resting, const Vector3& anchor_pos, RBParticle* other) : 
	SpringForceGenerator(k, resting, other) {

}

AnchoredSpringForceGenerator::~AnchoredSpringForceGenerator()
{
	if (_other != nullptr)
		delete _other;
	else
		delete _other_RB;
}

void AnchoredSpringForceGenerator::updateForce(Particle* particle, double t)
{
	Vector3 force = _other->getPosition().p - particle->getPosition().p;

	const float length = force.normalize();
	const float delta_x = length - _rest_length;

	force *= delta_x * _k;

	particle->addForce(force);
}

void AnchoredSpringForceGenerator::updateForce(RBParticle* particle, double t)
{
	Vector3 force = _other->getPosition().p - particle->getPosition().p;

	const float length = force.normalize();
	const float delta_x = length - _rest_length;

	force *= delta_x * _k;

	particle->addForce(force);
}
