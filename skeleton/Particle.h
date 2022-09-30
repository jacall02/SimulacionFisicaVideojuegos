#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle() {};
	Particle(Vector3 pos, Vector3 vel, Vector3 ac, double damp);
	~Particle();

	void integrate(double t);

	void setMass(double m) { inverse_mass = m; };
	void setVelocity(double x, double y, double z) { vel = Vector3(x, y, z); };
	void setAcceleration(double x, double y, double z) { ac = Vector3(x, y, z); };
	void setDamping(double d) { damping = d; };
	void setPosition(double x, double y, double z) { pose.p = Vector3(x, y, z); };

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
	enum ShotType{ PISTOL, ARTILLERY, FIREBALL, LASER};
public:
	Proyectile(ShotType currentShotType, Vector3 pos, Vector3 dir);
};
