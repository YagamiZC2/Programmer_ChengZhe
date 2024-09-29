#pragma once
//ìGÇÃç\ë¢ëÃ
struct ITEM
{
	int Type;
	bool Enable;
	Float2 Position;
	Float2 Size;
};

void InitItem();
void UninitItem();
void UpdateItem();
void DrawItem();
void CreatItem(int type, float x, float y, float sizeX, float sizeY);
void ItemJudge(float pl, float pr, float pt, float pb, int runspeed);


ITEM* GetItem();
#define ITEM_MAX 100
