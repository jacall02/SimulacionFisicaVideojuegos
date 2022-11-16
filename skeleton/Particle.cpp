#include "Particle.h"
#include "ParticleGenerator.h"

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 ac, double damping, ParticleType type, int life, float inverse_mass) :
	vel_(vel), acc_(ac), damping_(damping), type_(type), life_(life), inverse_mass_(inverse_mass)
{
	pose = physx::PxTransform(pos.x, pos.y, pos.z);
	force_ = Vector3(0, 0, 0);
	setParticle();
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::setParticle() {
	switch (type_)
	{
	case Particle::WATER:
		renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(2)), &pose, Vector4(0, 0, 0.6, 1));
		break;
	case Particle::MIST:
		renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1)), &pose, Vector4(0.7, 0.7, 0.7, 0.3));
		break;
	case Particle::FIRE:
		renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(3)), &pose, Vector4(1, 0.2, 0.2, 1));
		break;
	default:
		break;
	}
}

void Particle::integrate(double t)
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

void Particle::clearForce()
{
	force_ *= 0;
}

void Particle::addForce(const Vector3& f)
{
	force_ += f;
}

Proyectile::Proyectile(ShotType currentShotType, Vector3 pos, Vector3 dir)
{
	type = currentShotType;
	setPosition(pos);
	auto vel = getVelocity();
	switch (currentShotType)
	{
	case PISTOL:
		setInverseMass(2.0f); // 2.0 Kg
		vel = dir * 35;
		setVelocity(vel);
		setAcceleration({ 0.0f, -1.0f, 0.0f });
		setDamping(0.99f);
		break;
	case ARTILLERY:
		setInverseMass(200.0f); // 200.0 Kg
		vel = dir * 40;
		setVelocity(vel); 
		setAcceleration({ 0.0f, -20.0f, 0.0f });
		setDamping(0.99f);
		break;
	case FIREBALL:
		setInverseMass(1.0f); // 1.0 Kg
		vel = dir * 10;
		setVelocity(vel);
		setAcceleration({ 0.0f, 0.6f, 0.0f }); // floats
		setDamping(0.9f);
		break;
	case LASER:
		setInverseMass(0.1f); // almost no weight
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
}

Firework::Firework(Vector3 pos, Vector3 vel, Vector3 ac, double damp, float time, Vector4 color, float inverse_mass) 
{
	vel_ = vel;
	acc_ = ac;
	damping_ = damp;
	life_ = time;
	pose = physx::PxTransform(pos.x, pos.y, pos.z);
	color_ = color;
	inverse_mass_ = inverse_mass;
	force_ = Vector3(0, 0, 0);

	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(0.5)), &pose, color_);
}

Firework* Firework::clone()
{
	return new Firework(pose.p, vel_, Vector3(0, 0, 0), damping_,
		(rand() % 3 - ((rand() % 20) / 10)),
		Vector4(color_.z, color_.x, color_.y, 1));
}

list<Firework*> Firework::explode()
{
	list<Firework*> lista;

	for (auto gen : _gens) {
		gen->setPos(pose.p);

		auto listaAux = gen->generateFireworks();

		lista.insert(lista.end(), listaAux.begin(), listaAux.end());
	}

	return lista;
}
