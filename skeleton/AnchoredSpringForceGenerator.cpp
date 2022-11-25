#include "AnchoredSpringForceGenerator.h"

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(double k, double resting, const Vector3& anchor_pos) : 
	SpringForceGenerator(k, resting, nullptr) {
	_other = new Cubo(anchor_pos, 10, 2, 10, { 0.4, 1.0, 0.2, 1.0 });

}

AnchoredSpringForceGenerator::~AnchoredSpringForceGenerator()
{
	delete _other;
}

void AnchoredSpringForceGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInverseMass()) < 1e-10)
		return;

}
