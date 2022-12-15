#include "RBParticle.h"

RBParticle::RBParticle(Vector3 pos, Vector3 vel, Vector3 ac, double damping, int life, float inverse_mass, Vector3 size, Vector4 color, PxPhysics* gPhysics) :
	vel_(vel), acc_(ac), damping_(damping), life_(life), inverse_mass_(inverse_mass), size_(size), color_(color)
{
	pose = physx::PxTransform(pos.x, pos.y, pos.z);
	force_ = Vector3(0, 0, 0);
	gPhysics_ = gPhysics;
	setRBParticle();
}

RBParticle::~RBParticle()
{
	DeregisterRenderItem(renderItem);
}

void RBParticle::setRBParticle() {
	PxRigidDynamic* rigido = gPhysics_->createRigidDynamic(PxTransform(pose));
	rigido->setLinearVelocity(vel_);
	rigido->setAngularVelocity({ 1.0,0.0,0.0 });
	PxShape* shape = CreateShape(PxBoxGeometry(size_.x / 2.0, size_.y / 2.0, size_.z / 2.0));
	rigido->attachShape(*shape);
	Vector3 inertia = { size_.y * size_.y + size_.z * size_.z,
						size_.y * size_.y + size_.z * size_.z,
						size_.y * size_.y + size_.z * size_.z };
}

void RBParticle::integrate(double t)
{
	if (inverse_mass_ <= 0.0f) return;

	pose = physx::PxTransform(pose.p.x + vel_.x * t, pose.p.y + vel_.y * t, pose.p.z + vel_.z * t);

	Vector3 totalAcceleration = acc_;
	totalAcceleration += force_ * inverse_mass_;

	vel_ += totalAcceleration * t;

	vel_ *= powf(damping_, t);

	life_ -= t;

	clearForce();
}

void RBParticle::clearForce()
{
	force_ *= 0;
}

void RBParticle::addForce(const Vector3& f)
{
	force_ += f;
}

RBCubo::RBCubo(Vector3 pos, Vector3 vel, Vector3 ac, double damping, int life, float inverse_mass, Vector3 size, Vector4 color)
{
	vel_ = vel;
	acc_ = ac;
	damping_ = damping;
	life_ = life;
	inverse_mass_ = inverse_mass;
	size_ = size;
	color_ = color;

	pose = physx::PxTransform(pos.x, pos.y, pos.z);
	force_ = Vector3(0, 0, 0);
	setRBParticle();
}

void RBCubo::setRBParticle() {
	renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(hX_, hY_, hZ_)), &pose, color_);
}