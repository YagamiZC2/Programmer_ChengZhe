#include "main.h"
#include "texture.h"
#include "sprite.h"
#include <time.h>
#include "sound.h"
#include "block.h"
#include "camera.h"
#include "player.h"
#include "controller.h"

static unsigned int g_Texture1;
static unsigned int g_Texture2;

//敵の構造体変数
static BLOCK g_Block[BLOCK_MAX];

BLOCK* GetBlock()
{
	return g_Block;
}


void InitBlock()
{
	g_Texture1 = LoadTexture("rom:/floor.tga");//テクスチャを読み込み
	g_Texture2 = LoadTexture("rom:/block.tga");
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		g_Block[i].Enable = false;
		g_Block[i].Position.x = 0.0f;
		g_Block[i].Position.y = 0.0f;
		g_Block[i].Life = 1;
		g_Block[i].Size.x = 100.0f;
		g_Block[i].Size.y = 100.0f;
	}
	
}

void UninitBlock()
{
	UnloadTexture(g_Texture2);
	UnloadTexture(g_Texture1);//テクスチャの解放

}

void UpdateBlock()
{

}

void DrawBlock()
{
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_Block[i].Enable == true) {

			CAMERA* camera = GetCamera();
			switch (g_Block[i].Type)
			{
			case 0:
				DrawSpriteQuad(
					g_Block[i].Position.x - camera->Position.x,
					g_Block[i].Position.y - camera->Position.y,
					g_Block[i].Size.x,
					g_Block[i].Size.y,
					1.f, 1.f, 1.f, 1.f,
					g_Texture1,
					0.0f, 0.0f, 1.0f, 1.0f);
				break;
			case 1:
				DrawSpriteQuad(
					g_Block[i].Position.x - camera->Position.x,
					g_Block[i].Position.y - camera->Position.y,
					g_Block[i].Size.x,
					g_Block[i].Size.y,
					1.f, 1.f, 1.f, 1.f,
					g_Texture2,
					0.0f, 0.0f, 1.0f, 1.0f);
			default:
				break;
			}
		}
	}
}

void CreatBlock(int type, float x, float y, float sizeX, float sizeY)
{
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_Block[i].Enable == false)
		{
			g_Block[i].Enable = true;
			g_Block[i].Position.x = x;
			g_Block[i].Position.y = y;
			g_Block[i].Size.x = sizeX;
			g_Block[i].Size.y = sizeY;
			g_Block[i].Life = 1;
			g_Block[i].TimeCount = 0;
			g_Block[i].Type = type;
			break;
		}
	}
}

void BlockJudge(float pl, float pr, float pt, float pb, int oldjump) {
	PLAYER* player = GetPlayer();
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_Block[i].Enable == false) continue;

		float bl = g_Block[i].Position.x - g_Block[i].Size.x * 0.5f;
		float br = g_Block[i].Position.x + g_Block[i].Size.x * 0.5f;
		float bt = g_Block[i].Position.y - g_Block[i].Size.y * 0.5f;
		float bb = g_Block[i].Position.y + g_Block[i].Size.y * 0.5f;

		if (bl < pr && pl < br && bt < pb && pt < bb)
		{
			float dl = bl - pr;
			float dr = br - pl;
			float dt = bt - pb;
			float db = bb - pt;
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

					if (dy < 0.0f) {
						//着地landing
						player->Jump = false;

						if (oldjump) {
							//キャラ潰すchara shrink
							player->Scale.x = 1.5f;
							player->Scale.y = 0.5f;
						}
					}

					if (dx < 0.0f && player->Jump) {		//壁左タッチ判定
						player->Jump = false;
					}


					if (dx < 0.0f&& player->Jump) {		//壁右タッチ判定
						player->Jump = false;			
					}
				}
			}
			else
			{
				/*player->Jump = true;*/
				if (dx * player->Velocity.x < 0.0f)
				{
					player->Position.x += dx;
					player->Velocity.x = 0.0f;
				}
			}

		}
	}
}