#include "ParticleSystem.h"

UniformParticleGenerator* fuente;
GaussianParticleGenerator* nube;

ParticleSystem::ParticleSystem()
{
	fuente = new UniformParticleGenerator({ 0, 0, 0 }, { 0, 0, 0 },
		{ 0, 80, 0 }, { 10, 20, 10 }, { 0, 0, 0 }, 4, 20, 1.0, 1.0, { 0.2, 0.2, 1.0, 1.0 }, 95);

	nube = new GaussianParticleGenerator({ 0, 0, 0 }, { 100, 100, 100 },
		{ 0, 0, 0 }, { 2, 2, 2 }, { 0, 0, 0 }, 10, 10, 1.0, 1.0, { 0.8, 0.8, 0.8, 0.6 }, 80);


	gravityForceGen_ = new GravityForceGenerator(Vector3(0, -9.8, 0));
	windForceGen_ = new WindForceGenerator(1, 0, Vector3(100, 0, 0), Vector3(0,50,0), 20);
	windForceGen2_ = new WindForceGenerator(1, 0, Vector3(-100, -10, 0), Vector3(100, 100, 0), 50);
	whirlwindForceGen_ = new WhirlwindForceGenerator(1, 0, 1.0, 1.0, Vector3(0, 50, 0), 50);
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
			forceRegistry_->addRegistry(whirlwindForceGen_, particula);
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