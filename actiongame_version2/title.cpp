#include "main.h"
#include "texture.h"
#include "title.h"
#include "sprite.h"
#include "controller.h"
#include "sound.h"

static unsigned int g_Texture;


void InitTitle()
{
	g_Texture = LoadTexture("rom:/title2.tga");//�e�N�X�`����ǂݍ���

	PlayBGM(STRM_CYLINDER);//BGM�Đ�
}

void UninitTitle()
{
	UnloadTexture(g_Texture);//�e�N�X�`���̉��
}

void UpdateTitle()
{
	if (GetControllerPress(NpadButton::A::Index))
	{
		SetScene(SCENE_GAME);
	}
}

void DrawTitle()
{
	DrawSpriteQuad(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT, 1.f, 1.f, 1.f, 1.f, g_Texture, 0.0f, 0.f, 1.0f, 1.0f);
	
}


