#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator()
{

}

void SpringForceGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInverseMass()) < 1e-10)
		return;

}
