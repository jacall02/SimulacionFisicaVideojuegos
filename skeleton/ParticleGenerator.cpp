#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator()
{

}

ParticleGenerator::~ParticleGenerator()
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
	active_ = false;
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
	active_ = false;
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

CircleParticleGenerator::CircleParticleGenerator(Vector3 pos, Vector3 vel, int num, Firework* model)
{
	pos_ = pos;
	vel_ = vel;
	_num_particles = num;
	model_ = model;
	active_ = true;
}

list<Particle*> CircleParticleGenerator::generateParticles()
{
	return list<Particle*>();
}

list<Firework*> CircleParticleGenerator::generateFireworks()
{
	list<Firework*> lista;

	float angle = 0;
	for (int i = 0; i < _num_particles; i++)
	{
		angle += ((360 / _num_particles) + (((rand() % 30))));

		Vector3 vel = Vector3(cos(angle * (_Pi / 180)), sin(angle * (_Pi / 180)), 0);

		Firework* particle = model_->clone();
		particle->setPosition(pos_);
		particle->setVelocity(vel.getNormalized() * ((rand() % 20) + 20));

		if (reps_ > 0) {
			auto sistema = new CircleParticleGenerator(pos_, vel_, ((rand() % 5) + 5), particle);
			sistema->reps_ = reps_ - 1;
			particle->_gens.emplace_back(sistema);
		}

		lista.push_back(particle);
	}

	return lista;
}

void CircleParticleGenerator::setParticle(Firework* model)
{
	model_ = model;
}
