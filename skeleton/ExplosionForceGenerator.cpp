#include "ExplosionForceGenerator.h"
#include <iostream>

ExplosionForceGenerator::ExplosionForceGenerator()
{
}

ExplosionForceGenerator::ExplosionForceGenerator(Vector3 pos, double K, double radius, double constante)
{
	position_ = pos;
	K_ = K;
	radius_ = radius;
	constante_ = constante;
	isActive_ = false;

	//new Particle(pos, { 0,0,0 }, { 0,0,0 }, 1.0, 0, 1.0, radius_, { 1.0, 1.0, 0.0, 0.1 });
}

void ExplosionForceGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInverseMass()) < 1e-10)
		return;

	Vector3 particlePos = particle->getPosition().p;


	double r = pow((particlePos.x - position_.x), 2) +
		pow((particlePos.y - position_.y), 2) +
		pow((particlePos.z - position_.z), 2);

	if (r < radius_) {

		Vector3 diferencia = Vector3((particlePos.x - position_.x), (particlePos.y - position_.y), (particlePos.z - position_.z));

		Vector3 explosionF = (K_ / r) * diferencia * std::exp(-t / constante_);

		particle->addForce(explosionF);
	}

	radius_ += vel_expansion * t;
}

void ExplosionForceGenerator::updateForce(RBParticle* particle, double t)
{
	if (fabs(particle->getInverseMass()) < 1e-10)
		return;

	Vector3 particlePos = particle->getPosition().p;


	double r = pow((particlePos.x - position_.x), 2) +
		pow((particlePos.y - position_.y), 2) +
		pow((particlePos.z - position_.z), 2);

	if (r < radius_) {

		Vector3 diferencia = Vector3((particlePos.x - position_.x), (particlePos.y - position_.y), (particlePos.z - position_.z));

		Vector3 explosionF = (K_ / r) * diferencia * std::exp(-t / constante_);

		particle->addForce(explosionF);
	}

	radius_ += vel_expansion * t;
}
