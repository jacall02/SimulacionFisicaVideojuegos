#include "BuoyancyForceGenerator.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(float h, float v, float d) {

	_liquid_particle = new Cubo({ 0.0, h, 0.0}, 1000, 1, 1000, { 0.2, 0.4, 1.0, 1.0 });
	_height = h;
	_volume = v;
	_liquid_density = d;

}

void BuoyancyForceGenerator::updateForce(Particle* particle, double t)
{
	float h = particle->getPosition().p.y;
	float h0 = _liquid_particle->getPosition().p.y;

	Vector3 f(0.0);
	float inmersed = 0.0;
	if (h - h0 > _height * 0.5)
		inmersed = 0.0;
	else if (h0 - h > _height * 0.5)
		inmersed = 1.0;
	else
		inmersed = (h0 - h) / _height + 0.5;

	f.y = _liquid_density * _volume * inmersed * 9.8;

	particle->addForce(f);
}
