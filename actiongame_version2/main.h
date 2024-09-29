#pragma once

#include "system.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define NUM_VERTEX_QUADS		(4)	// ���_��(�l�p�`)


// ���_���
struct VERTEX_3D
{
	Float3 Position;	// ���W
	Float4 Color;		// �F
	Float2 TexCoord;	// �e�N�X�`�����W
};

enum SCENE {
	SCENE_NONE,
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_BOSS,
	SCENE_RESULT,
};

void SetScene(SCENE Scene);