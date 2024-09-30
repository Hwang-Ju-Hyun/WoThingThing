#include "Congratulation.h"
#include "GameStateManager.h"
#include "StageBoss_Lvl.h"
#include "MainMenu_Lvl.h"
#include "Stage01_Lvl.h"
#include"EventManager.h"
//
#include"StageBoss_Lvl.h"
//
s8 CongratulationFont;


Level::Congratulation::Congratulation()
{
}

Level::Congratulation::~Congratulation()
{
}

void Level::Congratulation::Init()
{
	CongratulationFont=AEGfxCreateFont("Assets/esamanru-Bold.ttf", 72);
	Level::StageBoss_Lvl::Stage2 = false;
}

void Level::Congratulation::Update()
{
	AEGfxPrint(CongratulationFont, "Congratulation!", -0.3f, 0.f, 1.f, 1.f, 1.f, 1.f, 1.f);
	
	AEGfxPrint(CongratulationFont, "Press ESC Exit", -0.15f, -0.4f, 0.3f, 1.f, 1.f, 1.f, 1.f);

	if (AEInputCheckCurr(AEVK_ESCAPE))
	{
		GSM::GameStateManager* gsm = GSM::GameStateManager::GetInst();
		gsm->ChangeLevel(nullptr);
	}
}

void Level::Congratulation::Exit()
{
	EventManager::GetInst()->RemoveAllEvent();
}
