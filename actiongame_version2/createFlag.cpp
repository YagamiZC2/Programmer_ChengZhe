#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "createFlag.h"
#include "sound.h"
#include "camera.h"

static unsigned int g_Texture;
static CAMERA* camera = GetCamera();

//�e�̍\����
struct CREATEFLAG
{
	bool Enable;
	Float2 Position;
};

static CREATEFLAG g_CreateFlag;


void InitCreateFlag()
{
	g_Texture = LoadTexture("rom:/box.tga");//�e�N�X�`����ǂݍ���

	g_CreateFlag.Enable = false;
	g_CreateFlag.Position.x = -800.0f;
	g_CreateFlag.Position.y = -100.0f;

}
void UninitCreateFlag()
{
	UnloadTexture(g_Texture);
}
void UpdateCreateFlag()
{
	g_CreateFlag.Position.x;
	g_CreateFlag.Position.y;
}

void DrawCreateFlag()
{
	float tw = 1.0f;
	float th = 1.0f;
	float u = 0.0f;
	float v = 0.0f;

	DrawSpriteQuad(
		g_CreateFlag.Position.x - camera->Position.x, g_CreateFlag.Position.y - camera->Position.y,
		50.0f, 50.0f,
		1.f, 1.f, 1.f, 1.f, 
		g_Texture, 
		u, v, tw, th); //u,v �n�_�@tw,th�͕�
}

void UpdateFlag(float x, float y)
{
	g_CreateFlag.Position.x = x;
	g_CreateFlag.Position.y = y;
}