#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "controller.h"
#include "bullet.h"
#include "player.h"
#include "sound.h"
#include "camera.h"
#include "block.h"
#include "runguage.h"
#include "item.h"
#include "score.h"
#include "enemy.h"
#include "getItem.h"
#include "explosion.h"
#include "lift.h"

static unsigned int g_Texture;
static PLAYER g_Player;
static int ZRStatus = 1;
static int runspeed = 150;
static int timecount;



PLAYER* GetPlayer()
{
	return &g_Player;
}

void InitPlayer()
{
	g_Texture = LoadTexture("rom:/dino2.tga");//テクスチャを読み込み

	g_Player.Position.x = -800.0f;
	g_Player.Position.y = 312.0f;

	g_Player.Velocity.x = 0.0f;
	g_Player.Velocity.y = 0.0f;

	g_Player.count = 0;
	g_Player.Life = 10;
	g_Player.buff = 0;
	g_Player.status = 0;
	g_Player.runCount = 0;

	g_Player.Enable = true;
	g_Player.Left = false;
	g_Player.Run = false;
	g_Player.Jump = false;

	g_Player.Scale.x = 1.0f;
	g_Player.Scale.y = 1.0f;
}

void UninitPlayer()
{
	UnloadTexture(g_Texture);//テクスチャの解放
}

