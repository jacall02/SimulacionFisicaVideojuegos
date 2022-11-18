#pragma once

#include "Particle.h"
#include <list>
#include <random>

class ForceGenerator {
protected:
	bool isActive_ = true;
public:
	virtual void updateForce(Particle* particle, double duration) = 0;
	std::string _name;
	double t = -1e10;

	void setActive(bool active) { isActive_ = active; };
	bool getActive() { return isActive_; };
};

