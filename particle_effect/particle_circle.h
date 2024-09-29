#ifndef PARTICLE_CIRCLE_H
#define PARTICLE_CIRCLE_H

#include "particle.h"


class ParticleCircle :public Particle
{
public:
	ParticleCircle(Float2 start_postion, Float2 acce, ColorF color, int life)
		:Particle(start_postion, acce, life), color(color)
	{
	}
	~ParticleCircle() {}

private:
	ColorF color;

public:
	void Draw() override;

};



#endif PARTICLE_CIRCLE_H
