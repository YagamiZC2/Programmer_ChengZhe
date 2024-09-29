#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "buff.h"
#include "controller.h"
#include "player.h"
#include "sound.h"
#include "buff.h"
#include "score.h"

static unsigned int g_Texture;

//弾の構造体
struct BUFF
{
	bool Enable;
	Float2 Position;
	int type;
};

#define BUFF_MAX 50
//弾の構造体変数
static BUFF g_Buff[BUFF_MAX];

void InitBuff()
{
	g_Texture = LoadTexture("rom:/buff.tga");//テクスチャを読み込み

	for (int i = 0; i < BUFF_MAX; i++)
	{
		g_Buff[i].Enable = false;
		g_Buff[i].Position.x = 0.0f;
		g_Buff[i].Position.y = 0.0f;
		g_Buff[i].type = 0;
	}
}

void UninitBuff()
{
	UnloadTexture(g_Texture);
}

void UpdateBuff()
{

	for (int i = 0; i < BUFF_MAX; i++)
	{
		if (g_Buff[i].Enable == false)
			continue;

		switch (g_Buff[i].type)
		{
		case 0:
			g_Buff[i].Position.x -= 10.0f;		//タイプ0のバフ移動する
			break;
		case 1:
			g_Buff[i].Position.x -= 0.0f;		//タイプ１のバフ移動しない

			break;
		}
		
		if (g_Buff[i].Position.x < -SCREEN_WIDTH / 2 - 50)		//画面外判定
			g_Buff[i].Enable = false;							//画面外判定
		if (g_Buff[i].Position.x > SCREEN_WIDTH / 2)			//画面外判定
			g_Buff[i].Enable = false;							//画面外判定
		if (g_Buff[i].Position.y < -SCREEN_HEIGHT / 2)			//画面外判定
			g_Buff[i].Enable = false;							//画面外判定
		if (g_Buff[i].Position.y > SCREEN_HEIGHT / 2)			//画面外判定
			g_Buff[i].Enable = false;							//画面外判定
	}

}

void DrawBuff()
{
	for (int i = 0; i < BUFF_MAX; i++)
	{
		if (g_Buff[i].Enable == true)
			DrawSpriteQuad(
				g_Buff[i].Position.x,					//
				g_Buff[i].Position.y,					//
				75.f, 75.f,								//
				1.f, 1.f, 1.f, 1.f,						//
				g_Texture,								//
				0.0f, 0.0f, 1.0f, 1.0f);				//
	}
}
void CreatBuff(float x, float y, int type)
{
	for (int i = 0; i < BUFF_MAX; i++)
	{
		if (g_Buff[i].Enable == false)
		{
			g_Buff[i].Enable = true;
			g_Buff[i].Position.x = x;
			g_Buff[i].Position.y = y;
			g_Buff[i].type = type;
			break;
		}
	}
}