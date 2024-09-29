#include "main.h"
#include "controller.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"
#include "sample.h"
#include <math.h>
#include "bullet.h"

static unsigned int g_Texture;
static float g_rag = 0.0f;
static float speed = 1.0f;
static float sx, sy;
static Float2 Start;
static Float2 End;
static Float2 Bullet;
//SIN,COSのテスト構造体
struct CIRCLE
{
	Float2 Position;
};


void InitSample()
{
	g_Texture = LoadTexture("rom:/bullet.tga");//テクスチャを読み込み
	Start.x = -960.0f;
	Start.y = 540.f;
	End.x = 0.0f;
	End.y = 0.0f;
}
void UninitSample()
{
	UnloadTexture(g_Texture);
}
void UpdateSample()
{
	sx = cosf(g_rag) * speed + Start.x;
	sy = sinf(g_rag) * speed + Start.y;
	End.x = sx;
	End.y = sy;
	if (GetControllerPress(NpadButton::Left::Index))
	{
		speed -= 1.0f;
	}

	if (GetControllerPress(NpadButton::Right::Index))
	{
		speed += 1.0f;
	}

	if (GetControllerPress(NpadButton::Up::Index))
	{
		g_rag -= 0.01f;

	}
	if (GetControllerPress(NpadButton::Down::Index))
	{
		g_rag += 0.01f;
	}
	float bx = Start.x - End.x;
	float by = Start.y - End.y;
	float l = sqrt(bx * bx + by * by);
	bx /= l;
	by /= l;
	Bullet.x = bx * speed * 0.1;
	Bullet.y = by * speed * 0.1;
	if (GetControllerTrigger(NpadButton::A::Index))
	{
		CreatBullet(Start.x, Start.y, -Bullet.x, -Bullet.y);
	}
}

void DrawSample()
{
	DrawLine(End, Start);
	Float2 lines{
		200.0f, 300.0f
	};

	Float2 linee{
		600.0f, 150.0f
	};

	DrawLine(lines, linee);
}

void DrawLine(Float2 s, Float2 e)
{
	//sからeまでの長さをはかる
	Float2 v;
	v.x = e.x - s.x;
	v.y = e.y - s.y;
	float length = sqrtf(v.y * v.y + v.x * v.x);

	//sからeの向きを調べる
	Float2 dir;
	dir.x = v.x / length;
	dir.y = v.y / length;

	//手抜き...点の数
	int n = length;

	//線を描く
	for (int i = 0; i < n; i++)
	{
		DrawSpriteQuad(s.x + dir.x * i, s.y + dir.y * i,
			32.f, 32.f, 1.f, 1.f, 1.f, 1.f, g_Texture, 0.0f, 0.0f, 1.0f, 1.0f);
	}
}


//cx cy ball center
//line sx sy start x start y
//line ex ey end x end y
//25 bullet radius