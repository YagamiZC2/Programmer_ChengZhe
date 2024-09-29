#include "stdafx.h"
#include "particle_square.h"

void ParticleSquare::Draw()
{
	
	ColorF now = color;
	now.a = 1.0f - (float)GetAge() / GetLife();
	RectF{ Arg::center(GetPosition()),16.0f }.draw(now);
}
