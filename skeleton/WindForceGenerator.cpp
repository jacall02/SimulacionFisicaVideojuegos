#include "WindForceGenerator.h"
#include <iostream>

WindForceGenerator::WindForceGenerator()
{
}

WindForceGenerator::WindForceGenerator(const float k1, const float k2, Vector3 windVelocity,
	Vector3 pos, int radius)
{
	setDrag(k1, k2);
	windVelocity_ = windVelocity;
	position_ = pos;
	radius_ = radius;
	isActive_ = true;

	//new Particle(pos, { 0,0,0 }, { 0,0,0 }, 1.0, 0, 1.0, radius_, { 1.0, 0.0, 0.0, 0.1 });
}

void WindForceGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInverseMass()) < 1e-10)
		return;

	Vector3 particlePos = particle->getPosition().p;
	if ((particlePos.x <= position_.x + radius_ && particlePos.x >= position_.x - radius_) &&
		(particlePos.y <= position_.y + radius_ && particlePos.y >= position_.y - radius_) &&
		(particlePos.z <= position_.z + radius_ && particlePos.z >= position_.z - radius_)) {

		Vector3 v = particle->getVelocity() - windVelocity_;
		float velocity_module = v.normalize();
		Vector3 dragF;
		velocity_module = _k1 * velocity_module + _k2 * velocity_module * velocity_module;
		dragF = -v * velocity_module;

		particle->addForce(dragF);
	}
}

void WindForceGenerator::updateForce(RBParticle* particle, double t)
{
	if (fabs(particle->getInverseMass()) < 1e-10)
		return;

	Vector3 particlePos = particle->getPosition().p;
	if ((particlePos.x <= position_.x + radius_ && particlePos.x >= position_.x - radius_) &&
		(particlePos.y <= position_.y + radius_ && particlePos.y >= position_.y - radius_) &&
		(particlePos.z <= position_.z + radius_ && particlePos.z >= position_.z - radius_)) {

		Vector3 v = particle->getVelocity() - windVelocity_;
		float velocity_module = v.normalize();
		Vector3 dragF;
		velocity_module = _k1 * velocity_module + _k2 * velocity_module * velocity_module;
		dragF = -v * velocity_module;

		particle->addForce(dragF);
	}
}
