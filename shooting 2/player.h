#pragma once
struct PLAYER
{
	bool Enable;
	Float2 Position;
	int Life;
};

void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();
PLAYER* GetPlayer();