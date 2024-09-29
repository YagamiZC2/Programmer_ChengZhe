#include "stdafx.h"
#include "emitter.h"
#include "particle_square.h"
#include "particle_circle.h"
#include "particle_star.h"
#include "particle_heart.h"
#include <random>

emitter::emitter(int particle_max, int amount,
	Float2 position, Float2 max_acce, Float2 min_acce)
	:
	particle_count_max(particle_max),
	amount(amount),
	position(position),
	max_acceleration(max_acce),
	min_acceleration(min_acce)
{
	particles = new Particle * [particle_count_max];
	std::random_device rd;
	mt.seed(rd());//random
	
}

emitter::~emitter()
{
	for (int i = 0; i < particle_count; i++)
	{
		delete particles[i];
	}
	delete[] particles;
}

void emitter::Update()
{

	//寿命チェック
	for (int i = 0; i < particle_count; i++)
	{
		if (particles[i]->IsDead())
		{
			delete particles[i];
			particles[i] = nullptr;
			//--particle_count;
			particles[i] = particles[--particle_count];
		}
	}

	//更新
	for (int i = 0; i < particle_count; i++)
	{
		particles[i]->Update();
	}

	//生成
	for (int i = particle_count; i < particle_count + amount; i++)
	{
		particles[i]=spawnParticle();
	}
	particle_count += amount;

}

void emitter::Draw()
{

	const ScopedRenderStates2D blend{ BlendState::Additive };

	for (int i = 0; i < particle_count; i++)
	{
		particles[i]->Draw();
	}
}

void emitter::addForce(Float2 force)
{
	for (int i = 0; i < particle_count; i++)
	{
		particles[i]->AddForce(force);
	}
}

Particle* emitter::spawnParticle()
{
	//(0~2)
	std::uniform_int_distribution<> dist(0, 3);
	int n = dist(mt);

	//float(-.1~.1)
	std::uniform_real_distribution<> rdist(-1.0, 1.0);
	Float2 acceleration{rdist(mt), rdist(mt) };


	std::uniform_real_distribution<> cdist(0.1f, 0.9f);
	ColorF color{cdist(mt), cdist(mt) , cdist(mt) ,1.0f};

	std::uniform_int_distribution<> ldist(30, 60*3);
	int life = ldist(mt);

	switch (n)
	{
	case 0:
		return new ParticleSquare(position, acceleration, color, life);
		break;
	case 1:
		return new ParticleCircle(position, acceleration, color, life);
		break;
	case 2:
		return new ParticleStar(position, acceleration, color, life);
		break;
	case 3:
		return new ParticleHeart(position, acceleration, color, life);
		break;
	default:
		break;
	}

	return nullptr;
}
