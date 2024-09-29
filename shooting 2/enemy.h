#pragma once
//ìGÇÃç\ë¢ëÃ
struct ENEMY
{
	int Type;
	bool Enable;
	Float2 Position;
	int Life;
	int TimeCount;

};

void InitEnemy();
void UninitEnemy();
void UpdateEnemy();
void DrawEnemy();
void CreatEnemy(int, float, float);
ENEMY* GetEnemy();
#define ENEMY_MAX 20