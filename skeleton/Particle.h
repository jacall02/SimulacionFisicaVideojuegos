#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(Vector3 pos, Vector3 vel, Vector3 ac, double damp);
	~Particle();

	void integrate(double t);

private: 
	Vector3 vel;
	Vector3 ac;
	double damping;
	physx::PxTransform pose; //A render item le pasaremos la dirección de esta pose, para que se actualice automáticamente
	RenderItem* renderItem;
};

