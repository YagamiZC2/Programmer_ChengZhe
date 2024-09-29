#include "main.h"
#include "texture.h"
#include "sprite.h"
#include <time.h>
#include "sound.h"
#include "block.h"
#include "camera.h"
#include "player.h"
#include "score.h"
#include "trap.h"


static unsigned int g_Texture1;
static unsigned int g_Texture2;

//敵の構造体変数
static TRAP g_Trap[TRAP_MAX];

TRAP* GetTrap()
{
	return g_Trap;
}
static PLAYER* player = GetPlayer();
static CAMERA* camera = GetCamera();

void InitTrap()
{
	g_Texture1 = LoadTexture("rom:/trap.tga");//テクスチャを読み込み
	g_Texture2 = LoadTexture("rom:/punch_trap.tga");

	for (int i = 0; i < TRAP_MAX; i++)
	{
		g_Trap[i].Enable = false;
		g_Trap[i].Position.x = 0.0f;
		g_Trap[i].Position.y = 0.0f;
		g_Trap[i].Size.x = 100.0f;
		g_Trap[i].Size.y = 100.0f;
		g_Trap[i].count = 0;
	}



}

void UninitTrap()
{

	UnloadTexture(g_Texture1);//テクスチャの解放

}

void UpdateTrap()
{
	for (int i = 0; i < TRAP_MAX; i++)
	{
		if (g_Trap[i].Enable == false)
			continue;

		g_Trap[i].count++;
		switch (g_Trap[i].Type)
		{
		case 0:

			break;
		case 1:

			if (g_Trap[i].count > 16) g_Trap[i].count = 0;
			break;
		default:
			break;
		}
		

		//	}
		//}
	}
}

void DrawTrap()
{
	for (int i = 0; i < TRAP_MAX; i++)
	{
		
		if (g_Trap[i].Enable == true) {

			for (int i = 0; i < TRAP_MAX; i++)
			{
				if (g_Trap[i].Enable == true) {

					CAMERA* camera = GetCamera();
					float tw, th, u, v;
					int g_Texture;
					switch (g_Trap[i].Type)
					{//start of switch
					case 0:
						tw = 1.0f;
						th = 1.0f;
						u = 0.0f;
						v = 0.0f;
						g_Texture = g_Texture1;
						break;
					case 1:
						tw = 1.0f / 16.0f;
						th = 1.0f;
						u = 1.0f / 16.0f*(g_Trap[i].count % 16); //4は何フレームごとき一回画像切り替える
						v = 0.0f;
						g_Texture = g_Texture2;
						break;
					default:
						break;
					}//end of switch

					DrawSpriteQuad(
						g_Trap[i].Position.x - camera->Position.x,
						g_Trap[i].Position.y - camera->Position.y,
						g_Trap[i].Size.x,
						g_Trap[i].Size.y,
						1.f, 1.f, 1.f, 1.f,
						g_Texture,
						u, v, tw, th);
				}
			}
		}
	}
}

void CreatTrap(int type, float x, float y, float sizeX, float sizeY)
{
	for (int i = 0; i < TRAP_MAX; i++)
	{
		if (g_Trap[i].Enable == false)
		{
			g_Trap[i].Enable = true;
			g_Trap[i].Position.x = x;
			g_Trap[i].Position.y = y;
			g_Trap[i].Size.x = sizeX;
			g_Trap[i].Size.y = sizeY;
			g_Trap[i].Type = type;
			g_Trap[i].count = 0;
			break;
		}
	}
}

void TrapJudge(float pl, float pr, float pt, float pb, int runspeed) {

	for (int i = 0; i < TRAP_MAX; i++)
	{
		if (g_Trap[i].Enable == false) continue;

		float trapl = g_Trap[i].Position.x - g_Trap[i].Size.x * 0.1f;
		float trapr = g_Trap[i].Position.x + g_Trap[i].Size.x * 0.1f;
		float trapt = g_Trap[i].Position.y - g_Trap[i].Size.y * 0.1f;
		float trapb = g_Trap[i].Position.y + g_Trap[i].Size.y * 0.1f;

		if (trapl < pr && pl < trapr && trapt < pb && pt < trapb)
		{
			float dl = trapl - pr;
			float dr = trapr - pl;
			float dt = trapt - pb;
			float db = trapb - pt;
			float dx, dy;
			if (abs(dx) > abs(dy) || abs(dy) < 1.0f) {

				//sound
				PlaySE(WSD_BULLET_HIT);

				//trap触った結果
				switch (g_Trap[i].Type)
				{
				case 0:
					player->Position.x = player->Spawn.x;
					player->Position.y = player->Spawn.y;
					break;
				case 1:
					//if(g_Trap[i].count > 7)
					//player->Position.y -= 200.f;
					break;
				default:
					break;
				}

				//エフェクト



			}
		}

	}
}