void UpdatePlayer()
{
	if (g_Player.Enable == false)
		return;

	timecount++;
	CAMERA* camera = GetCamera();


	if (GetControllerTrigger(NpadButton::Y::Index)) {

		if (g_Player.Left) {
			CreatBullet(g_Player.Position.x, g_Player.Position.y, -20.0f, 0.0f);
		}
		else {
			CreatBullet(g_Player.Position.x, g_Player.Position.y, 20.0f, 0.0f);
		}

		
	}

	//十字キー移動
	if (GetControllerPress(NpadButton::Left::Index))
	{
		g_Player.count++;
		g_Player.Left = true;
		g_Player.Velocity.x = -10.0f;
		if (g_Player.Run) g_Player.Velocity.x += -5.0f;

	}
	else if (GetControllerPress(NpadButton::Right::Index))
	{
		g_Player.count++;
		g_Player.Left = false;
		g_Player.Velocity.x = 10.0f;
		if (g_Player.Run) g_Player.Velocity.x += 5.0f;

	}


	//Jump状態
	if (!g_Player.Jump) {
		if (GetControllerPress(NpadButton::A::Index))
		{
			if (!g_Player.Run) {
				g_Player.Velocity.y = -25.0f;
			}
			else {
				g_Player.Velocity.y = -30.0f;
			}

			g_Player.Scale.x = 0.5f;
			g_Player.Scale.y = 1.5f;
		}
	}

	//前のjump状態
	bool oldjump = g_Player.Jump;

	g_Player.Jump = true;


	g_Player.Scale.x += (1.0f - g_Player.Scale.x)*0.2f;
	g_Player.Scale.y += (1.0f - g_Player.Scale.y)*0.2f;


	//走る状態
	if (g_Player.runCount > 0)
	{
		g_Player.runCount--;
		addRunGuage(-1);
	}

	////
	if (g_Player.HitstopTimeCount > 0) {
		g_Player.HitstopTimeCount--;
		return;
	}

	if (g_Player.runCount == 0) ZRStatus = 1;

	if (GetControllerPress(NpadButton::ZR::Index))
	{
		if (g_Player.runCount >= runspeed) {
			g_Player.Run = false;
			ZRStatus = 0;
		}
		else if (ZRStatus == 1) {
			g_Player.Run = true;
			g_Player.runCount++;
			g_Player.runCount++;
			addRunGuage(2);
		}
	}

	if (GetControllerRelease(NpadButton::ZR::Index))
	{
		g_Player.Run = false;
	}

	//摩擦力

	g_Player.Velocity.x += -g_Player.Velocity.x * 0.2f;


	//重力
	g_Player.Velocity.y += 1.0f;


	//移動
	g_Player.Position.x += g_Player.Velocity.x;
	g_Player.Position.y += g_Player.Velocity.y;


	//地面判定
	if (g_Player.Position.y > 500.0f) {
		g_Player.Position.y = 500.0f;
		g_Player.Velocity.y = 0.0f;
		g_Player.Jump = false;
	}

	float pl = g_Player.Position.x - 48.0f;
	float pr = g_Player.Position.x + 48.0f;
	float pt = g_Player.Position.y - 48.0f;
	float pb = g_Player.Position.y + 48.0f;

	//block当たり判定
	BlockJudge(pl, pr, pt, pb, oldjump);
	//enemy当たり判定
	EnemyJudge(pl, pr, pt, pb, oldjump);
	//lift当たり判定
	LiftJudge(pl, pr, pt, pb, oldjump);
	//item当たり判定
	ItemJudge(pl, pr, pt, pb, runspeed);


	//BLOCK* block = GetBlock();

	//for (int i = 0; i < BLOCK_MAX; i++)
	//{
	//	if (block[i].Enable == false) continue;

	//	float bl = block[i].Position.x - block[i].Size.x * 0.5f;
	//	float br = block[i].Position.x + block[i].Size.x * 0.5f;
	//	float bt = block[i].Position.y - block[i].Size.y * 0.5f;
	//	float bb = block[i].Position.y + block[i].Size.y * 0.5f;

	//	if (bl < pr && pl < br && bt < pb && pt < bb)
	//	{
	//		float dl = bl - pr;
	//		float dr = br - pl;
	//		float dt = bt - pb;
	//		float db = bb - pt;
	//		float dx, dy;

	//		if (-dl < dr) {
	//			dx = dl;
	//		}
	//		else {
	//			dx = dr;
	//		}

	//		if (-dt < db) {
	//			dy = dt;
	//		}
	//		else {
	//			dy = db;
	//		}

	//		if (abs(dx) > abs(dy) || abs(dy) < 5.0f)
	//		{
	//			if (dy * g_Player.Velocity.y < 0.0f)
	//			{
	//				g_Player.Position.y += dy;
	//				g_Player.Velocity.y = 0.0f;

	//				if (dy < 0.0f) {
	//					//着地landing
	//					g_Player.Jump = false;

	//					if (oldjump) {
	//						//キャラ潰すchara shrink
	//						g_Player.Scale.x = 1.5f;
	//						g_Player.Scale.y = 0.5f;
	//					}

	//				}
	//			}

	//		}
	//		else
	//		{
	//			if (dx * g_Player.Velocity.x < 0.0f)
	//			{
	//				g_Player.Position.x += dx;
	//				g_Player.Velocity.x = 0.0f;
	//			}
	//		}

	//	}
	//}
		////////////////////////////////////////////////////////////////////

	//ENEMY* enemy = GetEnemy();

	//for (int i = 0; i < ENEMY_MAX; i++)
	//	{
	//		if (enemy[i].Enable == false) continue;

	//		float el = enemy[i].Position.x - enemy[i].Size.x * 0.5f;
	//		float er = enemy[i].Position.x + enemy[i].Size.x * 0.5f;
	//		float et = enemy[i].Position.y - enemy[i].Size.y * 0.5f;
	//		float eb = enemy[i].Position.y + enemy[i].Size.y * 0.5f;

	//		if (el < pr && pl < er && et < pb && pt < eb)
	//		{
	//			float dl = el - pr;
	//			float dr = er - pl;
	//			float dt = et - pb;
	//			float db = eb - pt;
	//			float dx, dy;

	//			if (-dl < dr) {
	//				dx = dl;
	//			}
	//			else {
	//				dx = dr;
	//			}

	//			if (-dt < db) {
	//				dy = dt;
	//			}
	//			else {
	//				dy = db;
	//			}

	//			if (abs(dx) > abs(dy) || abs(dy) < 5.0f)
	//			{
	//				if (dy * g_Player.Velocity.y < 0.0f)
	//				{
	//					g_Player.Position.y += dy;
	//					g_Player.Velocity.y = 0.0f;

	//					if (dy < 0.0f) g_Player.Jump = false;
	//					if (dy < 0.0f)
	//					{

	//						//サウンド
	//						PlaySE(WSD_BULLET_HIT);

	//						//Player移動
	//						g_Player.Velocity.y = -20.0f;

	//						//attack hitstop
	//						HitStopPlayer(5);

	//						//カメラ振動
	//						ShakeCamera(30.0f);

	//						if (oldjump) {
	//							//キャラ潰すchara shrink
	//							g_Player.Scale.x = 1.5f;
	//							g_Player.Scale.y = 0.5f;
	//						}

	//						//life minus
	//						enemy[i].HP--;
	//						if (enemy[i].HP <= 0) {

	//							enemy[i].Enable = false;

	//							//エフェクト
	//							CreatExplosion(
	//								enemy[i].Position.x - camera->Position.x,
	//								enemy[i].Position.y - camera->Position.y);

	//							//アイテムドロップ
	//							CreatItem(0, enemy[i].Position.x, enemy[i].Position.y, 50.0f, 50.0f);
	//						}

	//					}

	//				}

	//			}
	//			else
	//			{
	//				if (dx * g_Player.Velocity.x < 0.0f)
	//				{
	//					g_Player.Position.x += dx;
	//					g_Player.Velocity.x = 0.0f;
	//				}
	//			}

	//		}
	//	}

	///////////////////////////////////////////////////////////////////
	// lift
	//LIFT* lift = GetLift();

	//for (int i = 0; i < LIFT_MAX; i++)
	//{
	//	if (g_Player.Life == 0 || lift[i].Enable == false)
	//		continue;

	//	float ll = lift[i].Position.x - lift[i].Size.x * 0.5f;
	//	float lr = lift[i].Position.x + lift[i].Size.x * 0.5f;
	//	float lt = lift[i].Position.y - lift[i].Size.y * 0.5f;
	//	float lb = lift[i].Position.y + lift[i].Size.y * 0.5f;

	//	if (ll < pr && pl < lr && lt < pb && pt < lb)
	//	{
	//		float dl = ll - pr;
	//		float dr = lr - pl;
	//		float dt = lt - pb;
	//		float db = lb - pt;
	//		float dx, dy;

	//		if (-dl < dr) {
	//			dx = dl;
	//		}
	//		else {
	//			dx = dr;
	//		}

	//		if (-dt < db) {
	//			dy = dt;
	//		}
	//		else {
	//			dy = db;
	//		}
	//		if (abs(dx) > abs(dy) || abs(dy) < 5.0f) {
	//			if (dy * g_Player.Velocity.y < 0.0f)
	//			{
	//				g_Player.Position.y += dy;
	//				g_Player.Velocity.y = 0.0f;
	//				if (dy < 0.0f) {
	//					g_Player.Jump = false;
	//					//Liftに付けて移動
	//					g_Player.Position.x +=
	//						lift[i].Position.x - lift[i].OldPosition.x;
	//					g_Player.Position.y +=
	//						lift[i].Position.y - lift[i].OldPosition.y;

	//					if (oldjump) {
	//						//キャラ潰すchara shrink
	//						g_Player.Scale.x = 1.5f;
	//						g_Player.Scale.y = 0.5f;
	//					}
	//				}
	//			}
	//		}
	//		else {
	//			if (dx * g_Player.Velocity.x < 0.0f)
	//			{
	//				g_Player.Position.x += dx;
	//				g_Player.Velocity.x = 0.0f;
	//			}
	//		}
	//	}
	//}
		///////////////////////////////////////////////////////////////////
		//item判定
	//ITEM* item = GetItem();

	//for (int i = 0; i < ITEM_MAX; i++)
	//{
	//	if (item[i].Enable == false) continue;

	//	float iteml = item[i].Position.x - item[i].Size.x * 0.5f;
	//	float itemr = item[i].Position.x + item[i].Size.x * 0.5f;
	//	float itemt = item[i].Position.y - item[i].Size.y * 0.5f;
	//	float itemb = item[i].Position.y + item[i].Size.y * 0.5f;

	//	if (iteml < pr && pl < itemr && itemt < pb && pt < itemb)
	//	{
	//		float dl = iteml - pr;
	//		float dr = itemr - pl;
	//		float dt = itemt - pb;
	//		float db = itemb - pt;
	//		float dx, dy;
	//		if (abs(dx) > abs(dy) || abs(dy) < 5.0f) {

	//			//sound
	//			PlaySE(WSD_BULLET_HIT);

	//			//スコア加算
	//			runspeed += 20;

	//			//エフェクト
	//			CreatGetItem(
	//				item[i].Position.x,
	//				item[i].Position.y);

	//			addScore(100);

	//			item[i].Enable = false;
	//		}
	//	}

	//}

}

