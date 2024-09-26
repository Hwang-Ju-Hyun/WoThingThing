#include "GameOver_Lvl.h"
#include "GameStateManager.h"
#include "MainMenu_Lvl.h"
#include "Stage01_Lvl.h"
#include"EventManager.h"
//
#include"StageBoss_Lvl.h"
//
s8 gameoverFont;

Level::GameOver_Lvl::GameOver_Lvl()
{
}

Level::GameOver_Lvl::~GameOver_Lvl()
{
	//AEGfxDestroyFont(gameoverFont);
}

void Level::GameOver_Lvl::Init()
{
	gameoverFont = AEGfxCreateFont("Assets/esamanru-Bold.ttf", 72);
	Level::StageBoss_Lvl::Stage2 = false;
}

void Level::GameOver_Lvl::Update()
{
	const char* test1 = "YOU DIED";
	const char* test2 = "Press R Restart";
	const char* test3 = "Press ESC Exit";
	f32 w, h;

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxGetPrintSize(gameoverFont, test1, 1.f, &w, &h);

	//AEGfxPrint(gameoverFont, "YOU DIED", -0.3, 0, 1, 1, 1, 1, 1);
	AEGfxPrint(gameoverFont, test1, -w / 2, -h / 2, 1, 1, 1, 1, 1);

	//AEGfxPrint(gameoverFont, "Press R Restart", -0.15, -0.3, 0.3, 1, 1, 1, 1);
	AEGfxPrint(gameoverFont, test2, -0.15f, -0.3f, 0.3f, 1.f, 1.f, 1.f, 1.f);
	//AEGfxPrint(gameoverFont, "Press ESC Exit", -0.15, -0.4, 0.3, 1, 1, 1, 1);
	AEGfxPrint(gameoverFont, test3, -0.15f, -0.4f, 0.3f, 1.f, 1.f, 1.f, 1.f);



	if (AEInputCheckCurr(AEVK_R))
	{
		GSM::GameStateManager* gsm = GSM::GameStateManager::GetInst();
		gsm->ChangeLevel(new Level::Stage01_Lvl);
	}
	if (AEInputCheckCurr(AEVK_ESCAPE))
	{
		GSM::GameStateManager* gsm = GSM::GameStateManager::GetInst();
		gsm->ChangeLevel(nullptr);
	}

}

void Level::GameOver_Lvl::Exit()
{
	EventManager::GetInst()->RemoveAllEvent();
}
