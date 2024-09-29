#pragma once
//ìGÇÃç\ë¢ëÃ
struct BOSS
{
	int Type;
	bool Enable;
	Float2 Position;
	int HP;
	int TimeCount;
	Float2 Size;
};

typedef enum BOSS_STATE {
	BOSS_STATE_ENTRY,
	BOSS_STATE_FIRST,
	BOSS_STATE_SECOND,
	BOSS_STATE_END
};


void InitBoss();
void UninitBoss();
void UpdateBoss();
void DrawBoss();
void CreatBoss(int type, float x, float y, float sizeX, float sizeY);
void BossJudge(float pl, float pr, float pt, float pb, int oldjump);
BOSS* GetBoss();
#define BOSS_MAX 