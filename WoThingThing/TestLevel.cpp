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

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

int Level::TestLevel::enemy_dir = 1;//

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


	//리지디드 바디 물어보기
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
				enemy_dir = 0;
			}
			if (AEInputCheckCurr(VK_RIGHT))
			{
				Enemy_trs->AddPos(10.f, 0.f);
				enemy_dir = 1;
			}

		}
    }
	if (ColliderManager::GetInst()->PlayerSearch(Enemy,Test_player))
	{
		//std::cout << "SearchPlayer" << std::endl;
		Enemy_trs->GetPos();
		//lerp를 사용해서 enemy_trs에서

	}
}

void Level::TestLevel::Exit()
{
}
