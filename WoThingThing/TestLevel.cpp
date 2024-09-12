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
	//애들
	Enemy->AddComponent("RigidBody", new RigidBodyComponent(Enemy));

	//Ai
	Enemy->AddComponent("Ai", new AiComponent(Enemy));
	AiComponent* Enemy_state = (AiComponent*)Enemy->FindComponent("Ai");
	Enemy_state->SetTarget(Test_player);//순서중요 trager부터 먼저 세팅 해준다 그리고 먼저 palyer부터 만들어준다.
	Enemy_state->Setdir(true);//true가 왼쪽, false가 오른쪽
	Enemy_state->Setdir_time(1.0f);
	//적 ai유형 Melee, Sniper, Boss 
	//스테이지 많아지면 Boss1,Boss2 이런식으로 관리
	 
	
	//스나이퍼 세팅값은 "IDLE_Sniper", "Sniper"
	//SetSniper_bullet 추가 필수!! 
	//총알 오브젝트 무조건 추가해주기

	
	//근접 세팅값은 "IDLE", "Melee"
	Enemy_state->SetState("IDLE", "Melee");
	//Enemy_state->SetTarget(Test_player);

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
    }
	//if (ColliderManager::GetInst()->PlayerSearch(Enemy,Test_player))
	//{
	//	//SetSearch(true);
	//}
	//else 
	//{
	//	//SetSearch(false);
	//}
}

void Level::TestLevel::Exit()
{
}
