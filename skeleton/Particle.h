#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle() {};
	Particle(Vector3 pos, Vector3 vel, Vector3 ac, double damp);
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
	double getDamping(){ return damping; };
	physx::PxTransform getPosition() { return pose; };

private: 
	Vector3 vel;
	Vector3 ac;
	double damping;
	double inverse_mass;
	physx::PxTransform pose; //A render item le pasaremos la dirección de esta pose, para que se actualice automáticamente
	RenderItem* renderItem;
};

class Proyectile : public Particle
{
public:
	enum ShotType{ PISTOL, ARTILLERY, FIREBALL, LASER};
	Proyectile(ShotType currentShotType, Vector3 pos, Vector3 dir);
private:
	ShotType type;
};
