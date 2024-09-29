#include "main.h"
#include "player.h"
#include "camera.h"

static CAMERA g_Camera;

CAMERA* GetCamera() {
	return &g_Camera;
}

void InitCamera() {

	g_Camera.Position.x = 0.0f;
	g_Camera.Position.y = 0.0f;

	g_Camera.Offset.x = 0.0f;
	g_Camera.Offset.y = 0.0f;

	g_Camera.ShakeOffset = 0.0f;
	g_Camera.TimeCount = 0;
}

void UpdateCamera() {
	PLAYER* player = GetPlayer();

	g_Camera.TimeCount++;


	//player¶‰E”»’f@{
	//ƒJƒƒ‰offset‰ÁZ
	if (player->Left) {
		g_Camera.Offset.x += (-200.0f - g_Camera.Offset.x) * 0.01f;
	}
	else {
		g_Camera.Offset.x += (200.0f - g_Camera.Offset.x) * 0.01f;
	}

	
	g_Camera.Offset.y += (23.0f + player->Position.y / 100.0f - g_Camera.Offset.y) * 0.01f;

	//ƒJƒƒ‰ˆÊ’uŒvZ
	g_Camera.Position.x += (player->Position.x + g_Camera.Offset.x - g_Camera.Position.x) * 0.1f;//üŒ`•âŠ®
	g_Camera.Position.y += (-10.0f + player->Position.y + g_Camera.Offset.y - g_Camera.Position.y) * 0.1f;

	//ƒJƒƒ‰shake
	g_Camera.Position.y += sinf(g_Camera.TimeCount * 3) * g_Camera.ShakeOffset;//”gì‚é

	//ƒJƒƒ‰U“®ŒyŒ¸
	g_Camera.ShakeOffset += -g_Camera.ShakeOffset * 0.1f;
}

void ShakeCamera(float Offset) {
	g_Camera.ShakeOffset = Offset;
}