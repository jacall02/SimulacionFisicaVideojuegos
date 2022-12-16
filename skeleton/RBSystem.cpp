#include "RBSystem.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringForceGenerator.h"
#include "BungeeForceGenerator.h"
#include "BuoyancyForceGenerator.h"

UniformRigidGenerator* fuente;


RBSystem::RBSystem(PxScene* scene, PxPhysics* gPhysics) : scene_(scene), gPhysics_(gPhysics)
{

	fuente = new UniformRigidGenerator({ 0.0,100.0,0.0 }, { 0.0,0.0,0.0 }, { 0.0,5.0,2.0 }, { 0.0,1.0,1.0 },
		{ 0.0,0.0,0.0 }, 1, 40, 1, { 1.0,0.5,1.5 }, { 1.0,0.5,1.0,1.0 }, 1.0, gPhysics_, scene_);

	forceRegistry_ = new RigidForceRegistry();
	windForceGen_ = new WindForceGenerator(1, 0, Vector3(100, 0, 0), Vector3(0, 50, 0), 20);

}

void RBSystem::update(double t)
{
	forceRegistry_->updateForces(t);
	if (fuente->getActive()) {
		for (auto solido : fuente->uniformGenerator()) {
			solidosRigidos_.push_back(solido);
			forceRegistry_->addRegistry(windForceGen_, solido);
		}
	}

}

UniformRigidGenerator* RBSystem::getParticleGenerator(Generator name)
{
	switch (name)
	{
	case RBSystem::FUENTE:
		return fuente;
		break;
	default:
		break;
	}
}
