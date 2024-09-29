#ifndef PARTICLE_SQUARE_H
#define PARTICLE_SQUARE_H

#include "particle.h"


class ParticleSquare :public Particle
{
public:
	ParticleSquare(Float2 start_postion, Float2 acce, ColorF color, int life)
		:Particle(start_postion, acce, life), color(color)
	{
	}
	~ParticleSquare() {}

private:
	ColorF color;

public:
	void Draw() override;

};



#endif PARTICLE_SQUARE_H
