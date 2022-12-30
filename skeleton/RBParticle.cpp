#include "RBParticle.h"

RBParticle::RBParticle(Vector3 pos, Vector3 vel, Vector3 ac, double damping, int life, float inverse_mass, Vector3 size, Vector4 color, PxPhysics* gPhysics, PxScene* scene) :
	vel_(vel), acc_(ac), damping_(damping), life_(life), inverse_mass_(inverse_mass), size_(size), color_(color)
{
	pose = physx::PxTransform(pos.x, pos.y, pos.z);
	force_ = Vector3(0, 0, 0);
	scene_ = scene;
	gPhysics_ = gPhysics;
	setRBParticle();
}

RBParticle::~RBParticle()
{
	DeregisterRenderItem(renderItem_);
	delete renderItem_;
	if (rigido_ != nullptr) {
		scene_->removeActor(*rigido_);
		rigido_->release();
	}
}

void RBParticle::setRBParticle() {
	rigido_ = gPhysics_->createRigidDynamic(PxTransform(pose));
	rigido_->setLinearVelocity(vel_);
	rigido_->setAngularVelocity({ 1.0,0.0,0.0 });
	shape_ = CreateShape(PxSphereGeometry(size_.x / 2.0));
	rigido_->attachShape(*shape_);
	Vector3 inertia = { size_.y * size_.y + size_.z * size_.z,
						size_.y * size_.y + size_.z * size_.z,
						size_.y * size_.y + size_.z * size_.z };
	rigido_->setMassSpaceInertiaTensor(inertia);
	renderItem_ = new RenderItem(shape_, rigido_, color_);
	scene_->addActor(*rigido_);
}

void RBParticle::integrate(double t)
{
	life_ -= t;
}

void RBParticle::addForce(const Vector3& f)
{
	rigido_->addForce(f);
}

RBCubo::RBCubo()
{
}

RBCubo::RBCubo(Vector3 pos, Vector3 vel, Vector3 ac, double damping, int life, float inverse_mass, Vector3 size, Vector4 color, PxPhysics* gPhysics, PxScene* scene)
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
	scene_ = scene;
	gPhysics_ = gPhysics;
	setRBParticle();
}

void RBCubo::setRBParticle() {
	rigido_ = gPhysics_->createRigidDynamic(PxTransform(pose));
	rigido_->setLinearVelocity(vel_);
	rigido_->setAngularVelocity({ 1.0,0.0,0.0 });
	PxShape* shape = CreateShape(PxBoxGeometry(size_.x / 2.0, size_.y / 2.0, size_.z / 2.0));
	rigido_->attachShape(*shape);
	Vector3 inertia = { size_.y * size_.y + size_.z * size_.z,
						size_.y * size_.y + size_.z * size_.z,
						size_.y * size_.y + size_.z * size_.z };
	rigido_->setMassSpaceInertiaTensor(inertia);
	renderItem_ = new RenderItem(shape, rigido_, color_);
	scene_->addActor(*rigido_);
}

RBStatic::RBStatic(Vector3 pos, Vector3 vel, Vector3 ac, double damping, int life, float inverse_mass, Vector3 size, Vector4 color, PxPhysics* gPhysics, PxScene* scene)
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
	scene_ = scene;
	gPhysics_ = gPhysics;
	setRBParticle();
}

RBStatic::~RBStatic() {

	if (renderItem_ != nullptr) {
		DeregisterRenderItem(renderItem_);
		delete renderItem_;
	}
	if (rigidoEstatico_ != nullptr) {
		scene_->removeActor(*rigidoEstatico_);
		rigidoEstatico_->release();
	}
}

void RBStatic::setRBParticle() {
	rigidoEstatico_ = gPhysics_->createRigidStatic(pose);
	PxShape* shape = CreateShape(PxBoxGeometry(size_.x / 2.0, size_.y / 2.0, size_.z / 2.0));
	rigidoEstatico_->attachShape(*shape);
	if (color_.w == 0.0)
		shape = CreateShape(PxBoxGeometry(size_.x / 200.0, size_.y / 200.0, size_.z / 200.0));
	renderItem_ = new RenderItem(shape, rigidoEstatico_, color_);
	scene_->addActor(*rigidoEstatico_);

	rigido_ = gPhysics_->createRigidDynamic(pose);
	PxShape* shapeAux = CreateShape(PxBoxGeometry(size_.x / 2.0, size_.y / 2.0, size_.z / 2.0));
	rigido_->attachShape(*shapeAux);
}