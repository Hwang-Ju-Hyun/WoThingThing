#include "Stage01_Lvl.h"
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
#include "AEUtil.h"
#include "AELineSegment2.h"

Level::Stage01_Lvl::Stage01_Lvl()
{
}

Level::Stage01_Lvl::~Stage01_Lvl()
{
}

void Level::Stage01_Lvl::Init()
{
    //Object and Component Init
	player = new GameObject("Player1");
	GoManager::GetInst()->AddObject(player);
	player->AddComponent("Transform", new TransComponent(player));
	player->AddComponent("Sprite", new SpriteComponent(player));
    player->AddComponent("RigidBody", new RigidBodyComponent(player));

    mouseAim = new GameObject("mouseAim");
    GoManager::GetInst()->AddObject(mouseAim);
    mouseAim->AddComponent("Transform", new TransComponent(mouseAim));
    mouseAim->AddComponent("Sprite", new SpriteComponent(mouseAim));

}

void Level::Stage01_Lvl::Update()
{
    //Component 
    TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
    SpriteComponent* player_spr = (SpriteComponent*)player->FindComponent("Sprite");
    RigidBodyComponent* player_rig = (RigidBodyComponent*)player->FindComponent("RigidBody");

    float dt = AEFrameRateControllerGetFrameTime();
    //PlayerMovement
    for (auto obj : GoManager::GetInst()->Allobj())
    {
        if (obj->GetName() == "Player1")
        {
            if (AEInputCheckTriggered(AEVK_W)) //jump
            {
                player_rig->Jump(300);
            }
            if (AEInputCheckCurr(AEVK_A)) //Left
            {
                if (player_trs->GetPos().x > -770)
                    player_trs->AddPos(-10.f, 0.f);
            }
            if (AEInputCheckCurr(AEVK_D)) //Right
            {
                if (player_trs->GetPos().x < 770)
                    player_trs->AddPos(10.f, 0.f);
            }
            //space bar : dash
            //Right Click : Right attack
            //left shift : time manipulation
        }
    }

    //mouse position : aim
    TransComponent* aim_trs = (TransComponent*)mouseAim->FindComponent("Transform");
    SpriteComponent* aim_spr = (SpriteComponent*)mouseAim->FindComponent("Sprite");
    s32 mouseX, mouseY;
    AEInputGetCursorPosition(&mouseX, &mouseY);
    mouseX -= 800;              //mouse X position lerp
    mouseY -= 450, mouseY *= -1;//mouse Y position lerp
    aim_trs->SetPos(mouseX, mouseY);

    //line: player to aim




    if (AEInputCheckCurr(AEVK_R) == true)
    {
        GSM::GameStateManager::GetInst()->ChangeLevel(new Level::Stage01_Lvl);
    }
    else if (AEInputCheckCurr(AEVK_E) == true)
    {
        GSM::GameStateManager::GetInst()->ChangeLevel(nullptr);
    }
    else if (AEInputCheckCurr(AEVK_T) == true)
    {
        GSM::GameStateManager::GetInst()->ChangeLevel(new Level::MainMenu_Lvl);
    }
}

void Level::Stage01_Lvl::Exit()
{
    //std::cout << "Stage01 : Exit" << std::endl;  
    //delete All Object 컴포넌트와 컴포넌트 매니저는 game오브젝트 소멸되면서 자동으로 됨
    //이게 최선일까....
    //MemoryLeak Problem solved ↓    
    auto res = ResourceManager::GetInst()->GetReource();
    //밑에 있는거 이렇게 지우면 안됨 수정하셈    
    //res.FindRes("bgm")->second->UnLoad(); <- 수정중
    ResourceManager::GetInst()->RemoveAllRes();
    GoManager::GetInst()->RemoveAllObj();    
}
