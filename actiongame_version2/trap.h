#pragma once
//ìGÇÃç\ë¢ëÃ
struct TRAP
{
	int Type;
	int count;
	bool Enable;
	Float2 Position;
	Float2 Size;
};

void InitTrap();
void UninitTrap();
void UpdateTrap();
void DrawTrap();
void CreatTrap(int type, float x, float y, float sizeX, float sizeY);
void TrapJudge(float pl, float pr, float pt, float pb, int runspeed);


TRAP* GetTrap();
#define TRAP_MAX 1000
