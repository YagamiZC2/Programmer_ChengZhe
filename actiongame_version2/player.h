#pragma once
struct PLAYER
{
	Float2 Scale;
	Float2 Position;
	Float2 Velocity;
	Float2 Spawn;

	int Life;
	int buff;
	int status;
	int count;
	int runCount;
	int HitstopTimeCount;
	int MissTimeCount;

	bool Enable;
	bool Left;
	bool Run;
	bool Jump;
	bool Hurt;

};

void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();
PLAYER* GetPlayer();

void HitStopPlayer(int TimeCount);
void MissPlayer();