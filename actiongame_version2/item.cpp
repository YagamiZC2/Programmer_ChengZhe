#include "main.h"
#include "texture.h"
#include "sprite.h"
#include <time.h>
#include "sound.h"
#include "block.h"
#include "camera.h"
#include "item.h"
#include "player.h"
#include "getItem.h"
#include "score.h"


static unsigned int g_Texture1;
static unsigned int g_Texture2;
static unsigned int timecount;
//敵の構造体変数
static ITEM g_Item[ITEM_MAX];
static int totalItems = 5;
static PLAYER* player = GetPlayer();

ITEM* GetItem()
{
	return g_Item;
}

void InitItem()
{
	
	g_Texture1 = LoadTexture("rom:/sandwish.tga");//テクスチャを読み込み
	g_Texture2 = LoadTexture("rom:/gem.tga");
	for (int i = 0; i < ITEM_MAX; i++)
	{
		g_Item[i].Enable = false;
		g_Item[i].Position.x = 0.0f;
		g_Item[i].Position.y = 0.0f;
		g_Item[i].Size.x = 100.0f;
		g_Item[i].Size.y = 100.0f;
	}

	

}

void UninitItem()
{

	UnloadTexture(g_Texture1);//テクスチャの解放

}

void UpdateItem()
{
	if (totalItems > 0) return;
	CreatItem(1, 0, 0, 100, 100);
	
}

void DrawItem()
{
	for (int i = 0; i < ITEM_MAX; i++)
	{
		CAMERA* camera = GetCamera();
		if (g_Item[i].Enable == true) {

			//float tw = 1.0f / 8.0f;
			//float th = 1.0f / 8.0f;
			//float u = 1.0f / 8.0f * (count % 8);
			//float v = 1.0f / 8.0f*(count / 8);
			float tw = 1.0f;
			float th = 1.0f;
			float u = 0.0f;
			float v = 0.0f;
			if (g_Item[i].Type == 0) {
				DrawSpriteQuad(
					g_Item[i].Position.x - camera->Position.x,
					g_Item[i].Position.y - camera->Position.y,
					g_Item[i].Size.x,
					g_Item[i].Size.y,
					1.f, 1.f, 1.f, 1.f,
					g_Texture1,
					u, v, tw, th);
			}
			else
			{
				DrawSpriteQuad(
					g_Item[i].Position.x - camera->Position.x,
					g_Item[i].Position.y - camera->Position.y,
					g_Item[i].Size.x,
					g_Item[i].Size.y,
					1.f, 1.f, 1.f, 1.f,
					g_Texture2,
					u, v, tw, th);
			}

		}
	}
}

void CreatItem(int type, float x, float y, float sizeX, float sizeY)
{
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (g_Item[i].Enable == false)
		{
			g_Item[i].Enable = true;
			g_Item[i].Position.x = x;
			g_Item[i].Position.y = y;
			g_Item[i].Size.x = sizeX;
			g_Item[i].Size.y = sizeY;
			g_Item[i].Type = type;
			break;
		}
	}
}

void ItemJudge(float pl, float pr, float pt, float pb, int runspeed) {

	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (g_Item[i].Enable == false) continue;

		float iteml = g_Item[i].Position.x - g_Item[i].Size.x * 0.5f;
		float itemr = g_Item[i].Position.x + g_Item[i].Size.x * 0.5f;
		float itemt = g_Item[i].Position.y - g_Item[i].Size.y * 0.5f;
		float itemb = g_Item[i].Position.y + g_Item[i].Size.y * 0.5f;

		if (iteml < pr && pl < itemr && itemt < pb && pt < itemb)
		{
			float dl = iteml - pr;
			float dr = itemr - pl;
			float dt = itemt - pb;
			float db = itemb - pt;
			float dx, dy;
			if (abs(dx) > abs(dy) || abs(dy) < 5.0f) {

				//sound
				PlaySE(WSD_BULLET_HIT);

				//スコア加算
				totalItems -= 1;
				if (g_Item[i].Type == 1) {
					
					

					g_Item[i].Enable = false;

					player->status = 1;

					
				}
				//エフェクト
				CreatGetItem(
					g_Item[i].Position.x,
					g_Item[i].Position.y);

				addScore(100);

				g_Item[i].Enable = false;
			}
		}

	}
}
