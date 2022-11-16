#include "ParticleDragGenerator.h"
#include <iostream>

void ParticleDragGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInverseMass()) < 1e-10)
		return;

	Vector3 v = particle->getVelocity();
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	dragF = -v * drag_coef;

	std::cout << dragF.x << "\t" << dragF.y << "\t" << dragF.z << std::endl;
	particle->addForce(dragF);
}
