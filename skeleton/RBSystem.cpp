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
	torbellino = new WhirlwindForceGenerator(1, 0, 1.0, 1.0, Vector3(-100, 10, -100), 400);
	viento = new WindForceGenerator(1, 0, Vector3(10, 0, -10), Vector3(0, 200, 0), 80);
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
	case RBSystem::VIENTO:
		return viento;
		break;
	case RBSystem::TORBELLINO:
		return torbellino;
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
	UniformRigidGenerator* gen = new UniformRigidGenerator({ 0, 15, 0 }, { 30, 10, 30 },
		{ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 100, 100, 1.5, { 2.0,2.0,2.0 },
		{ 0.8, 0.4, 0.4, 1.0 }, 1000, gPhysics_, scene_, false);
	for (auto particula : gen->uniformGenerator()) {
		solidosRigidos_.push_back(particula);
		forceRegistry_->addRegistry(explosion, particula);
		forceRegistry_->addRegistry(torbellino, particula);
		forceRegistry_->addRegistry(viento, particula);
	}
}

void RBSystem::generateSueloPiedra()
{
	UniformRigidGenerator* gen = new UniformRigidGenerator({ 0, 15, 0 }, { 40, 10, 40 },
		{ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 100, 100, 4.0, { 3.0,3.0,3.0 },
		{ 0.5, 0.5, 0.5 , 1.0 }, 100, gPhysics_, scene_, true);
	for (auto particula : gen->uniformGenerator()) {
		solidosRigidos_.push_back(particula);
		forceRegistry_->addRegistry(explosion, particula);
		forceRegistry_->addRegistry(torbellino, particula);
		forceRegistry_->addRegistry(viento, particula);
	}
}

void RBSystem::generateSueloNieve()
{
	UniformRigidGenerator* gen = new UniformRigidGenerator({ 0, 15, 0 }, { 30, 10, 30 },
		{ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 100, 100, 1.0, { 4.0,4.0,4.0 },
		{ 0.9, 0.9, 0.9 , 0.9 }, 100, gPhysics_, scene_, false);
	for (auto particula : gen->uniformGenerator()) {
		solidosRigidos_.push_back(particula);
		forceRegistry_->addRegistry(explosion, particula);
		forceRegistry_->addRegistry(torbellino, particula);
		forceRegistry_->addRegistry(viento, particula);
	}
}

void RBSystem::generateSueloBaldosas()
{
}

void RBSystem::generateBloquePiedra(float x, float z)
{
	UniformRigidGenerator* gen = new UniformRigidGenerator({ x, 6, z }, { 0, 0, 0 },
		{ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 1, 100, 8.0, { (float)(rand() % 5) + 5,
		(float)(rand() % 10) + 5, (float)(rand() % 5) + 5 },
		{ 0.5, 0.5, 0.5, 1.0 }, 1000, gPhysics_, scene_, true);
	for (auto particula : gen->uniformGenerator()) {
		solidosRigidos_.push_back(particula);
		forceRegistry_->addRegistry(explosion, particula);
		forceRegistry_->addRegistry(torbellino, particula);
		forceRegistry_->addRegistry(viento, particula);
	}

}

void RBSystem::generateBloqueHielo(float x, float z)
{
	UniformRigidGenerator* gen = new UniformRigidGenerator({ x, 6, z }, { 0, 0, 0 },
		{ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 1, 100, 6.0, { (float)(rand() % 5) + 5,
		(float)(rand() % 10) + 5, (float)(rand() % 5) + 5 },
		{ 0.8, 0.8, 1.0, 1.0 }, 1000, gPhysics_, scene_, true);
	for (auto particula : gen->uniformGenerator()) {
		solidosRigidos_.push_back(particula);
		forceRegistry_->addRegistry(explosion, particula);
		forceRegistry_->addRegistry(torbellino, particula);
		forceRegistry_->addRegistry(viento, particula);
	}

}

void RBSystem::generateArbol(float x, float z)
{
	UniformRigidGenerator* gen = new UniformRigidGenerator({ x, 6, z }, { 0, 0, 0 },
		{ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 1, 100, 20.0, { 6.0, 12.0, 6.0 },
		{ 0.8, 0.4, 0.4, 1.0 }, 1000, gPhysics_, scene_, true);
	for (auto particula : gen->uniformGenerator()) {
		solidosRigidos_.push_back(particula);
		forceRegistry_->addRegistry(explosion, particula);
		forceRegistry_->addRegistry(torbellino, particula);
		forceRegistry_->addRegistry(viento, particula);
	}

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

void RBSystem::generateExplosion() {
	UniformRigidGenerator* gen = new UniformRigidGenerator({ 0, 10, 0 }, { 10, (float)(rand() % 5) + 5,10 },
		{ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 50, 100, 0.5, { 10.0,12.0,5.0 },
		{ 0.4, 0.4, 0.4, 0.9 }, 1000, gPhysics_, scene_, false);
	for (auto particula : gen->uniformGenerator()) {
		solidosRigidos_.push_back(particula);
		//forceRegistry_->addRegistry(explosion, particula);
		forceRegistry_->addRegistry(torbellino, particula);
		forceRegistry_->addRegistry(viento, particula);
	}

	UniformRigidGenerator* gen2 = new UniformRigidGenerator({ 0, 10, 0 }, { 0, (float)(rand() % 5) + 5, 0 },
		{ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 50, 100, 0.5, { 5.0,12.0,5.0 },
		{ 0.4, 0.4, 0.4, 0.9 }, 1000, gPhysics_, scene_, false);
	for (auto particula : gen2->uniformGenerator()) {
		solidosRigidos_.push_back(particula);
		//forceRegistry_->addRegistry(explosion, particula);
		forceRegistry_->addRegistry(torbellino, particula);
		forceRegistry_->addRegistry(viento, particula);
	}
}