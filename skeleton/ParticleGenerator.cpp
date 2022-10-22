#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator()
{
	_num_particles = 10;
}

ParticleGenerator::~ParticleGenerator()
{
}

void ParticleGenerator::setParticle(Particle* model)
{
}

GaussianParticleGenerator::GaussianParticleGenerator()
{
}

list<Particle*> GaussianParticleGenerator::generateParticles()
{
	list<Particle*> lista;

	//default_random_engine re;
	random_device re;
	mt19937 gen(re());


	normal_distribution<> posX(-100, 100);
	normal_distribution<> posY(200, 400);
	normal_distribution<> posZ(-300, 10);
						  			  
	normal_distribution<> velX(-10, 10);
	normal_distribution<> velY(-10, 10);
	normal_distribution<> velZ(-10, 10);

	Vector3 pos, vel;

	for (int i = 0; i < _num_particles; i++)
	{
		pos.x = posX(gen);
		pos.y = posY(gen);
		pos.z = posZ(gen);
		vel.x = velX(gen);
		vel.y = velY(gen);
		vel.z = velZ(gen);
																			
		Particle* particula = new Particle(pos, vel, { 0, -10, 0 }, 0.99f);	
		lista.push_back(particula);											
	}																		
																			
																			
	return lista;															
}																			
																			
UniformParticleGenerator::UniformParticleGenerator()						
{																			
}																			
																			
list<Particle*> UniformParticleGenerator::generateParticles()				
{																			
	list<Particle*> lista;													
																			
	random_device rd;														
	mt19937 gen(rd());														

	uniform_real_distribution<> posX(-1, 1);								
	uniform_real_distribution<> posY(-1, 1);								
	uniform_real_distribution<> posZ(-1, 1);								
																			
	uniform_real_distribution<> velX(-10, 10);								
	uniform_real_distribution<> velY(50, 100);								
	uniform_real_distribution<> velZ(-10, 10);

	Vector3 pos, vel;														
																			
	for (int i = 0; i < _num_particles; i++)								
	{																		
		pos.x = posX(gen);													
		pos.y = posY(gen);													
		pos.z = posZ(gen);													
		vel.x = velX(gen);
		vel.y = velY(gen);
		vel.z = velZ(gen);

		Particle* particula = new Particle(pos, vel, {0, -10, 0}, 0.99f);
		lista.push_back(particula);
	}


    return lista;
}
																		
list<Firework*> UniformParticleGenerator::generateParticles1()				
{																			
	list<Firework*> lista;													
																			
	random_device rd;														
	mt19937 gen(rd());														
																			
	uniform_real_distribution<> posX(-100, 100);								
	uniform_real_distribution<> posY(-100, 100);								
	uniform_real_distribution<> posZ(-100, 100);								
																			
	uniform_real_distribution<> velX(-10, 10);								
	uniform_real_distribution<> velY(50, 100);
	uniform_real_distribution<> velZ(-10, 10);	

	Vector3 pos, vel;														
																			
	for (int i = 0; i < _num_particles; i++)								
	{																		
		pos.x = posX(gen);													
		pos.y = posY(gen);													
		pos.z = posZ(gen);													
		vel.x = velX(gen);
		vel.y = velY(gen);
		vel.z = velZ(gen);

		Firework* particula = new Firework(pos, vel, {0, -10, 0}, 0.99f);
		lista.push_back(particula);
	}


    return lista;
}
