#pragma once
#include "Particle.h"

#include <list>
#include <string>
#include <random>


using namespace std;

class ParticleGenerator
{
protected:
	Vector3 pos_, offPos_, vel_, offVel_, acc_;
	double _generation_probability;
	Particle::ParticleType type_;
	int _num_particles;
	Particle* model_;

public:
	ParticleGenerator();
	~ParticleGenerator();
	void setParticle(Particle* model);
	virtual list<Particle*> generateParticles() = 0;

	void setPos(Vector3 pos) { pos_ = pos; };
};

class GaussianParticleGenerator : public ParticleGenerator {
public:
	GaussianParticleGenerator(Vector3 pos, Vector3 offPos, Vector3 vel, Vector3 offVel, Vector3 acc, int num, Particle::ParticleType type, double propability = 100);
	virtual list<Particle*> generateParticles();
};


class UniformParticleGenerator : public ParticleGenerator {
public:
	UniformParticleGenerator(Vector3 pos, Vector3 offPos, Vector3 vel, Vector3 offVel, Vector3 acc, int num, Particle::ParticleType type, double propability = 100);
	virtual list<Particle*> generateParticles();
};


class CircleParticleGenerator : public ParticleGenerator {
public:
	CircleParticleGenerator(Vector3 pos, Vector3 vel, int num, Particle::ParticleType type);
	virtual list<Particle*> generateParticles();
	list<Firework*> generateFireworks();
};

