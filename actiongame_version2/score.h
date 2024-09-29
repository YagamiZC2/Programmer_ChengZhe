#pragma once

struct SCORE
{
	bool Enable;
	Float2 Position;
	int count;
};

void InitScore();
void UninitScore();
void UpdateScore();
void DrawScore();
void addScore(int Count);
SCORE* GetScore();