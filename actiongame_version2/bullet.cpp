#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"
#include "controller.h"
#include "enemy.h"
#include "sound.h"
#include "explosion.h"
#include "score.h"
#include "buff.h"
#include "boss.h"
#include "player.h"
#include "camera.h"
#include "block.h"

static unsigned int g_Texture;
static 	CAMERA* camera = GetCamera();

//弾の構造体
struct BULLET
{
	bool Enable;
	Float2 Position;
	Float2 Velocity;
	//int bullet_level;
	int timecount;
	bool Left;
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
		g_Bullet[i].Position.x = 0.0f;
		g_Bullet[i].Position.y = 0.0f;
		g_Bullet[i].Velocity.x = 0.0f;
		g_Bullet[i].Velocity.y = 0.0f;
		g_Bullet[i].timecount = 0;
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

		g_Bullet[i].timecount++;
		if (g_Bullet[i].timecount >240 ) g_Bullet[i].Enable = false;

		g_Bullet[i].Position.x += g_Bullet[i].Velocity.x;
		g_Bullet[i].Position.y += g_Bullet[i].Velocity.y;

		////重力
		//g_Bullet[i].Velocity.y += 0.3f;

		//if (g_Bullet[i].Velocity.x < 0.1f && g_Bullet[i].Velocity.x > 0.0f) g_Bullet[i].Enable = false;
		//if (g_Bullet[i].Velocity.x < 0.0f && g_Bullet[i].Velocity.x > -0.1f) g_Bullet[i].Enable = false;
		//反射
		//if (g_Bullet[i].Position.x > SCREEN_WIDTH / 2 -50.0f) {
		//	g_Bullet[i].Position.x = SCREEN_WIDTH / 2 - 50.0f;
		//	g_Bullet[i].Velocity.x = -g_Bullet[i].Velocity.x * 0.9f;
		//}
		//if (g_Bullet[i].Position.x < -SCREEN_WIDTH / 2 + 50.0f) {
		//	g_Bullet[i].Position.x = -SCREEN_WIDTH / 2 + 50.0f;
		//	g_Bullet[i].Velocity.x = -g_Bullet[i].Velocity.x * 0.9f;
		//}
		//if (g_Bullet[i].Position.y < -SCREEN_HEIGHT / 2 - 50.0f) {
		//	g_Bullet[i].Velocity.y *= 0.9f;
		//	g_Bullet[i].Position.y = -SCREEN_HEIGHT / 2 + 50.0f;
		//	g_Bullet[i].Velocity.y = -g_Bullet[i].Velocity.y * 0.9f;
		//}
		//if (g_Bullet[i].Position.y > SCREEN_HEIGHT / 2 - 50.0f) {
		//	g_Bullet[i].Velocity.y *= 0.9f;
		//	g_Bullet[i].Position.y = SCREEN_HEIGHT / 2 - 50.0f;
		//	g_Bullet[i].Velocity.y = -g_Bullet[i].Velocity.y * 0.9f;
		//}

		//画面外判定
		//if (g_Bullet[i].Position.x > (SCREEN_WIDTH / 2 + 10 + camera->Position.x)
		//	|| g_Bullet[i].Position.x < (-SCREEN_WIDTH / 2 - camera->Position.x)
		//	|| g_Bullet[i].Position.y < (-SCREEN_HEIGHT / 2 - camera->Position.y)
		//	|| g_Bullet[i].Position.y > (SCREEN_HEIGHT / 2 + camera->Position.y)
		//	)
		//	g_Bullet[i].Enable = false;


		float bullet_l = g_Bullet[i].Position.x - 10.0f;		//Bulletの左
		float bullet_r = g_Bullet[i].Position.x + 10.0f;		//Bulletの右
		float bullet_t = g_Bullet[i].Position.y - 10.0f;		//Bulletの上
		float bullet_b = g_Bullet[i].Position.y + 10.0f;		//Bulletの下

		BLOCK* block = GetBlock();

		for (int i = 0; i < BLOCK_MAX; i++)
		{
			if (block[i].Enable == false) continue;

			float bl = block[i].Position.x - block[i].Size.x * 0.5f;		 //ブロックの左
			float br = block[i].Position.x + block[i].Size.x * 0.5f;		 //ブロックの右
			float bt = block[i].Position.y - block[i].Size.y * 0.5f;		 //ブロックの上
			float bb = block[i].Position.y + block[i].Size.y * 0.5f;		 //ブロックの下

			if (bl < bullet_r && bullet_l < br && bt < bullet_b && bullet_t < bb)
			{
				float dl = bl - bullet_r;			 //ブロック左とBulletの右判定
				float dr = br - bullet_l;			 //ブロック右とBulletの左判定
				float dt = bt - bullet_b;			 //ブロック上とBulletの下判定
				float db = bb - bullet_t;			 //ブロック下とBulletの上判定
				float dx, dy;						

				if (-dl < dr) {
					dx = dl;
				}
				else {
					dx = dr;
				}

				if (-dt < db) {
					dy = dt;
				}
				else {
					dy = db;
				}

				if (abs(dx) > abs(dy) || abs(dy) < 5.0f)
				{
					if (dy * g_Bullet[i].Velocity.y < 0.0f)
					{
						g_Bullet[i].Position.y += dy;
						g_Bullet[i].Velocity.y = -g_Bullet[i].Velocity.y * 0.9f;

					}
				}
				else
				{
					if (dx * g_Bullet[i].Velocity.x < 0.0f)
					{
						g_Bullet[i].Position.x += dx;
						g_Bullet[i].Velocity.x = -g_Bullet[i].Velocity.x * 0.9f;
					}
				}
			}
		}
	}
}

void DrawBullet()
{

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].Enable == true) {


			float tw = 1.0f;
			float th = 1.0f;
			float u = 0.0f;
			float v = 0.0f;

			if (g_Bullet[i].Left == true) {
				u += 100.0f;
				tw = -tw;
			}

			DrawSpriteQuad(
				g_Bullet[i].Position.x - camera->Position.x,
				g_Bullet[i].Position.y - camera->Position.y,
				100.f, 100.f,
				1.f, 1.f, 1.f, 1.f,
				g_Texture,
				u, v, tw, th);
		}

	}
}

void CreatBullet(float x, float y, float vx, float vy, bool left)
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
			g_Bullet[i].Left = left;
			g_Bullet[i].timecount = 0;
			break;
		}
	}
}