#include "RigidBodyGenerator.h"
#include "RBParticle.h"



RigidBodyGenerator::RigidBodyGenerator() {

}

RigidBodyGenerator::~RigidBodyGenerator() {

}

RBParticle* RigidBodyGenerator::GenerateSolid(Vector3 pos, Vector3 vel, Vector3 acc,
	int life, float inverse_mass, Vector3 size, Vector4 color)
{
	RBParticle* rigido = new RBCubo(pos, vel, acc, 0.95, life, inverse_mass, size, color, gPhysics_, scene_);
	return rigido;
}
RBParticle* RigidBodyGenerator::GenerateSolidSphere(Vector3 pos, Vector3 vel, Vector3 acc,
	int life, float inverse_mass, Vector3 size, Vector4 color)
{
	RBParticle* rigido = new RBParticle(pos, vel, acc, 0.95, life, inverse_mass, size, color, gPhysics_, scene_);
	return rigido;
}
RBParticle* RigidBodyGenerator::GenerateStatic(Vector3 pos, Vector3 vel, Vector3 acc,
	int life, float inverse_mass, Vector3 size, Vector4 color)
{
	RBParticle* rigido = new RBStatic(pos, vel, acc, 0.95, life, inverse_mass, size, color, gPhysics_, scene_);
	return rigido;
}

UniformRigidGenerator::UniformRigidGenerator(Vector3 pos, Vector3 offPos,
	Vector3 vel, Vector3 offVel, Vector3 acc, int num,
	int life, float inverse_mass, Vector3 size, Vector4 color, double propability, PxPhysics* gPhysics, PxScene* scene, bool cuadrado)
{
	pos_ = pos;
	offPos_ = offPos;
	vel_ = vel;
	offVel_ = offVel;
	acc_ = acc;
	_num_particles = num;
	life_ = life;
	inverse_mass_ = inverse_mass;
	size_ = size;
	color_ = color;
	_generation_probability = propability;
	active_ = false;
	gPhysics_ = gPhysics;
	scene_ = scene;
	cuadrado_ = cuadrado;
}



list<RBParticle*> UniformRigidGenerator::uniformGenerator()
{
	list<RBParticle*> lista;

	random_device rd;
	mt19937 gen(rd());

	uniform_real_distribution<> posX(pos_.x - offPos_.x, pos_.x + offPos_.x);
	uniform_real_distribution<> posY(pos_.y - offPos_.y, pos_.y + offPos_.y);
	uniform_real_distribution<> posZ(pos_.z - offPos_.z, pos_.z + offPos_.z);

	uniform_real_distribution<>velX(vel_.x - offVel_.x, vel_.x + offVel_.x);
	uniform_real_distribution<> velY(vel_.y - offVel_.y, vel_.y + offVel_.y);
	uniform_real_distribution<> velZ(vel_.z - offVel_.z, vel_.z + offVel_.z);

	Vector3 newPos, newVel;

	for (int i = 0; i < _num_particles; i++)
	{
		if (((rand() % 100) < _generation_probability))
		{
			newPos.x = posX(gen);
			newPos.y = posY(gen);
			newPos.z = posZ(gen);
			newVel.x = velX(gen);
			newVel.y = velY(gen);
			newVel.z = velZ(gen);


			RBParticle* rigido;
			if(cuadrado_)
				rigido = GenerateSolid(newPos, newVel, acc_, life_, inverse_mass_, size_, color_);
			else
				rigido = GenerateSolidSphere(newPos, newVel, acc_, life_, inverse_mass_, size_, color_);

			lista.push_back(rigido);
		}
	}


	return lista;
}

list<RBParticle*> UniformRigidGenerator::staticGenerator()
{
	list<RBParticle*> lista;

	for (int i = 0; i < _num_particles; i++)
	{
		if (((rand() % 100) < _generation_probability))
		{
			RBParticle* rigido;
			rigido = GenerateStatic(pos_, vel_, acc_, life_, inverse_mass_, size_, color_);
			
			lista.push_back(rigido);
		}
	}


	return lista;
}