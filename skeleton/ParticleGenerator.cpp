#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator()
{

}

ParticleGenerator::~ParticleGenerator()
{
}

void ParticleGenerator::setParticle(Particle* model)
{
}

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 pos, Vector3 offPos,
	Vector3 vel, Vector3 offVel, Vector3 acc, int num, Particle::ParticleType type, double propability) {
	
	pos_ = pos;
	offPos_ = offPos;
	vel_ = vel;
	offVel_ = offVel;
	acc_ = acc;
	_num_particles = num;
	type_ = type;
	_generation_probability = propability;
} 

list<Particle*> GaussianParticleGenerator::generateParticles()
{
	list<Particle*> lista;

	//default_random_engine re;
	random_device re;
	mt19937 gen(re());


	normal_distribution<> posX(pos_.x - offPos_.x, pos_.x + offPos_.x);
	normal_distribution<> posY(pos_.y - offPos_.y, pos_.y + offPos_.y);
	normal_distribution<> posZ(pos_.z - offPos_.z, pos_.z + offPos_.z);
						  							
	normal_distribution<> velX(vel_.x - offVel_.x, vel_.x + offVel_.x);
	normal_distribution<> velY(vel_.y - offVel_.y, vel_.y + offVel_.y);
	normal_distribution<> velZ(vel_.z - offVel_.z, vel_.z + offVel_.z);

	Vector3 pos, vel;

	for (int i = 0; i < _num_particles; i++)
	{
		if(((rand() % 100) < _generation_probability))
		{
			pos.x = posX(gen);
			pos.y = posY(gen);
			pos.z = posZ(gen);
			vel.x = velX(gen);
			vel.y = velY(gen);
			vel.z = velZ(gen);
																			
			Particle* particula = new Particle(pos, vel, acc_, 0.99f, type_);	
			lista.push_back(particula);											
		}
	}																		
																			
																			
	return lista;															
}																																						
																			
UniformParticleGenerator::UniformParticleGenerator(Vector3 pos, Vector3 offPos,
	Vector3 vel, Vector3 offVel, Vector3 acc, int num, Particle::ParticleType type, double propability)
{
	pos_ = pos;
	offPos_ = offPos;
	vel_ = vel;
	offVel_ = offVel;
	acc_ = acc;
	_num_particles = num;
	type_ = type;
	_generation_probability = propability;
}

list<Particle*> UniformParticleGenerator::generateParticles()
{																			
	list<Particle*> lista;													
																			
	random_device rd;														
	mt19937 gen(rd());														

	uniform_real_distribution<> posX(pos_.x - offPos_.x, pos_.x + offPos_.x);
	uniform_real_distribution<> posY(pos_.y - offPos_.y, pos_.y + offPos_.y);
	uniform_real_distribution<> posZ(pos_.z - offPos_.z, pos_.z + offPos_.z);
																				
	uniform_real_distribution<> velX(vel_.x - offVel_.x, vel_.x + offVel_.x);								
	uniform_real_distribution<> velY(vel_.y - offVel_.y, vel_.y + offVel_.y);								
	uniform_real_distribution<> velZ(vel_.z - offVel_.z, vel_.z + offVel_.z);

	Vector3 pos, vel;														
																			
	for (int i = 0; i < _num_particles; i++)
	{
		if (((rand() % 100) < _generation_probability))
		{
			pos.x = posX(gen);
			pos.y = posY(gen);
			pos.z = posZ(gen);
			vel.x = velX(gen);
			vel.y = velY(gen);
			vel.z = velZ(gen);

			Particle* particula = new Particle(pos, vel, acc_, 0.99f, type_);
			lista.push_back(particula);
		}
	}


    return lista;
}
																		
list<Firework*> UniformFireworkGenerator::generateFireworks()				
{																			
	list<Firework*> lista;													
																			
	random_device rd;
	mt19937 gen(rd());

	uniform_real_distribution<> posX(pos_.x - offPos_.x, pos_.x + offPos_.x);
	uniform_real_distribution<> posY(pos_.y - offPos_.y, pos_.y + offPos_.y);
	uniform_real_distribution<> posZ(pos_.z - offPos_.z, pos_.z + offPos_.z);

	uniform_real_distribution<> velX(vel_.x - offVel_.x, vel_.x + offVel_.x);
	uniform_real_distribution<> velY(vel_.y - offVel_.y, vel_.y + offVel_.y);
	uniform_real_distribution<> velZ(vel_.z - offVel_.z, vel_.z + offVel_.z);

	Vector3 pos, vel;
																			
	for (int i = 0; i < _num_particles; i++)								
	{																		
		pos.x = posX(gen);													
		pos.y = posY(gen);													
		pos.z = posZ(gen);													
		vel.x = velX(gen);
		vel.y = velY(gen);
		vel.z = velZ(gen);

		Firework* particula = new Firework(pos, vel, acc_, 0.99f);
		lista.push_back(particula);
	}


    return lista;
}
