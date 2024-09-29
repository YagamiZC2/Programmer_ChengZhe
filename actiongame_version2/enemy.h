#pragma once
//ìGÇÃç\ë¢ëÃ
struct ENEMY
{
	int Type;
	int count;
	int HitstopTimeCount;
	int HP;
	bool Enable;
	bool Left;
	bool Active;
	Float2 Position;
	Float2 Size;
	Float2 Velocity;

};

void InitEnemy();
void UninitEnemy();
void UpdateEnemy();
void DrawEnemy();
void CreatEnemy(int type, float x, float y, float sizeX, float sizeY);
void HitStopEnemy(int TimeCount);
void EnemyJudge(float pl, float pr, float pt, float pb, int oldjump);


ENEMY* GetEnemy();
#define ENEMY_MAX 100