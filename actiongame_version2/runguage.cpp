#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "controller.h"
#include "bullet.h"
#include "player.h"
#include "sound.h"
#include "runguage.h"

static unsigned int g_Texture;

static RUNGUAGE g_RunGuage;

RUNGUAGE* GetRunGuage()
{
	return &g_RunGuage;
}

void InitRunGuage()
{
	g_Texture = LoadTexture("rom:/gauge.tga");//�e�N�X�`����ǂݍ���


	g_RunGuage.Enable = true;
	g_RunGuage.Position.x = 600.0f;
	g_RunGuage.Position.y = -400.0f;
	g_RunGuage.runspeed = 150;
	g_RunGuage.count = 0;

}

void UninitRunGuage()
{
	UnloadTexture(g_Texture);//�e�N�X�`���̉��
}

void UpdateRunGuage()
{
	if (g_RunGuage.Enable == false)
		return;
}

void DrawRunGuage()
{


	if (g_RunGuage.Enable == false)return;

	double count = g_RunGuage.count;  //���݂̃X�^�~�i
	double maxG = g_RunGuage.runspeed;  //max�X�^�~�i
	double ratio;
	ratio = ((maxG - count) / maxG * 100);  //�c��X�^�~�i���S�X�^�~�i�̊���
	int x_cor;

	if (ratio == 100) {
		x_cor = 0;
	}
	if (ratio == 0) {
		x_cor = 4;
	}
	if (ratio < 100 && ratio >=66)
	{
		x_cor = 1;
	}
	if (ratio < 66 && ratio >= 33)
	{
		x_cor = 2;
	}
	if (ratio < 33 && ratio > 0)
	{
		x_cor = 3;
	}


	float tw = 1.0f / 5.0f;
	float th = 1.0f / 1.0f;
	float u = 1.0f / 5.0f * x_cor;
	float v = 0.0f;


	DrawSpriteQuad(
		g_RunGuage.Position.x,
		g_RunGuage.Position.y,
		250.0f, 50.0f,
		1.f, 1.f, 1.f, 1.f,
		g_Texture,
		u, v, tw, th); //u,v �n�_�@tw,th�͕�
	
}

void addRunGuage(int RunCount, int runspeed) // runspeed�͑���鎞�Ԃ̏��
{
	g_RunGuage.count += RunCount;
	g_RunGuage.runspeed = runspeed;
}
