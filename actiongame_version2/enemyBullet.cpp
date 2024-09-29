#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "enemyBullet.h"
#include "controller.h"
#include "player.h"
#include "sound.h"
#include "explosion.h"
#include "camera.h"

static unsigned int g_Texture;

//弾の構造体
struct ENEMY_BULLET
{
	bool Enable;
	Float2 Position;
	Float2 Velocity;
	int Type;
	float Speed;
	int TimeCount;
};

#define ENEMY_BULLET_MAX 500
//弾の構造体変数
static ENEMY_BULLET g_EnemyBullet[ENEMY_BULLET_MAX];
static void update_type0(int index);
static void update_type1(int index);
static void update_type2(int index);
static void update_type3(int index);
static CAMERA* camera = GetCamera();

void InitEnemyBullet()
{
	g_Texture = LoadTexture("rom:/enemybullet.tga");//テクスチャを読み込み
	for (int i = 0; i < ENEMY_BULLET_MAX; i++)
	{
		g_EnemyBullet[i].Enable = false;
		g_EnemyBullet[i].Position.x = SCREEN_WIDTH / 2 - i * 100;
		g_EnemyBullet[i].Position.y = 300.f;
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

		switch (g_EnemyBullet[i].Type)
		{
		case 0:
			update_type0(i);
			break;
		case 1:
			update_type1(i);
			break;
		case 2:
			update_type2(i);
			break;
		case 3:
			update_type3(i);
			break;
		default:
			break;
		}

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

			if (dx * dx + dy * dy < 130.0f * 130.0f)
			{
				PlaySE(WSD_BULLET_HIT);
				player->Life++;
				g_EnemyBullet[i].Enable = false;
				break;
			}
		}
		if (player->Life == 0)
		{
			CreatExplosion(player->Position.x, player->Position.y);
			SetScene(SCENE_RESULT);
			PlaySE(WSD_EXPLOSION);
		}
	}
}

void DrawEnemyBullet()
{
	for (int i = 0; i < ENEMY_BULLET_MAX; i++)
	{
		if (g_EnemyBullet[i].Enable == true)
			DrawSpriteQuad(
				g_EnemyBullet[i].Position.x - camera->Position.x,
				g_EnemyBullet[i].Position.y - camera->Position.y,
				75.f, 75.f, 1.f, 1.f, 1.f, 1.f,
				g_Texture,
				0.0f, 0.0f, 1.0f, 1.0f);
	}
}
void CreatEnemyBullet(int Type, float x, float y, float vx, float vy)
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

			break;
		}
	}
}

void update_type0(int index) {
	g_EnemyBullet[index].Position.x += g_EnemyBullet[index].Velocity.x;
	g_EnemyBullet[index].Position.y += g_EnemyBullet[index].Velocity.y;
}

void update_type1(int index) {
	PLAYER* player = GetPlayer();
	if (player->Enable && g_EnemyBullet[index].TimeCount <= 60)
	{
		float x = player->Position.x - g_EnemyBullet[index].Position.x;
		float y = player->Position.y - g_EnemyBullet[index].Position.y;

		float l = sqrtf(x*x + y * y);

		x /= l;
		y /= l;

		g_EnemyBullet[index].Velocity.x -= x * g_EnemyBullet[index].Speed;
		g_EnemyBullet[index].Velocity.y -= y * g_EnemyBullet[index].Speed;
	}

	update_type0(index);
}

void update_type2(int index) {

	PLAYER* player = GetPlayer();
	if (player->Enable)
	{
		float x = player->Position.x - g_EnemyBullet[index].Position.x;
		float y = player->Position.y - g_EnemyBullet[index].Position.y;

		float old_angle = atan2(g_EnemyBullet[index].Velocity.x, g_EnemyBullet[index].Velocity.y);

		float angle = atan2f(y, x);//float type

		//差分
		float diff = angle - old_angle;

		//sign
		float sign = diff < 0 ? -1 : 1;


		//max angle
		float max_angle = 3.14159f / 180.0f * 5.0f;

		if (abs(diff) > max_angle)
		{
			angle = old_angle + max_angle;
		}

		g_EnemyBullet[index].Velocity.x -= sinf(angle) * g_EnemyBullet[index].Speed;
		g_EnemyBullet[index].Velocity.y -= cosf(angle) * g_EnemyBullet[index].Speed;
	}

	update_type0(index);
}

void update_type3(int index) {

	int n = 16;
	float pi = 3.14159f;
	float sh = pi * 2 / n;


	if (g_EnemyBullet[index].TimeCount > 30)
	{
		for (int i = 0; i < n; i++)
		{
			float vx = sin(sh * i) * 10.0f;
			float vy = cos(sh * i) * 10.0f;

			CreatEnemyBullet(0, g_EnemyBullet[index].Position.x,
				g_EnemyBullet[index].Position.y, vx, vy);//正方向弾
		}
		g_EnemyBullet[index].Enable = false;
	}

	update_type0(index);
}