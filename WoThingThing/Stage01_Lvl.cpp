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

#include "Utility.h"
#include "CameraManager.h"
#include "AEInput.h"
#include "AEUtil.h"
#include "AEMath.h"

Level::Stage01_Lvl::Stage01_Lvl()
{
}

Level::Stage01_Lvl::~Stage01_Lvl()
{
}


void Level::Stage01_Lvl::Init()
{    
    //Object and Component Init
    Serializer::GetInst()->LoadLevel("temp.json");
    player = new GameObject("Player");
    GoManager::GetInst()->AddObject(player); //GetInst() == GetPtr()
    player->AddComponent("Transform", new TransComponent(player));
    player->AddComponent("Sprite", new SpriteComponent(player));
    player->AddComponent("RigidBody", new RigidBodyComponent(player));
    player->AddComponent("PlayerComp", new PlayerComponent(player));

    aimTrace = new GameObject("aimTrace");
    GoManager::GetInst()->AddObject(aimTrace);
    aimTrace->AddComponent("Transform", new TransComponent(aimTrace));
    aimTrace->AddComponent("Sprite", new SpriteComponent(aimTrace));   
    
    //EventManager에서 요거 지우쇼 
    RePosition* Platform_Player = new RePosition;
    EventManager::GetInst()->AddEntity("Collision",Platform_Player);
    
    Serializer::GetInst()->LoadLevel("temp.json");


    CameraManager::GetInst()->SetMouse(mouseAim);
    CameraManager::GetInst()->SetPlayer(player);
    CameraManager::GetInst()->SetAim(aimTrace);
}

void Level::Stage01_Lvl::Update()
{
    //Component 
    TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
    SpriteComponent* player_spr = (SpriteComponent*)player->FindComponent("Sprite");
    RigidBodyComponent* player_rig = (RigidBodyComponent*)player->FindComponent("RigidBody");
    PlayerComponent* player_comp = (PlayerComponent*)player->FindComponent("PlayerComp");

    //Right Click : Right attack

    if (AEInputCheckCurr(AEVK_R) == true)
    {
        //GSM::GameStateManager::GetInst()->ChangeLevel(new Level::Stage01_Lvl);
    }
    else if (AEInputCheckCurr(AEVK_E) == true)
    {
        GSM::GameStateManager::GetInst()->ChangeLevel(nullptr);
    }
    else if (AEInputCheckCurr(AEVK_T) == true)
    {
        GSM::GameStateManager::GetInst()->ChangeLevel(new Level::MainMenu_Lvl);
    }

    for (auto obj : GoManager::GetInst()->Allobj())
    {        
        if (obj->GetName() == "Platform")
        {
            if (ColliderManager::GetInst()->IsCollision(player, obj))
            {
                Collision* colEvent = new Collision(player,obj);
                colEvent->SetEventName("Collision");                
                EventManager::GetInst()->AddEvent(colEvent);                                                
            }
        }
    }    

    CameraManager::GetInst()->Update();
}

void Level::Stage01_Lvl::Exit()
{

    auto res = ResourceManager::GetInst()->GetReource();
    ResourceManager::GetInst()->RemoveAllRes();
    GoManager::GetInst()->RemoveAllObj();
}
