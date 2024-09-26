#include "MainMenu_Lvl.h"
#include "header.h"
#include "GameObject.h"
#include "GoManager.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "TransComponent.h"
#include "SpriteComponent.h"
#include "ColliderManager.h"
#include "GameStateManager.h"

#include "Resource.h"
#include "ResourceManager.h"
#include "TextResource.h"
#include "ImageResource.h"
#include "AudioResource.h"

#include "Stage01_Lvl.h"
#include "CompManager.h"
#include "MapEditor.h"
#include "StageBoss_Lvl.h"
#include "Serializer.h"

#include"StageBoss_Lvl.h"
#include "StageTutorial.h"


void Level::MainMenu_Lvl::Init()
{
	Screen = new GameObject("MainMenu");

	StartBtn = new GameObject("Start");
	HowBtn = new GameObject("How");
	ExitBtn = new GameObject("Exit");
	
	GoManager::GetInst()->AddObject(Screen);
	GoManager::GetInst()->AddObject(StartBtn);
	GoManager::GetInst()->AddObject(HowBtn);
	GoManager::GetInst()->AddObject(ExitBtn);
	
	//Screen Texture============================================================================
	Screen->AddComponent("Transform", new TransComponent(Screen));
	Screen->AddComponent("Sprite", new SpriteComponent(Screen));
	TransComponent* screen_trs = (TransComponent*)Screen->FindComponent("Transform");
	screen_trs->SetPos(0, 0);
	screen_trs->SetScale({ 1600, 900 });
	SpriteComponent* screen_spr = (SpriteComponent*)Screen->FindComponent("Sprite");
	ResourceManager::GetInst()->Get("MainMenu", "Assets/MainMenu.png");
	ImageResource* screenImg = (ImageResource*)ResourceManager::GetInst()->FindRes("MainMenu");
	screen_spr->SetTexture(screenImg->GetImage());
	//==========================================================================================

	//StartBtn==================================================================================
	StartBtn->AddComponent("Transform", new TransComponent(StartBtn));
	StartBtn->AddComponent("Sprite", new SpriteComponent(StartBtn));
	TransComponent* StartBtn_trs = (TransComponent*)StartBtn->FindComponent("Transform");
	StartBtn_trs->SetPos(10, -40);
	SpriteComponent* StartBtn_spr = (SpriteComponent*)StartBtn->FindComponent("Sprite");
	ResourceManager::GetInst()->Get("StartBtn", "Assets/StartBtn.png");
	ImageResource* StartBtnImg = (ImageResource*)ResourceManager::GetInst()->FindRes("StartBtn");
	StartBtn_spr->SetTexture(StartBtnImg->GetImage());
	//==========================================================================================

	//HowBtn====================================================================================
	HowBtn->AddComponent("Transform", new TransComponent(HowBtn));
	HowBtn->AddComponent("Sprite", new SpriteComponent(HowBtn));
	TransComponent* HowBtn_trs = (TransComponent*)HowBtn->FindComponent("Transform");
	HowBtn_trs->SetPos(10, -170);
	SpriteComponent* HowBtn_spr = (SpriteComponent*)HowBtn->FindComponent("Sprite");
	ResourceManager::GetInst()->Get("HowBtn", "Assets/HowBtn.png");
	ImageResource* HowBtnImg = (ImageResource*)ResourceManager::GetInst()->FindRes("HowBtn");
	HowBtn_spr->SetTexture(HowBtnImg->GetImage());
	//==========================================================================================

	//ExitBtn===================================================================================
	ExitBtn->AddComponent("Transform", new TransComponent(ExitBtn));
	ExitBtn->AddComponent("Sprite", new SpriteComponent(ExitBtn));
	TransComponent* ExitBtn_trs = (TransComponent*)ExitBtn->FindComponent("Transform");
	ExitBtn_trs->SetPos(10, -298);
	SpriteComponent* ExitBtn_spr = (SpriteComponent*)ExitBtn->FindComponent("Sprite");
	ResourceManager::GetInst()->Get("ExitBtn", "Assets/ExitBtn.png");
	ImageResource* ExitBtnImg = (ImageResource*)ResourceManager::GetInst()->FindRes("ExitBtn");
	ExitBtn_spr->SetTexture(ExitBtnImg->GetImage());
	//==========================================================================================

	btnSfx = ResourceManager::GetInst()->Get("btnSFX", "Assets/SelectBtn.wav");
	btn_res = static_cast<AudioResource*>(btnSfx);

	mainmenuBGM = ResourceManager::GetInst()->Get("mainmenuBGM", "Assets/MainMenuBGM.mp3");
	BGM_res = static_cast<AudioResource*>(mainmenuBGM);
	BGM_res->PlayMusicOrSFX(BGM_res, Sound::MUSIC, bgm_volume, bgm_pitch, -1);
}

