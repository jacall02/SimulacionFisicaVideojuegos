#pragma once

#include "Particle.h"
#include <list>
#include <random>
#include "RBParticle.h";

using namespace physx;


class ForceGenerator {
protected:
	bool isActive_ = true;
public:
	virtual void updateForce(Particle* particle, double duration) = 0;
	virtual void updateForce(RBParticle* rigido, double duration) = 0;
	std::string _name;
	double t = -1e10;

	void setActive(bool active) { isActive_ = active; };
	bool getActive() { return isActive_; };
};

