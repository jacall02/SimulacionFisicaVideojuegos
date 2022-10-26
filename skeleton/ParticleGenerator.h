#pragma once
#include "Particle.h"

#include <list>
#include <string>
#include <random>


using namespace std;

class ParticleGenerator
{
private:
	string _name;
protected:
	Vector3 pos_, offPos_, vel_, offVel_, acc_;
	double _generation_probability;
	Particle::ParticleType type_;
	int _num_particles;

public:
	ParticleGenerator();
	~ParticleGenerator();
	void setParticle(Particle* model);
	virtual list<Particle*> generateParticles() = 0;
};

class GaussianParticleGenerator : public ParticleGenerator {
private:

public:
	GaussianParticleGenerator(Vector3 pos, Vector3 offPos, Vector3 vel, Vector3 offVel, Vector3 acc, int num, Particle::ParticleType type, double propability = 100);
	virtual list<Particle*> generateParticles();
};


class UniformParticleGenerator : public ParticleGenerator {
private:
	Vector3 _vel_width, _pos_width;

public:
	UniformParticleGenerator(Vector3 pos, Vector3 offPos, Vector3 vel, Vector3 offVel, Vector3 acc, int num, Particle::ParticleType type, double propability = 100);
	virtual list<Particle*> generateParticles();
	list<Firework*> generateFireworks();
};

