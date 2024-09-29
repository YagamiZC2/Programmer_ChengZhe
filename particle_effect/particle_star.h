#ifndef PARTICLE_STAR_H
#define PARTICLE_STAR_H

#include "particle.h"


class ParticleStar :public Particle
{
public:
	ParticleStar(Float2 start_postion, Float2 acce, ColorF color, int life)
		:Particle(start_postion, acce, life), color(color)
	{
	}
	~ParticleStar() {}

private:
	ColorF color;

public:
	void Draw() override;

};



#endif PARTICLE_STAR_H
