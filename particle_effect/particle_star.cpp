#include "stdafx.h"
#include "particle_star.h"

void ParticleStar::Draw()
{

	ColorF now = color;
	now.a = 1.0f - (float)GetAge() / GetLife();
	Shape2D::Star(8.0f, {GetPosition()},(float)now.a*120.0f).draw(now);
}
