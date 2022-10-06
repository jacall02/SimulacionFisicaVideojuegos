#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 ac, double damping) : 
	vel(vel), ac(ac), damping(damping)
{
	pose = physx::PxTransform(pos.x, pos.y, pos.z);
	setParticle();
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::setParticle() {
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(3)), &pose, Vector4(1, 0, 0, 1));
}

void Particle::integrate(double t)
{
	pose = physx::PxTransform(pose.p.x + vel.x * t, pose.p.y + vel.y * t, pose.p.z + vel.z * t);
	vel += ac * t;
	vel *= powf(damping, t);
}

Proyectile::Proyectile(ShotType currentShotType, Vector3 pos, Vector3 dir)
{
	type = currentShotType;
	setPosition(pos);
	auto vel = getVelocity();
	switch (currentShotType)
	{
	case PISTOL:
		setMass(2.0f); // 2.0 Kg
		vel = dir * 35;
		setVelocity(vel);
		setAcceleration({ 0.0f, -1.0f, 0.0f });
		setDamping(0.99f);
		break;
	case ARTILLERY:
		setMass(200.0f); // 200.0 Kg
		vel = dir * 40;
		setVelocity(vel); 
		setAcceleration({ 0.0f, -20.0f, 0.0f });
		setDamping(0.99f);
		break;
	case FIREBALL:
		setMass(1.0f); // 1.0 Kg
		vel = dir * 10;
		setVelocity(vel);
		setAcceleration({ 0.0f, 0.6f, 0.0f }); // floats
		setDamping(0.9f);
		break;
	case LASER:
		setMass(0.1f); // almost no weight
		vel = dir * 100;
		setVelocity(vel);
		setAcceleration({ 0.0f, 0.0f, 0.0f });
		setDamping(0.99f);
		break;
	}
	setParticle();
}

void Proyectile::setParticle() {
	physx::PxShape* forma;
	Vector4 color;
	switch (type)
	{
	case Proyectile::PISTOL:
		forma = CreateShape(physx::PxSphereGeometry(2));
		color = Vector4(0.5, 0, 1, 1);
		break;
	case Proyectile::ARTILLERY:
		forma = CreateShape(physx::PxSphereGeometry(4));
		color = Vector4(0.2, 0.2, 0.2, 1);
		break;
	case Proyectile::FIREBALL:
		forma = CreateShape(physx::PxSphereGeometry(3));
		color = Vector4(1, 0.4, 0, 1);
		break;
	case Proyectile::LASER:
		forma = CreateShape(physx::PxSphereGeometry(1));
		color = Vector4(1, 0, 0, 1);
		break;
	default:
		break;
	}
	renderItem = new RenderItem(forma, &pose, color);
	time = glutGet(GLUT_ELAPSED_TIME);
}