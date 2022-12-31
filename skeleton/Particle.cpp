#include "Particle.h"
#include "ParticleGenerator.h"

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 ac, double damping, int life, float inverse_mass, float size, Vector4 color) :
	vel_(vel), acc_(ac), damping_(damping), life_(life), inverse_mass_(inverse_mass), size_(size), color_(color)
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
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(size_)), &pose, color_);
}

void Particle::integrate(double t)
{
	if (inverse_mass_ <= 0.0f) return;

	Vector3 totalAcceleration = acc_;
	totalAcceleration += force_ * inverse_mass_;

	vel_ += totalAcceleration * t;

	vel_ *= powf(damping_, t);

	pose = physx::PxTransform(pose.p.x + vel_.x * t, pose.p.y + vel_.y * t, pose.p.z + vel_.z * t);


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
		Vector4(color_.x, color_.y, color_.z, 1));
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


Cubo::Cubo(Vector3 pos, Vector3 vel, Vector3 ac, double damping, int life, float inverse_mass, float size, Vector4 color)
{
	vel_ = vel;
	acc_ = ac;
	damping_ = damping;
	life_ = life;
	inverse_mass_ = inverse_mass;
	hX_ = size;
	hY_ = size;
	hZ_ = size;
	color_ = color;

	pose = physx::PxTransform(pos.x, pos.y, pos.z);
	force_ = Vector3(0, 0, 0);
	setParticle();
}

Cubo::Cubo(Vector3 pos, float hX, float hY, float hZ, Vector4 color)
{
	vel_ = Vector3(0);
	acc_ = Vector3(0);
	damping_ = 0;
	life_ = 10000;
	inverse_mass_ = 0;
	hX_ = hX;
	hY_ = hY;
	hZ_ = hZ;
	color_ = color;

	pose = physx::PxTransform(pos.x, pos.y, pos.z);
	force_ = Vector3(0, 0, 0);
	setParticle();
}
Cubo::Cubo(Vector3 pos, float hX, float hY, float hZ, Vector4 color, float inverse_mass)
{
	vel_ = Vector3(0);
	acc_ = Vector3(0);
	damping_ = 0.9;
	life_ = 10000;
	inverse_mass_ = inverse_mass_;
	hX_ = hX;
	hY_ = hY;
	hZ_ = hZ;
	color_ = color;

	pose = physx::PxTransform(pos.x, pos.y, pos.z);
	force_ = Vector3(0, 0, 0);
	setParticle();
}

void Cubo::setParticle() {
	renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(hX_, hY_, hZ_)), &pose, color_);
}



ExplosiveFirework::ExplosiveFirework(Vector3 pos, Vector3 vel, Vector3 ac, double damp, float time, Vector4 color, float inverse_mass)
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
