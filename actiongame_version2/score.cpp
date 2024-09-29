#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "controller.h"
#include "bullet.h"
#include "player.h"
#include "sound.h"
#include "score.h"

static unsigned int g_Texture;

static SCORE g_Score;

SCORE* GetScore()
{
	return &g_Score;
}

void InitScore()
{
	g_Texture = LoadTexture("rom:/number.tga");//テクスチャを読み込み

	
	g_Score.Enable = true;
	g_Score.Position.x = -600.0f;
	g_Score.Position.y = -400.0f;
	g_Score.count = 0;
	
}

void UninitScore()
{
	UnloadTexture(g_Texture);//テクスチャの解放
}

void UpdateScore()
{
	if (g_Score.Enable == false)
		return;
	
	/*if(g_Score.count<0) SetScene(SCENE_RESULT);*/
	//これはまだ使える、後で戻す
	
}

void DrawScore()
{
	if (g_Score.Enable == false)
		return;
	int count = g_Score.count;


	for (int i = 0; i < 5; i++)
	{
		int num = count % 10;
		count /= 10;
	
		float tw = 1.0f / 5.0f;
		float th = 1.0f / 5.0f;
		float u = 1.0f / 5.0f*(num % 5);
		float v = 1.0f / 5.0f*(num / 5);
		DrawSpriteQuad(
			g_Score.Position.x-40.0f*i,
			g_Score.Position.y,
			70.0f, 70.0f,
			1.f, 1.f, 1.f, 1.f,
			g_Texture,
			u, v, tw, th); //u,v 始点　tw,thは幅
	}
}

void addScore(int Count) 
{
	g_Score.count += Count;
}