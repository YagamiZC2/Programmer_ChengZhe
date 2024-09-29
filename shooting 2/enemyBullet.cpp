#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "enemyBullet.h"
#include "controller.h"
#include "player.h"
#include "sound.h"
#include "explosion.h"

static unsigned int g_Texture;

//弾の構造体
struct ENEMY_BULLET
{
	bool Enable;
	Float2 Position;
	Float2 Velocity;
	int Life;
};

#define ENEMY_BULLET_MAX 50
//弾の構造体変数
static ENEMY_BULLET g_EnemyBullet[ENEMY_BULLET_MAX];

void InitEnemyBullet()
{
	g_Texture = LoadTexture("rom:/enemyBullet.tga");//テクスチャを読み込み
	for (int i = 0; i < ENEMY_BULLET_MAX; i++)
	{
		g_EnemyBullet[i].Enable = false;
		g_EnemyBullet[i].Position.x = SCREEN_WIDTH / 2 - i * 100;
		g_EnemyBullet[i].Position.y = 300.f;
		g_EnemyBullet[i].Life = 1;
	}
}
void UninitEnemyBullet()
{
	UnloadTexture(g_Texture);
}
void UpdateEnemyBullet()
{

	for (int i = 0; i < ENEMY_BULLET_MAX; i++)
	{
		if (g_EnemyBullet[i].Enable == false)
			continue;

			g_EnemyBullet[i].Position.x += g_EnemyBullet[i].Velocity.x;
			g_EnemyBullet[i].Position.y += g_EnemyBullet[i].Velocity.y;


		if (g_EnemyBullet[i].Position.x < -SCREEN_WIDTH / 2 - 50)
			g_EnemyBullet[i].Enable = false;
		if (g_EnemyBullet[i].Position.x > SCREEN_WIDTH / 2)
			g_EnemyBullet[i].Enable = false;
		if (g_EnemyBullet[i].Position.y < -SCREEN_HEIGHT / 2)
			g_EnemyBullet[i].Enable = false;
		if (g_EnemyBullet[i].Position.y > SCREEN_HEIGHT / 2)
			g_EnemyBullet[i].Enable = false;

		//敵の弾とプレイヤーの衝突判定
		PLAYER* player = GetPlayer();
		if (player->Enable == true)
		{
			float dx = player->Position.x - g_EnemyBullet[i].Position.x;
			float dy = player->Position.y - g_EnemyBullet[i].Position.y;

			if (dx * dx + dy * dy < 80.0f * 80.0f)
			{
				PlaySE(WSD_BULLET_HIT);
				player->Life--;
				g_EnemyBullet[i].Enable = false;
				if (player->Life == 0)
				{
					player->Enable = false;
					CreatExplosion(player->Position.x, player->Position.y);
					PlaySE(WSD_EXPLOSION);
				}
				break;
			}
		}
	}
}

void DrawEnemyBullet()
{
	for (int i = 0; i < ENEMY_BULLET_MAX; i++)
	{
		if (g_EnemyBullet[i].Enable == true)
			DrawSpriteQuad(g_EnemyBullet[i].Position.x, g_EnemyBullet[i].Position.y, 75.f, 75.f, 1.f, 1.f, 1.f, 1.f, g_Texture, 0.0f, 0.0f, 1.0f, 1.0f);
	}
}
void CreatEnemyBullet(float x, float y, float vx, float vy)
{
	for (int i = 0; i < ENEMY_BULLET_MAX; i++)
	{
		if (g_EnemyBullet[i].Enable == false)
		{
			g_EnemyBullet[i].Enable = true;
			g_EnemyBullet[i].Position.x = x;
			g_EnemyBullet[i].Position.y = y;
			g_EnemyBullet[i].Velocity.x = vx;
			g_EnemyBullet[i].Velocity.y = vy;
			g_EnemyBullet[i].Life = 1;
			break;
		}
	}
}