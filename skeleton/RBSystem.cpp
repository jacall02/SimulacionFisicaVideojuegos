#include "RBSystem.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringForceGenerator.h"
#include "BungeeForceGenerator.h"
#include "BuoyancyForceGenerator.h"
#include "RigidBodyGenerator.h"

UniformRigidGenerator* fuente;


RBSystem::RBSystem(PxScene* scene, PxPhysics* gPhysics) : scene_(scene), gPhysics_(gPhysics)
{

	fuente = new UniformRigidGenerator({ 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, { 0.0,5.0,2.0 }, { 0.0,1.0,1.0 },
		{ 0.0,0.0,0.0 }, 1, 40, 1, { 1.0,0.5,1.5 }, { 1.0,0.5,1.0,1.0 }, 1.0, gPhysics_);

}

void RBSystem::update(double t)
{
	forceRegistry_->updateForces(t);

	/*for (int i = 0; i < solidosRigidos_.size(); i++) {
		if (solidosRigidos_[i]->getLife() < 0) {
			auto p = solidosRigidos_[i];
			forceRegistry_->deleteParticleRegistry(p);
			delete p;
			solidosRigidos_.erase(solidosRigidos_.begin() + i);
			i--;
		}
	}*/

	if (fuente->getActive()) {
		for (auto solido : fuente->uniformGenerator()) {
			solidosRigidos_.push_back(solido);
			forceRegistry_->addRegistry(gravityForceGen_, solido);
		}
	}

}