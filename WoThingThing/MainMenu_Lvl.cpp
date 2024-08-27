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
#include "Stage01_Lvl.h"
#include "CompManager.h"
#include "Serializer.h"

void Level::MainMenu_Lvl::Init()
{
#ifndef DEBUG
	//std::cout << "MainMenu_Lvl Init" << std::endl;
#endif
	StartButton = new GameObject("Start");
	ExitButton = new GameObject("Exit");
	
	GoManager::GetInst()->AddObject(StartButton);
	GoManager::GetInst()->AddObject(ExitButton);

	StartButton->AddComponent("Transform", new TransComponent(StartButton));
	StartButton->AddComponent("Sprite", new SpriteComponent(StartButton));

	ExitButton->AddComponent("Transform", new TransComponent(ExitButton));
	ExitButton->AddComponent("Sprite", new SpriteComponent(ExitButton));

}

void Level::MainMenu_Lvl::Update()
{

	TransComponent* StartBtn_trs = (TransComponent*)StartButton->FindComponent("Transform");
	SpriteComponent* StartBtn_spr = (SpriteComponent*)StartButton->FindComponent("Sprite");	

	TransComponent* ExitBtn_trs = (TransComponent*)ExitButton->FindComponent("Transform");
	SpriteComponent* ExitBtn_spr = (SpriteComponent*)ExitButton->FindComponent("Sprite");		

	for (auto comp : CompManager::GetInst()->AllComp())
	{
		if (comp->GetName() == "Sprite")
		{
			SpriteComponent::Color& BtnColor = static_cast<SpriteComponent*>(comp)->GetColor();
			{
				BtnColor.red = 255;
				BtnColor.blue = 0;
				BtnColor.green = 0;
			}
		}
	}



	s32 mousePosX, mousePosY;
	AEVec2 StartBtnPos = StartBtn_trs->GetPos();
	AEVec2 StartBtnScale = StartBtn_trs->GetScale();
	AEVec2 ExitBtnPos = ExitBtn_trs->GetPos();
	AEVec2 ExitBtnScale = ExitBtn_trs->GetScale();
	s32 window_width  = 1600;
	s32 window_height = 900;
	AEInputGetCursorPosition(&mousePosX, &mousePosY);
	//std::cout << mousePosX << " " << mousePosY << std::endl;
	if (AEInputCheckTriggered(AEVK_LBUTTON)==true)
	{				
		s32 StartBtn_left = window_width / 2.f - fabs(StartBtnPos.x - StartBtnScale.x / 2.f);
		s32 StartBtn_right = window_width / 2.f + fabs(StartBtnPos.x + StartBtnScale.x / 2.f);
		s32 StartBtn_top = window_height / 2.f - fabs(StartBtnPos.y - StartBtnScale.y / 2.f);
		s32 StartBtn_bottom = window_height / 2.f + fabs(StartBtnPos.y + StartBtnScale.y / 2.f);

		s32 ExitBtn_left = window_width / 2.f - fabs(ExitBtnPos.x - ExitBtnScale.x / 2.f);
		s32 ExitBtn_right = window_width / 2.f + fabs(ExitBtnPos.x + ExitBtnScale.x / 2.f);
		s32 ExitBtn_top = 600;//sorry
		s32 ExitBtn_bottom = window_height / 2.f + fabs(fabs(ExitBtnPos.y) + ExitBtnScale.y/2.f);		
		
		if (StartBtn_left < mousePosX &&
			StartBtn_right > mousePosX &&
			StartBtn_top < mousePosY &&
			StartBtn_bottom > mousePosY)
		{
			GSM::GameStateManager::GetInst()->ChangeLevel(new Level::Stage01_Lvl);
		}
		else if (ExitBtn_left < mousePosX &&
			ExitBtn_right > mousePosX &&
			ExitBtn_top < mousePosY &&
			ExitBtn_bottom > mousePosY)
		{			
			GSM::GameStateManager::GetInst()->ChangeLevel(nullptr);			
		}
	}


	auto text_res = ResourceManager::GetInst()->Get("text", "../Extern/Assets/liberation-mono.ttf");
	TextResource* MenuText_res = static_cast<TextResource*>(text_res);
	MenuText_res->SetText("START");

	auto font = MenuText_res->GetFont();
	auto text = MenuText_res->GetText();
	auto height = MenuText_res->GetHeight();

	AEGfxPrint(font, text, -0.07f, 1.f - (height + 0.93), 1, 1, 1, 1, 1);	


	MenuText_res->SetText("EXIT");
	AEGfxPrint(font, text, -0.05f, 1.f - (height + 1.37), 1, 1, 1, 1, 1);
}

void Level::MainMenu_Lvl::Exit()
{
	Serializer::GetInst()->SaveLevel("temp.json");
#ifndef DEBUG
	//std::cout << "MainMenu_Lvl Exit" << std::endl;
#endif	
	//ResourceManager::GetInst()->RemoveAllRes();
	GoManager::GetInst()->RemoveAllObj();
	GSM::GameStateManager::GetInst()->ChangeLevel(nullptr);
}
