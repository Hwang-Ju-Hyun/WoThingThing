#include "TestLevel.h"
#include "header.h"
#include "MainMenu_Lvl.h"
#include "GameStateManager.h"
#include "GameObject.h"
#include "GoManager.h"
#include "BaseComponent.h"
#include "TransComponent.h"
#include "SpriteComponent.h"
#include "CompManager.h"
#include "ColliderManager.h"
#include "RigidBodyComponent.h"
#include "ResourceManager.h"
#include "AudioResource.h"
#include "TextResource.h"
#include "Utility.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "AEInput.h"
#include"AiComponent.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

bool Level::TestLevel::enemy_dir = true;//

Level::TestLevel::TestLevel()
{

}

Level::TestLevel::~TestLevel()
{

}

void Level::TestLevel::Init()
{
	Test_player = new GameObject("Test_player");
	Enemy = new GameObject("Enemy");
	GoManager::GetInst()->AddObject(Test_player);
	GoManager::GetInst()->AddObject(Enemy);

	Test_player->AddComponent("Transform", new TransComponent(Test_player));
	Test_player->AddComponent("Sprite", new SpriteComponent(Test_player));

	Enemy->AddComponent("Transform", new TransComponent(Enemy));
	Enemy->AddComponent("Sprite", new SpriteComponent(Enemy));
	Enemy->AddComponent("Ai", new AiComponent(Enemy));
	AiComponent* Enemy_state = (AiComponent*)Enemy->FindComponent("Ai");
	Enemy_state->SetState("IDLE");


	//������� �ٵ� �����
}

void Level::TestLevel::Update()
{
	TransComponent* player_trs = (TransComponent*)Test_player->FindComponent("Transform");
	SpriteComponent* player_spr = (SpriteComponent*)Test_player->FindComponent("Sprite");

	TransComponent* Enemy_trs = (TransComponent*)Enemy->FindComponent("Transform");
	SpriteComponent* Enemy_spr = (SpriteComponent*)Enemy->FindComponent("Sprite");

    for (auto player : GoManager::GetInst()->Allobj())
    {
        if (player->GetName() == "Test_player")
        {
            if (AEInputCheckCurr(AEVK_W))
            {
				player_trs->AddPos(0.f, 10.f);
            }
            if (AEInputCheckCurr(AEVK_S))
            {
				player_trs->AddPos(0.f, -10.f);
            }
			if (AEInputCheckCurr(AEVK_D))
			{
				player_trs->AddPos(10.f, 0.f);
			}
			if (AEInputCheckCurr(AEVK_A))
			{
				player_trs->AddPos(-10.f, 0.f);
			}

        }

		if (player->GetName() == "Enemy")
		{
			if (AEInputCheckCurr(VK_UP))
			{
				Enemy_trs->AddPos(0.f, 10.f);
			}
			if (AEInputCheckCurr(VK_DOWN))
			{
				Enemy_trs->AddPos(0.f, -10.f);
			}
			if (AEInputCheckCurr(VK_LEFT))
			{
				Enemy_trs->AddPos(-10.f, 0.f);
				enemy_dir = true;
			}
			if (AEInputCheckCurr(VK_RIGHT))
			{
				Enemy_trs->AddPos(10.f, 0.f);
				enemy_dir = false;
			}

		}
    }
	if (ColliderManager::GetInst()->PlayerSearch(Enemy,Test_player))
	{
		//std::cout << "SearchPlayer" << std::endl;
		Enemy_trs->GetPos();
		//lerp�� ����ؼ� enemy_trs����

	}
}

void Level::TestLevel::Exit()
{
}
