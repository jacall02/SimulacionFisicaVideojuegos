#pragma once

#include <map>
#include "ForceGenerator.h"

typedef std::pair<ForceGenerator*, Particle*> FRPair;

class ParticleForceRegistry : public std::multimap<ForceGenerator*, Particle*>
{
public:
	void updateForces(double duration) {
		for (auto it = begin(); it != end(); it++) {
			if(it->first->getActive())
				it->first->updateForce(it->second, duration);
		}
	}

	void addRegistry(ForceGenerator* fg, Particle* p) {
		insert({ fg, p });
	}


	void deleteParticleRegistry(Particle* p) {
		for (auto it = begin(); it != end(); ) {
			if (it->second == p) {
				it = erase(it);
			}
			else it++;
		}
	}
};

class RigidForceRegistry : public std::multimap<ForceGenerator*, PxRigidDynamic*>
{
public:
	void updateForces(double duration) {
		for (auto it = begin(); it != end(); it++) {
			if(it->first->getActive())
				it->first->updateForce(it->second, duration);
		}
	}

	void addRegistry(ForceGenerator* fg, PxRigidDynamic* p) {
		insert({ fg, p });
	}


	void deleteParticleRegistry(PxRigidDynamic* p) {
		for (auto it = begin(); it != end(); ) {
			if (it->second == p) {
				it = erase(it);
			}
			else it++;
		}
	}
};

