#include "main.h"
#include "controller.h"
#include "sound.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "game2.h"

//プロトタイプ宣言
void Init();
void Update();
void Draw();
void Uninit();

static SCENE g_Scene;


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
	InitSound();//サウンドの初期化

	InitSystem();//system初期化

	InitController();//コントローラー初期化

	g_Scene = SCENE_NONE;

	SetScene(SCENE_GAME);

}

void Update()//更新処理
{

	UpdateController();

	switch (g_Scene)
	{
	case SCENE_TITLE:
		UpdateTitle();
		break;

	case SCENE_GAME:
		UpdateGame();
		break;

	case SCENE_BOSS:
		UpdateGame2();
		break;

	case SCENE_RESULT:
		UpdateResult();
		break;

	default:
		break;
	}

	UpdateSound();//サンウドの更新
}

void Draw()//描画処理
{
	//クリア色設定
	glClearColor(1.f, 1.f, 1.f, 1.f);

	//画面クリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (g_Scene)
	{
	case SCENE_TITLE://タイトルだった場合
		DrawTitle();
		break;

	case SCENE_GAME://ゲームだった場合
		DrawGame();
		break;

	case SCENE_BOSS:
		DrawGame2();
		break;

	case SCENE_RESULT:
		DrawResult();
		break;

	default:
		break;

	}

	SwapBuffers();//画面を切り替える処理
}

void Uninit()//終了処理
{
	
	UninitController();

	UninitSystem();//system終了

	UninitSound();//サンウド終了

	UninitTitle();
}


void SetScene(SCENE Scene)

{
	////過去の画面を呼び出している

	g_Scene = Scene;

	switch (g_Scene)
	{
	case SCENE_TITLE://タイトルだった場合
		InitTitle();
		break;

	case SCENE_GAME://ゲームだった場合

		InitGame();
		break;

	case SCENE_BOSS:
		/*UninitGame();*/
		InitGame2();
		break;

	case SCENE_RESULT:
		InitResult();
		break;

	default:
		break;

	}

}