#include "RBSystem.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringForceGenerator.h"
#include "BungeeForceGenerator.h"
#include "BuoyancyForceGenerator.h"

UniformRigidGenerator* fuente;


RBSystem::RBSystem(PxScene* scene, PxPhysics* gPhysics) : scene_(scene), gPhysics_(gPhysics)
{

	fuente = new UniformRigidGenerator({ 0.0,100.0,0.0 }, { 100.0,0.0,100.0 }, { 0.0,5.0,2.0 }, { 0.0,1.0,1.0 },
		{ 0.0,0.0,0.0 }, 1, 40, 1, { 10.0,0.5,1.5 }, { 1.0,0.5,1.0,1.0 }, 1.0, gPhysics_, scene_);

	forceRegistry_ = new RigidForceRegistry();
	windForceGen_ = new WindForceGenerator(1, 0, Vector3(100, 0, 0), Vector3(0, 50, 0), 20);
	whirlwindForceGen_ = new WhirlwindForceGenerator(1, 0, 1.0, 1.0, Vector3(0, 50, 0), 50);
	whirlwindForceGen_->setActive(true);
	explosion = new ExplosionForceGenerator(Vector3(0, 10, 0), 200000, 10, 2);
}

void RBSystem::update(double t)
{
	for (int i = 0; i < solidosRigidos_.size(); i++) {
		solidosRigidos_[i]->integrate(t);
		auto pos = solidosRigidos_[i]->getPosition().p;
		if (solidosRigidos_[i]->getLife() < 0 ||
			pos.x < -2000 || pos.x > 2000 || pos.z < -2000 || pos.z > 2000) {
			auto p = solidosRigidos_[i];
			forceRegistry_->deleteParticleRegistry(p);
			delete p;
			solidosRigidos_.erase(solidosRigidos_.begin() + i);
			i--;
		}
	}

	forceRegistry_->updateForces(t);
	if (fuente->getActive()) {
		for (auto solido : fuente->uniformGenerator()) {
			solidosRigidos_.push_back(solido);
			forceRegistry_->addRegistry(explosion, solido);
			//forceRegistry_->addRegistry(whirlwindForceGen_, solido);
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

ForceGenerator* RBSystem::getForceGenerator(FGenerator name)
{
	switch (name)
	{
	case RBSystem::EXPLOSION:
		return explosion;
		break;
	default:
		break;
	}
}


// PROYECTO FINAL
void RBSystem::clearScene()
{
	for (int i = 0; i < solidosRigidos_.size(); i++) {
		auto p = solidosRigidos_[i];
		forceRegistry_->deleteParticleRegistry(p);
		delete p;
		solidosRigidos_.erase(solidosRigidos_.begin() + i);
		i--;
	}
}

void RBSystem::generateSueloArena()
{
	UniformRigidGenerator* gen = new UniformRigidGenerator({ 0, 10, 0 }, { 30, 1, 30 },
		{ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 40, 100, 1.0, { 1.0,1.0,1.0 },
		{ 0.8, 0.4, 0.4,1.0 }, 100, gPhysics_, scene_);
	for (auto particula : gen->uniformGenerator()) {
		solidosRigidos_.push_back(particula);
		forceRegistry_->addRegistry(explosion, particula);
	}
}

void RBSystem::generateSueloPiedra()
{
}

void RBSystem::generateSueloNieve()
{
}

void RBSystem::generateSueloBaldosas()
{
}

void RBSystem::generateBloqueArena(float x, float z)
{
}

void RBSystem::generateBloquePiedra(float x, float z)
{
}

void RBSystem::generateBloqueHielo(float x, float z)
{
}

void RBSystem::generateArbol(float x, float z)
{
}

void RBSystem::generateEstructura(float x, float z)
{
}

void RBSystem::generateGelatina(float x, float z)
{
}

void RBSystem::generateJaulaS()
{
}

void RBSystem::generateJaulaM()
{
}

void RBSystem::generateJaulaL()
{
}
