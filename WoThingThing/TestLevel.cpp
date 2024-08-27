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

Level::TestLevel::TestLevel()
{

}

Level::TestLevel::~TestLevel()
{

}

void Level::TestLevel::Init()
{
	player = new GameObject("Player");
	Enemy = new GameObject("Enemy");
	GoManager::GetInst()->AddObject(player);
	GoManager::GetInst()->AddObject(Enemy);

	player->AddComponent("Transform", new TransComponent(player));
	player->AddComponent("Sprite", new SpriteComponent(player));

	Enemy->AddComponent("Transform", new TransComponent(Enemy));
	Enemy->AddComponent("Sprite", new SpriteComponent(Enemy));


	//리지디드 바디 물어보기
}

void Level::TestLevel::Update()
{
	TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
	SpriteComponent* player_spr = (SpriteComponent*)player->FindComponent("Sprite");

	TransComponent* Enemy_trs = (TransComponent*)Enemy->FindComponent("Transform");
	SpriteComponent* Enemy_spr = (SpriteComponent*)Enemy->FindComponent("Sprite");

    for (auto player : GoManager::GetInst()->Allobj())
    {
        if (player->GetName() == "Player")
        {
            if (AEInputCheckCurr(AEVK_W))
            {
                    player_trs->AddPos(0.f, 10.f);
            }
            if (AEInputCheckCurr(AEVK_S))
            {
					player_trs->AddPos(0.f, -10.f);
            }
			if (AEInputCheckCurr(AEVK_A))
			{
				player_trs->AddPos(0.f, -10.f);
			}
			if (AEInputCheckCurr(AEVK_D))
			{
				player_trs->AddPos(0.f, 10.f);
			}

        }
    }





}

void Level::TestLevel::Exit()
{
}
