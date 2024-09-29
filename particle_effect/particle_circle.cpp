#include "stdafx.h"
#include "particle_circle.h"

void ParticleCircle::Draw()
{

	ColorF now = color;
	now.a = 1.0f - (float)GetAge() / GetLife();
	Circle{GetPosition(),8.0f }.draw(now);
}
