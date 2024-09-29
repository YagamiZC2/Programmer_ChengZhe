#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "controller.h"

static float g_Scroll;
static unsigned int g_Texture;

void InitBg()
{
	g_Scroll = 0.0f;//初期化

	g_Texture = LoadTexture("rom:/bg_forest.tga");//テクスチャを読み込み
}

void UninitBg()
{
	UnloadTexture(g_Texture);//テクスチャの解放
}

void UpdateBg()
{
	/*Float2 stick = GetControllerLeftStick();
	g_Scroll += stick.x *0.005f;

	if (GetControllerPress(NpadButton::Right::Index))
	{
		g_Scroll += 0.005f;
		if (g_Scroll > 1.0f)
			g_Scroll -= 1.0f;
	}
	
	if (GetControllerPress(NpadButton::Left::Index))
	{
		g_Scroll -= 0.005f;
		if (g_Scroll < -1.0f)
			g_Scroll += 1.0f;
	}
	*/
	/*g_Scroll += 0.0025f;
	if (g_Scroll > 1.0f)
		g_Scroll -= 1.0f;*/
}

void DrawBg()
{
	DrawSpriteQuad(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT, 1.f, 1.f, 1.f, 1.f, g_Texture, g_Scroll, 0.f, 1.0f, 1.0f);
	
}