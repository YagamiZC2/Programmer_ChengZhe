#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"
#include "controller.h"
#include "enemy.h"
#include "sound.h"
#include "explosion.h"
#include "player.h"

static unsigned int g_Texture;

//弾の構造体
struct BULLET
{
	bool Enable;
	Float2 Position;
	Float2 Velocity;
	int bullet_level;
	int Life;
};

#define BULLET_MAX 200
//弾の構造体変数
static BULLET g_Bullet[BULLET_MAX];

void InitBullet()
{
	g_Texture = LoadTexture("rom:/bullet.tga");//テクスチャを読み込み
	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].Enable = false;
		g_Bullet[i].Position.x = SCREEN_WIDTH / 2 - i * 100;
		g_Bullet[i].Position.y = 300.f;
		g_Bullet[i].Life = 1;
	}
}
void UninitBullet()
{
	UnloadTexture(g_Texture);
}
void UpdateBullet()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].Enable == false)
			continue;
		g_Bullet[i].Position.x += g_Bullet[i].Velocity.x;
		g_Bullet[i].Position.y += g_Bullet[i].Velocity.y;
		g_Bullet[i].Position.y += 1.0f;

		//反射
		if (g_Bullet[i].Position.x > SCREEN_WIDTH / 2 + 10) {
			g_Bullet[i].Velocity.y = -g_Bullet[i].Velocity.y;
			g_Bullet[i].Velocity.y = SCREEN_WIDTH / 2 + 10;
			g_Bullet[i].Position.x *= 0.98f;
			g_Bullet[i].Position.y *= 0.98f;
		}
		if (g_Bullet[i].Position.x < -SCREEN_WIDTH / 2) {
			g_Bullet[i].Position.x = -g_Bullet[i].Position.x;
			g_Bullet[i].Position.x = -SCREEN_WIDTH / 2;
			g_Bullet[i].Position.x *= 0.98f;
			g_Bullet[i].Position.y *= 0.98f;
		}
		if (g_Bullet[i].Position.y > -SCREEN_HEIGHT / 2) {
			g_Bullet[i].Velocity.y = -g_Bullet[i].Velocity.y;
			g_Bullet[i].Velocity.y = -SCREEN_HEIGHT / 2;
			g_Bullet[i].Position.x *= 0.98f;
			g_Bullet[i].Position.y *= 0.98f;
		}
		if (g_Bullet[i].Position.y > SCREEN_HEIGHT / 2) {
			g_Bullet[i].Velocity.y = -g_Bullet[i].Velocity.y;
			g_Bullet[i].Velocity.y = SCREEN_HEIGHT / 2;
			g_Bullet[i].Position.x *= 0.98f;
			g_Bullet[i].Position.y *= 0.98f;
		}

		//画面外判定
		if (g_Bullet[i].Position.x > SCREEN_WIDTH / 2 + 10
			|| g_Bullet[i].Position.x < -SCREEN_WIDTH / 2
			|| g_Bullet[i].Position.y < -SCREEN_HEIGHT / 2
			|| g_Bullet[i].Position.y > SCREEN_HEIGHT / 2
			)
			g_Bullet[i].Enable = false;

		//敵との衝突判定
		ENEMY* enemy = GetEnemy();
		PLAYER* player = GetPlayer();
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			if (enemy[j].Enable == false)
				continue;

			if (g_Bullet[i].Enable == false) continue;
			if (i == j) continue;

			float dx = g_Bullet[i].Position.x - g_Bullet[j].Position.x;
			float dy = g_Bullet[i].Position.y - g_Bullet[j].Position.y;

			if (dx * dx + dy * dy < 150.0f * 150.0f)
			{
				float tempx = g_Bullet[i].Velocity.x;
				float tempy = g_Bullet[i].Velocity.x;

				g_Bullet[i].Velocity.x = g_Bullet[j].Velocity.x;
				g_Bullet[i].Velocity.y = g_Bullet[i].Velocity.y;
				g_Bullet[i].Velocity.x = tempx;
				g_Bullet[i].Velocity.x = tempy;
				break;
			}
		}
	}
}

void DrawBullet()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].Enable == true)
			DrawSpriteQuad(g_Bullet[i].Position.x, g_Bullet[i].Position.y,
				100.f, 100.f, 1.f, 1.f, 1.f, 1.f, g_Texture,
				0.0f, 0.0f, 1.0f, 1.0f);
	}//powered up bullets neet set up
}

void CreatBullet(float x, float y, float vx, float vy)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].Enable == false)
		{
			g_Bullet[i].Enable = true;
			g_Bullet[i].Position.x = x;
			g_Bullet[i].Position.y = y;
			g_Bullet[i].Velocity.x = vx;
			g_Bullet[i].Velocity.y = vy;
			//g_Bullet[i].bullet_level = level;
			g_Bullet[i].Life = 1;
			break;
		}
	}
}