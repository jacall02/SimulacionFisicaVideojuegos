#pragma once
#include "Particle.h"

#include <list>
#include <string>

using namespace std;

class ParticleGenerator
{
private:
	string _name;
	Vector3 _mean_pos, _mean_vel;
	double _generation_probability;
	int _num_particles;
	Particle* _model;

public:
	ParticleGenerator();
	~ParticleGenerator();
	void setParticle(Particle* model);
	virtual list<Particle*> generateParticles() = 0;
};

class GaussianParticleGenerator : public ParticleGenerator {
private:
	Vector3 std_dev_pos, std_dev_vel;
	double std_dev_t;

public:
	GaussianParticleGenerator();
	virtual list<Particle*> generateParticles();
};


class UniformParticleGenerator : public ParticleGenerator {
private:
	Vector3 _vel_width, _pos_width;

public:
	UniformParticleGenerator();
	virtual list<Particle*> generateParticles();
};

