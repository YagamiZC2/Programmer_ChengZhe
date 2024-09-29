#ifndef PARTICLE_HEART_H
#define PARTICLE_HEART_H

#include "particle.h"


class ParticleHeart :public Particle
{
public:
	ParticleHeart(Float2 start_postion, Float2 acce, ColorF color, int life)
		:Particle(start_postion, acce, life), color(color)
	{
	}
	~ParticleHeart() {}

private:
	ColorF color;

public:
	void Draw() override;

};



#endif PARTICLE_HEART_H
