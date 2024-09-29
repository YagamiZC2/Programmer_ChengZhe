#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "controller.h"
#include "player.h"
#include "camera.h"

static float g_Scroll;
static float g_Scroll2;
static float g_Scroll3;
static unsigned int g_Texture;
static unsigned int g_Texture2;
static unsigned int g_Texture3;

void InitBg()
{
	g_Scroll = 0.0f;//初期化
	g_Scroll2 = 0.0f;
	g_Scroll3 = 0.0f;

	g_Texture = LoadTexture("rom:/bluesky_bg.tga");//テクスチャを読み込み
	g_Texture2 = LoadTexture("rom:/bg.tga");
	g_Texture3 = LoadTexture("rom:/bg3.tga");

}

void UninitBg()
{
	UnloadTexture(g_Texture);//テクスチャの解放
}

void UpdateBg()
{
}

void DrawBg()
{
	PLAYER* player = GetPlayer();
	CAMERA* camera = GetCamera();
	if (player->status == 0) {
		DrawSpriteQuad(
			0.f, 0.f,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			1.f, 1.f, 1.f, 1.f,
			g_Texture,
			camera->Position.x / SCREEN_WIDTH,
			SCREEN_HEIGHT,//camera->Position.y/
			1.0f, 1.0f);
	}
	else if (player->status == 2) {
		DrawSpriteQuad(
			0.f, 0.f,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			1.f, 1.f, 1.f, 1.f,
			g_Texture2,
			g_Scroll, 0.f, 1.0f, 1.0f);

	}
	

	//DrawSpriteQuad(
	//	0.f, 0.f,
	//	SCREEN_WIDTH, SCREEN_HEIGHT,
	//	1.f, 1.f, 1.f, 1.f,
	//	g_Texture3,
	//	g_Scroll3, 0.f, 1.0f, 1.0f);
	
}