#include "GameStart.h"
#include "GameStateManager.h"

#include "MainMenu_Lvl.h"
#include "Stage01_Lvl.h"
#include "GameOver_Lvl.h"

#include "GoManager.h"
#include "GameObject.h"
#include "TransComponent.h"
#include "SpriteComponent.h"

#include "ResourceManager.h"
#include "ImageResource.h"
#include "StageBoss_Lvl.h"

Level::GameStart_Lvl::GameStart_Lvl()
{
}

Level::GameStart_Lvl::~GameStart_Lvl()
{
}

f32 Level::GameStart_Lvl::lerp(f32 a, f32 b, f32 v)
{
	return a + v * (b - a);
}

void Level::GameStart_Lvl::Init()
{
	ResourceManager::GetInst()->Get("DigipenLogo", "Assets/DigiPen_WHITE.png");
	ResourceManager::GetInst()->Get("TeamLogo", "Assets/TeamLogo.png");

	DigipenLogo = new GameObject("DigipenLogo");
	TeamLogo = new GameObject("TeamLogo");

	GoManager::GetInst()->AddObject(DigipenLogo);
	GoManager::GetInst()->AddObject(TeamLogo);

	DigipenLogo->AddComponent("Transform", new TransComponent(DigipenLogo));
	DigipenLogo->AddComponent("Sprite", new SpriteComponent(DigipenLogo));
	TransComponent* digipenLogo_trs = (TransComponent*)DigipenLogo->FindComponent("Transform");
	SpriteComponent* digipenLogo_spr = (SpriteComponent*)DigipenLogo->FindComponent("Sprite");
	ImageResource* digipenResource = (ImageResource*)ResourceManager::GetInst()->FindRes("DigipenLogo");
	digipenLogo_trs->SetPos(0, 0);
	digipenLogo_trs->SetScale({ 1200,450 });
	digipenLogo_spr->SetTexture(digipenResource->GetImage());

	TeamLogo->AddComponent("Transform", new TransComponent(TeamLogo));
	TransComponent* teamLogo_trs = (TransComponent*)TeamLogo->FindComponent("Transform");
	teamLogo_trs->SetPos(0, 0);
	teamLogo_trs->SetScale({ 1000,500 });

	TeamLogo->AddComponent("Sprite", new SpriteComponent(TeamLogo));
	SpriteComponent* teamLogo_spr = (SpriteComponent*)TeamLogo->FindComponent("Sprite");
	ImageResource* teamResource = (ImageResource*)ResourceManager::GetInst()->FindRes("TeamLogo");
	teamLogo_spr->SetTexture(teamResource->GetImage());


	logoSec = 0.f;
	logoVec = 0.f;


	preTime = 0.f;
	totallogoTime = 0.f;

	Level::StageBoss_Lvl::Stage2 = false;
}

void Level::GameStart_Lvl::Update()
{
	preTime = totallogoTime;
	totallogoTime += AEFrameRateControllerGetFrameTime();

	if ((preTime <= 3.f && totallogoTime > 3.f) || (preTime <= 6.f && totallogoTime > 6.f) || (preTime <= 9.f && totallogoTime > 9.f))
	{
		logoSec = 0.f;
		logoVec = 0.f;
	}
	SpriteComponent* digipenLogo_spr = (SpriteComponent*)DigipenLogo->FindComponent("Sprite");
	SpriteComponent* teamLogo_spr = (SpriteComponent*)TeamLogo->FindComponent("Sprite");

	logoSec += AEFrameRateControllerGetFrameTime();
	logoVec += logoSec / 100;
	if (totallogoTime <= 3.f)
	{
		digipenLogo_spr->SetAlpha(lerp(0, 1, logoVec));

		teamLogo_spr->SetAlpha(0);
	}
	else if (totallogoTime > 3.f && totallogoTime <= 6.f)
	{
		digipenLogo_spr->SetAlpha(lerp(1, 0, logoVec));
	}
	else if(totallogoTime > 6.f && totallogoTime <= 9.f)
	{
		teamLogo_spr->SetAlpha(lerp(0, 1, logoVec));
	}
	else if (totallogoTime > 9.f && totallogoTime < 12.f)
	{
		teamLogo_spr->SetAlpha(lerp(1, 0, logoVec));
	}

	else if (totallogoTime >= 13.f)
	{
		GSM::GameStateManager* gsm = GSM::GameStateManager::GetInst();
		gsm->ChangeLevel(new Level::MainMenu_Lvl);
	}
}

void Level::GameStart_Lvl::Exit()
{
	ResourceManager::GetInst()->RemoveAllRes();
	GoManager::GetInst()->RemoveAllObj();
}
