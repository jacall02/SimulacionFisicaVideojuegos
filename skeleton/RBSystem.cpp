#include "RBSystem.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringForceGenerator.h"
#include "BungeeForceGenerator.h"
#include "BuoyancyForceGenerator.h"

RBSystem::RBSystem(PxScene* scene, PxPhysics* gPhysics) : scene_(scene), gPhysics_(gPhysics)
{
}

void RBSystem::update(double t)
{

}

PxRigidDynamic* RBSystem::GenerateSolid(Vector3 pos, Vector3 vel, Vector3 acc,
	int life, float inverse_mass, float size, Vector4 color)
{
	PxRigidDynamic* rigido = gPhysics_->createRigidDynamic(PxTransform(pos));
	rigido->setLinearVelocity(vel);
	rigido->setAngularVelocity({ 1.0,0.0,0.0 });
	PxShape* shape = CreateShape(PxBoxGeometry(size / 2.0, size / 2.0, size / 2.0));
	rigido->attachShape(*shape);
	Vector3 inertia = { size.y * size.y + size.z * size.z,
						size.y * size.y + size.z * size.z,
						size.y * size.y + size.z * size.z };

}

list<PxRigidDynamic*> RBSystem::uniformGenerator(Vector3 pos, Vector3 offPos,
	Vector3 vel, Vector3 offVel, Vector3 acc, int num,
	int life, float inverse_mass, float size, Vector4 color, double propability)
{
	list<PxRigidDynamic*> lista;

	random_device rd;
	mt19937 gen(rd());

	uniform_real_distribution<> posX(pos.x - offPos.x, pos.x + offPos.x);
	uniform_real_distribution<> posY(pos.y - offPos.y, pos.y + offPos.y);
	uniform_real_distribution<> posZ(pos.z - offPos.z, pos.z + offPos.z);

	uniform_real_distribution<> velX(vel.x - offVel.x, vel.x + offVel.x);
	uniform_real_distribution<> velY(vel.y - offVel.y, vel.y + offVel.y);
	uniform_real_distribution<> velZ(vel.z - offVel.z, vel.z + offVel.z);

	Vector3 newPos, newVel;

	for (int i = 0; i < num; i++)
	{
		if (((rand() % 100) < propability))
		{
			newPos.x = posX(gen);
			newPos.y = posY(gen);
			newPos.z = posZ(gen);
			newVel.x = velX(gen);
			newVel.y = velY(gen);
			newVel.z = velZ(gen);

			PxRigidDynamic* rigido = GenerateSolid(newPos, newVel, acc, life, inverse_mass, size, color);
			lista.push_back(rigido);
		}
	}


	return lista;
}
