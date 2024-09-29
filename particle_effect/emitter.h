#ifndef EMITTER_H
#define EMITTER_H
#include "particle.h"
#include <random>


class emitter
{

private:
	
	Float2 position;
	int particle_count_max;
	int particle_count=0; //particle数

	int amount;//1 frame内particle何個排出する
	Float2 max_acceleration;
	Float2 min_acceleration;

	Particle** particles;

	//random
	std::mt19937 mt;

public:
	emitter(int particle_max, int amount, Float2 position, Float2 max_acce, Float2 min_acce);
	~emitter();

	void Update();
	void Draw();
	void addForce(Float2 force);

	void SetPosition(Float2 position)
	{
		emitter::position = position;
	}

private:
	Particle* spawnParticle();
};
#endif // !EMITTER_H



