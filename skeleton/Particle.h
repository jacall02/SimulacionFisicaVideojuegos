#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <list>

using namespace std;

class Particle
{
public:
	enum ParticleType { WATER, MIST, FIRE, };

	Particle() {};
	Particle(Vector3 pos, Vector3 vel, Vector3 ac, double damp, ParticleType type = WATER, int time = 10);
	~Particle();

	void setParticle();

	void integrate(double t);

	void setMass(double m) { inverse_mass = m; };
	void setVelocity(Vector3 v) { vel = v; };
	void setAcceleration(Vector3 a) { ac = a; };
	void setDamping(double d) { damping = d; };
	void setPosition(Vector3 p) { pose.p = p; };

	double getMass() { return inverse_mass; };
	Vector3 getVelocity() { return vel; };
	Vector3 getAcceleration() { return ac; };
	double getDamping() { return damping; };
	physx::PxTransform getPosition() { return pose; };

	float getLife() { return life; };

private: 
	Vector3 vel;
	Vector3 ac;
	double damping;
	double inverse_mass;

protected:
	RenderItem* renderItem;
	physx::PxTransform pose; //A render item le pasaremos la dirección de esta pose, para que se actualice automáticamente
	float life;

	ParticleType type_;
};

class Proyectile : public Particle
{
public:
	enum ShotType{ PISTOL, ARTILLERY, FIREBALL, LASER};
	Proyectile(ShotType currentShotType, Vector3 pos, Vector3 dir);
	void setParticle();
private:
	ShotType type;
};

class Firework : public Particle
{
public:
	enum FireworkType { NORMAL };
	Firework(Vector3 pos, Vector3 vel, Vector3 ac, double damp, int time = 10);
	int update(double t);
	virtual Particle* clone() const;
	list<Particle*> explode();

private:
	//list<shared_ptr Particle> _gens;
};
