
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "background.h"
#include "sample.h"
#include "controller.h"
#include "bullet.h"
//プロトタイプ宣言
void Init();
void Update();
void Draw();
void Uninit();

extern "C" void nnMain()
{
	//******初期化処理********
	Init();


    while( true )
	{
		//******更新処理********
		Update();

		//******描画処理********
		Draw();

	}


	//******終了処理********
	Uninit();
}

void Init() //初期化処理
{
	InitSystem();//system初期化
	InitBg();
	InitSample();
	InitController();
	InitBullet();
}

void Update()//更新処理
{


	UpdateBg();
	UpdateSample();
	UpdateController();
	UpdateBullet();

}

void Draw()//描画処理
{
	//クリア色設定
	glClearColor(1.f, 1.f, 1.f, 1.f);

	//画面クリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawBg();
	DrawSample();
	DrawBullet();
	SwapBuffers();//画面を切り替える処理
}

void Uninit()//終了処理
{
	UninitBg();
	UninitSample();
	UninitBullet();
	UninitController();
	UninitSystem();//system終了
}
