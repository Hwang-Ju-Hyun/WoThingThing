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
	player = new GameObject("Player1");
	GoManager::GetInst()->AddObject(player);
	player->AddComponent("Transform", new TransComponent(player));
	player->AddComponent("Sprite", new SpriteComponent(player));
    player->AddComponent("RigidBody", new RigidBodyComponent(player));

    mouseAim = new GameObject("mouseAim");
    GoManager::GetInst()->AddObject(mouseAim);
    mouseAim->AddComponent("Transform", new TransComponent(mouseAim));
    mouseAim->AddComponent("Sprite", new SpriteComponent(mouseAim));

    aimTrace = new GameObject("aimTrace");
    GoManager::GetInst()->AddObject(aimTrace);
    aimTrace->AddComponent("Transform", new TransComponent(aimTrace));
    aimTrace->AddComponent("Sprite", new SpriteComponent(aimTrace));
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
    TransComponent* aimTrace_trs = (TransComponent*)aimTrace->FindComponent("Transform");
    SpriteComponent* aimTrace_spr = (SpriteComponent*)aimTrace->FindComponent("Sprite");
    //position
    AEVec2 traceDirection = { (mouseX - player_trs->GetPos().x),(mouseY - player_trs->GetPos().y) };
    aimTrace_trs->SetPos((mouseX + player_trs->GetPos().x)/2.f, (mouseY + player_trs->GetPos().y) / 2.f);
    //scale
    float dis = AEVec2Length(&traceDirection);
    aimTrace_trs->SetScale({dis, 1});
    //rotation
    AEVec2 nor_traceDirection = { 0,0 };
    AEVec2Normalize(& nor_traceDirection, &traceDirection);

    //if mouse position in sector 3, 4 : reverse line
    if (nor_traceDirection.y < 0)
        nor_traceDirection.x *= -1;
    //////////////////////////////////////////////////

    aimTrace_trs->SetRot(AEACos(nor_traceDirection.x));
   
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
    //delete All Object ������Ʈ�� ������Ʈ �Ŵ����� game������Ʈ �Ҹ�Ǹ鼭 �ڵ����� ��
    //�̰� �ּ��ϱ�....
    //MemoryLeak Problem solved ��    
    auto res = ResourceManager::GetInst()->GetReource();
    //�ؿ� �ִ°� �̷��� ����� �ȵ� �����ϼ�    
    //res.FindRes("bgm")->second->UnLoad(); <- ������
    ResourceManager::GetInst()->RemoveAllRes();
    GoManager::GetInst()->RemoveAllObj();    
}
