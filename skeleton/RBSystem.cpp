#include "RBSystem.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringForceGenerator.h"
#include "BungeeForceGenerator.h"
#include "BuoyancyForceGenerator.h"

RBSystem::RBSystem(PxScene* scene, PxPhysics* gPhysics) : scene_(scene), gPhysics_(gPhysics)
{
}

void RBSystem::update(double t)
{
	forceRegistry_->updateForces(t);

	for (int i = 0; i < particles.size(); i++) {
		particles[i]->integrate(t);
		if (particles[i]->getLife() < 0) {
			auto p = particles[i];
			forceRegistry_->deleteParticleRegistry(p);
			delete p;
			particles.erase(particles.begin() + i);
			i--;
		}
	}

	if (getParticleGenerator(ParticleSystem::FUENTE)->getActive()) {
		auto fuenteGenerator = getParticleGenerator(ParticleSystem::FUENTE);
		for (auto particula : fuenteGenerator->generateParticles()) {
			particles.push_back(particula);
			forceRegistry_->addRegistry(gravityForceGen_, particula);
			//forceRegistry_->addRegistry(windForceGen_, particula);
			//forceRegistry_->addRegistry(windForceGen2_, particula);
			forceRegistry_->addRegistry(whirlwindForceGen_, particula);
		}
	}

}




list<PxRigidDynamic*> RBSystem::setUniformGenerator(Vector3 pos, Vector3 offPos,
	Vector3 vel, Vector3 offVel, Vector3 acc, int num,
	int life, float inverse_mass, Vector3 size, Vector4 color, double propability) {

}