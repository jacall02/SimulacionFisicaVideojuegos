#include "ParticleSystem.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringForceGenerator.h"
#include "BungeeForceGenerator.h"
#include "BuoyancyForceGenerator.h"

UniformParticleGenerator* fuente;
GaussianParticleGenerator* nube;
UniformParticleGenerator* pruebas;
UniformParticleGenerator* suelo;
ExplosionForceGenerator* explosion;
WhirlwindForceGenerator* torbellino;

ParticleSystem::ParticleSystem()
{
	fuente = new UniformParticleGenerator({ 0, 0, 0 }, { 0, 0, 0 },
		{ 0, 80, 0 }, { 10, 20, 10 }, { 0, 0, 0 }, 4, 20, 1.0, 1.0, { 0.2, 0.2, 1.0, 1.0 }, 95);

	nube = new GaussianParticleGenerator({ 100, 200, 100 }, { 100, 100, 100 },
		{ 0, 0, 0 }, { 2, 2, 2 }, { 0, 0, 0 }, 10, 10, 1.0, 1.0, { 0.8, 0.8, 0.8, 0.6 }, 80);

	pruebas = new UniformParticleGenerator({ -50, 0, -50 }, { 10, 10, 10 },
		{ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 20, 20, 1.0, 0.5, { 0.2, 1.0, 0.6 , 1.0 }, 100);

	suelo = new UniformParticleGenerator({ -100, 0, -100 }, { 100, 0, 100 },
		{ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 100, 20, 1.0, 0.2, { 0.8, 0.4, 0.4 , 1.0 }, 100);

	gravityForceGen_ = new GravityForceGenerator(Vector3(0, -9.8, 0));
	windForceGen_ = new WindForceGenerator(1, 0, Vector3(100, 0, 0), Vector3(0, 50, 0), 20);
	windForceGen2_ = new WindForceGenerator(1, 0, Vector3(-100, -10, 0), Vector3(100, 100, 0), 50);
	whirlwindForceGen_ = new WhirlwindForceGenerator(1, 0, 1.0, 1.0, Vector3(0, 50, 0), 50);
	whirlwindForceGen_->setActive(true);
	explosionForceGen_ = new ExplosionForceGenerator(Vector3(0, 0, 0), 200000, 10, 2);

	explosion = new ExplosionForceGenerator(Vector3(-100, -10, -100), 200000, 10, 2);
	torbellino = new WhirlwindForceGenerator(1, 0, 1.0, 1.0, Vector3(-100, 10, -100), 400);

	forceRegistry_ = new ParticleForceRegistry();

}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::update(double t)
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

	if (getParticleGenerator(ParticleSystem::NUBE)->getActive()) {
		auto nubeGenerator = getParticleGenerator(ParticleSystem::NUBE);
		for (auto particula : nubeGenerator->generateParticles()) {
			particles.push_back(particula);
			//forceRegistry_->addRegistry(gravityForceGen_, particula);
			//forceRegistry_->addRegistry(whirlwindForceGen_, particula);
		}
	}

	if (getParticleGenerator(ParticleSystem::PRUEBAS)->getActive()) {
		auto pruebasGenerator = getParticleGenerator(ParticleSystem::PRUEBAS);
		for (auto particula : pruebasGenerator->generateParticles()) {
			particles.push_back(particula);
			forceRegistry_->addRegistry(explosion, particula);
			forceRegistry_->addRegistry(torbellino, particula);
		}
	}

	if (getParticleGenerator(ParticleSystem::SUELO)->getActive()) {
		auto sueloGenerator = getParticleGenerator(ParticleSystem::SUELO);
		for (auto particula : sueloGenerator->generateParticles()) {
			particles.push_back(particula);
			forceRegistry_->addRegistry(explosion, particula);
			forceRegistry_->addRegistry(torbellino, particula);
		}
	}
}

ParticleGenerator* ParticleSystem::getParticleGenerator(Generator name)
{
	switch (name)
	{
	case ParticleSystem::FUENTE:
		return fuente;
		break;
	case ParticleSystem::NUBE:
		return nube;
		break;
	case ParticleSystem::PRUEBAS:
		return pruebas;
		break;
	case ParticleSystem::SUELO:
		return suelo;
		break;
	default:
		break;
	}
}

ForceGenerator* ParticleSystem::getForceGenerator(FGenerator name)
{
	switch (name)
	{
	case ParticleSystem::EXPLOSION:
		return explosion;
		break;
	case ParticleSystem::TORBELLINO:
		return torbellino;
		break;
	default:
		break;
	}
}

FireworkSystem::FireworkSystem()
{

}

void FireworkSystem::update(double t) {
	for (int i = 0; i < fireworks.size(); i++) {
		fireworks[i]->integrate(t);
		if (fireworks[i]->getLife() < 0) {
			auto p = fireworks[i];
			auto listaAux = fireworks[i]->explode();
			delete p;
			fireworks.erase(fireworks.begin() + i);
			i--;
			fireworks.insert(fireworks.end(), listaAux.begin(), listaAux.end());
		}
	}
}

void FireworkSystem::shootFirework(Vector3 pos, Vector3 vel, Vector3 acc, float time)
{
	pos.x = (pos.x - ((rand() % 200)));
	pos.z = (pos.z - ((rand() % 200)));
	pos.y = (pos.z - ((rand() % 100)));
	acc.y *= ((rand() % 2) + 1);
	Firework* particula = new Firework(pos, vel, acc, 0.99f, time,
		Vector4((rand() % 10) / 10.0, (rand() % 10) / 10.0, (rand() % 10) / 10.0, 1));
	fireworks.push_back(particula);
	auto sistema = new CircleParticleGenerator(pos, vel, (rand() % 10) + 5, particula);
	sistema->reps_ = (rand() % 3);
	particula->_gens.emplace_back(sistema);
}

void ParticleSystem::generateSpringDemo() {
	Particle* p1 = new Particle({ -10.0, 50.0, 0.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 60, 1, 2, { 1.0,1.0,0.2,1.0 });
	Particle* p2 = new Particle({ 10.0, 10.0, 0.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 60, 1, 2, { 0.2,1.0,1.0,1.0 });
	p2->setInverseMass(2.0);
	SpringForceGenerator* f1 = new SpringForceGenerator(1, 10, p2);
	forceRegistry_->addRegistry(f1, p1);
	SpringForceGenerator* f2 = new SpringForceGenerator(1, 10, p1);
	forceRegistry_->addRegistry(f2, p2);

	forceRegistry_->addRegistry(whirlwindForceGen_, p1);

	particles.push_back(p1);
	particles.push_back(p2);



	Particle* p3 = new Particle({ 30.0, 30.0, 0.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 60, 1, 2, { 1.0, 0.5,0.2,1.0 });
	AnchoredSpringForceGenerator* f3 = new AnchoredSpringForceGenerator(1, 10, { 30.0, 60.0, 0.0 });
	forceRegistry_->addRegistry(f3, p3);

	particles.push_back(p3);



	Particle* p4 = new Particle({ 10.0, 60.0, -10.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 60, 1, 2, { 0.8,0.2,0.2,1.0 });
	Particle* p5 = new Particle({ 10.0, 40.0, -10.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 60, 1, 2, { 0.8,1.0,1.0,1.0 });
	BungeeForceGenerator* f4 = new BungeeForceGenerator(1, 20, p5);
	forceRegistry_->addRegistry(f4, p4);
	BungeeForceGenerator* f5 = new BungeeForceGenerator(1, 20, p4);
	forceRegistry_->addRegistry(f5, p5);
	forceRegistry_->addRegistry(gravityForceGen_, p4);

	particles.push_back(p4);
	particles.push_back(p5);





	Particle* p6 = new Particle({ -50.0, 50.0, -30.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 60, 1, 2, { 0.1,0.0,1.0,1.0 });
	AnchoredSpringForceGenerator* f6 = new AnchoredSpringForceGenerator(10, 10, { -50.0, 60.0, -30.0 });
	forceRegistry_->addRegistry(f6, p6);
	particles.push_back(p6);

	Particle* p7 = new Particle({ -50.0, 40.0, -30.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 60, 1, 2, { 0.4,0.0,1.0,1.0 });
	SpringForceGenerator* f7 = new SpringForceGenerator(1, 10, p6);
	forceRegistry_->addRegistry(f7, p7);
	particles.push_back(p7);

	Particle* p8 = new Particle({ -50.0, 30.0, -30.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 60, 1, 2, { 0.7,0.0,1.0,1.0 });
	SpringForceGenerator* f8 = new SpringForceGenerator(1, 10, p7);
	forceRegistry_->addRegistry(f8, p8);
	particles.push_back(p8);

	Particle* p9 = new Particle({ -50.0, 20.0, -30.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 60, 1, 2, { 1.0,0.0,1.0,1.0 });
	SpringForceGenerator* f9 = new SpringForceGenerator(1, 10, p8);
	forceRegistry_->addRegistry(f9, p9);
	particles.push_back(p9);

	Particle* p10 = new Particle({ -50.0, 10.0, -30.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 60, 1, 2, { 1.0,0.0,0.7,1.0 });
	SpringForceGenerator* f10 = new SpringForceGenerator(1, 10, p9);
	forceRegistry_->addRegistry(f10, p10);
	particles.push_back(p10);

	Particle* p11 = new Particle({ -50.0, 0.0, -30.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 60, 1, 2, { 1.0,0.0,0.4,1.0 });
	SpringForceGenerator* f11 = new SpringForceGenerator(1, 10, p10);
	forceRegistry_->addRegistry(f11, p11);
	particles.push_back(p11);

	Particle* p12 = new Particle({ -50.0, -10.0, -30.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 60, 1, 2, { 1.0,0.0,0.1,1.0 });
	SpringForceGenerator* f12 = new SpringForceGenerator(1, 5, p11);
	forceRegistry_->addRegistry(f12, p12);
	particles.push_back(p12);

	forceRegistry_->addRegistry(gravityForceGen_, p6);
	forceRegistry_->addRegistry(gravityForceGen_, p7);
	forceRegistry_->addRegistry(gravityForceGen_, p8);
	forceRegistry_->addRegistry(gravityForceGen_, p9);
	forceRegistry_->addRegistry(gravityForceGen_, p10);
	forceRegistry_->addRegistry(gravityForceGen_, p11);
	forceRegistry_->addRegistry(gravityForceGen_, p12);



	Particle* p13 = new Particle({ -10.0, 10.0, -30.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 60, 1, 2, { 1.0, 1.0,0.2,1.0 });
	//Cubo* cubo = new Cubo({ -10.0, 100.0, -30.0 }, 10.0, 30.0, 5.0, { 1.0, 1.0,0.2,1.0 }, 10.0f);
	BuoyancyForceGenerator* f13 = new BuoyancyForceGenerator(10.0, 10.0, 1.0);
	forceRegistry_->addRegistry(f13, p13);
	forceRegistry_->addRegistry(gravityForceGen_, p13);

	particles.push_back(p13);
}

void ParticleSystem::generateSueloArena()
{

}
