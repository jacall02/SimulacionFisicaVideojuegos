#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 ac, double damping) : 
	vel(vel), ac(ac), damping(damping)
{
	pose = physx::PxTransform(pos.x, pos.y, pos.z);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(3)), &pose, Vector4(1, 0, 0, 1));
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	delete renderItem;
}

void Particle::integrate(double t)
{
	pose = physx::PxTransform(pose.p.x + vel.x * t, pose.p.y + vel.y * t, pose.p.z + vel.z * t);
	vel += ac * t;
	vel *= powf(damping, t);
}

Proyectile::Proyectile(ShotType currentShotType, Vector3 pos, Vector3 dir)
{
	switch (currentShotType)
	{
	case PISTOL:
		setMass(2.0f); // 2.0 Kg
		setVelocity(0.0f, 0.0f, 35.0f); // 35 m/s
		setAcceleration(0.0f, -1.0f, 0.0f);
		setDamping(0.99f);
		break;
	case ARTILLERY:
		setMass(200.0f); // 200.0 Kg
		setVelocity(0.0f, 30.0f, 40.0f);
		setAcceleration(0.0f, -20.0f, 0.0f);
		setDamping(0.99f);
		break;
	case FIREBALL:
		setMass(1.0f); // 1.0 Kg
		setVelocity(0.0f, 0.0f, 10.0f);
		setAcceleration(0.0f, 0.6f, 0.0f); // floats
		setDamping(0.9f);
		break;
	case LASER:
		setMass(0.1f); // almost no weight
		setVelocity(0.0f, 0.0f, 100.0f); // No gravity
		setAcceleration(0.0f, 0.0f, 0.0f);
		setDamping(0.99f);
		break;
	}

	setPosition(0.0f, 1.5f, 0.0f);
	/*shot->startTime = GetLastFrame();
	shot->type = currentShotType;*/
}
