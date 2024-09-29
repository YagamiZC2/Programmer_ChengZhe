#include "stdafx.h"
#include "particle_heart.h"

void ParticleHeart::Draw()
{

	ColorF now = color;
	now.a = 1.0f - (float)GetAge() / GetLife();
	Shape2D::Heart(10.0f, { GetPosition() }).draw(now);
}
