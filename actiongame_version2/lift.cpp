#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "sound.h"
#include "camera.h"
#include "lift.h"
#include "player.h"

static unsigned int g_Texture1;
static unsigned int g_Texture2;
//敵の構造体変数
static LIFT g_Lift[LIFT_MAX];
static int g_TimeCount;


LIFT* GetLift()
{
	return g_Lift;
}


void InitLift()
{
	g_Texture1 = LoadTexture("rom:/block.tga");//テクスチャを読み込み

	for (int i = 0; i < LIFT_MAX; i++)
	{
		g_Lift[i].Enable = false;
	}
	g_TimeCount = 0;
}

void UninitLift()
{
	UnloadTexture(g_Texture2);
	UnloadTexture(g_Texture1);//テクスチャの解放

}

void UpdateLift()
{
	
	for (int i = 0; i < LIFT_MAX; i++)
	{
		g_Lift[i].TimeCount++;

		if (g_Lift[i].Enable == true) {
			
			g_Lift[i].OldPosition = g_Lift[i].Position; // 04/12

			g_Lift[i].Position.x = g_Lift[i].Center.x + cosf(g_Lift[i].TimeCount * g_Lift[i].Speed) * g_Lift[i].Radius.x;

			switch (g_Lift[i].Type)
			{
			case 0:
				g_Lift[i].Velocity.y = g_Lift[i].Center.y + sinf(g_Lift[i].TimeCount * g_Lift[i].Speed) * g_Lift[i].Radius.y;
				break;
			case 1:
				g_Lift[i].Velocity.y = g_Lift[i].Center.y + cosf(g_Lift[i].TimeCount * g_Lift[i].Speed) * g_Lift[i].Radius.y;
				break;

			}
			
			g_Lift[i].Position.x += g_Lift[i].Velocity.x * 0.01;
			g_Lift[i].Position.y += g_Lift[i].Velocity.y * 0.01;
		}

		
	}
}

void DrawLift()
{

	CAMERA* camera = GetCamera();

	for (int i = 0; i < LIFT_MAX; i++)
	{
		if (g_Lift[i].Enable == true) {

			CAMERA* camera = GetCamera();
			switch (g_Lift[i].Type)
			{
			case 0:
				DrawSpriteQuad(
					g_Lift[i].Position.x - camera->Position.x,
					g_Lift[i].Position.y - camera->Position.y,
					g_Lift[i].Size.x,
					g_Lift[i].Size.y,
					1.f, 1.f, 1.f, 1.f,
					g_Texture1,
					0.0f, 0.0f, 1.0f, 1.0f);
				break;
			case 1:
				DrawSpriteQuad(
					g_Lift[i].Position.x - camera->Position.x,
					g_Lift[i].Position.y - camera->Position.y,
					g_Lift[i].Size.x,
					g_Lift[i].Size.y,
					1.f, 1.f, 1.f, 1.f,
					g_Texture1,
					0.0f, 0.0f, 1.0f, 1.0f);
			default:
				break;
			}
		}
	}
}

void CreatLift(int type, float x, float y, float sizeX, float sizeY, float radiusX, float radiusY, float speed)
{
	for (int i = 0; i < LIFT_MAX; i++)
	{
		if (g_Lift[i].Enable == false)
		{
			g_Lift[i].Enable = true;
			g_Lift[i].Position.x = x;
			g_Lift[i].Position.y = y;
			g_Lift[i].Velocity.x = 0.0f;
			g_Lift[i].Velocity.y = 0.0f;
			g_Lift[i].Size.x = sizeX;
			g_Lift[i].Size.y = sizeY;
			g_Lift[i].Life = 1;
			g_Lift[i].TimeCount = 0;
			g_Lift[i].Type = type;
			g_Lift[i].Center.x = x;
			g_Lift[i].Center.y = y;
			g_Lift[i].Radius.x = radiusX;
			g_Lift[i].Radius.y = radiusY;
			g_Lift[i].OldPosition.x = x;
			g_Lift[i].OldPosition.y = y;
			g_Lift[i].TimeCount = 0;
			g_Lift[i].Speed = speed;
			break;
		}
	}
}

void LiftJudge(float pl, float pr, float pt, float pb, int oldjump) {
	PLAYER* player = GetPlayer();
	for (int i = 0; i < LIFT_MAX; i++)
	{
		if (player->Life == 0 || g_Lift[i].Enable == false)
			continue;

		float ll = g_Lift[i].Position.x - g_Lift[i].Size.x * 0.5f;
		float lr = g_Lift[i].Position.x + g_Lift[i].Size.x * 0.5f;
		float lt = g_Lift[i].Position.y - g_Lift[i].Size.y * 0.5f;
		float lb = g_Lift[i].Position.y + g_Lift[i].Size.y * 0.5f;

		if (ll < pr && pl < lr && lt < pb && pt < lb)
		{
			float dl = ll - pr;
			float dr = lr - pl;
			float dt = lt - pb;
			float db = lb - pt;
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
			if (abs(dx) > abs(dy) || abs(dy) < 5.0f) {
				if (dy * player->Velocity.y < 0.0f)
				{
					player->Position.y += dy;
					player->Velocity.y = 0.0f;
					if (dy < 0.0f) {
						player->Jump = false;
						//Liftに付けて移動
						player->Position.x +=
							g_Lift[i].Position.x - g_Lift[i].OldPosition.x;
						player->Position.y +=
							g_Lift[i].Position.y - g_Lift[i].OldPosition.y;

						if (oldjump) {
							//キャラ潰すchara shrink
							player->Scale.x = 1.5f;
							player->Scale.y = 0.5f;
						}
					}
				}
			}
			else {
				if (dx * player->Velocity.x < 0.0f)
				{
					player->Position.x += dx;
					player->Velocity.x = 0.0f;
				}
			}
		}
	}
}
