#pragma once

struct RUNGUAGE
{
	bool Enable;
	Float2 Position;
	int count;
	int runspeed;
};

void InitRunGuage();
void UninitRunGuage();
void UpdateRunGuage();
void DrawRunGuage();
void addRunGuage(int,int);
RUNGUAGE* GetRunGuage();