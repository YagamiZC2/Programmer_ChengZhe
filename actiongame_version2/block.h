#pragma once
//ìGÇÃç\ë¢ëÃ
struct BLOCK
{
	int Type;
	bool Enable;
	Float2 Position;
	int Life;
	int TimeCount;
	Float2 Size;
};

void InitBlock();
void UninitBlock();
void UpdateBlock();
void DrawBlock();
void CreatBlock(int type, float x , float y, float sizeX, float sizeY);
void BlockJudge(float pl, float pr, float pt, float pb, int oldjump);

BLOCK* GetBlock();
#define BLOCK_MAX 500
