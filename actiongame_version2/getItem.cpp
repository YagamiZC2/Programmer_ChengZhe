#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "getItem.h"
#include "controller.h"
#include "enemy.h"
#include "sound.h"
#include "camera.h"

static unsigned int g_Texture;

//�e�̍\����
struct GETITEM
{
	bool Enable;
	Float2 Position;
	int count;
};

#define GETITEM_MAX 20

static GETITEM g_GetItem[GETITEM_MAX];


void InitGetItem()
{
	g_Texture = LoadTexture("rom:/item_feedback.tga");//�e�N�X�`����ǂݍ���
	for (int i = 0; i < GETITEM_MAX; i++)
	{
		g_GetItem[i].Enable = false;
		g_GetItem[i].Position.x = 0.0f;
		g_GetItem[i].Position.y = 0.0f;
	}
}
void UninitGetItem()
{
	UnloadTexture(g_Texture);
}
void UpdateGetItem()
{
	for (int i = 0; i < GETITEM_MAX; i++)
	{
		if (g_GetItem[i].Enable == false)
			continue;

		g_GetItem[i].count++;
		if (g_GetItem[i].count > 16) g_GetItem[i].Enable = false;
		//16�͑��\���ł���t���[����
	}
}

void DrawGetItem()
{
	for (int i = 0; i < GETITEM_MAX; i++)
	{
		CAMERA* camera = GetCamera();
		float tw = 1.0f / 4.0f;
		float th = 1.0f;
		float u = 1.0f / 4.0f*(g_GetItem[i].count / 4); //4�͉��t���[�����Ƃ����摜�؂�ւ���
		//float v = 1.0f / 5.0f*(g_GetItem[i].count / 5);
		float v = 0;
		if (g_GetItem[i].Enable == true)
			
			DrawSpriteQuad(
				g_GetItem[i].Position.x - camera->Position.x,
				g_GetItem[i].Position.y - camera->Position.y,
				100.0f, 100.0f,
				1.f, 1.f, 1.f, 1.f,
				g_Texture,
				u, v, tw, th); //u,v �n�_�@tw,th�͕�
	}
}
void CreatGetItem(float x, float y)
{
	for (int i = 0; i < GETITEM_MAX; i++)
	{
		if (g_GetItem[i].Enable == false)
		{
			g_GetItem[i].Enable = true;
			g_GetItem[i].Position.x = x;
			g_GetItem[i].Position.y = y;
			g_GetItem[i].count = 0;
			break;
		}
	}
}