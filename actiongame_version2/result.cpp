#include "main.h"
#include "texture.h"//Load Texture�̃w�b�_�[
#include"title.h"
#include"sprite.h"//DrawSprite�̃w�b�_�[
#include"controller.h"
#include "player.h"
#include "score.h"

static unsigned int g_Texture;
static unsigned int g_Texture2;
static unsigned int g_Texture3;
static int status;
void InitResult()
{
	//�e�N�X�`���̓ǂݍ���
	g_Texture = LoadTexture("rom:/Theresult.tga");
	g_Texture2 = LoadTexture("rom:/Theresult.tga");
	g_Texture3 = LoadTexture("rom:/Theresult.tga");

	PLAYER* player = GetPlayer();
	SCORE* score = GetScore();
	if (player->Life <= 0) {
		status = 0;
	}
	else if (player->status == 1 && score->count <= 0) {
		status = 1;
	}
	else {
		status = 2;
	}
}


void UninitResult()
{
	//�e�N�X�`���[�̉��
	UnloadTexture(g_Texture);
}


void UpdateResult()
{
	if (GetControllerTrigger(NpadButton::A::Index))
	{
		SetScene(SCENE_TITLE);//�Ăяo�����́@A�{�^������������ł����
	}


}

void DrawResult()
{
	switch (status)
	{
	case 0:
		DrawSpriteQuad(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT, 1.f, 1.f, 1.f, 1.f, g_Texture, 0.0f, 0.f, 1.0f, 1.0f);
		break;
	case 1:
		DrawSpriteQuad(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT, 1.f, 1.f, 1.f, 1.f, g_Texture2, 0.0f, 0.f, 1.0f, 1.0f);
		break;
	case 2:
		DrawSpriteQuad(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT, 1.f, 1.f, 1.f, 1.f, g_Texture3, 0.0f, 0.f, 1.0f, 1.0f);
		break;
	default:
		break;
	}

}