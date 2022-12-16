#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include "Particle.h"
#include "ParticleSystem.h"

#include <iostream>
#include "RBSystem.h"



using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;


PxMaterial* gMaterial = NULL;

PxPvd* gPvd = NULL;

PxDefaultCpuDispatcher* gDispatcher = NULL;
PxScene* gScene = NULL;
ContactReportCallback gContactReportCallback;

std::vector<Particle*> particles;
ParticleSystem* sistemaParticulas;
FireworkSystem* sistemaFuegosArtificiales;
RBSystem* sistemaSolidos;


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.9f, 0.5f, 0.7f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);


	// Suelo
	PxRigidStatic* Suelo = gPhysics->createRigidStatic(PxTransform({ 0.0, 0.0, 0.0 }));
	PxShape* shape_suelo = CreateShape(PxBoxGeometry(100, 0.1, 100));
	Suelo->attachShape(*shape_suelo);
	RenderItem* item = new RenderItem(shape_suelo, Suelo, { 0.8, 0.8, 0.8, 1 });
	gScene->addActor(*Suelo);

	// Pared
	PxRigidStatic* Pared = gPhysics->createRigidStatic(PxTransform({ 10.0, 10.0, -30.0 }));
	PxShape* shape_pared = CreateShape(PxBoxGeometry(40.0, 20.0, 5.0));
	Pared->attachShape(*shape_pared);
	item = new RenderItem(shape_pared, Pared, { 0.8, 0.8, 0.8, 1 });
	gScene->addActor(*Pared);


	sistemaParticulas = new ParticleSystem();
	//sistemaParticulas->generateSpringDemo();
	sistemaFuegosArtificiales = new FireworkSystem();

	sistemaSolidos = new RBSystem(gScene, gPhysics);
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	for (int i = 0; i < particles.size(); i++) {
		particles[i]->integrate(t);
		if (particles[i]->getLife() < 0) {
			auto p = particles[i];
			delete p;
			particles.erase(particles.begin() + i);
			i--;
		}
	}

	sistemaParticulas->update(t);
	sistemaFuegosArtificiales->update(t);
	sistemaSolidos->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();

	gFoundation->release();

	for (int i = 0; i < particles.size(); i++) {
		delete particles[i];
	}
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch (toupper(key))
	{
		//case 'B': break;
		//case ' ':	break;
	case '1':
	{
		Proyectile* particula = new Proyectile(Proyectile::PISTOL,
			camera.p + GetCamera()->getDir() * 10, GetCamera()->getDir());
		particles.push_back(particula);
		break;
	}
	case '2':
	{
		Proyectile* particula = new Proyectile(Proyectile::ARTILLERY,
			camera.p + GetCamera()->getDir() * 10, GetCamera()->getDir());
		particles.push_back(particula);
		break;
	}
	case '3':
	{
		Proyectile* particula = new Proyectile(Proyectile::FIREBALL,
			camera.p + GetCamera()->getDir() * 10, GetCamera()->getDir());
		particles.push_back(particula);
		break;
	}
	case '4':
	{
		Proyectile* particula = new Proyectile(Proyectile::LASER,
			camera.p + GetCamera()->getDir() * 10, GetCamera()->getDir());
		particles.push_back(particula);
		break;
	}
	case 'F':
	{
		sistemaFuegosArtificiales->shootFirework(Vector3(-100, -100, -100),
			Vector3(0, 1, 0), Vector3(0, 100, 0), 1.8);
		break;
	}
	case 'N':
	{
		sistemaParticulas->getParticleGenerator(ParticleSystem::FUENTE)->setActive(
			!sistemaParticulas->getParticleGenerator(ParticleSystem::FUENTE)->getActive());
		break;
	}
	case 'M':
	{
		sistemaParticulas->getParticleGenerator(ParticleSystem::NUBE)->setActive(
			!sistemaParticulas->getParticleGenerator(ParticleSystem::NUBE)->getActive());
		break;
	}
	case 'B':
	{
		sistemaParticulas->getParticleGenerator(ParticleSystem::PRUEBAS)->setActive(
			!sistemaParticulas->getParticleGenerator(ParticleSystem::PRUEBAS)->getActive());
		break;
	}
	case 'V':
	{
		sistemaParticulas->getParticleGenerator(ParticleSystem::SUELO)->setActive(
			!sistemaParticulas->getParticleGenerator(ParticleSystem::SUELO)->getActive());
		break;
	}
	case 'P':
	{
		sistemaParticulas->getForceGenerator(ParticleSystem::EXPLOSION)->setActive(
			!sistemaParticulas->getForceGenerator(ParticleSystem::EXPLOSION)->getActive());
		sistemaSolidos->getForceGenerator(RBSystem::EXPLOSION)->setActive(
			!sistemaSolidos->getForceGenerator(RBSystem::EXPLOSION)->getActive());
		break;
	}
	case 'O':
	{
		sistemaParticulas->getForceGenerator(ParticleSystem::TORBELLINO)->setActive(
			!sistemaParticulas->getForceGenerator(ParticleSystem::TORBELLINO)->getActive());
		break;
	}
	case 'Q':
	{
		sistemaSolidos->getParticleGenerator(RBSystem::FUENTE)->setActive(
			!sistemaSolidos->getParticleGenerator(RBSystem::FUENTE)->getActive());
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char* const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for (PxU32 i = 0; i < frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}