#pragma once

#include "system.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define NUM_VERTEX_QUADS		(4)	// 頂点数(四角形)


// 頂点情報
struct VERTEX_3D
{
	Float3 Position;	// 座標
	Float4 Color;		// 色
	Float2 TexCoord;	// テクスチャ座標
};

enum SCENE {
	SCENE_NONE,
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_BOSS,
	SCENE_RESULT,
};

void SetScene(SCENE Scene);