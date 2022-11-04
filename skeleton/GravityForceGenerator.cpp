#include "GravityForceGenerator.h"

void GravityForceGenerator::updateForce(Particle* particle, double t){
	if (fabs(particle->getInverseMass()) < 1e-10)
		return;

	particle->addForce(_gravity * particle->getMass());
}
