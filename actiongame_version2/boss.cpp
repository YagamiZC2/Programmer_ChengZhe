#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "enemy.h"
#include "enemyBullet.h"
#include <time.h>
#include "sound.h"
#include "boss.h"
#include "explosion.h"
#include "camera.h"
#include "player.h"
#include <stdlib.h>

static unsigned int g_Texture;


//敵の構造体変数
static BOSS g_Boss;
static BOSS_STATE g_state = BOSS_STATE_ENTRY;
static int g_TimeCount;
static CAMERA* camera = GetCamera();
static PLAYER* player = GetPlayer();

static void update_entry(void);
static void update_first(void);
static void update_second(void);
static void update_end(void);



BOSS* GetBoss()
{
	return &g_Boss;
}


void InitBoss()
{
	g_Texture = LoadTexture("rom:/boss2.tga");//テクスチャを読み込み


	g_Boss.Enable = false;
	g_Boss.Position.x = 0.0f;
	g_Boss.Position.y = 0.0f;
	g_Boss.HP = 5;
	g_Boss.TimeCount = 0;
	g_state = BOSS_STATE_ENTRY;
	g_TimeCount = 0;
	
}

void UninitBoss()
{
	UnloadTexture(g_Texture);//テクスチャの解放

}

void UpdateBoss()
{
	switch (g_state)
	{
	case BOSS_STATE_ENTRY:
		CreatBoss(0, 800.0f, 0.0f, 594.f, 512.f);
		update_entry();
		break;
	case BOSS_STATE_FIRST:
		update_first();
		break;
	case BOSS_STATE_SECOND:
		update_second();
		break;
	case BOSS_STATE_END:
		update_end();
		break;
	default:
		break;
	}
	g_TimeCount++;
	g_Boss.TimeCount++;
			
}

void DrawBoss()
{
	if (g_Boss.Enable == true) {
		DrawSpriteQuad(
			g_Boss.Position.x - camera->Position.x,
			g_Boss.Position.y - camera->Position.y,
			g_Boss.Size.x,			//size of x y
			g_Boss.Size.y,
			1.f, 1.f, 1.f, 1.f,
			g_Texture,
			0.0f, 0.0f, 1.0f, 1.0f);//vector
	}
}

void CreatBoss(int type, float x, float y, float sizeX, float sizeY)
{

	if (g_Boss.Enable == false)
	{
		g_Boss.Type = type;
		g_Boss.Enable = true;
		g_Boss.Position.x = x;
		g_Boss.Position.y = y;
		g_Boss.Size.x = sizeX;
		g_Boss.Size.y = sizeY;
		g_Boss.HP = 5;
		g_Boss.TimeCount = 0;
	}
	
}

void update_entry(void) {				//boss 登場
	g_Boss.Position.x -= 1.0f;

	if (g_Boss.Position.x < 600) {
		g_state = BOSS_STATE_FIRST;
	}
}

void update_first(void) {				//第一段階
	float pi = 3.14159f;

	float angle = pi/6 * sin(0.05f * g_Boss.TimeCount);

	float vx = sinf(angle - pi*0.5f) * 5.0f;
	float vy = cosf(angle - pi*0.5f) * 5.0f;

	if (g_Boss.TimeCount % 15 == 0 && g_Boss.Enable == true)
	{
		CreatEnemyBullet(
			3,						//タイプ
			g_Boss.Position.x,		//
			g_Boss.Position.y,		//
			vx, vy);				//方向

		PlaySE(WSD_BULLET_SHOOT);
	}

	if (g_Boss.TimeCount >= 60 * 5) g_state = BOSS_STATE_SECOND;	//300frame後第二段階入る

}

void update_second(void) {

	if (g_Boss.TimeCount % 60 == 0 && g_Boss.Enable == true)
	{
		CreatEnemyBullet(
			2,							//タイプ
			g_Boss.Position.x,			//
			g_Boss.Position.y,			//
			-10.0f, 0.0f);				//方向

		PlaySE(WSD_BULLET_SHOOT);
	}

	//if (g_Boss.Life <= 0) g_state = BOSS_STATE_END;
}

void update_end(void) {
	g_Boss.Enable = false;
	SetScene(SCENE_RESULT);
}

void BossJudge(float pl, float pr, float pt, float pb, int oldjump) {


		if (g_Boss.Enable == false) return;

		float bossl = g_Boss.Position.x - g_Boss.Size.x * 0.5f;
		float bossr = g_Boss.Position.x + g_Boss.Size.x * 0.5f;
		float bosst = g_Boss.Position.y - g_Boss.Size.y * 0.5f;
		float bossb = g_Boss.Position.y + g_Boss.Size.y * 0.5f;

		if (bossl < pr && pl < bossr && bosst < pb && pt < bossb)
		{
			float dl = bossl - pr;
			float dr = bossr - pl;
			float dt = bosst - pb;
			float db = bossb - pt;
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
				if (dy * player->Velocity.y < 0.0f)
				{
					player->Position.y += dy;
					player->Velocity.y = 0.0f;

					if (dy < 0.0f) player->Jump = false;
					if (dy < 0.0f)
					{

						//サウンド
						PlaySE(WSD_BULLET_HIT);

						//Player移動
						player->Velocity.y = -20.0f;

						//attack hitstop
						HitStopPlayer(5);

						//カメラ振動
						ShakeCamera(30.0f);

						if (oldjump) {
							//キャラ潰すchara shrink
							player->Scale.x = 1.5f;
							player->Scale.y = 0.5f;
						}

						//life minus
						g_Boss.HP--;

						srand(time(NULL));
						int random_x = rand() % 700 + -200;

						g_Boss.Position.x += random_x;

						if (g_Boss.HP <= 0) {

							g_Boss.Enable = false;

							//エフェクト
							CreatExplosion(
								g_Boss.Position.x - camera->Position.x,
								g_Boss.Position.y - camera->Position.y);

							g_state = BOSS_STATE_END;
							
						}

					}

				}

			}
			else
			{
				if (dx * player->Velocity.x < 0.0f)
				{
					player->Position.x += dx;
					player->Velocity.x = 0.0f;
				}
			}
		}


}