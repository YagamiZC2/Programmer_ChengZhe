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
#include "trap.h"
#include "createFlag.h"
#include "boss.h"

static unsigned int g_Texture;
static PLAYER g_Player;
static int ZRStatus = 1;
static int runspeed = 150;
static int timecount;
static CAMERA* camera = GetCamera();


PLAYER* GetPlayer()
{
	return &g_Player;
}

void InitPlayer()
{
	g_Texture = LoadTexture("rom:/dino2.tga");//�e�N�X�`����ǂݍ���

	g_Player.Position.x = -800.0f;
	g_Player.Position.y = -100.0f;

	g_Player.Velocity.x = 0.0f;
	g_Player.Velocity.y = 0.0f;

	g_Player.Spawn.x = -800.0f;
	g_Player.Spawn.y = -100.0f;

	g_Player.count = 0;
	g_Player.Life = 10;
	g_Player.buff = 0;
	g_Player.status = 0;
	g_Player.runCount = 0;

	g_Player.Enable = true;
	g_Player.Left = false;
	g_Player.Run = false;
	g_Player.Jump = false;
	g_Player.Hurt = false;

	g_Player.Scale.x = 1.0f;
	g_Player.Scale.y = 1.0f;
	g_Player.HitstopTimeCount = 0;
	g_Player.MissTimeCount= 0;
}

void UninitPlayer()
{
	UnloadTexture(g_Texture);//�e�N�X�`���̉��
}

void UpdatePlayer()
{
	if (g_Player.Enable == false)
		return;
	if (g_Player.status == 1)
		SetScene(SCENE_BOSS);

	if (g_Player.MissTimeCount > 0) {
		g_Player.MissTimeCount--;
		if (g_Player.MissTimeCount <= 0) {
			SetScene(SCENE_RESULT);
		}
	}

	timecount++;

	if (GetControllerTrigger(NpadButton::X::Index)) {
		g_Player.Spawn.x = g_Player.Position.x;
		g_Player.Spawn.y = g_Player.Position.y;
		UpdateFlag(g_Player.Spawn.x, g_Player.Spawn.y);
	}

	if (GetControllerTrigger(NpadButton::Y::Index)) {

		if (g_Player.Left) {
			CreatBullet(g_Player.Position.x, g_Player.Position.y, -20.0f, 0.0f, g_Player.Left);
		}//player������bullet�����ς���
		else {
			CreatBullet(g_Player.Position.x, g_Player.Position.y, 20.0f, 0.0f, g_Player.Left);
		}

		
	}

	//�\���L�[�ړ�
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


	//Jump���

	if (!g_Player.Jump) {
		if (GetControllerPress(NpadButton::A::Index))
		{
			if (!g_Player.Run) {
				g_Player.Velocity.y = -25.0f;		//jump��ԉ������ĂȂ���
			}
			else {
				g_Player.Velocity.y = -30.0f;		//jump��ԉ������Ă�
			}

			g_Player.Scale.x = 0.5f;				//player�ۂ��ۂ��
			g_Player.Scale.y = 1.5f;
		}
	}

	//�O��jump���
	bool oldjump = g_Player.Jump;

	g_Player.Jump = true;


	g_Player.Scale.x += (1.0f - g_Player.Scale.x)*0.2f;
	g_Player.Scale.y += (1.0f - g_Player.Scale.y)*0.2f;


	//������
	if (g_Player.runCount > 0)
	{
		g_Player.runCount--;  //����Q�[�W��Ɍ��Z��
		addRunGuage(-1,runspeed);
	}

	////
	if (g_Player.HitstopTimeCount > 0) {
		g_Player.HitstopTimeCount--;
		return;
	}

	if (g_Player.runCount == 0) ZRStatus = 1;

	//ZR�����Ƒ����Ԃɓ���
	if (GetControllerPress(NpadButton::ZR::Index))
	{
		//��莞�ԓ������̎��Ԕ���
		if (g_Player.runCount >= runspeed) {
			g_Player.Run = false;		//���ԃI�[�o�[��ԂƑ���Ȃ��Ȃ�
			ZRStatus = 0;		//ZR�{�^���𖳌�������
		}
		else if (ZRStatus == 1) {	//ZR�{�^���L�������Ԑ�����
			g_Player.Run = true;	//����锻�f�ɓ���
			g_Player.runCount++;
			g_Player.runCount++;
			addRunGuage(2,runspeed);			//����Q�[�W���Z
		}
	}

	if (GetControllerRelease(NpadButton::ZR::Index))
	{
		g_Player.Run = false;
	}

	//���C��

	g_Player.Velocity.x += -g_Player.Velocity.x * 0.2f;


	//�d��
	g_Player.Velocity.y += 1.0f;


	//�ړ�
	g_Player.Position.x += g_Player.Velocity.x;
	g_Player.Position.y += g_Player.Velocity.y;


	g_Player.Hurt = false;

	float pl = g_Player.Position.x - 48.0f;
	float pr = g_Player.Position.x + 48.0f;
	float pt = g_Player.Position.y - 48.0f;
	float pb = g_Player.Position.y + 48.0f;

	//block�����蔻��
	BlockJudge(pl, pr, pt, pb, oldjump);

	//enemy�����蔻��
	EnemyJudge(pl, pr, pt, pb, oldjump);

	//lift�����蔻��
	LiftJudge(pl, pr, pt, pb, oldjump);

	//item�����蔻��
	ItemJudge(pl, pr, pt, pb, runspeed);


	//trap�����蔻��
	TrapJudge(pl, pr, pt, pb, runspeed);

	//boss�����蔻��
	BossJudge(pl, pr, pt, pb, oldjump);
}

void DrawPlayer()
{	
	if (g_Player.Enable == false)
		return;
	
	if (g_Player.MissTimeCount > 0) return;

	int count = g_Player.count / 10;

	//player status adjustment
	int startPNG = 5;
	int numberofFrames = 5;

	//player�Î~����
	if (abs(g_Player.Velocity.x) <= 0.001f && abs(g_Player.Velocity.y) <= 1.001f)
	{
		startPNG = 1;
		numberofFrames = 3;
		count = timecount / 10;
	}

	//player��jump����

	if (g_Player.Hurt == true) {
		startPNG = 15;
		numberofFrames = 3;
	}
	else if (g_Player.Jump == true) 
	{
		startPNG = 5;
		numberofFrames = 1;
	}
	else if (g_Player.Run == true) //�����Ԕ���
	{
		startPNG = 20;
		numberofFrames = 4;
		count = g_Player.count / 5;
	}

	//�J�n�摜�I��
	count = startPNG + count % numberofFrames;


	float tw = 1.0f / 24.0f;
	float th = 1.0f / 1.0f;
	float u = 1.0f / 24.0f*(count % 24);
	float v = 1.0f / 1.0f*(count / 24);

	//player��������
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


void MissPlayer() {
	g_Player.MissTimeCount = 60;//��b��

	//effect
	/*CreatExplosion(
		g_Player.Position.x - camera->Position.x ,
		g_Player.Position.y - camera->Position.y);*/

	//�J�����U��
	ShakeCamera(30.0f);

	//player��ړ�
	g_Player.Velocity.y = -20.0f;

	g_Player.Hurt = true;

}