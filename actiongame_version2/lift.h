#pragma once
//ìGÇÃç\ë¢ëÃ
struct LIFT
{
	int Type;
	bool Enable;
	Float2 Position;
	Float2 Velocity;
	int Life;
	int TimeCount;
	Float2 Size;
	Float2 Center;
	Float2 Radius;
	Float2 OldPosition;//1204
	float Speed;
};

void InitLift();
void UninitLift();
void UpdateLift();
void DrawLift();
void CreatLift(int type, float x, float y, float sizeX, float sizeY, float radiusX, float radiusY, float speed);
void LiftJudge(float pl, float pr, float pt, float pb, int oldjump);


LIFT* GetLift();
#define LIFT_MAX 100