bool onceSFX = false;
void Level::MainMenu_Lvl::Update()
{
	//AddComponent를 사용하여 map에 저장하는 이유는 저장한 컴포넌트에 해당하는 기능을 다른곳에서도 사용가능하게 할려고 만들어준다.
	TransComponent*  StartBtn_trs = (TransComponent*)StartBtn->FindComponent("Transform");
	TransComponent*  HowBtn_trs = (TransComponent*)HowBtn->FindComponent("Transform");
	TransComponent*  ExitBtn_trs = (TransComponent*)ExitBtn->FindComponent("Transform");

	StartBtn_trs->SetScale({ 280,95 });
	HowBtn_trs->SetScale({ 280,95 });
	ExitBtn_trs->SetScale({ 282,98 });

	s32 mousePosX, mousePosY;
	AEInputGetCursorPosition(&mousePosX, &mousePosY);
	AEVec2 mousePos = { mousePosX - 800.f,  -(mousePosY - 450.f) };


	if (AETestPointToRect(&mousePos, &StartBtn_trs->TempGetPos(), 280, 90))
	{
		if (!onceSFX)
		{
			btn_res->PlayMusicOrSFX(btn_res, Sound::MUSIC, bgm_volume, bgm_pitch, 0);
			onceSFX = true;
		}

		AEVec2 Scale = { StartBtn_trs->GetScale().x, StartBtn_trs->GetScale().y };
		StartBtn_trs->SetScale({ Scale.x * 1.15f, Scale.y * 1.15f });
		if (AEInputCheckTriggered(AEVK_LBUTTON))
		{
			GSM::GameStateManager::GetInst()->ChangeLevel(new Level::Stage01_Lvl);
		}
	}
	else if (AETestPointToRect(&mousePos, &HowBtn_trs->TempGetPos(), 280, 90))
	{
		if (!onceSFX)
		{
			btn_res->PlayMusicOrSFX(btn_res, Sound::MUSIC, bgm_volume, bgm_pitch, 0);
			onceSFX = true;
		}
		AEVec2 Scale = { HowBtn_trs->GetScale().x, HowBtn_trs->GetScale().y };
		HowBtn_trs->SetScale({ Scale.x * 1.15f, Scale.y * 1.15f });
		if (AEInputCheckTriggered(AEVK_LBUTTON))
		{
			GSM::GameStateManager::GetInst()->ChangeLevel(new Level::StageTutorial_Lvl);
		}
	}
	else if (AETestPointToRect(&mousePos, &ExitBtn_trs->TempGetPos(), 280, 90))
	{
		if (!onceSFX)
		{
			btn_res->PlayMusicOrSFX(btn_res, Sound::MUSIC, bgm_volume, bgm_pitch, 0);
			onceSFX = true;
		}
		AEVec2 Scale = { ExitBtn_trs->GetScale().x, ExitBtn_trs->GetScale().y };
		ExitBtn_trs->SetScale({ Scale.x * 1.15f, Scale.y * 1.15f });
		if (AEInputCheckTriggered(AEVK_LBUTTON))
		{
			GSM::GameStateManager::GetInst()->ChangeLevel(nullptr);
		}
	}
	else
		onceSFX = false;

}

void Level::MainMenu_Lvl::Exit()
{

	ResourceManager::GetInst()->RemoveAllRes();
	GoManager::GetInst()->RemoveAllObj();
	
}
