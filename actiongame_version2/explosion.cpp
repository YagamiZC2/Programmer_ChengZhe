#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "explosion.h"
#include "controller.h"
#include "enemy.h"
#include "sound.h"

static unsigned int g_Texture;

//弾の構造体
struct EXPLOSION
{
	bool Enable;
	Float2 Position;
	int count;
};

#define EXPLOSION_MAX 20

static EXPLOSION g_Explosion[EXPLOSION_MAX];

static int g_TimeCount[EXPLOSION_MAX];

void InitExplosion()
{
	g_Texture = LoadTexture("rom:/explosion.tga");//テクスチャを読み込み
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		g_Explosion[i].Enable = false;
		g_Explosion[i].Position.x = 0.0f;
		g_Explosion[i].Position.y = 0.0f;
	}
}
void UninitExplosion()
{
	UnloadTexture(g_Texture);
}
void UpdateExplosion()
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_Explosion[i].Enable == false)
			continue;
		
		//g_TimeCount[i]++;
		//if (g_TimeCount[i] == 30)
		//{
		//	g_Explosion[i].Enable = false;
		//	g_TimeCount[i] = 0;
		//}

		g_Explosion[i].count++;
		if (g_Explosion[i].count > 23) g_Explosion[i].Enable = false;
	
	}
}

void DrawExplosion()
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		float tw=1.0f / 5.0f;
		float th=1.0f / 4.0f;
		float u = 1.0f / 5.0f*(g_Explosion[i].count % 5);
		float v = 1.0f / 1.0f*(g_Explosion[i].count / 5);
		if (g_Explosion[i].Enable == true)
			DrawSpriteQuad(g_Explosion[i].Position.x, g_Explosion[i].Position.y, 400.0f, 400.0f, 
				1.f, 1.f, 1.f, 1.f, g_Texture, u, v, tw, th); //u,v 始点　tw,thは幅
	}
}

void CreatExplosion(float x, float y)
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_Explosion[i].Enable == false)
		{
			g_Explosion[i].Enable = true;
			g_Explosion[i].Position.x = x;
			g_Explosion[i].Position.y = y;
			g_Explosion[i].count = 0;
			break;
		}
	}
}