void DrawPlayer()
{	
	if (g_Player.Enable == false)
		return;
	
	int count = g_Player.count / 10;

	CAMERA* camera = GetCamera();
	//player status adjustment
	int startPNG = 5;
	int numberofFrames = 5;


	if (abs(g_Player.Velocity.x) <= 0.001f && abs(g_Player.Velocity.y) <= 1.001f)
	{
		startPNG = 1;
		numberofFrames = 3;
		count = timecount / 10;
	}

	if (g_Player.Jump == true) 
	{
		startPNG = 5;
		numberofFrames = 1;
	}
	else if (g_Player.Run == true) 
	{
		startPNG = 20;
		numberofFrames = 4;
		count = g_Player.count / 5;
	}

	count = startPNG + count % numberofFrames;


	float tw = 1.0f / 24.0f;
	float th = 1.0f / 1.0f;
	float u = 1.0f / 24.0f*(count % 24);
	float v = 1.0f / 1.0f*(count / 24);

	if (g_Player.Left == true) {
		u += 1.0f / 24.0f;
		tw = -tw;
	}

	DrawSpriteQuad(
		g_Player.Position.x - camera->Position.x,
		g_Player.Position.y - camera->Position.y - (g_Player.Scale.y- 1.0f) * 48.0f,
		96.0f * g_Player.Scale.x, 
		96.0f * g_Player.Scale.y,
		1.f, 1.f, 1.f, 1.f,
		g_Texture,
		u, v, tw, th);
}

void HitStopPlayer(int TimeCount) {
	g_Player.HitstopTimeCount = TimeCount;
}