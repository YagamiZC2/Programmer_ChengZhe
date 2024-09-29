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

void InitGame()
{
	///////////////////////////https://itch.io/
	///////////////////////////https://ldtk.io/

	InitPlayer();

	InitCamera();

	InitBlock();

	InitRunGuage();

	InitBg();

	InitBullet();

	InitBuff();

	InitItem();

	InitEnemy();

	InitScore();

	InitGetItem();

	InitLift();

	//InitBoss();

	//InitEnemyBullet();

	InitExplosion();

	InitTrap();

	InitCreateFlag();
	

	
	PlayBGM(STRM_CYLINDER);//BGM再生

	//レベルデザイン

	//   0
	//  00
	// 000
	//0000
	CreatBlock(0,   0, 500, 100, 100);
	/*CreatBlock(0, 100, 500, 100, 100);*/
	//CreatBlock(0, 200, 500, 100, 100);
	//CreatBlock(0, 300, 500, 100, 100);
	CreatBlock(0, 100, 400, 100, 100);
	//CreatBlock(0, 200, 400, 100, 100);
	CreatBlock(0, 200, 300, 100, 100);
	//CreatBlock(0, 300, 400, 100, 100);
	//CreatBlock(0, 300, 300, 100, 100);
	CreatBlock(0, 300, 200, 100, 100);

	//0
	//00
	//000
	//0000
	CreatBlock(0, -100, 500, 100, 100);
	//CreatBlock(0, -200, 500, 100, 100);
	//CreatBlock(0, -300, 500, 100, 100);
	//CreatBlock(0, -400, 500, 100, 100);
	//CreatBlock(0, -200, 400, 100, 100);
	//CreatBlock(0, -300, 400, 100, 100);
	//CreatBlock(0, -300, 300, 100, 100);
	CreatBlock(0, -400, 400, 100, 100);
	CreatBlock(0, -400, 300, 100, 100);
	CreatBlock(0, -400, 200, 100, 100);

	CreatItem(0, -400, 100, 50, 50);

	//00000000
	CreatBlock(0,  -500,  800, 100, 100);
	CreatBlock(0,  -600,  800, 100, 100);
	CreatBlock(0, -1000, 800, 100, 100);
	CreatBlock(0, -1100,  800, 100, 100);

	CreatItem(0, -400, 750, 50, 50);


	CreatBlock(0, -100, 600, 100, 100);
	CreatBlock(0, -200, 600, 100, 100);
	CreatBlock(0, -300, 600, 100, 100);
	CreatBlock(0, -400, 600, 100, 100);
	CreatBlock(0, -500, 600, 100, 100);
	CreatBlock(0,    0, 600, 100, 100);
	CreatBlock(0,  100, 600, 100, 100);
	CreatBlock(0,  200, 600, 100, 100);
	CreatBlock(0,  300, 600, 100, 100);

	//0
	// 0
	//  0
	//   0
	CreatBlock(0, -1000, 500, 100, 100);
					
	CreatBlock(0, -1100, 400, 100, 100);
					
	CreatBlock(0, -1200, 300, 100, 100);
					
	CreatBlock(0, -1300, 200, 100, 100);

	CreatItem(0, -1000, 400, 50, 50);

	CreatItem(0, -1300, 100, 50, 50);
					
	//   0			
	//  0			
	// 0			
	//0				
	CreatBlock(0, -1100, 0, 100, 100);
					
	CreatBlock(0, -1000, -100, 100, 100);
					
	CreatBlock(0, -900, -200, 100, 100);
					
	CreatBlock(0,  -800, -300, 100, 100);

	//   0		
	//  0 0			
	// 0   0		
	//0	    0
	CreatBlock(0,  800, 300, 100,  100);
	CreatBlock(0,  900, 200, 100,  100);
	CreatBlock(0, 1000, 100, 100, 100);
	CreatBlock(0, 1100,   0, 100,   100);
	CreatBlock(0, 1200, 100, 100, 100);
	CreatBlock(0, 1300, 200, 100, 100);
	CreatBlock(0, 1400, 300, 100, 100);

	CreatItem(0, 1100, 50, 50, 50);

	//added blocks 右bound
	CreatBlock(0, 1000, -800, 100, 100);
	CreatBlock(0, 1000, -900, 100, 100);
	CreatBlock(0, 1000, -1000, 100, 100);
	CreatBlock(0, 1000, -1100, 100, 100);
	CreatBlock(0, 1000, -1200, 100, 100);



	//added blocks 右boundのJumpパッドその１
	CreatBlock(0, 600, -1000, 100, 100);
	CreatBlock(0, 700, -1100, 100, 100);
	CreatBlock(0, 800, -1200, 100, 100);
	CreatBlock(0, 900, -1300, 100, 100);
	CreatBlock(0, 1000, -1400, 100, 100);
	CreatBlock(0, 1100, -1500, 100, 100);
	CreatBlock(0, 1200, -1600, 100, 100);
	CreatBlock(0, 1300, -1700, 100, 100);

	//左右ジャンプ壁
	CreatBlock(0, 1000, -400, 100, 500);
	CreatBlock(0, 600, -100, 100, 500);
	//壁用ブロック
	CreatBlock(0, 900, -300, 100, 100);
	CreatBlock(0, 700, 0, 100, 100);

	//左右ジャンプ壁2
	CreatBlock(0, -200, -500, 100, 500);
	CreatBlock(0,  300, -400, 100, 500);
	//壁用ブロック2
	CreatBlock(0, -100, -400, 100, 100);
	CreatBlock(0,  200, -300, 100, 100);

	//start rod

	CreatBlock(0, -600, -600, 50, 50);

	CreatBlock(0, -800, -700, 50, 50);
	CreatBlock(0, -900, -800, 50, 50);

	CreatBlock(0, -400, -800, 50, 50);
	//CreatBlock(0, -500, -900, 50, 50);

	CreatBlock(0, -700, -950, 50, 50);
	//CreatBlock(0, -700, -1000, 50, 50);

	//CreatBlock(0, -400, -1000, 50, 50);
	CreatBlock(0, -400, -1100, 50, 50);

	CreatBlock(0, -800, -1100, 50, 50);
	CreatBlock(0, -600, -1200, 50, 50);

	CreatItem(0, -600, -1250, 50, 50);


	
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

	CreatTrap(1,  800, 800, 480, 160);
	CreatTrap(1, 1100, 800, 480, 160);
	CreatTrap(1, 1400, 800, 480, 160);
	CreatTrap(0, 400, 600, 100, 100);
	CreatTrap(0, 500, 600, 100, 100);
	CreatTrap(0, 600, 600, 100, 100);

	CreatEnemy(0, 200, 0, 100, 100);
	CreatEnemy(0, 600, 0, 100, 100);
	CreatEnemy(0, 900, 0, 100, 100);


	CreatLift(0, 1500, 0, 200.0f, 200.0f, 300.0f, 300.0f, 0.01f);
	CreatLift(0, 1700, 0, 100.0f, 100.0f, 200.0f, 200.0f, 0.01f);

	CreatItem(0, 1600, -1000, 50, 50);

	CreatLift(1, -500, 0, 200.0f, 200.0f, 200.0f, 200.0f, 0.01f);
	CreatLift(1, -900, 0, 100.0f, 100.0f, 400.0f, 400.0f, 0.01f);

	//item
	//横
	
	
	

}


void UninitGame()
{
	StopBGM();
	
	UninitPlayer();

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

	//UninitBoss();

	//UninitEnemyBullet();

	UninitExplosion();

	UninitTrap();

	UninitCreateFlag();

}


void UpdateGame()
{
	UpdatePlayer();

	UpdateCamera();

	UpdateBlock();

	UpdateBullet();

	UpdateRunGuage();

	UpdateItem();

	UpdateBg();

	UpdateEnemy();

	UpdateGetItem();

	UpdateScore();

	UpdateBuff();

	UpdateLift();

	UpdateExplosion();

	UpdateTrap();

	UpdateCreateFlag();


	if (GetControllerPress(NpadButton::Plus::Index))
	{
		SetScene(SCENE_RESULT);
	}

}

void DrawGame()
{

	//scene
	DrawBg();
	DrawBlock();
	DrawTrap();
	DrawItem();
	DrawLift();

	DrawBuff();

	//character
	DrawCreateFlag();
	DrawEnemy();
	DrawBullet();
	DrawPlayer();

	//UI
	DrawRunGuage();
	DrawScore();

	//effect
	DrawGetItem();
	DrawExplosion();




}
