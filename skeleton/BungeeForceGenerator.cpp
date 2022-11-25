#include "BungeeForceGenerator.h"

void BungeeForceGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInverseMass()) < 1e-10)
		return;

}
