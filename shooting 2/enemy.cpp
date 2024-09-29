#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "enemy.h"
#include "enemyBullet.h"
#include <time.h>
#include "sound.h"

static unsigned int g_Texture[2];

//敵の構造体変数
static ENEMY g_Enemy[ENEMY_MAX];

static int g_TimeCount;

ENEMY* GetEnemy()
{
	return g_Enemy;
}


void InitEnemy()
{
	g_Texture[0] = LoadTexture("rom:/enemy.tga");//テクスチャを読み込み
	g_Texture[1] = LoadTexture("rom:/enemy2.tga");
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_Enemy[i].Enable = false;
		g_Enemy[i].Position.x = SCREEN_WIDTH / 2 - i * 100;
		g_Enemy[i].Position.y = 300.f;
		g_Enemy[i].Life = 1;
	}
	g_TimeCount = 0;
	
}

void UninitEnemy()
{
	UnloadTexture(g_Texture[0]);//テクスチャの解放
	UnloadTexture(g_Texture[1]);
}

void UpdateEnemy()
{
	srand((unsigned int)time(NULL));
	g_TimeCount++;

	switch (g_TimeCount)
	{
	case 120:
		CreatEnemy(rand() % 2, 1160.0f, 300.0f);
		CreatEnemy(rand() % 2, 1060.0f, 250.0f);
		CreatEnemy(rand() % 2, 960.0f, 200.0f);
		break;
	case 360:
		CreatEnemy(rand() % 2, 960.0f, 200.0f);
		CreatEnemy(rand() % 2, 1060.0f, 150.0f);
		CreatEnemy(rand() % 2, 1160.0f, 100.0f);
		break;
	case 600:
		CreatEnemy(rand() % 2, 960.0f, 50.0f);
		CreatEnemy(rand() % 2, 1060.0f, 50.0f);
		CreatEnemy(rand() % 2, 1160.0f, 50.0f);
		break;
	case 720:
		g_TimeCount = 0;
		break;
	}

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].Enable == true)
		{
			g_Enemy[i].TimeCount++;
			switch (g_Enemy[i].Type)
			{
			case 0:
				g_Enemy[i].Position.x -= 7.f;

				if (g_Enemy[i].TimeCount % 30 == 0)
				{
					CreatEnemyBullet(g_Enemy[i].Position.x, g_Enemy[i].Position.y, -15.0f, -5.0f);
					PlaySE(WSD_BULLET_SHOOT);
				}
				break;
			case 1:
				g_Enemy[i].Position.x -= 5.f;

				if (g_Enemy[i].TimeCount % 60 == 0)
				{
					CreatEnemyBullet(g_Enemy[i].Position.x, g_Enemy[i].Position.y, -15.0f, 0.0f);
					PlaySE(WSD_BULLET_SHOOT);
				}
				break;
			default:
				break;

			}
		}
		if (g_Enemy[i].Position.x < -SCREEN_WIDTH / 2 - 50)
			g_Enemy[i].Enable = false;

	}
	
}

void DrawEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		switch (g_Enemy[i].Type)
		{
		case 0:
			if (g_Enemy[i].Enable == true)
				DrawSpriteQuad(g_Enemy[i].Position.x, g_Enemy[i].Position.y, 150.f, 150.f, 1.f, 1.f, 1.f, 1.f, g_Texture[1], 0.0f, 0.0f, 1.0f, 1.0f);
			break;
		case 1:
			if (g_Enemy[i].Enable == true)
				DrawSpriteQuad(g_Enemy[i].Position.x, g_Enemy[i].Position.y, 150.f, 150.f, 1.f, 1.f, 1.f, 1.f, g_Texture[0], 0.0f, 0.0f, 1.0f, 1.0f);
			break;
		}

	}
}

void CreatEnemy(int Type, float x, float y)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].Enable == false)
		{
			g_Enemy[i].Type = Type;
			g_Enemy[i].Enable = true;
			g_Enemy[i].Position.x = x;
			g_Enemy[i].Position.y = y;
			g_Enemy[i].Life = 1;
			g_Enemy[i].TimeCount = 0;
			break;
		}
	}
}