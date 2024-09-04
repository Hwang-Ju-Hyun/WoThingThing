#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#include <iostream>
#include "header.h"

#include "GameStateManager.h"
#include "MainMenu_Lvl.h"
#include "Stage01_Lvl.h"

#include "GameObject.h"
#include "GoManager.h"

#include "BaseComponent.h"
#include "TransComponent.h"
#include "SpriteComponent.h"
#include "RigidBodyComponent.h"
#include "PlayerComponent.h"
#include "CompManager.h"

#include "EventManager.h"
#include "ColliderManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "AudioResource.h"
#include "TextResource.h"

#include "Serializer.h"
#include "NaveMeshManager.h"
#include "Utility.h"
#include "AiComponent.h"
#include "CameraManager.h"
#include "PathFindMoveComponent.h"
#include "StageBoss_Lvl.h"
#include "AEInput.h"
#include "AEUtil.h"
#include "AEMath.h"

Level::StageBoss_Lvl::StageBoss_Lvl()
{
}

Level::StageBoss_Lvl::~StageBoss_Lvl()
{
}

void Level::StageBoss_Lvl::Init()
{
	Serializer::GetInst()->LoadLevel("stageBoss.json");

    player = new GameObject("Player");
    GoManager::GetInst()->AddObject(player); //GetInst() == GetPtr()
    player->AddComponent("Transform", new TransComponent(player));
    player->AddComponent("Sprite", new SpriteComponent(player));
    player->AddComponent("PlayerComp", new PlayerComponent(player));

    aimTrace = new GameObject("aimTrace");
    GoManager::GetInst()->AddObject(aimTrace);
    aimTrace->AddComponent("Transform", new TransComponent(aimTrace));
    aimTrace->AddComponent("Sprite", new SpriteComponent(aimTrace));

    //EventManager에서 요거 지우쇼 
    RePosition* Platform_Player = new RePosition;
    //EventManager::GetInst()->AddEntity("Collision",Platform_Player);

    //Enemy
    Enemy = new GameObject("Enemy");
    GoManager::GetInst()->AddObject(Enemy);

    //Enemy->AddComponent("Transform", new TransComponent(Enemy));
    //Enemy->AddComponent("Sprite", new SpriteComponent(Enemy));
    //Enemy->AddComponent("RigidBody", new RigidBodyComponent(Enemy));
    //Enemy->AddComponent("Ai", new AiComponent(Enemy));
    //AiComponent* Enemy_state = (AiComponent*)Enemy->FindComponent("Ai");
    //Enemy_state->SetTarget(player);//순서중요 trager부터 먼저 세팅 해준다 그리고 먼저 palyer부터 만들어준다.
    //Enemy_state->Setdir(true);//true가 오른쪽, false가 왼쪽
    //Enemy_state->Setdir_time(1.0f);
    //Enemy_state->SetState("IDLE", "Melee");



    auto vecObj = GoManager::GetInst()->Allobj();
    for (int i = 0; i < vecObj.size(); i++)
    {
        if (vecObj[i]->GetName() == "Node")
        {
            vecObj[i]->AddComponent("Sprite", new SpriteComponent(vecObj[i]));
            SpriteComponent* node_spr = static_cast<SpriteComponent*>(vecObj[i]->FindComponent("Sprite"));
            node_spr->m_color.red = 155;
            node_spr->m_color.green = 250;
            node_spr->m_color.blue = 255;
        }
    }

    //TEST==========
    //Enemy_TEST = new GameObject("Enemy_TEST");
    //GoManager::GetInst()->AddObject(Enemy_TEST);
    //
    //Enemy_TEST->AddComponent("Transform", new TransComponent(Enemy_TEST));
    //Enemy_TEST->AddComponent("Sprite", new SpriteComponent(Enemy_TEST));
    //Enemy_TEST->AddComponent("RigidBody", new RigidBodyComponent(Enemy_TEST));
    //Enemy_TEST->AddComponent("PathFindMove", new PathFindMoveComponent(Enemy_TEST));
    //TEST===========


    CameraManager::GetInst()->SetMouse(mouseAim);
    CameraManager::GetInst()->SetPlayer(player);
    CameraManager::GetInst()->SetAim(aimTrace);
    NaveMeshManager::GetInst()->SetPlayer(player);
    NaveMeshManager::GetInst()->CreateLinkTable();
}

void Level::StageBoss_Lvl::Update()
{
	//stage01맵을 불러오자
	if (AEInputCheckTriggered(AEVK_F1))
		GSM::GameStateManager::GetInst()->ChangeLevel(new Stage01_Lvl);
}

void Level::StageBoss_Lvl::Exit()
{
	Serializer::GetInst()->SaveLevel("stageBoss.json");
}

void Level::StageBoss_Lvl::HandleCollision(GameObject* obj1, GameObject* obj2)
{
}
