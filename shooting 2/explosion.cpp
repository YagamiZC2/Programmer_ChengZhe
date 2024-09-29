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
	int Count;
	bool Enable;
	Float2 Position;
};

#define EXPLOSION_MAX 20

static EXPLOSION g_Explosion[EXPLOSION_MAX];


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
		g_Explosion[i].Count++;
		if (g_Explosion[i].Count > 15)
		{
			g_Explosion[i].Enable = false;
		}
	
	}
}

void DrawExplosion()
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		float tw = 1.0f / 8.0f;
		float th = 1.0f / 2.0f;
		float u = 1.0f / 8.0f * (g_Explosion[i].Count % 8);
		float v = 1.0f / 2.0f * (g_Explosion[i].Count / 8);
		if (g_Explosion[i].Enable == true)
			DrawSpriteQuad(g_Explosion[i].Position.x, g_Explosion[i].Position.y, 200.0f, 200.0f, 1.f, 1.f, 1.f, 1.f, g_Texture, u, v, tw, th);
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
			g_Explosion[i].Count = 0;
			break;
		}
	}
}