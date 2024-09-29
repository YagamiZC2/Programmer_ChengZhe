#include "main.h"
#include "texture.h"
#include "sprite.h"
#include <time.h>
#include "sound.h"
#include "block.h"
#include "camera.h"
#include "enemy.h"
#include "player.h"
#include "explosion.h"
#include "item.h"


static unsigned int g_Texture;
static unsigned int timecount;
//�G�̍\���̕ϐ�
static ENEMY g_Enemy[ENEMY_MAX];
static CAMERA* camera = GetCamera();
static PLAYER* player = GetPlayer();


ENEMY* GetEnemy()
{
	return g_Enemy;
}

void InitEnemy()
{
	g_Texture = LoadTexture("rom:/dinoB.tga");//�e�N�X�`����ǂݍ���

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_Enemy[i].Enable = false;
		g_Enemy[i].Left = true;
		g_Enemy[i].Active = false;
		g_Enemy[i].Position.x = 0.0f;
		g_Enemy[i].Position.y = 0.0f;
		g_Enemy[i].Size.x = 50.0f;
		g_Enemy[i].Size.y = 50.0f;
		g_Enemy[i].count = 0;
		g_Enemy[i].Velocity.x = 0.0f;
		g_Enemy[i].Velocity.y = 0.0f;
		g_Enemy[i].HitstopTimeCount = 0;
		g_Enemy[i].HP = 3;
	}

}

void UninitEnemy()
{

	UnloadTexture(g_Texture);//�e�N�X�`���̉��

}

void UpdateEnemy()
{
	timecount++;

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].Enable==true)
		{
			if (abs(player->Position.x - g_Enemy[i].Position.x) <= SCREEN_WIDTH / 2 ||
				abs(player->Position.y - g_Enemy[i].Position.y) <= SCREEN_HEIGHT / 2) 
			{
				g_Enemy[i].Active = true;
			}

			if (g_Enemy[i].Active == false) continue;

			if (g_Enemy[i].HitstopTimeCount > 0) {
				g_Enemy[i].HitstopTimeCount--;
				continue;
			}

			//�d��
			g_Enemy[i].Velocity.y += 1.0f;

			//�ړ�
			g_Enemy[i].Position.x += g_Enemy[i].Velocity.x;
			g_Enemy[i].Position.y += g_Enemy[i].Velocity.y;


			//enemy���W
			float el = g_Enemy[i].Position.x - g_Enemy[i].Size.x * 0.5f;
			float er = g_Enemy[i].Position.x + g_Enemy[i].Size.x * 0.5f;
			float et = g_Enemy[i].Position.y - g_Enemy[i].Size.y * 0.5f;
			float eb = g_Enemy[i].Position.y + g_Enemy[i].Size.y * 0.5f;


			//block����
			BLOCK* block = GetBlock();

			for (int j = 0; j < BLOCK_MAX; j++)
			{
				if (block[j].Enable == false) continue;

				float bl = block[j].Position.x - block[j].Size.x * 0.5f;
				float br = block[j].Position.x + block[j].Size.x * 0.5f;
				float bt = block[j].Position.y - block[j].Size.y * 0.5f;
				float bb = block[j].Position.y + block[j].Size.y * 0.5f;

				if (bl < er && el < br && bt < eb && et < bb)
				{
					float dl = bl - er;
					float dr = br - el;
					float dt = bt - eb;
					float db = bb - et;
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
						if (dy * g_Enemy[i].Velocity.y < 0.0f)
						{
							g_Enemy[i].Position.y += dy;
							g_Enemy[i].Velocity.y = 0.0f;
						}

					}
					else
					{
						if (dx * g_Enemy[i].Velocity.x < 0.0f)
						{
							g_Enemy[i].Position.x += dx;
							g_Enemy[i].Velocity.x *= -1.0f;
							g_Enemy[i].Left = !g_Enemy[i].Left;
						}
					}

				}
			}
		}
		
	}

}

void DrawEnemy()
{
	
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].Enable == true) {

			int count = timecount / 10;//time escaped
			int run = 5;//start png number
			int numberofpng = 5;//how many frame
			count = run + count % numberofpng;

			float tw = 1.0f / 24.0f;
			float th = 1.0f / 1.0f;
			float u = 1.0f / 24.0f * (count % 24);
			float v = 1.0f / 1.0f*(count / 24);

			if (g_Enemy[i].Left == true) {
				u += 1.0f / 24.0f;
				tw = -tw;
			}

			DrawSpriteQuad(
				g_Enemy[i].Position.x - camera->Position.x,
				g_Enemy[i].Position.y - camera->Position.y,
				g_Enemy[i].Size.x,
				g_Enemy[i].Size.y,
				1.f, 1.f, 1.f, 1.f,
				g_Texture,
				u, v, tw, th);
			
		}
	}
}

void CreatEnemy(int type, float x, float y, float sizeX, float sizeY)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].Enable == false)
		{
			g_Enemy[i].Enable = true;
			g_Enemy[i].Active = false;
			g_Enemy[i].Position.x = x;
			g_Enemy[i].Position.y = y;
			g_Enemy[i].Size.x = sizeX;
			g_Enemy[i].Size.y = sizeY;
			g_Enemy[i].Type = type;
			g_Enemy[i].Velocity.x = -1.0f;
			g_Enemy[i].Velocity.y = 0.0f;

			break;
		}
	}
}

void HitStopEnemy(int TimeCount) {
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_Enemy[i].HitstopTimeCount = TimeCount;
		break;
	}
}

void EnemyJudge(float pl, float pr, float pt, float pb, int oldjump) {

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].Enable == false) continue;

		float el = g_Enemy[i].Position.x - g_Enemy[i].Size.x * 0.5f;
		float er = g_Enemy[i].Position.x + g_Enemy[i].Size.x * 0.5f;
		float et = g_Enemy[i].Position.y - g_Enemy[i].Size.y * 0.5f;
		float eb = g_Enemy[i].Position.y + g_Enemy[i].Size.y * 0.5f;

		if (el < pr && pl < er && et < pb && pt < eb)
		{
			float dl = el - pr;
			float dr = er - pl;
			float dt = et - pb;
			float db = eb - pt;
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

						//�T�E���h
						PlaySE(WSD_BULLET_HIT);

						//Player�ړ�
						player->Velocity.y = -20.0f;

						//attack hitstop
						HitStopPlayer(5);

						//�J�����U��
						ShakeCamera(30.0f);

						if (oldjump) {
							//�L�����ׂ�chara shrink
							player->Scale.x = 1.5f;
							player->Scale.y = 0.5f;
						}

						//life minus
						g_Enemy[i].HP--;
						if (g_Enemy[i].HP <= 0) {

							g_Enemy[i].Enable = false;

							//�G�t�F�N�g
							CreatExplosion(
								g_Enemy[i].Position.x - camera->Position.x,
								g_Enemy[i].Position.y - camera->Position.y);

							//�A�C�e���h���b�v
							CreatItem(0, g_Enemy[i].Position.x, g_Enemy[i].Position.y, 50.0f, 50.0f);
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
}