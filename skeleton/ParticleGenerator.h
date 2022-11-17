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
	int _num_particles;
	bool active_;
	float size_;
	int life_;
	double inverse_mass_;
	Vector4 color_;

public:
	ParticleGenerator();
	~ParticleGenerator();
	virtual list<Particle*> generateParticles() = 0;

	void setActive(bool a) { active_ = a; };
	bool getActive() { return active_; };

	void setPos(Vector3 pos) { pos_ = pos; };
};

class GaussianParticleGenerator : public ParticleGenerator {
public:
	GaussianParticleGenerator(Vector3 pos, Vector3 offPos, Vector3 vel, Vector3 offVel, Vector3 acc, int num, int life, float inverse_mass, float size, Vector4 color, double propability);
	virtual list<Particle*> generateParticles();
};


class UniformParticleGenerator : public ParticleGenerator {
public:
	UniformParticleGenerator(Vector3 pos, Vector3 offPos, Vector3 vel, Vector3 offVel, Vector3 acc, int num, int life, float inverse_mass, float size, Vector4 color, double propability);
	virtual list<Particle*> generateParticles();
};


class CircleParticleGenerator : public ParticleGenerator {
private:
	Firework* model_;
public:
	CircleParticleGenerator(Vector3 pos, Vector3 vel, int num, Firework* model);
	virtual list<Particle*> generateParticles();
	virtual list<Firework*> generateFireworks();
	void setParticle(Firework* model);

	int reps_;
};

