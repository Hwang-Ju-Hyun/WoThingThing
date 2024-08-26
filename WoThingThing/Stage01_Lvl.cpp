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


Level::Stage01_Lvl::Stage01_Lvl()
{
}

Level::Stage01_Lvl::~Stage01_Lvl()
{
}

void Level::Stage01_Lvl::Init()
{
    //Object and Component Init
	player1 = new GameObject("Player1");

	GoManager::GetInst()->AddObject(player1);

	player1->AddComponent("Transform", new TransComponent(player1));
	player1->AddComponent("Sprite", new SpriteComponent(player1));
      
}

void Level::Stage01_Lvl::Update()
{
    //Component 
    TransComponent* player1_trs = (TransComponent*)player1->FindComponent("Transform");
    SpriteComponent* player1_spr = (SpriteComponent*)player1->FindComponent("Sprite");


    //PlayerMovement
    for (auto player : GoManager::GetInst()->Allobj())
    {
        if (player->GetName() == "Player1")
        {
            if (AEInputCheckCurr(AEVK_W)) //jump
            {
                if (player1_trs->GetPos().y < 380)
                    player1_trs->AddPos(0.f, 10.f);
            }
            if (AEInputCheckCurr(AEVK_S)) //Not exist
            {
                if (player1_trs->GetPos().y > -380)
                    player1_trs->AddPos(0.f, -10.f);
            }
            if (AEInputCheckCurr(AEVK_A))
            {
                if (player1_trs->GetPos().x > -770)
                    player1_trs->AddPos(-10.f, 0.f);
            }
            if (AEInputCheckCurr(AEVK_D))
            {
                if (player1_trs->GetPos().x < 770)
                    player1_trs->AddPos(10.f, 0.f);
            }
        }
    }

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
