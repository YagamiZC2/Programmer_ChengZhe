#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "controller.h"
#include "bullet.h"
#include "player.h"
#include "sound.h"

static unsigned int g_Texture;
static PLAYER g_Player;

PLAYER* GetPlayer()
{
	return &g_Player;
}
void InitPlayer()
{
	g_Texture = LoadTexture("rom:/player.tga");//�e�N�X�`����ǂݍ���

	g_Player.Position.x = -700.0f;
	g_Player.Position. y = 300.0f;

	g_Player.Enable = true;
	g_Player.Life = 3;
}

void UninitPlayer()
{
	UnloadTexture(g_Texture);//�e�N�X�`���̉��
}

void UpdatePlayer()
{
	if (g_Player.Enable == false)
		return;
	//�X�e�B�b�N�ړ�
	Float2 stick = GetControllerLeftStick();
	g_Player.Position.x += stick.x *10.0f;
	g_Player.Position.y -= stick.y *10.0f;

	//�^�b�`�p�l���ړ�
	/*if (GetControllerTouchScreen())
	{
		Float2 touchPos = GetControllerTouchScreenPosition();
		g_Position.x = touchPos.x;
		g_Position.y = touchPos.y;
	}*/
	//�\���L�[�ړ�
	if (GetControllerPress(NpadButton::Left::Index))
	{
		g_Player.Position.x -= 10.0f;
	}

	if (GetControllerPress(NpadButton::Right::Index))
	{
		g_Player.Position.x += 10.0f;
	}
	
	if (GetControllerPress(NpadButton::Up::Index))
	{
		g_Player.Position.y -= 10.0f;
	}
	if (GetControllerPress(NpadButton::Down::Index))
	{
		g_Player.Position.y += 10.0f;

	}

	//��ʐ���
	if (g_Player.Position.x < -700.f)//Left
		g_Player.Position.x = -700.f;
	if (g_Player.Position.x > 500.f)//Right
		g_Player.Position.x = 500.f;
	if (g_Player.Position.y < -400.f)//Up
		g_Player.Position.y = -400.f;
	if (g_Player.Position.y > 300.f)//Down
		g_Player.Position.y = 300.f;

		if (GetControllerTrigger(NpadButton::A::Index))
		{
			CreatBullet(g_Player.Position.x + 100, g_Player.Position.y, 15.0f, 0.0f);
			PlaySE(WSD_BULLET_SHOOT);//���ʉ��Đ�
		}
		if (GetControllerTrigger(NpadButton::X::Index))
		{
			CreatBullet(g_Player.Position.x + 100, g_Player.Position.y, 15.0f, -5.0f);
			PlaySE(WSD_BULLET_SHOOT);
		}
		if (GetControllerTrigger(NpadButton::B::Index))
		{
			CreatBullet(g_Player.Position.x + 100, g_Player.Position.y, 15.0f, 5.0f);
			PlaySE(WSD_BULLET_SHOOT);
		}
		if (GetControllerTrigger(NpadButton::ZR::Index))
		{
			CreatBullet(g_Player.Position.x + 100, g_Player.Position.y, 15.0f, 0.0f);
			CreatBullet(g_Player.Position.x + 100, g_Player.Position.y, 15.0f, -5.0f);
			CreatBullet(g_Player.Position.x + 100, g_Player.Position.y, 15.0f, 5.0f);
			PlaySE(WSD_BULLET_SHOOT);
		}
}

void DrawPlayer()
{	
	if (g_Player.Enable == false)
		return;

	DrawSpriteQuad(g_Player.Position.x, g_Player.Position.y, 100.f, 100.f, 1.f, 1.f, 1.f, 1.f, g_Texture, 0.0f, 0.0f, 1.0f, 1.0f);
}