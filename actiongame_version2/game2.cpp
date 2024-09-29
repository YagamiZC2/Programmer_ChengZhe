#include "main.h"
#include "texture.h"
#include "player.h"
#include "background.h"
#include "controller.h"
#include "enemy.h"
#include "bullet.h"
#include "enemyBullet.h"
#include "sound.h"
#include "explosion.h"
#include "score.h"
#include "game.h"
#include "result.h"
#include "buff.h"
#include "boss.h"
#include "block.h"
#include "camera.h"
#include "runguage.h"
#include "item.h"
#include "getItem.h"
#include "lift.h"
#include "trap.h"
#include "createFlag.h"

void InitGame2()
{

	/*UninitPlayer();

	UninitBlock();

	UninitBullet();

	UninitRunGuage();

	UninitItem();

	UninitBg();

	UninitEnemy();

	UninitBuff();

	UninitScore();

	UninitGetItem();

	UninitLift();

	UninitExplosion();

	UninitTrap();

	UninitCreateFlag();*/


	InitPlayer();

	InitCamera();

	InitBlock();

	InitRunGuage();

	InitBg();

	InitLift();

	InitExplosion();

	InitTrap();

	InitCreateFlag();

	/*UninitItem();

	UninitEnemy();

	UninitBuff();

	UninitScore();

	UninitGetItem();*/


	InitBoss();

	InitEnemyBullet();


	//レベルデザイン

	

	//0
	//00
	//000
	//0000
	CreatBlock(0, -100, 500, 100, 100);
	CreatBlock(0, -400, 400, 100, 100);
	CreatBlock(0, -400, 300, 100, 100);
	CreatBlock(0, -400, 200, 100, 100);

	//00000000
	CreatBlock(0, -500, 800, 100, 100);
	CreatBlock(0, -600, 800, 100, 100);
	CreatBlock(0, -1000, 800, 100, 100);
	CreatBlock(0, -1100, 800, 100, 100);

	CreatBlock(0, -100, 600, 100, 100);
	CreatBlock(0, -200, 600, 100, 100);
	CreatBlock(0, -300, 600, 100, 100);
	CreatBlock(0, -400, 600, 100, 100);
	CreatBlock(0, -500, 600, 100, 100);
	CreatBlock(0, 0, 600, 100, 100);
	CreatBlock(0, 100, 600, 100, 100);
	CreatBlock(0, 200, 600, 100, 100);
	CreatBlock(0, 300, 600, 100, 100);




	CreatBlock(0, 300,  -100, 100, 100);
	CreatBlock(0, 400,  -100, 100, 100);
	CreatBlock(0, 500,  -100, 100, 100);
	CreatBlock(0, 800,  -500, 100, 100);
	CreatBlock(0, 900,  -500, 100, 100);
	CreatBlock(0, 1000, -500, 100, 100);
	CreatBlock(0, 1100, -500, 100, 100);
	CreatBlock(0, 1200, -500, 100, 100);

	//0
	// 0
	//  0
	//   0
	CreatBlock(0, -1000, 500, 100, 100);

	CreatBlock(0, -1100, 400, 100, 100);

	CreatBlock(0, -1200, 300, 100, 100);

	CreatBlock(0, -1300, 200, 100, 100);


	//   0			
	//  0			
	// 0			
	//0				
	CreatBlock(0, -1100, 0, 100, 100);

	CreatBlock(0, -1000, -100, 100, 100);

	CreatBlock(0, -900, -200, 100, 100);

	CreatBlock(0, -800, -300, 100, 100);



	//added blocks 右bound
	CreatBlock(0, 1000, -800, 100, 100);
	CreatBlock(0, 1000, -900, 100, 100);
	CreatBlock(0, 1000, -1000, 100, 100);
	CreatBlock(0, 1000, -1100, 100, 100);
	CreatBlock(0, 1000, -1200, 100, 100);

	for (int i = -20; i < 20; i++)
	{
		//底
		CreatBlock(0, i * 500, 1100, 500, 500);
		CreatBlock(0, -i * 500, 1100, 500, 500);

		//天
		CreatBlock(0, i * 500, -2300, 500, -500);
		CreatBlock(0, -i * 500, -2300, 500, -500);
	}

	//辺
	CreatBlock(1, 3000, 0, 2000, 4000);
	CreatBlock(1, -3000, 0, 2000, 4000);

	CreatTrap(1, -800, 800, 480, 160);

	CreatTrap(1, 800, 800, 480, 160);

	CreatTrap(0, 400, 600, 100, 100);

	CreatLift(0, 200, 0, 200.0f, 200.0f, 300.0f, 300.0f, 0.01f);
	CreatLift(0, 400, 0, 100.0f, 100.0f, 200.0f, 200.0f, 0.01f);

	static PLAYER* player = GetPlayer();

	player->status = 2;

}


void UninitGame2()
{
	StopBGM();

	UninitPlayer();

	UninitBlock();

	UninitBullet();

	UninitRunGuage();

	UninitBg();

	UninitLift();

	UninitBoss();

	UninitEnemyBullet();

	UninitExplosion();

	UninitTrap();

	UninitCreateFlag();

}


void UpdateGame2()
{
	UpdatePlayer();

	UpdateCamera();

	UpdateBlock();

	UpdateBullet();

	UpdateRunGuage();

	UpdateBg();

	UpdateLift();

	UpdateBoss();

	UpdateEnemyBullet();

	UpdateExplosion();

	UpdateTrap();

	UpdateCreateFlag();


	if (GetControllerPress(NpadButton::Plus::Index))
	{
		SetScene(SCENE_RESULT);
	}

}

void DrawGame2()
{

	//scene
	DrawBg();
	DrawBlock();
	DrawTrap();
	DrawLift();

	//character
	DrawCreateFlag();
	DrawBullet();
	DrawPlayer();
	DrawBoss();
	DrawEnemyBullet();

	//effect
	DrawExplosion();




}
