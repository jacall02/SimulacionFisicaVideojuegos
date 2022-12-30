#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <list>
#include <memory>

using namespace std;
using namespace physx;

class CircleParticleGenerator;

class RBParticle
{
public:
	RBParticle() {};
	RBParticle(Vector3 pos, Vector3 vel, Vector3 ac, double damping, int life, float inverse_mass, Vector3 size, Vector4 color, PxPhysics* gPhysics, PxScene* scene);
	~RBParticle();

	virtual void setRBParticle();

	void integrate(double t);

	void setInverseMass(double m) { inverse_mass_ = m; };
	void setVelocity(Vector3 v) { vel_ = v; };
	void setAcceleration(Vector3 a) { acc_ = a; };
	void setDamping(double d) { damping_ = d; };
	void setPosition(Vector3 p) { pose.p = p; };
	void setColor(Vector4 c) { color_ = c; };

	double getMass() { return inverse_mass_ / 1.0; };
	double getInverseMass() { return inverse_mass_; };
	Vector3 getVelocity() { return vel_; };
	Vector3 getAcceleration() { return acc_; };
	double getDamping() { return damping_; };
	virtual physx::PxTransform getPosition() { return rigido_->getGlobalPose(); };
	float getLife() { return life_; };
	Vector4 getColor() { return color_; };

	void clearForce();

	void addForce(const Vector3& f);

protected:
	Vector4 color_;
	Vector3 size_;
	Vector3 acc_;
	double damping_;
	double inverse_mass_;
	Vector3 vel_;
	RenderItem* renderItem_ = nullptr;
	physx::PxTransform pose; //A render item le pasaremos la dirección de esta pose, para que se actualice automáticamente
	float life_;

	Vector3 force_;

	PxScene* scene_;
	PxPhysics* gPhysics_;
	PxRigidDynamic* rigido_;
	PxShape* shape_;
};

class RBCubo : public RBParticle
{
public:
	RBCubo();
	RBCubo(Vector3 pos, Vector3 vel, Vector3 ac, double damping, int life, float inverse_mass, Vector3 size, Vector4 color, PxPhysics* gPhysics, PxScene* scene);
	virtual void setRBParticle();
};

class RBStatic : public RBCubo
{
	PxRigidStatic* rigidoEstatico_;

public:
	RBStatic(Vector3 pos, Vector3 vel, Vector3 ac, double damping, int life, float inverse_mass, Vector3 size, Vector4 color, PxPhysics* gPhysics, PxScene* scene);
	~RBStatic();
	virtual void setRBParticle();

	virtual physx::PxTransform getPosition() { return rigidoEstatico_->getGlobalPose(); }; 
};

