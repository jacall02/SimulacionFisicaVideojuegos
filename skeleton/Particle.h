#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <list>
#include <memory>

using namespace std;

class CircleParticleGenerator;

class Particle
{
public:
	enum ParticleType { WATER, MIST, FIRE, };

	Particle() {};
	Particle(Vector3 pos, Vector3 vel, Vector3 ac, double damp, ParticleType type = WATER, int time = 10, float inverse_mass = 1.0f);
	~Particle();

	void setParticle();

	void integrate(double t);

	void setInverseMass(double m) { inverse_mass_ = m; };
	void setVelocity(Vector3 v) { vel_ = v; };
	void setAcceleration(Vector3 a) { acc_ = a; };
	void setDamping(double d) { damping_ = d; };
	void setPosition(Vector3 p) { pose.p = p; };
	void setColor(Vector4 c) { color_ = c; };

	double getMass() { return inverse_mass_/1.0; };
	double getInverseMass() { return inverse_mass_; };
	Vector3 getVelocity() { return vel_; };
	Vector3 getAcceleration() { return acc_; };
	double getDamping() { return damping_; };
	physx::PxTransform getPosition() { return pose; };
	float getLife() { return life_; };
	Vector4 getColor() { return color_; };

	void clearForce();

	void addForce(const Vector3& f);

protected:
	Vector4 color_;
	Vector3 acc_;
	double damping_;
	double inverse_mass_;
	Vector3 vel_;
	RenderItem* renderItem;
	physx::PxTransform pose; //A render item le pasaremos la dirección de esta pose, para que se actualice automáticamente
	float life_;
	ParticleType type_;

	Vector3 force_;
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
	Particle* model_;
public:
	void setModel(Particle* model) { model_ = model; };
	Particle* getModel() { return model_; };

	Firework(Vector3 pos, Vector3 vel, Vector3 ac, double damp, float time, Vector4 color, float inverse_mass = 1.0f);
	int update(double t);
	Firework* clone();
	list<Firework*> explode();

	list<shared_ptr<CircleParticleGenerator>> _gens;
private:
};
