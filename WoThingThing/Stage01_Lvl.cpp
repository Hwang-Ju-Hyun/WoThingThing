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
    
    player->AddComponent("PlayerComp", new PlayerComponent(player));

    aimTrace = new GameObject("aimTrace");
    GoManager::GetInst()->AddObject(aimTrace);
    aimTrace->AddComponent("Transform", new TransComponent(aimTrace));
    aimTrace->AddComponent("Sprite", new SpriteComponent(aimTrace));   
    
    //EventManager에서 요거 지우쇼 
    RePosition* Platform_Player = new RePosition;
    EventManager::GetInst()->AddEntity("Collision",Platform_Player);
        


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
    std::cout << "FrameCnt: " << AEFrameRateControllerGetFrameCount() << std::endl;
    int cnt = 0;
    for (auto obj : GoManager::GetInst()->Allobj())
    {        
        if (obj->GetName() == "Platform")
        {
            if (ColliderManager::GetInst()->IsCollision(player, obj))
            {
                HandleCollision(player, obj);
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

void Level::Stage01_Lvl::HandleCollision(GameObject* obj1, GameObject* obj2)
{
    // Transform 및 RigidBody 컴포넌트 가져오기
    TransComponent* obj_trs1 = static_cast<TransComponent*>(obj1->FindComponent("Transform"));
    TransComponent* obj_trs2 = static_cast<TransComponent*>(obj2->FindComponent("Transform"));
    RigidBodyComponent* obj_rb1 = static_cast<RigidBodyComponent*>(obj1->FindComponent("RigidBody"));
    PlayerComponent* obj_player = static_cast<PlayerComponent*>(obj1->FindComponent("PlayerComp"));

    AEVec2 obj1_Pos = obj_trs1->GetPos();
    AEVec2 obj2_Pos = obj_trs2->GetPos();

    AEVec2 obj1_Scale = obj_trs1->GetScale();
    AEVec2 obj2_Scale = obj_trs2->GetScale();


    //check 4 distance
    float distanceUpper = std::fabs(obj2_Pos.y + (obj2_Scale.y / 2.f) - (obj1_Pos.y - obj1_Scale.y / 2.f));
    float distanceDown = std::fabs(obj2_Pos.y - (obj2_Scale.y / 2.f) - (obj1_Pos.y + obj1_Scale.y / 2.f));
    float distanceRight = std::fabs(obj2_Pos.x+(obj2_Scale.x/2.f) - (obj1_Pos.x - obj1_Scale.x / 2.f));
    float distanceLeft = std::fabs(obj2_Pos.x -(obj2_Scale.x/2.f) - (obj1_Pos.x + obj1_Scale.x / 2.f));	

    
    float distArr[4] = { distanceUpper,distanceRight,distanceLeft,distanceDown };
    float minDistance = distArr[0];
    int direct = 0;
    for (int i = 1; i < 4; i++)
    {
        if (minDistance > distArr[i])
        {
            minDistance = distArr[i];
            direct = i;
        }
    }
    std::cout << "FrameCnt: " << AEFrameRateControllerGetFrameCount() << std::endl;
    std::cout << "Player : " << obj_trs1->GetPos().x << "\t" << obj_trs1->GetPos().y << std::endl;
    std::cout << "Plat   : " << obj_trs2->GetPos().x << "\t" << obj_trs2->GetPos().y << std::endl;
    std::cout << "Dis    : " << minDistance << "  " << distArr[0] << "  " << distArr[1] << std::endl;
    std::cout << "Direct : " << direct << std::endl;
    std::cout << std::endl;

    switch (direct)
    {
    case 0://Upper
        obj_trs1->AddPos({ 0,minDistance });
        obj_player->SetJumpVelocityZero();
        obj_player->SetJumpCntZero();
        break;
    case 1://Right
        obj_trs1->AddPos({ minDistance , 0 });
        break;
    case 2://Left		
        obj_trs1->AddPos({ -minDistance, 0 });
        break;
    case 3://Down
        obj_trs1->AddPos({ 0,-minDistance });
        obj_player->SetJumpVelocityZero();
        break;
    }
}
