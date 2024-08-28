#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
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
#include "Serializer.h"
#include "AEInput.h"
#include "AEUtil.h"
#include "AELineSegment2.h"
#include "AEMath.h"
#include <iostream>

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

    mouseAim = new GameObject("mouseAim");
    GoManager::GetInst()->AddObject(mouseAim);
    mouseAim->AddComponent("Transform", new TransComponent(mouseAim));
    mouseAim->AddComponent("Sprite", new SpriteComponent(mouseAim));

    aimTrace = new GameObject("aimTrace");
    GoManager::GetInst()->AddObject(aimTrace);
    aimTrace->AddComponent("Transform", new TransComponent(aimTrace));
    aimTrace->AddComponent("Sprite", new SpriteComponent(aimTrace));
        
    //EventManager에서 요거 지우쇼 
    RePosition* Platform_Player = new RePosition;
    EventManager::GetInst()->AddEntity("Collision",Platform_Player);

    Serializer::GetInst()->LoadLevel("temp.json");

}
int cnt = 0;
bool katanaActive, shotActive = false;
void Level::Stage01_Lvl::Update()
{
    //Component 
    TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
    SpriteComponent* player_spr = (SpriteComponent*)player->FindComponent("Sprite");
    RigidBodyComponent* player_rig = (RigidBodyComponent*)player->FindComponent("RigidBody");

    //Player Movement

    //Jump
    if (AEInputCheckTriggered(AEVK_W))
    {
        cnt++;
        if (cnt <= 100)
            player_rig->Jump(400);
    }
    //Landing
    if (player_trs->GetPos().y <= -379.f)
        cnt = 0;

    if (AEInputCheckCurr(AEVK_W)&& AEInputCheckCurr(AEVK_D) && AEInputCheckTriggered(AEVK_SPACE))
        player_rig->Dash({ 1, 1 });
    //Left
    if (AEInputCheckCurr(AEVK_A))
    {
        if (player_trs->GetPos().x > -770)
            player_trs->AddPos(-5.f, 0.f);

        //Dash
        if (AEInputCheckCurr(AEVK_W) && AEInputCheckTriggered(AEVK_SPACE))
            player_rig->Dash({ -1, 1 });
        else if (AEInputCheckTriggered(AEVK_SPACE))
            player_rig->Dash({ -1, 0 });
    }

    //Right
    if (AEInputCheckCurr(AEVK_D))
    {
        if (player_trs->GetPos().x < 770)
            player_trs->AddPos(5.f, 0.f);

        //Dash
        if (AEInputCheckCurr(AEVK_W) && AEInputCheckTriggered(AEVK_SPACE))
            player_rig->Dash({ 1, 1 });
        else if (AEInputCheckTriggered(AEVK_SPACE))
            player_rig->Dash({ 1, 0 });
    }
    //Right Click : Right attack


    //Mouse Position
    TransComponent* aim_trs = (TransComponent*)mouseAim->FindComponent("Transform");
    SpriteComponent* aim_spr = (SpriteComponent*)mouseAim->FindComponent("Sprite");
    s32 mouseX, mouseY;
    AEInputGetCursorPosition(&mouseX, &mouseY);
    mouseX -= 800;              //mouse X position lerp
    mouseY -= 450, mouseY *= -1;//mouse Y position lerp
    aim_trs->SetPos(mouseX, mouseY);

    if (AEInputCheckTriggered(AEVK_1))
    {
        katanaActive = true, shotActive = false;
    }
    if (AEInputCheckTriggered(AEVK_2))
    {
        katanaActive = false, shotActive = true;
    }


    //line: player to aim
    TransComponent* aimTrace_trs = (TransComponent*)aimTrace->FindComponent("Transform");
    SpriteComponent* aimTrace_spr = (SpriteComponent*)aimTrace->FindComponent("Sprite");
    if (katanaActive)
    {
        aimTrace_trs->SetScale({ 0, 0 });
    }

    if(shotActive)
    {

        //position
        AEVec2 traceDirection = { (mouseX - player_trs->GetPos().x),(mouseY - player_trs->GetPos().y) };
        aimTrace_trs->SetPos((mouseX + player_trs->GetPos().x) / 2.f, (mouseY + player_trs->GetPos().y) / 2.f);
        //scale
        float dis = AEVec2Length(&traceDirection);
        aimTrace_trs->SetScale({ dis, 1 });
        //rotation
        AEVec2 nor_traceDirection = { 0,0 };
        AEVec2Normalize(&nor_traceDirection, &traceDirection);

        //if mouse position in sector 3, 4 : reverse line
        if (nor_traceDirection.y < 0)
            nor_traceDirection.x *= -1;
        //////////////////////////////////////////////////
        aimTrace_trs->SetRot(AEACos(nor_traceDirection.x));
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

    for (auto obj : GoManager::GetInst()->Allobj())
    {        
        if (obj->GetName() == "Platform")
        {
            if (ColliderManager::GetInst()->IsCollision(player, obj))
            {
                Collision* colEvent = new Collision(player,obj);
                colEvent->SetEventName("Collision");                
                EventManager::GetInst()->AddEvent(colEvent);                                
                //break;
            }
        }
    }
    
}

void Level::Stage01_Lvl::Exit()
{

    auto res = ResourceManager::GetInst()->GetReource();
    ResourceManager::GetInst()->RemoveAllRes();
    GoManager::GetInst()->RemoveAllObj();
}
